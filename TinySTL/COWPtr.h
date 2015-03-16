#ifndef _COWPTR_H_
#define _COWPTR_H_

#include "Memory.h"

namespace TinySTL{
	template<class T>
	class cow_ptr{
	private:
		shared_ptr<T> ptr_;
	};
}

#endif