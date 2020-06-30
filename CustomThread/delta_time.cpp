#include "delta_time.h"

delta_time::delta_time() {
	start();
}
void delta_time::start() {
	start_time = timer.now();
}
int delta_time::get_delta() {
	auto now = timer.now();
	return std::chrono::duration_cast<ms>(now - start_time).count();
}