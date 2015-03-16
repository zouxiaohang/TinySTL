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

		const element_type& operator *()const;
		const element_type *operator ->()const;
		//注意 这两个函数可能会改变指针指向的对象的内容，需要cow机制
		//element_type& operator *();
		//element_type *operator ->();

		element_type *get();
		const element_type *get()const;

		operator bool() const;
	private:
		shared_ptr<element_type> ptr_;
	public:
		template<class T1, class T2>
		friend bool operator == (const cow_ptr<T1>& cp1, const cow_ptr<T2>& cp2);
		template<class T>
		friend bool operator == (const cow_ptr<T>& cp, nullptr_t p);
		template<class T>
		friend bool operator == (nullptr_t p, const cow_ptr<T>& cp);
		template<class T1, class T2>
		friend bool operator != (const cow_ptr<T1>& cp1, const cow_ptr<T2>& cp2);
		template<class T>
		friend bool operator != (const cow_ptr<T>& cp, nullptr_t p);
		template<class T>
		friend bool operator != (nullptr_t p, const cow_ptr<T>& cp);
	};
}

#include "Detail\COWPtr.impl.h"

#endif