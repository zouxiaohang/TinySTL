#ifndef _BITMAP_IMPL_H_
#define _BITMAP_IMPL_H_

namespace TinySTL{
	template<size_t N>
	void bitmap<N>::allocateAndFillN(size_t n, uint8_t val){
		start_ = dataAllocator::allocate(n);
		finish_ = uninitialized_fill_n(start_, n, val);
	}
	template<size_t N>
	void bitmap<N>::THROW(size_t n)const{
		if (!(0 <= n && n < size()))
			throw std::out_of_range("Out Of Range");
	}
	template<size_t N>
	void bitmap<N>::setNthInInt8(uint8_t& i, size_t nth, bool newVal){//nth从0开始
		uint8_t temp = getMask(i, nth);
		if ((bool)temp == newVal){
			return;
		}
		else{
			if (temp){//nth位为1
				temp = ~temp;
				i = i & temp;
			}
			else{//nth位为0
				i = i | (1 << nth);
			}
		}
	}
	template<size_t N>
	size_t bitmap<N>::roundUp8(size_t bytes){
		return ((bytes + EAlign::ALIGN - 1) & ~(EAlign::ALIGN - 1));
	}
	template<size_t N>
	bitmap<N>& bitmap<N>::set(){
		uninitialized_fill_n(start_, sizeOfUINT8_, ~0);
		return *this;
	}
	template<size_t N>
	bitmap<N>& bitmap<N>::reset(){
		uninitialized_fill_n(start_, sizeOfUINT8_, 0);
		return *this;
	}
	template<size_t N>
	bool bitmap<N>::test(size_t pos) const{
		THROW(pos);
		const auto nth = getNth(pos);
		const auto mth = getMth(pos);
		uint8_t *ptr = start_ + nth;
		uint8_t temp = getMask(*ptr, mth);
		if (temp)
			return true;
		return false;
	}
	template<size_t N>
	bitmap<N>::bitmap() :size_(roundUp8(N)), sizeOfUINT8_(roundUp8(N) / 8){
		allocateAndFillN(sizeOfUINT8_, 0);
	}
	template<size_t N>
	bitmap<N>& bitmap<N>::set(size_t pos, bool val){
		THROW(pos);
		const auto nth = getNth(pos);
		const auto mth = getMth(pos);
		uint8_t *ptr = start_ + nth;//get the nth uint8_t
		setNthInInt8(*ptr, mth, val);
		return *this;
	}
	template<size_t N>
	bitmap<N>& bitmap<N>::reset(size_t pos){
		set(pos, false);
		return *this;
	}
	template<size_t N>
	bitmap<N>& bitmap<N>::flip(){
		uint8_t *ptr = start_;
		for (; ptr != finish_; ++ptr){
			uint8_t n = *ptr;
			*ptr = ~n;
		}
		return *this;
	}
	template<size_t N>
	bitmap<N>& bitmap<N>::flip(size_t pos){
		THROW(pos);
		const auto nth = getNth(pos);
		const auto mth = getMth(pos);
		uint8_t *ptr = start_ + nth;
		uint8_t temp = getMask(*ptr, mth);
		if (temp)
			setNthInInt8(*ptr, mth, false);
		else
			setNthInInt8(*ptr, mth, true);
		return *this;
	}
	template<size_t N>
	size_t bitmap<N>::count() const{
		uint8_t *ptr = start_;
		size_t sum = 0;
		for (; ptr != finish_; ++ptr){
			for (int i = 0; i != 8; ++i){
				uint8_t t = getMask(*ptr, i);
				if (t){
					++sum;
				}
			}
		}
		return sum;
	}
	template<size_t N>
	bool bitmap<N>::any() const{
		uint8_t *ptr = start_;
		for (; ptr != finish_; ++ptr){
			uint8_t n = *ptr;
			if (n != 0)
				return true;
		}
		return false;
	}
	template<size_t N>
	bool bitmap<N>::all() const{
		uint8_t *ptr = start_;
		for (; ptr != finish_; ++ptr){
			uint8_t n = *ptr;
			if (n != (uint8_t)~0)
				return false;
		}
		return true;
	}
	template<size_t N>
	bool bitmap<N>::none() const{
		return !any();
	}
	template<size_t N>
	string bitmap<N>::to_string() const{
		string str;
		uint8_t *ptr = start_;
		for (; ptr != finish_; ++ptr){
			uint8_t n = *ptr;
			for (int i = 0; i != 8; ++i){
				uint8_t t = getMask(n, i);
				if (t) str += "1";
				else str += "0";
			}
		}
		return str;
	}

	template<size_t N>
	std::ostream& operator <<(std::ostream& os, const bitmap<N>& bm){
		os << bm.to_string();
		return os;
	}
}

#endif