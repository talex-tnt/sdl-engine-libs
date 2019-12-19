#pragma once
#include "Assert.h"

namespace cpp
{
namespace utils
{
//////////////////////////////////////////////////////////////////////////
//								Slot
//////////////////////////////////////////////////////////////////////////
class ISlot
{
public:
	virtual ~ISlot() = default;
	virtual bool IsBlocked() const = 0;
	virtual void SetBlocked(bool i_isBlocked) = 0; 
};

template<typename ... ArgsT>
class SignalBase<ArgsT...>::Slot : public ISlot
{
public:
	Slot(CallbackT i_callback);
	Slot(Slot&&) = default;
	Slot& operator=(Slot&&) = default;
	~Slot() = default;

	Slot(const Slot&) = delete;
	Slot& operator=(const Slot&) = delete;

	void operator()(ArgsT ... i_args);
	bool IsBlocked() const noexcept final override;
	void SetBlocked(bool i_isBlocked) noexcept final override;

private:
	CallbackT m_callback;
	bool m_isBlocked;
};


} // namespace utils


namespace utils
{

// Signal ////////////////////////////////////////////////////////////////

template<typename ... ArgsT>
inline utils::SignalBase<ArgsT...>::SignalBase()
	: m_deleteSlotFun(std::make_shared<DeleteSlotFun>(
		std::bind(&SignalBase::DeleteSlot, this, std::placeholders::_1)))
	, m_threadId(std::this_thread::get_id())
{ }

template<typename ... ArgsT>
inline utils::Connection utils::SignalBase<ArgsT...>::Connect(CallbackT i_callback)
{
	DB_ASSERT_MSG(m_threadId == std::this_thread::get_id(), "Thread Id Mismatch");

	m_slots.emplace_back(std::make_shared<Slot>(i_callback));
	return Connection(m_slots.back(), m_deleteSlotFun, m_threadId);
}

template<typename ... ArgsT>
template<typename _Fx, typename _Type1, typename ... _Types>
inline utils::Connection utils::SignalBase<ArgsT...>::Connect(_Fx&& i_fun, _Type1&& i_arg1, _Types&&... i_args)
{
	DB_ASSERT_MSG(m_threadId == std::this_thread::get_id(), "Thread Id Mismatch");
	
	m_slots.emplace_back(std::make_shared<Slot>(
		std::bind(std::forward<_Fx>(i_fun), std::forward<_Type1>(i_arg1), std::forward<_Types>(i_args)...)
	));
	return Connection(m_slots.back(), m_deleteSlotFun, m_threadId);
}

template<typename ... ArgsT>
template<typename ... Args>
inline void utils::SignalBase<ArgsT...>::Emit(Args&&... i_args)
{
	DB_ASSERT_MSG(m_threadId == std::this_thread::get_id(), "Thread Id Mismatch");
	for ( std::shared_ptr<Slot>& slot : m_slots )
	{
		if ( !slot->IsBlocked() )
		{
			( *slot )( std::forward<Args>(i_args)... );
		}
	}
}

template<typename ... ArgsT>
void utils::SignalBase<ArgsT...>::DeleteSlot(const ISlotPtr& i_slot)
{
	DB_ASSERT_MSG(m_threadId == std::this_thread::get_id(), "Thread Id Mismatch");

	SlotsCollection::const_iterator end = m_slots.cend();
	SlotsCollection::const_iterator it = std::find(m_slots.cbegin(), end, i_slot);
	DB_ASSERT_MSG(it != end, "Slot Not Found!");
	if ( it != end )
	{
		m_slots.erase(it);
	}
}

template<typename ... ArgsT>
bool utils::SignalBase<ArgsT...>::IsSlotConnected(const ISlotPtr& i_slot) const
{
	DB_ASSERT_MSG(m_threadId == std::this_thread::get_id(), "Thread Id Mismatch");
	SlotsCollection::const_iterator end = m_slots.cend();
	SlotsCollection::const_iterator it = std::find(m_slots.cbegin(), end, i_slot);
	return ( it != end );
}

template<typename ... ArgsT>
inline std::size_t utils::SignalBase<ArgsT...>::GetSlotCount() const noexcept
{
	return m_slots.size();
}

// Slot //////////////////////////////////////////////////////////////////////////

template<typename ... ArgsT>
inline utils::SignalBase<ArgsT...>::Slot::Slot(CallbackT i_callback) 
	: m_callback(i_callback), m_isBlocked(false)
{ }

template<typename ... ArgsT>
inline void utils::SignalBase<ArgsT...>::Slot::operator()(ArgsT ... i_args)
{
	DB_ASSERT_MSG(m_callback != nullptr, "Valid Callback expected");
	if ( m_callback != nullptr )
	{
		m_callback(std::forward<ArgsT>(i_args)...);
	}
}

template<typename ... ArgsT>
inline bool utils::SignalBase<ArgsT...>::Slot::IsBlocked() const noexcept
{
	return m_isBlocked;
}

template<typename ... ArgsT>
inline void utils::SignalBase<ArgsT...>::Slot::SetBlocked(bool i_isBlocked) noexcept
{
	m_isBlocked = i_isBlocked;
}

// Connection //////////////////////////////////////////////////////////////////////////

inline utils::Connection::Connection(
	std::weak_ptr<ISlot> i_slot, 
	std::weak_ptr<DeleteSlotFun> i_deleteSlotFun,
	const std::thread::id i_threadId)
	: m_slot(std::move(i_slot)), m_deleteSlotFun(std::move(i_deleteSlotFun)), m_threadId(i_threadId)
{ }

inline utils::Connection::Connection()
	: m_slot(), m_deleteSlotFun(), m_threadId(std::this_thread::get_id())
{ }

inline utils::Connection::Connection(Connection&& rhs)
	: m_slot(std::move(rhs.m_slot))
	, m_deleteSlotFun(std::move(rhs.m_deleteSlotFun))
	, m_threadId(rhs.m_threadId)
{ }

inline typename utils::Connection& utils::Connection::operator=(Connection&& rhs)
{
	if (this != &rhs)
	{
		m_slot = std::move(rhs.m_slot);
		m_deleteSlotFun = std::move(rhs.m_deleteSlotFun);
		m_threadId = rhs.m_threadId;
	}
	return *this;
}

inline utils::Connection::~Connection()
{
	DB_ASSERT_MSG(m_threadId == std::this_thread::get_id(), "Thread Id Mismatch");
	Disconnect();
}

inline bool utils::Connection::IsBlocked() const noexcept
{
	DB_ASSERT_MSG(m_threadId == std::this_thread::get_id(), "Thread Id Mismatch");
	if ( std::shared_ptr<ISlot> slot = m_slot.lock() )
	{
		return slot->IsBlocked();
	}
	return false;
}

inline void utils::Connection::SetBlocked(bool i_isBlocked) noexcept
{
	DB_ASSERT_MSG(m_threadId == std::this_thread::get_id(), "Thread Id Mismatch");
	if ( std::shared_ptr<ISlot> slot = m_slot.lock() )
	{
		slot->SetBlocked(i_isBlocked);
	}
}

inline void utils::Connection::Disconnect()
{
	DB_ASSERT_MSG(m_threadId == std::this_thread::get_id(), "Thread Id Mismatch");
	std::shared_ptr<ISlot> slot = m_slot.lock();
	std::shared_ptr<DeleteSlotFun> slotDeleter = m_deleteSlotFun.lock();
	if ( slot && slotDeleter )
	{
		( *slotDeleter )( slot );
	}
}

inline bool utils::Connection::IsConnected() const
{
	DB_ASSERT_MSG(m_threadId == std::this_thread::get_id(), "Thread Id Mismatch");
	return !m_slot.expired();
}

} //namespace utils
} //namespace cpp