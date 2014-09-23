#include <iostream>
#include <list>
#include <memory>
#include <string>
#include <vector>
#include <iterator>
#include <utility>

#include "Vector.h"
#include "Profiler\Profiler.h"
#include "ReverseIterator.h"

using namespace std;
using namespace TinySTL;

int main(){
	int i = 11; int *ptr = &i;
	int array[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	TinySTL::vector<int> v(array, array + 9);
	
	
	for (auto rit = v.rbegin(); rit != v.rend();rit = rit + 1){ cout << *rit << endl; }
	//TinySTL::reverse_iterator<std::list<int>::iterator> rit(List.begin());

	system("pause");
	return 0;
}
