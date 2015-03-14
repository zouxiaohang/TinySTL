#include "StringTest.h"

#include <fstream>

namespace TinySTL{
	namespace StringTest{

		void testCase1(){
			const char *ptr = "hello world";

			stdStr s1(ptr);
			tsStr s2(ptr);
			assert(TinySTL::Test::container_equal(s1, s2));

			stdStr s3(ptr, 5);
			tsStr s4(ptr, 5);
			assert(TinySTL::Test::container_equal(s3, s4));

			stdStr s5(10, 'z');
			tsStr s6(10, 'z');
			assert(TinySTL::Test::container_equal(s5, s6));

			char arr[] = "zouxiaohang love cpp";
			stdStr s7(std::begin(arr), std::end(arr));
			tsStr s8(std::begin(arr), std::end(arr));
			assert(TinySTL::Test::container_equal(s7, s8));
		}
		void testCase2(){
			stdStr temp1("hello, world");
			tsStr temp2("hello, world");

			stdStr s1(temp1);
			tsStr s2(temp2);
			assert(TinySTL::Test::container_equal(s1, s2));

			stdStr s3(std::move(s1));
			tsStr s4(std::move(s2));
			assert(TinySTL::Test::container_equal(s3, s4));

			stdStr s5(temp1, 1);
			tsStr s6(temp2, 1);
			assert(TinySTL::Test::container_equal(s5, s6));

			stdStr s7(temp1, 0, 5);
			tsStr s8(temp2, 0, 5);
			assert(TinySTL::Test::container_equal(s7, s8));
		}
		void testCase3(){
			stdStr t1("hello, world");
			tsStr t2("hello, world");

			stdStr s1; s1 = 'a';
			tsStr s2; s2 = 'a';
			assert(TinySTL::Test::container_equal(s1, s2));

			stdStr s3; s3 = "hello";
			tsStr s4; s4 = "hello";
			assert(TinySTL::Test::container_equal(s3, s4));

			stdStr s5; s5 = t1;
			tsStr s6; s6 = t2;
			assert(TinySTL::Test::container_equal(s5, s6));

			stdStr s7; s7 = std::move(t1);
			tsStr s8; s8 = std::move(t2);
			assert(TinySTL::Test::container_equal(s7, s8));
		}
		void testCase4(){
			tsStr str("Test string");
			stdStr s(str.begin(), str.end());
			auto i = 0;
			for (tsStr::iterator it = str.begin(); it != str.end(); ++it, ++i){
				assert(*it == s[i]);
			}
			
			i = s.size() - 1;
			for (tsStr::reverse_iterator it = str.rbegin(); it != str.rend(); ++it, --i){
				assert(*it == s[i]);
			}
		}
		void testCase5(){
			tsStr s;
			assert(s.size() == 0);
			assert(s.length() == 0);

			s = "hello, world";
			assert(s.size() == 12);
			assert(s.size() == 12);
		}
		void testCase6(){
			stdStr s1("hello, world");
			tsStr s2("hello, world");

			s1.resize(5);
			s2.resize(5);
			assert(TinySTL::Test::container_equal(s1, s2));

			s1.resize(20, 'z');
			s2.resize(20, 'z');
			assert(TinySTL::Test::container_equal(s1, s2));

			s1.resize(6, 'a');
			s2.resize(6, 'a');
			assert(TinySTL::Test::container_equal(s1, s2));

			s1.resize(100);
			s2.resize(100);
			assert(TinySTL::Test::container_equal(s1, s2));
		}
		void testCase7(){
			tsStr s;
			s.reserve(10);
			assert(s.capacity() == 10);
		}
		void testCase8(){
			tsStr s;
			assert(s.empty());

			s = "hello, world";
			assert(!s.empty());

			s.clear();
			assert(s.empty());
		}
		void testCase9(){
			tsStr s;
			s.resize(10);
			for (auto i = 0; i != s.size(); ++i)
				s[i] = 'a' + i;
			assert(s == "abcdefghij");

			s.back() = 'Z';
			s.front() = 'A';
			assert(s == "AbcdefghiZ");
		}
		void testCase10(){
			stdStr s1;
			tsStr s2;
			for (auto i = 0; i != 10; ++i){
				s1.push_back('a' + i);
				s2.push_back('a' + i);
			}
			assert(TinySTL::Test::container_equal(s1, s2));
		}
		void testCase11(){
			stdStr s1;
			tsStr s2;

			s1.insert(s1.begin(), 'A'); 
			s2.insert(s2.begin(), 'A'); 
			assert(TinySTL::Test::container_equal(s1, s2));

			s1.insert(s1.end(), 2, 'Z');
			s2.insert(s2.end(), 2, 'Z');
			assert(TinySTL::Test::container_equal(s1, s2));

			size_t n = 2;
			s1.insert(2, 10, '@');
			s2.insert(2, 10, '@');
			assert(TinySTL::Test::container_equal(s1, s2));

			s1.insert(0, "hello, world");
			s2.insert(0, "hello, world");
			assert(TinySTL::Test::container_equal(s1, s2));

			s1.insert(s1.size() - 1, "zouxiaohang", 3);
			s2.insert(s2.size() - 1, "zouxiaohang", 3);
			assert(TinySTL::Test::container_equal(s1, s2));

			stdStr s3;
			tsStr s4;

			s3.insert(s3.begin(), s1.begin(), s1.end());
			s4.insert(s4.begin(), s2.begin(), s2.end());
			assert(TinySTL::Test::container_equal(s3, s4));

			s3.insert(1, s1);
			s4.insert(1, s2);
			assert(TinySTL::Test::container_equal(s3, s4));

			stdStr t1("zouxiaoHANG");
			tsStr t2("zouxiaoHANG");
			s3.insert(s3.size(), t1, 7, t1.size() - 7);
			s4.insert(s4.size(), t2, 7, t2.size() - 7);
			assert(TinySTL::Test::container_equal(s3, s4));
		}
		void testCase12(){
			stdStr s1;
			tsStr s2;

			s1.append(stdStr("abc"));
			s2.append(tsStr("abc"));
			assert(TinySTL::Test::container_equal(s1, s2));

			s1.append(stdStr("123456789"), 1, 3);
			s2.append(tsStr("123456789"), 1, 3);
			assert(TinySTL::Test::container_equal(s1, s2));

			s1.append("hello");
			s2.append("hello");
			assert(TinySTL::Test::container_equal(s1, s2));

			s1.append("world", 0, 5);
			s2.append("world", 0, 5);
			assert(TinySTL::Test::container_equal(s1, s2));

			s1.append(10, 'A');
			s2.append(10, 'A');
			assert(TinySTL::Test::container_equal(s1, s2));

			stdStr s3; s3.append(s1.begin(), s1.end());
			tsStr s4; s4.append(s2.begin(), s2.end());
			assert(TinySTL::Test::container_equal(s3, s4));
		}
		void testCase13(){
			stdStr s1;
			tsStr s2;

			s1 += 'A';
			s2 += 'A';
			assert(TinySTL::Test::container_equal(s1, s2));

			s1 += "hello";
			s2 += "hello";
			assert(TinySTL::Test::container_equal(s1, s2));

			s1 += stdStr("world");
			s2 += tsStr("world");
			assert(TinySTL::Test::container_equal(s1, s2));
		}
		void testCase14(){
			stdStr s1("hello world");
			tsStr s2("hello world");

			s1.pop_back();
			s2.pop_back();
			assert(TinySTL::Test::container_equal(s1, s2));
		}
		void testCase15(){
			stdStr s1("hello world");
			tsStr s2("hello world");

			s1.erase(s1.begin() + 1);
			s2.erase(s2.begin() + 1);
			assert(TinySTL::Test::container_equal(s1, s2));

			s1.erase(2, s1.size() - 4);
			s2.erase(2, s2.size() - 4);
			assert(TinySTL::Test::container_equal(s1, s2));

			s1.erase(s1.begin(), s1.end());
			s2.erase(s2.begin(), s2.end());
			assert(TinySTL::Test::container_equal(s1, s2));
		}
		void testCase16(){
			stdStr s1("zouxiaohang"), t1("I Love C++");
			tsStr s2("zouxiaohang"), t2("I Love C++");

			s1.replace(0, 3, t1);
			s2.replace(0, 3, t2);
			assert(TinySTL::Test::container_equal(s1, s2));

			s1.replace(s1.begin(), s1.begin() + s1.size() / 2, t1);
			s2.replace(s2.begin(), s2.begin() + s2.size() / 2, t2);
			assert(TinySTL::Test::container_equal(s1, s2));

			s1.replace(0, s1.size(), t1, 0, t1.size());
			s2.replace(0, s2.size(), t2, 0, t2.size());
			assert(TinySTL::Test::container_equal(s1, s2));

			s1.replace(0, s1.size(), "123456789");
			s2.replace(0, s2.size(), "123456789");
			assert(TinySTL::Test::container_equal(s1, s2));

			s1.replace(s1.begin(), s1.end(), stdStr("hubei"));
			s2.replace(s2.begin(), s2.end(), tsStr("hubei"));
			assert(TinySTL::Test::container_equal(s1, s2));

			s1.replace(0, s1.size(), "wuhan", 5);
			s2.replace(0, s2.size(), "wuhan", 5);
			assert(TinySTL::Test::container_equal(s1, s2));

			s1.replace(s1.begin(), s1.end(), "hongshanqu", 10);
			s2.replace(s2.begin(), s2.end(), "hongshanqu", 10);
			assert(TinySTL::Test::container_equal(s1, s2));

			s1.replace(0, s1.size(), 10, 'Z');
			s2.replace(0, s2.size(), 10, 'Z');
			assert(TinySTL::Test::container_equal(s1, s2));

			s1.replace(s1.begin(), s1.end(), 10, 'A');
			s2.replace(s2.begin(), s2.end(), 10, 'A');
			assert(TinySTL::Test::container_equal(s1, s2));

			s1.replace(s1.begin(), s1.end(), t1.begin(), t1.end());
			s2.replace(s2.begin(), s2.end(), t2.begin(), t2.end());
			assert(TinySTL::Test::container_equal(s1, s2));
		}
		void testCase17(){
			tsStr buyer("money");
			tsStr seller("goods");

			seller.swap(buyer);
			assert(seller == "money");
			assert(buyer == "goods");
		}
		void testCase18(){
			char buffer[20];
			tsStr str("Test string...");
			std::size_t length = str.copy(buffer, 6, 5);
			buffer[length] = '\0';
			std::equal(std::begin(buffer), std::end(buffer), str.begin());
		}
		void testCase19(){
			tsStr str("There are two needles in this haystack with needles.");
			tsStr str2("needle");

			auto found = str.find(str2);
			assert(found == 14);

			found = str.find("needles are small", found + 1, 6);
			assert(found == 44);

			found = str.find(tsStr("wuhan"));
			assert(found == tsStr::npos);

			found = str.find("haystack");
			assert(found == 30);

			found = str.find('.');
			assert(found == 51);

			str.replace(str.find(str2), str2.length(), "preposition");
			assert(TinySTL::Test::container_equal(str, 
				tsStr("There are two prepositions in this haystack with needles.")));
		}
		void testCase20(){
			tsStr str("The sixth sick sheik's sixth sheep's sick.");
			tsStr key("sixth");

			auto found = str.rfind(key);
			assert(found == 23);

			found = str.rfind(key, 24);
			assert(found == 23);

			found = str.rfind('.');
			assert(found == str.size() - 1);

			found = str.rfind("The");
			assert(found == 0);

			found = str.rfind("sick111", 10, 4);
			assert(found == 10);
		}
		void testCase21(){
			tsStr str("Please, replace the vowels in this sentence by asterisks.");
			tsStr key("aeiou");
			const char *arr = "aeiou";

			auto found = str.find_first_of(arr);
			assert(found == 2);

			found = str.find_first_of(arr, found + 1);
			assert(found == 3);

			found = str.find_first_of(arr, found + 1, 1);
			assert(found == 12);

			found = str.find_first_of(key, found + 1);
			assert(found == 14);

			found = str.find_first_of('v', found + 1);
			assert(found == 20);
		}
		void testCase22(){
			tsStr str("1234567890098765432112345678900");

			auto found = str.find_last_of('6');
			assert(found == 25);

			found = str.find_last_of('6', found - 1);
			assert(found == 14);

			found = str.find_last_of("01", 11, 2);
			assert(found == 10);

			found = str.find_last_of(tsStr("#1"), 19);
			assert(found == 19);
		}
		void testCase23(){
			tsStr str("look for non-alphabetic characters...");

			auto found = str.find_first_not_of("abcdefghijklmnopqrstuvwxyz ");
			assert(found == 12);
		}
		void testCase24(){
			tsStr str("12345678900987654321");

			auto found = str.find_last_not_of("023456789", str.size() - 2);
			assert(found == 0);
		}
		void testCase25(){
			tsStr str = "We think in generalities, but we live in details.";

			auto s = str.substr(3, 5);
			assert(TinySTL::Test::container_equal(s, tsStr("think")));
		}
		void testCase26(){
			tsStr str1("green apple");
			tsStr str2("red apple");

			assert(str1.compare(str2) != 0);
			assert(str1.compare(6, 5, "apple") == 0);
			assert(str2.compare(str2.size() - 5, 5, "apple") == 0);
			assert(str1.compare(6, 5, str2, 4, 5) == 0);
		}
		void testCase27(){
			tsStr firstlevel("com");
			tsStr secondlevel("cplusplus");
			tsStr scheme("http://");

			auto hostname = "www." + secondlevel + '.' + firstlevel;
			auto url = scheme + hostname;

			assert(TinySTL::Test::container_equal(url, tsStr("http://www.cplusplus.com")));
		}
		void testCase28(){
			tsStr foo = "alpha";
			tsStr bar = "beta";

			assert(!(foo == bar)); 
			assert(foo != bar); 
			assert(foo < bar); 
			assert(!(foo > bar)); 
			assert(foo <= bar); 
			assert(!(foo >= bar)); 
		}
		void testCase29(){
			tsStr name;
			std::ifstream in(".\\TestData\\string_test.txt");

			if (in){
				in >> name;
				assert(name == "zouxiaohang");
				in.close();
			}
		}

		void testAllCases(){
			testCase1();
			testCase2();
			testCase3();
			testCase4();
			testCase5();
			testCase6();
			testCase7();
			testCase8();
			testCase9();
			testCase10();
			testCase11();
			testCase12();
			testCase13();
			testCase14();
			testCase15();
			testCase16();
			testCase17();
			testCase18();
			testCase19();
			testCase20();
			testCase21();
			testCase22();
			testCase23();
			testCase24();
			testCase25();
			testCase26();
			testCase27();
			testCase28();
			testCase29();
		}
	}
}