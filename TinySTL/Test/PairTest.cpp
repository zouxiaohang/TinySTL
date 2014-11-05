#include <iostream>

#include "..\Utility.h"
#include "..\String.h"

using namespace TinySTL;
int main(){
	// test ctor
	pair <string, double> product1;                     // default constructor
	pair <string, double> product2("tomatoes", 2.30);   // value init
	pair <string, double> product3(product2);          // copy constructor
	product1 = make_pair(string("lightbulbs"), 0.99);   // using make_pair (move)
	product2.first = "shoes";                  // the type of first is string
	product2.second = 39.90;                   // the type of second is double
	std::cout << "The price of " << product1.first << " is $" << product1.second << '\n';
	std::cout << "The price of " << product2.first << " is $" << product2.second << '\n';
	std::cout << "The price of " << product3.first << " is $" << product3.second << '\n';

	//test operator =
	pair <string, int> planet, homeplanet;
	planet = make_pair(string("Earth"), 6371);
	homeplanet = planet;
	std::cout << "Home planet: " << homeplanet.first << '\n';
	std::cout << "Planet size: " << homeplanet.second << '\n';

	//test swap
	pair<int, char> foo1(10, 'a');
	pair<int, char> bar1(90, 'z');
	//foo1.swap(bar1);
	swap(foo1, bar1);
	std::cout << "foo contains: " << foo1.first;
	std::cout << " and " << foo1.second << '\n';

	//test relational operators
	pair<int, char> foo(10, 'z');
	pair<int, char> bar(90, 'a');
	if (foo == bar) std::cout << "foo and bar are equal\n";
	if (foo != bar) std::cout << "foo and bar are not equal\n";
	if (foo< bar) std::cout << "foo is less than bar\n";
	if (foo> bar) std::cout << "foo is greater than bar\n";
	if (foo <= bar) std::cout << "foo is less than or equal to bar\n";
	if (foo >= bar) std::cout << "foo is greater than or equal to bar\n";
	system("pause");
	return 0;
}