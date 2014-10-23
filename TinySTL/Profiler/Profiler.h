#ifndef _PROFILER_H_
#define _PROFILER_H_

#include <chrono>
#include <ctime>
#include <exception>
#include <iostream>
#include <memory>
#include <ratio>
#include <utility>

#ifdef WIN32
#include <Windows.h>
#include <Psapi.h>
#pragma comment(lib, "psapi.lib")
#else
#include <sys/resource>
#include <sys/time.h>
#endif

namespace TinySTL{
	namespace Profiler{

		class ProfilerInstance{
		public:
			typedef std::chrono::steady_clock SteadyClock;
			typedef SteadyClock::time_point TimePoint;
			typedef std::chrono::duration<double, std::ratio<1, 1>> DurationTime;//单位秒
			enum class MemoryUnit{KB_, MB_, GB_};
		private:
			#define KB / 1024
			#define MB KB / 1024
			#define GB MB / 1024
		private:
			static DurationTime duringTime;
			static TimePoint startTime;
			static TimePoint finishTime;
		public:
			static void start();//开始计时
			static void finish();//结束计时
			static void dumpDuringTime(std::ostream& os = std::cout);//打印时间

			static double second();//以秒为单位返回时间
			static double millisecond();//以毫秒为单位返回时间

			static size_t memory(MemoryUnit mu = MemoryUnit::KB_);//查询当前程序的内存使用量
		};
	}
}

#endif