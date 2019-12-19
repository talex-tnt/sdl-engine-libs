#pragma once
#include <memory>
#include <cpp-utils/Signal.h>
#include <chrono>

namespace app
{
namespace utils
{

class Clock
{
public:
	using SecT = std::chrono::duration<double>;
	using FrequencyT = float;
	using CycleT = std::uint64_t;

	static void Init(FrequencyT i_cyclesPerSeconds);

	explicit Clock(SecT startTimeSeconds = SecT(0.0f));

	void Update(SecT dtRealSeconds);

	CycleT GetTimeCycles() const;
	Clock::SecT GetElaspsedSeconds() const;
	SecT CalcDeltaSeconds(const Clock& other) const;

	void SetPaused(bool wantPaused);
	bool IsPaused() const;
	void SetTimeScale(float scale);
	float GetTimeScale() const;

private:
	static CycleT SecondsToCycles(SecT timeSeconds);
	static SecT CyclesToSeconds(CycleT timeCycles);

private:
	CycleT m_timeCycles;
	float m_timeScale;
	bool m_isPaused;
	static FrequencyT s_cyclesPerSecond;

	class SignalKey;
public:
	using UpdateSignal = cpp::utils::KeySignal<SignalKey, SecT>;
	UpdateSignal sig_onUpdate;

};
}
}