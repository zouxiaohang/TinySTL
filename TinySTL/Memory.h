#ifndef _MEMORY_H_
#define _MEMORY_H

#include <utility>

namespace TinySTL{
	template<class T>
	struct default_delete{
		void operator ()(T* ptr){ delete ptr; }
	};
	template<class T>
	struct default_delete < T[] > {
		void operator ()(T* ptr){ delete[] ptr; }
	};

	template<class T, class D = default_delete<T>>
	class unique_ptr{
	public:
		typedef T element_type;
		typedef D deleter_type;
		typedef element_type *pointer;
	public:
		explicit unique_ptr(T *data = nullptr) :data_(data){}
		unique_ptr(T *data, deleter_type del) :data_(data), deleter(del){}

		unique_ptr(unique_ptr&& up){ 
			clean();
			swap(data_, up.data_); 
		}
		unique_ptr& operator = (unique_ptr&& up){
			if (&up != this){
				clean();
				swap(*this, up);
			}
		}

		unique_ptr(const unique_ptr&) = delete;
		unique_ptr& operator = (const unique_ptr&) = delete;

		~unique_ptr(){ clean(); }

		pointer get()const{ return data_; }
		deleter_type& get_deleter(){ return deleter; }
		const deleter_type& get_deleter()const{ return deleter; }

		operator bool()const{ return get() != nullptr; }

		pointer release(){ 
			auto p = nullptr; 
			swap(p, data_);
			return p;
		}
		void reset(pointer p = pointer()){
			clean();
			data_ = p;
		}
		void swap(unique_ptr& up){
			swap(data_, up.data_);
		}

		element_type operator *()const{ return *data_; }
		pointer operator ->()const{ return data_; }
	private:
		inline void clean(){
			deleter(data_);
			data_ = nullptr;
		}
	private:
		element_type *data_;
		deleter_type deleter;
	};
	template <class T, class D>
	void swap(unique_ptr<T, D>& x, unique_ptr<T, D>& y){
		x.swap(y);
	}
	template <class T1, class D1, class T2, class D2>
	bool operator == (const unique_ptr<T1, D1>& lhs, const unique_ptr<T2, D2>& rhs){
		return lhs.get() == rhs.get();
	}
	template <class T1, class D1, class T2, class D2>
	bool operator != (const unique_ptr<T1, D1>& lhs, const unique_ptr<T2, D2>& rhs){
		return !(lhs == rhs);
	}

	template <class T, class... Args>
	unique_ptr<T> make_unique(Args&&... args){
		return unique_ptr<T>(new T(std::forward<Args>(args)...));
	};
}

#endif