#include <chrono>
#include <iostream>

using ms = std::chrono::milliseconds;
class Timer {
	using clock_t = std::chrono::steady_clock;
	using timepoint_t = clock_t::time_point;

private:
	timepoint_t m_begin;
	ms m_duration;
	bool m_flag;

public:
	Timer() : m_begin(clock_t::now()), m_duration(0), m_flag(false) {}

	void stop() {
		m_duration += std::chrono::duration_cast<ms> (clock_t::now() - m_begin);
		m_flag = false;
		std::cout << m_duration.count() << " ms" << std::endl;
	}

	void restart() {
		m_begin = clock_t::now();
		m_duration = ms(0);
		m_flag = true;
	}

	~Timer() noexcept {
		if (m_flag) { stop(); }
	}
};