#ifndef _REVERSE_ITERATOR_H_
#define _REVERSE_ITERATOR_H_

#include "Iterator.h"

namespace TinySTL{
	template<class Iterator>
	class reverse_iterator{
	public:
		typedef Iterator iterator_type;
		typedef typename iterator_traits<Iterator>::iterator_category iterator_category;
		typedef typename iterator_traits<Iterator>::value_type value_type;
		typedef typename iterator_traits<Iterator>::difference_type difference_type;
		typedef typename iterator_traits<Iterator>::pointer pointer;
		typedef const pointer const_pointer;
		typedef typename iterator_traits<Iterator>::reference reference;
		typedef const reference const_reference;
	private:
		Iterator base_;
		Iterator cur_;
	public:
		//构造。复制，析构相关
		reverse_iterator() :base_(0), cur_(0){}
		explicit reverse_iterator(iterator_type it) :base_(it), cur_(it - 1){}
		template <class Iter>
		reverse_iterator(const reverse_iterator<Iter>& rev_it){ 
			base_ = (iterator_type)rev_it.base(); 
			cur_ = base_ - 1;
		};

		//其他成员函数
		iterator_type base(){ return base_; }
		reference operator*(){ return (*cur_); }
		const_reference operator*()const{ return(*cur_); }
		pointer operator->(){ return &(operator *()); }
		const_pointer operator->()const{ return &(operator*()); }
		reverse_iterator& operator ++(){
			--base_;
			--cur_;
			return *this;
		}
		reverse_iterator& operator ++(int){
			reverse_iterator temp = *this;
			++(*this);
			return temp;
		}
		reverse_iterator& operator--(){
			++base_;
			++cur_;
			return *this;
		}
		reverse_iterator  operator--(int){
			reverse_iterator temp = *this;
			--(*this);
			return temp;
		}
		reference operator[] (difference_type n){
			return base()[-n - 1];
		}
		reverse_iterator operator + (difference_type n)const;
		reverse_iterator& operator += (difference_type n);
		reverse_iterator operator - (difference_type n)const;
		reverse_iterator& operator -= (difference_type n);
	private:
		Iterator advanceNStep(Iterator it,
			difference_type n,
			bool right,//true -> \ false <-
			random_access_iterator_tag){
			if (right){
				it += n;
			}else{
				it -= n;
			}
			return it;
		}
		Iterator advanceNStep(Iterator it,
			difference_type n,
			bool right,//true -> \ false <-
			bidirectional_iterator_tag){
			difference_type i;
			difference_type absN = n >= 0 ? n : -n;
			if ((right && n > 0) || (!right && n < 0)){// ->
				for (i = 0; i != absN; ++i){
					it = it + 1;
				}
			}
			else if ((!right && n > 0) || (right && n < 0)){// <-
				for (i = 0; i != absN; ++i){
					it = it - 1;
				}
			}
			return it;
		}
	public:
		template <class Iterator>
		friend bool operator == (const reverse_iterator<Iterator>& lhs, 
								const reverse_iterator<Iterator>& rhs);
		template <class Iterator>
		friend bool operator != (const reverse_iterator<Iterator>& lhs, 
								const reverse_iterator<Iterator>& rhs);
		template <class Iterator>
		friend bool operator < (const reverse_iterator<Iterator>& lhs,
								const reverse_iterator<Iterator>& rhs);
		template <class Iterator>
		friend bool operator <= (const reverse_iterator<Iterator>& lhs,
								const reverse_iterator<Iterator>& rhs);
		template <class Iterator>
		friend bool operator > (const reverse_iterator<Iterator>& lhs,
								const reverse_iterator<Iterator>& rhs);
		template <class Iterator>
		friend bool operator >= (const reverse_iterator<Iterator>& lhs,
								const reverse_iterator<Iterator>& rhs);

		template <class Iterator>
		friend reverse_iterator<Iterator> operator + (
			typename reverse_iterator<Iterator>::difference_type n,
			const reverse_iterator<Iterator>& rev_it);
		template <class Iterator>
		friend typename reverse_iterator<Iterator>::difference_type operator- (
			const reverse_iterator<Iterator>& lhs,
			const reverse_iterator<Iterator>& rhs);
	};// end of reverse_iterator

	template<class Iterator>
	reverse_iterator<Iterator>& reverse_iterator<Iterator>::operator += (difference_type n){
		base_ = advanceNStep(base_, n, false, iterator_category());
		cur_ = advanceNStep(cur_, n, false, iterator_category());
		return *this;
	}
	template<class Iterator>
	reverse_iterator<Iterator>& reverse_iterator<Iterator>::operator -= (difference_type n){
		base_ = advanceNStep(base_, n, true, iterator_category());
		cur_ = advanceNStep(cur_, n, true, iterator_category());
		return *this;
	}
	template<class Iterator>
	reverse_iterator<Iterator> reverse_iterator<Iterator>::operator + (difference_type n)const{
		reverse_iterator<Iterator> res = *this;
		res += n;
		return res;
	}
	template<class Iterator>
	reverse_iterator<Iterator> reverse_iterator<Iterator>::operator - (difference_type n)const{
		reverse_iterator<Iterator> res = *this;
		res -= n;
		return res;
	}

	template <class Iterator>
	bool operator == (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs){
		return lhs.cur_ == rhs.cur_;
	}
	template <class Iterator>
	bool operator != (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs){
		return !(lhs == rhs);
	}
	template <class Iterator>
	bool operator < (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs){
		return lhs.cur_ < rhs.cur_;
	}
	template <class Iterator>
	bool operator > (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs){
		return lhs.cur_ > rhs.cur_;
	}
	template <class Iterator>
	bool operator >= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs){
		return !(lhs < rhs);
	}
	template <class Iterator>
	bool operator <= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs){
		return !(lhs > rhs);
	}

	template <class Iterator>
	reverse_iterator<Iterator> operator + (
		typename reverse_iterator<Iterator>::difference_type n,
		const reverse_iterator<Iterator>& rev_it){
		return rev_it + n;
	}
	template <class Iterator>
	typename reverse_iterator<Iterator>::difference_type operator - (
		const reverse_iterator<Iterator>& lhs,
		const reverse_iterator<Iterator>& rhs){
		return lhs.cur_ - rhs.cur_;
	}
}

#endif