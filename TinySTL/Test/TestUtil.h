#ifndef _TEST_UTIL_H_
#define _TEST_UTIL_H_

#include <iterator>
#include <iostream>
#include <string>

namespace TinySTL{
	namespace Test{

		template<class Container>
		void print_container(Container& container, const std::string& name = ""){//不是每一个容器都有const_iterator
			std::cout << "Container " << name << " :";
			for (auto val : container){
				std::cout << val << " ";
			}
			std::cout << std::endl;
		}

		template<class Container1, class Container2>
		bool container_equal(Container1& con1, Container2& con2){//不是每一个容器都有const_iterator
			auto first1 = std::begin(con1), last1 = std::end(con1);
			auto first2 = std::begin(con2), last2 = std::end(con2);
			for (; first1 != last1 && first2 != last2; ++first1, ++first2){
				if (*first1 != *first2)
					return false;
			}
			return (first1 == last1 && first2 == last2);
		}
	}
}

#endif