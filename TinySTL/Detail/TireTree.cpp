#include "../TrieTree.h"

namespace TinySTL{
	trie_tree::trie_tree():data(new trie_node), size_(0){}
	trie_tree::~trie_tree(){
		if (data){
			data->map_childs.clear();
			delete data;
		}
	}
	bool trie_tree::empty()const{
		return size() == 0;
	}
	trie_tree::size_type trie_tree::size()const{
		return size_;
	}
	bool trie_tree::is_existed(const string& word)const{
		if (word.empty())
			return false;
		auto root = get_root();
		auto res = root->map_childs.find(word[0]);
		if (res == root->map_childs.end())//not found
			return false;
		else
			return _is_existed(word, res->second);
	}
	bool trie_tree::_is_existed(const string& word, std::shared_ptr<trie_node> sp)const{
		if (word.size() == 1)
			return sp->is_a_word;
		char ch = word[1];
		auto res = sp->map_childs.find(ch);
		if (res == sp->map_childs.end())//not found
			return false;
		else
			return _is_existed(word.substr(1), res->second);
	}
	bool trie_tree::insert(const string& word){
		if (is_existed(word))
			return true;
		if (word.empty())
			return false;
		char ch = word[0];
		auto root = get_root();
		auto res = root->map_childs.find(ch);
		if (res != root->map_childs.end()){
			return _insert(word.substr(1), res->second);
		}else{
			auto new_sp = std::make_shared<trie_node>();
			new_sp->data = ch;
			new_sp->is_a_word = (word.size() == 1 ? true : false);
			root->map_childs[ch] = new_sp;
			return _insert(word.substr(1), new_sp);
		}
	}
	bool trie_tree::_insert(const string& word, std::shared_ptr<trie_node> sp){
		if (word.empty()){
			++size_;
			sp->is_a_word = true;
			return true;
		}
		char ch = word[0];
		auto res = sp->map_childs.find(ch);
		if (res != sp->map_childs.end()){
			return _insert(word.substr(1), res->second);
		}else{
			auto new_sp = std::make_shared<trie_node>();
			new_sp->data = ch;
			new_sp->is_a_word = (word.size() == 1 ? true : false);
			sp->map_childs[ch] = new_sp;
			return _insert(word.substr(1), new_sp);
		}
	}
	void trie_tree::print_tree(std::ostream& os)const{
		auto root = get_root();
		if (root == NULL)
			os << "the trie_tree is empty!" << std::endl;
		for (auto cit = root->map_childs.cbegin(); cit != root->map_childs.cend(); ++cit)
			_print_tree(os, cit->second, string());
	}
	void trie_tree::_print_tree(std::ostream& os, std::shared_ptr<trie_node> sp, string word)const{
		word += sp->data;
		if (sp->is_a_word)
			os << word << std::endl;
		for (auto cit = sp->map_childs.cbegin(); cit != sp->map_childs.cend(); ++cit){
			_print_tree(os, cit->second, word);
		}
	}
	vector<string> trie_tree::get_word_by_prefix(const string& prefix)const{
		vector<string> words;
		auto root = get_root();
		if (root == NULL || prefix.size() == 0)
			return words;
		char ch = prefix[0];
		auto res = root->map_childs.find(ch);
		if (res != root->map_childs.end())
			_get_word_by_prefix(prefix, res->second, prefix, words);
		return words;
	}
	void trie_tree::_get_word_by_prefix(const string& prefix, std::shared_ptr<trie_node> sp,
		const string& real_prefix, vector<string>& words)const{
		if (prefix.size() == 1){
			if (sp->is_a_word)
				words.push_back(real_prefix);
			for (auto cit = sp->map_childs.cbegin(); cit != sp->map_childs.cend(); ++cit){
				__get_word_by_prefix(cit->second, string(), real_prefix, words);
			}
		}else{
			char ch = prefix[1];
			auto res = sp->map_childs.find(ch);
			if (res != sp->map_childs.end()){
				_get_word_by_prefix(prefix.substr(1), res->second, real_prefix, words);
			}
		}
	}
	void trie_tree::__get_word_by_prefix(std::shared_ptr<trie_node> sp, string& word, const string& prefix, vector<string>& words)const{
		word += sp->data;
		if (sp->is_a_word)
			words.push_back(prefix + word);
		for (auto cit = sp->map_childs.cbegin(); cit != sp->map_childs.cend(); ++cit){
			__get_word_by_prefix(cit->second, string(word), prefix, words);
		}
	}
}