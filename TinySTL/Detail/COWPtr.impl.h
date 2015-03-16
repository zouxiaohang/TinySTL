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
	const typename cow_ptr<T>::element_type& cow_ptr<T>::operator *()const{
		return *ptr_;
	}
	template<class T>
	const typename cow_ptr<T>::element_type *cow_ptr<T>::operator ->()const{
		return ptr_.operator->();
	}
	//注意 这两个函数可能会改变指针指向的对象的内容，需要cow机制
	//template<class T>
	//typename cow_ptr<T>::element_type& cow_ptr<T>::operator *();
	//template<class T>
	//typename cow_ptr<T>::element_type *cow_ptr<T>::operator ->();
	template<class T>
	typename cow_ptr<T>::element_type *cow_ptr<T>::get(){
		return ptr_.get();
	}
	template<class T>
	const typename cow_ptr<T>::element_type *cow_ptr<T>::get()const{
		return ptr_.get();
	}
	template<class T>
	cow_ptr<T>::operator bool()const{
		return ptr_ != nullptr;
	}

	template<class T1, class T2>
	bool operator == (const cow_ptr<T1>& cp1, const cow_ptr<T2>& cp2){
		return cp1.ptr_ == cp2.ptr_;
	}
	template<class T>
	bool operator == (const cow_ptr<T>& cp, nullptr_t p){
		return cp.ptr_ == p;
	}
	template<class T>
	bool operator == (nullptr_t p, const cow_ptr<T>& cp){
		return cp == p;
	}
	template<class T1, class T2>
	bool operator != (const cow_ptr<T1>& cp1, const cow_ptr<T2>& cp2){
		return !(cp1 == cp2);
	}
	template<class T>
	bool operator != (const cow_ptr<T>& cp, nullptr_t p){
		return !(cp == p);
	}
	template<class T>
	bool operator != (nullptr_t p, const cow_ptr<T>& cp){
		return !(cp == p);
	}
}

#endif