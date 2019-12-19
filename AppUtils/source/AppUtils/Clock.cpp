#include <AppUtils/Clock.h>
#include <assert.h>
namespace app
{
namespace utils
{
Clock::FrequencyT Clock::s_cyclesPerSecond = 0.f;

Clock::CycleT Clock::SecondsToCycles(Clock::SecT timeSeconds)
{
	return static_cast< Clock::CycleT >( timeSeconds.count() * s_cyclesPerSecond );
}

Clock::SecT Clock::CyclesToSeconds(Clock::CycleT timeCycles)
{
	return Clock::SecT(static_cast< float >( timeCycles ) / s_cyclesPerSecond);
}

void Clock::Init(float i_cyclesPerSeconds)
{
	s_cyclesPerSecond = i_cyclesPerSeconds;
}

Clock::Clock(Clock::SecT startTimeSeconds /*= 0.0f*/) :
	m_timeCycles(SecondsToCycles(startTimeSeconds)),
	m_timeScale(1.0f),
	m_isPaused(false)
{ }

Clock::CycleT Clock::GetTimeCycles() const
{
	return m_timeCycles;
}

Clock::SecT Clock::GetElaspsedSeconds() const
{
	return CyclesToSeconds(m_timeCycles);
}

Clock::SecT Clock::CalcDeltaSeconds(const Clock& other) const
{
	Clock::CycleT dt = m_timeCycles - other.m_timeCycles;
	return CyclesToSeconds(dt);
}

void Clock::Update(Clock::SecT dtRealSeconds)
{
	assert(s_cyclesPerSecond > 0.f); // Not initialiased?
	if ( !m_isPaused )
	{
		const Clock::SecT delta = dtRealSeconds * m_timeScale;
		const Clock::CycleT dtScaledCycles = SecondsToCycles(delta);
		m_timeCycles += dtScaledCycles;
		UpdateSignal::Emitter(sig_onUpdate).Emit(delta);
	}
}

void Clock::SetPaused(bool wantPaused)
{
	m_isPaused = wantPaused;
}

bool Clock::IsPaused() const
{
	return m_isPaused;
}

void Clock::SetTimeScale(float scale)
{
	m_timeScale = scale;
}

float Clock::GetTimeScale() const
{
	return m_timeScale;
}

}
}