#ifndef _UTILITY_H_
#define _UTILITY_H_

namespace TinySTL{
	//************ [swap] ***************
	template<class T>
	void swap(T& a, T& b){
		T temp = a;
		a = b;
		b = temp;
	}
	//*********** [pair] ****************
	template<class T1, class T2>
	struct pair{
	public:
		typedef T1 first_type;
		typedef T2 second_type;
	public:
		T1 first;
		T2 second;
	public:

	};
}
#endif