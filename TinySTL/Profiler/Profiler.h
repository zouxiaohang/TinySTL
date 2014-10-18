#ifndef _PROFILER_H_
#define _PROFILER_H_

#include <chrono>
#include <ctime>
#include <iostream>
#include <memory>
#include <ratio>
#include <utility>

namespace TinySTL{
	namespace Profiler{

		class ProfilerInstance{
		public:
			typedef std::chrono::steady_clock SteadyClock;
			typedef SteadyClock::time_point TimePoint;
			typedef std::chrono::duration<double> DurationTime;
		private:
			static DurationTime duringTime;
			static TimePoint startTime;
			static TimePoint finishTime;
		public:
			static void start();
			static void finish();
			static void dumpDuringTime(std::ostream& os = std::cout);

			static double second();
			static double millisecond();
		};
	}
}

#endif