#pragma once
#include <memory>
#include <vector>
#include <thread>

namespace cpp
{
namespace utils
{
class ISlot;
class Connection;

template<typename ... ArgsT>
class SignalBase
{
public:
	SignalBase();
	SignalBase(SignalBase&&)					= default;
	SignalBase& operator=(SignalBase&&)			= default;

	SignalBase(const SignalBase&)				= delete;
	SignalBase& operator=(const SignalBase&)	= delete;

	using Connection = Connection;

protected:
	~SignalBase()							= default;

public:
	using CallbackT = std::function<void(ArgsT...)>;
	Connection Connect(CallbackT i_callback);
	
	template<typename _Fx, typename _Type1, typename ... _Types>
	Connection Connect(_Fx&& i_fun, _Type1&& i_arg1, _Types&&... i_args); // std::bind(i_fun, i_args)

	std::size_t GetSlotCount() const noexcept;

protected:
	template<typename ... Args>
	void Emit(Args&&... i_args);

private:
	using ISlotPtr = std::shared_ptr<ISlot>;

	void DeleteSlot(const ISlotPtr& i_slot);
	bool IsSlotConnected(const ISlotPtr& i_slot) const;

private:
	class Slot;
	using SlotPtr = std::shared_ptr<Slot>;
	using SlotsCollection = std::vector<SlotPtr>;
	SlotsCollection m_slots;

	using DeleteSlotFun = std::function<void(const ISlotPtr&)>;
	std::shared_ptr<DeleteSlotFun> m_deleteSlotFun;

	const std::thread::id m_threadId;
};

template<typename ... ArgsT>
class Signal : public SignalBase<ArgsT...>
{
public:
	using SignalBase::Emit;
};


template<typename Key, typename ... ArgsT>
class KeySignal : public SignalBase<ArgsT...>
{
public:
	class Emitter
	{
	public:
		Emitter(KeySignal& i_sig) :m_sig(i_sig) { }
		template<typename ... Args>
		void Emit(Args&&... i_args) && { m_sig.Emit(std::forward<Args>(i_args)...); }
	private:
		KeySignal& m_sig;
	};
};


//////////////////////////////////////////////////////////////////////////
//							Connection
//////////////////////////////////////////////////////////////////////////
class Connection  //ScopedConnection
{
	//friend class Signal;
private:
	using SlotPtr = std::shared_ptr<ISlot>;
	using DeleteSlotFun = std::function<void(const SlotPtr&)>;

public:
	Connection(
		std::weak_ptr<ISlot> i_slot,
		std::weak_ptr<DeleteSlotFun> i_deleteSlotFun,
		std::thread::id i_threadId);
public:
	Connection();
	Connection(Connection&&);
	Connection& operator=(Connection&&);
	~Connection();

	Connection(const Connection&) = delete;		//only 1 connection at the time
	Connection& operator=(const Connection&) = delete;

	bool IsBlocked() const noexcept;
	void SetBlocked(bool i_isBlocked) noexcept;

	bool IsConnected() const;
	void Disconnect();

private:
	std::weak_ptr<ISlot> m_slot;
	std::weak_ptr<DeleteSlotFun> m_deleteSlotFun;
	std::thread::id m_threadId;
};

} //namespace utils 
} //namespace cpp 

#include "Signal.inl"