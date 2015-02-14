#ifndef _TRIE_TREE_H_
#define _TRIE_TREE_H_

#include "String.h"
#include "Vector.h"

#include <utility>
#include <memory>
#include <map>
#include <iostream>

namespace TinySTL{
	class trie_tree{
	private:
		struct trie_node{
			char data;
			bool is_a_word;
			std::map<char, std::shared_ptr<trie_node>> map_childs;
			trie_node() :data('\0'), is_a_word(false){}
		};
	public:
		typedef string value_type;
		typedef size_t size_type;
	private:
		trie_node *data;
		size_type size_;
	public:
		trie_tree();
		~trie_tree();
		trie_tree(const trie_tree&) = delete;
		trie_tree& operator = (const trie_tree&) = delete;

		bool empty()const;
		size_type size()const;

		vector<string> get_word_by_prefix(const string& prefix)const;
		void print_tree(std::ostream& os = std::cout)const;
		bool insert(const string& word);
		bool is_existed(const string& word)const;
	private:
		inline trie_node* get_root()const{ return data; }
		void _get_word_by_prefix(const string& prefix, std::shared_ptr<trie_node> sp, const string& real_prefix, vector<string>& words)const;
		void __get_word_by_prefix(std::shared_ptr<trie_node> sp, string& word, const string& prefix, vector<string>& words)const;
		void _print_tree(std::ostream& os, std::shared_ptr<trie_node> sp, string word)const;
		bool _insert(const string& word, std::shared_ptr<trie_node> sp);
		bool _is_existed(const string& word, std::shared_ptr<trie_node> sp)const;
	};// end of trie_tree
}

#endif