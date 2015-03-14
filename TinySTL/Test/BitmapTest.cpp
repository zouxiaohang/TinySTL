#include "BitmapTest.h"

namespace TinySTL{
	namespace BitmapTest{
		void testCase1(){
			bitmap<1> bt1;
			assert(bt1.size() == 8);

			bitmap<7> bt2;
			assert(bt2.size() == 8);

			bitmap<127> bt3;
			assert(bt3.size() == 128);
		}
		void testCase2(){
			bitmap<8> bt1, bt2;
			bt1.set();
			assert(bt1.to_string() == "11111111");
			bt1.reset();
			assert(bt1.to_string() == "00000000");

			bt2.set(0); bt2.set(2); bt2.set(4);
			assert(bt2.to_string() == "10101000");
			bt2.reset(0); bt2.reset(2); bt2.reset(4);
			assert(bt2.to_string() == "00000000");
		}
		void testCase3(){
			bitmap<8> bt;
			bt.flip();
			assert(bt.to_string() == "11111111");

			bt.flip(0);
			assert(bt.to_string() == "01111111");
		}
		void testCase4(){
			bitmap<8> bt;
			bt.set();
			assert(bt.count() == 8);

			bt.flip();
			assert(bt.count() == 0);

			bt.set(0);
			assert(bt.count() == 1);
		}
		void testCase5(){
			bitmap<8> bt;
			assert(!bt.test(0));

			bt.set(0);
			assert(bt.test(0));
		}
		void testCase6(){
			bitmap<8> bt;
			assert(!bt.any());
			assert(bt.none());
			assert(!bt.all());

			bt.set(0);
			assert(bt.any());
			assert(!bt.none());
			assert(!bt.all());

			bt.set();
			assert(bt.any());
			assert(!bt.none());
			assert(bt.all());

			bt.reset();
			assert(!bt.any());
			assert(bt.none());
			assert(!bt.all());
		}
		void testCase7(){
			bitmap<8> bt;
			bt.set(0); bt.set(2); bt.set(4); bt.set(6);
			assert(bt.to_string() == TinySTL::string("10101010"));
		}


		void testAllCases(){
			testCase1();
			testCase2();
			testCase3();
			testCase4();
			testCase5();
			testCase6();
			testCase7();
		}
	}
}