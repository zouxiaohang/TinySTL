#ifndef _REF_H_
#define _REF_H_

#include <atomic>

namespace TinySTL{
	namespace Detail{
		template<class T>
		struct ref_t{
			std::atomic<size_t> ncount_;
			T *data_;
			
			explicit ref_t(size_t n = 0, T *p = nullptr) :ncount_(n), data_(p){}
			ref_t(const ref_t&) = default;
			ref_t& operator = (const ref_t&) = default;

			size_t count()const{ return ncount_.load(); }
			T *get_data()const{ return data_; }

			ref_t& operator ++(){ 
				++ncount_; 
				return *this; 
			}
			ref_t operator ++(int){
				auto t = *this;
				++*this;
				return t;
			}
			ref_t& operator --(){
				--ncount_;
				return *this;
			}
			ref_t operator --(int){
				auto t = *this;
				--*this;
				return t;
			}
		};
	}
}

#endif