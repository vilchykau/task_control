#pragma once
#include <chrono>

class delta_time {
public:
	delta_time();
	void start();
	int get_delta();
private:
	using ms = std::chrono::duration<float, std::milli>;
	std::chrono::time_point<std::chrono::steady_clock> start_time;
	std::chrono::high_resolution_clock timer;
};