#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <utility>

#include "Allocator.h"
#include "Construct.h"
#include "Vector.h"
#include "UninitializedFunctions.h"

using namespace std;

int main(){
	int array[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	//TinySTL::vector<int> svec(array, array + 5);
	//svec.erase(svec.begin() + 1, svec.begin() + 4);//1,5
	TinySTL::vector<int> svec;
	cout << svec.capacity() << endl;
	svec.push_back(1);
	cout << svec.capacity() << endl;
	svec.push_back(2);
	cout << svec.capacity() << endl;
	svec.push_back(3);
	cout << svec.capacity() << endl;
	svec.push_back(4);
	cout << svec.capacity() << endl;
	svec.push_back(5);
	cout << svec.capacity() << endl;
	svec.push_back(6);
	cout << svec.capacity() << endl;
	svec.push_back(7);
	cout << svec.capacity() << endl;
	//svec.insert(svec.begin() + 0, array, array + 10);
	//svec.insert(svec.begin()+0, 10, 99);
	for (auto s : svec){ cout << s << endl; }
	system("pause");
	return 0;
}
