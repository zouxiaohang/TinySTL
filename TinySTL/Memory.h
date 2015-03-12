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
				swap(data_, up.data_);
			}
		}

		unique_ptr(const unique_ptr&) = delete;
		unique_ptr& operator = (const unique_ptr&) = delete;

		~unique_ptr(){ clean(); }
	private:
		inline void clean(){
			deleter(data_);
			data_ = nullptr;
		}
	private:
		element_type *data_;
		deleter_type deleter;
	};

	template <class T, class... Args>
	unique_ptr<T> make_unique(Args&&... args){
		return unique_ptr<T>(new T(std::forward<Args>(args)...));
	};
}

#endif