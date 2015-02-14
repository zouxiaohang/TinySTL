#include "TrieTreeTest.h"

namespace TinySTL{
	namespace TrieTreeTest{
		void testCase1(){
			trie_tree t;
			t.insert("abc");
			t.insert("def");

			assert(t.is_existed("abc"));
			assert(!t.is_existed("a"));
		}
		void testCase2(){
			trie_tree t;
			string arr[] = { "ab", "abbreviation", "abide", "abolish", "abstract"};
			for (const auto& str : arr){
				t.insert(str);
			}
			t.insert("action");

			auto v = t.get_word_by_prefix("ab");
			assert(TinySTL::Test::container_equal(v, arr));
		}
		void testCase3(){
			trie_tree t;
			string arr[] = { "a", "ab", "abc", "d", "a", "abc" };

			assert(t.empty());
			assert(t.size() == 0);

			for (const auto& str : arr){
				t.insert(str);
			}
			assert(!t.empty());
			assert(t.size() == 4);
		}

		void testAllCases(){
			testCase1();
			testCase2();
			testCase3();
		}
	}
}