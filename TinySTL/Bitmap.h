#ifndef _BITMAP_H_
#define _BITMAP_H_

#include <cstdint>
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
		const size_t size_;
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

		bitset& set();//TODO
		bitset& set(size_t pos, bool val = true);//TODO
		bitset& reset();//TODO
		bitset& reset(size_t pos);//TODO
		bitset& flip();//TODO
		bitset& flip(size_t pos);//TODO

		std::string to_string() const;//TODO
	private:
		size_t roundUp8(size_t bytes){
			return ((bytes + EAlign::ALIGN - 1) & ~(EAlign::ALIGN - 1));
		}
		void allocateAndFillN(const size_t n, const uint8_t val){
			start_ = dataAllocator::allocate(n);
			finish_ = uninitialized_fill_n(start_, n, val);
		}
	};// end of bitmap

	template<size_t N>
	bitmap<N>::bitmap() :size_(N){
		allocateAndFillN(size_, 0);
	}
}

#endif