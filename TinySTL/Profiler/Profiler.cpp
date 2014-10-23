#include "Profiler.h"

namespace TinySTL{
	namespace Profiler{

		ProfilerInstance::TimePoint ProfilerInstance::startTime;
		ProfilerInstance::TimePoint ProfilerInstance::finishTime;
		ProfilerInstance::DurationTime ProfilerInstance::duringTime;

		void ProfilerInstance::start(){
			startTime = SteadyClock::now(); 
		}

		void ProfilerInstance::finish(){
			finishTime = SteadyClock::now();
			duringTime = std::chrono::duration_cast<DurationTime>(finishTime - startTime);
		}

		void ProfilerInstance::dumpDuringTime(std::ostream& os){
			os << "total " << duringTime.count() * 1000 << " milliseconds" << std::endl;
		}

		double ProfilerInstance::second(){
			return duringTime.count();
		}

		double ProfilerInstance::millisecond(){
			return duringTime.count() * 1000;
		}

		size_t ProfilerInstance::memory(MemoryUnit mu){
			size_t memory = 0;
		#ifdef WIN32
			PROCESS_MEMORY_COUNTERS pmc;
			HANDLE hProcess = GetCurrentProcess();
			if (!GetProcessMemoryInfo(hProcess, &pmc, sizeof(pmc)))
				throw std::runtime_error("GetProcessMemoryInfo failed");
			CloseHandle(hProcess);
		#else
			struct rusage usage;
			if(getrusage(RUSAGE_SELF, &usage) == -1)
				throw std::runtime_error("getrusage failed");
			memory = usage.ru_maxrss / 1024;//如果某些linux平台不完全支持getrusage则ru_maxrss总是返回0
		#endif
			switch (mu){
			case MemoryUnit::KB_:
				memory = pmc.WorkingSetSize KB;
				break;
			case MemoryUnit::MB_:
				memory = pmc.WorkingSetSize MB;
				break;
			case MemoryUnit::GB_:
				memory = pmc.WorkingSetSize GB;
				break;
			}
			return memory;
		}
	}
}