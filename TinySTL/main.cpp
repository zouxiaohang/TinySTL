#include <iostream>

#include "Algorithm.h"
#include "String.h"
#include "Vector.h"
#include "Profiler\Profiler.h"

#include "AVLTree.h"
#include "BinarySearchTree.h"
#include "CircularBuffer.h"
#include "Deque.h"
#include "List.h"
#include "Queue.h"
#include "Stack.h"

using namespace std;
using namespace TinySTL::Profiler;

int main(){
	TinySTL::string str1("Hello World\n"), str2("This is TinySTL");
	std::cout << (str1 + str2) << std::endl;

	system("pause");
	return 0;
}