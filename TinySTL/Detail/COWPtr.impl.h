#ifndef _COWPTR_IMPL_H_
#define _COWPTR_IMPL_H_

namespace TinySTL{
	template<class T>
	cow_ptr<T>::cow_ptr(T *p = nullptr) :ptr_(p){}
	template<class T>
	template<class D>
	cow_ptr<T>::cow_ptr(T *p, D d) : ptr_(p, d){}
	template<class T>
	cow_ptr<T>::cow_ptr(const cow_ptr& cp){
		ptr_ = cp.ptr_;
	}
	template<class T>
	cow_ptr<T>& cow_ptr<T>::operator = (const cow_ptr& cp){
		if (this != &cp){
			ptr_.decrease_ref();
			ptr_ = cp.ptr_;
		}
		return *this;
	}
	template<class T>
	typename cow_ptr<T>::element_type cow_ptr<T>::operator *()const{
		return *ptr_;
	}
	template<class T>
	typename cow_ptr<T>::element_type *cow_ptr<T>::operator ->()const{
		return ptr_.operator->();
	}
}

#endif