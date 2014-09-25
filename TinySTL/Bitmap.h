#ifndef _BITMAP_H_
#define _BITMAP_H_

#include <cstdint>
#include <iostream>
#include <string>

#include "Allocator.h"
#include "UninitializedFunctions.h"

namespace TinySTL{

	template<size_t N>
	class bitmap{
	public:
		typedef allocator<uint8_t> dataAllocator;
	private:
		uint8_t *start_;
		uint8_t *finish_;
		const size_t size_;//the size of bit
		const size_t sizeOfUINT8_;//the size of how many uint8_t
		enum EAlign{ ALIGN = 8 };
	public:
		bitmap();
		explicit bitmap(const std::string& str);//TODO

		//Returns the number of bits in the bitset that are set (i.e., that have a value of one)
		size_t count() const;//TODO
		size_t size() const{ return size_; }
		//Returns whether the bit at position pos is set (i.e., whether it is one).
		bool test(size_t pos) const;//TODO
		//Returns whether any of the bits is set (i.e., whether at least one bit in the bitset is set to one).
		bool any() const;//TODO	
		//Returns whether none of the bits is set (i.e., whether all bits in the bitset have a value of zero).
		bool none() const;//TODO
		//Returns whether all of the bits in the bitset are set (to one).
		bool all() const;//TODO

		bitmap& set(){
			uninitialized_fill_n(start_, size_, ~0);
		}
		bitmap& set(size_t pos, bool val = true);//TODO
		bitmap& reset();//TODO
		bitmap& reset(size_t pos);//TODO
		bitmap& flip();//TODO
		bitmap& flip(size_t pos);//TODO

		std::string to_string() const;//TODO

		template<size_t N>
		friend std::ostream& operator <<(std::ostream& os, const bitmap<N>& bm);
	private:
		size_t roundUp8(size_t bytes){
			return ((bytes + EAlign::ALIGN - 1) & ~(EAlign::ALIGN - 1));
		}
		//将i的第nth为置为newVal
		void setNthInInt8(uint8_t& i, size_t nth, bool newVal){//nth从0开始
			uint8_t temp = i & (1 << nth); //取出i的第nth位
			if ((bool)temp == newVal){
				return;
			}else{
				if (temp){//nth位为1
					temp = ~temp;
					i = i & temp;
				}else{//nth位为0
					i = i | (1 << nth);
				}
			}
		}
		size_t getNth(size_t n){ return (n / 8); }
		void allocateAndFillN(size_t n, uint8_t val){
			start_ = dataAllocator::allocate(n);
			finish_ = uninitialized_fill_n(start_, n, val);
		}
	};// end of bitmap

	template<size_t N>
	bitmap<N>::bitmap() :size_(roundUp8(N)), sizeOfUINT8_(roundUp8(N) / 8 + 1){
		allocateAndFillN(sizeOfUINT8_, 0);
	}
}

#endif