#include "Profiler.h"

namespace TinySTL{
	namespace Profiler{

		ProfilerInstance::TimePoint ProfilerInstance::startTime;
		ProfilerInstance::TimePoint ProfilerInstance::finishTime;

		void ProfilerInstance::start(){
			startTime = SteadyClock::now(); 
		}
		void ProfilerInstance::finish(){
			finishTime = SteadyClock::now();
		}
		void ProfilerInstance::dumpDuringTime(std::ostream& os){
			typedef std::chrono::duration<double> DurationTime;
			DurationTime duringTime =
				std::chrono::duration_cast<DurationTime>(finishTime - startTime);
			os << "total " << duringTime.count() * 1000 << " milliseconds" << std::endl;
		}
	}
}