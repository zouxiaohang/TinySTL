#ifndef _COWPTR_H_
#define _COWPTR_H_

#include "Memory.h"

namespace TinySTL{
	template<class T>
	class cow_ptr{
	public:
		typedef T element_type;
	public:
		explicit cow_ptr(T *p = nullptr);
		template<class D>
		cow_ptr(T *p, D d);

		cow_ptr(const cow_ptr& cp);
		cow_ptr& operator = (const cow_ptr& cp);

		element_type operator *()const;
		element_type *operator ->()const;
	private:
		shared_ptr<element_type> ptr_;
	
	};
}

#include "Detail\COWPtr.impl.h"

#endif