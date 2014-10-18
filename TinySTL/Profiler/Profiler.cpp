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
	}
}