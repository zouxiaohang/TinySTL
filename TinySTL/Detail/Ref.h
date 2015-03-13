#ifndef _REF_H_
#define _REF_H_

#include <atomic>

namespace TinySTL{
	namespace Detail{
		template<class T>
		struct ref_t{
			std::atomic<size_t> ncount_;
			T *data_;
			
			explicit ref_t(T *p = nullptr): ncount_(0), data_(p){
				if (data_)
					ncount_ = 1;
			}
			ref_t(const ref_t&) = delete;
			ref_t& operator = (const ref_t&) = delete;

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
		template<class T>
		bool operator ==(const ref_t<T>& lhs, const ref_t<T>& rhs){
			return lhs.get_data() == rhs.get_data();
		}
		template<class T>
		bool operator !=(const ref_t<T>& lhs, const ref_t<T>& rhs){
			return !(lhs == rhs);
		}
	}
}

#endif