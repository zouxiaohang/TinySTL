#include "../Graph.h"

namespace TinySTL{
	namespace Detail{
		template<class Index, class Value, class EqualFunc>
		typename graph<Index, Value, EqualFunc>::node_type
			graph<Index, Value, EqualFunc>::make_node(const Index& index, const Value& val){
			return node_type(index, val);
		}
		template<class Index, class Value, class EqualFunc>
		typename const graph<Index, Value, EqualFunc>::node_type& 
			graph<Index, Value, EqualFunc>::get_node(const Index& index){
			for (auto& pair : nodes_){
				if (equal_func(pair.first.first, index))
					return pair.first;
			}
			static node_type empty_node;
			return empty_node;
		}
		template<class Index, class Value, class EqualFunc>
		bool graph<Index, Value, EqualFunc>::is_contained(const Index& index){
			for (auto& pair : nodes_){
				if (equal_func(pair.first.first, index))
					return true;
			}
			return false;
		}
		template<class Index, class Value, class EqualFunc>
		typename graph<Index, Value, EqualFunc>::nodes_set_type
			graph<Index, Value, EqualFunc>::empty_node_set(){
			return nodes_set_type();
		}
		template<class Index, class Value, class EqualFunc>
		bool graph<Index, Value, EqualFunc>::empty()const{
			return nodes_.empty();
		}
		template<class Index, class Value, class EqualFunc>
		typename graph<Index, Value, EqualFunc>::inner_iterator
			graph<Index, Value, EqualFunc>::begin(const Index& index){
			for (auto& pair : nodes_){
				if (equal_func(pair.first.first, index))
					return inner_iterator(this, (pair.second).begin());
			}
			return end(index);
		}
		template<class Index, class Value, class EqualFunc>
		typename graph<Index, Value, EqualFunc>::inner_iterator
			graph<Index, Value, EqualFunc>::end(const Index& index){
			for (auto& pair : nodes_){
				if (equal_func(pair.first.first, index))
					return inner_iterator(this, (pair.second).end());
			}
			return inner_iterator();
		}
		template<class Index, class Value, class EqualFunc>
		typename graph<Index, Value, EqualFunc>::iterator graph<Index, Value, EqualFunc>::begin(){
			return iterator(this, nodes_.begin());
		}
		template<class Index, class Value, class EqualFunc>
		typename graph<Index, Value, EqualFunc>::iterator graph<Index, Value, EqualFunc>::end(){
			return iterator(this, nodes_.end());
		}
		template<class Index, class Value, class EqualFunc>
		size_t graph<Index, Value, EqualFunc>::size()const{
			return size_;
		}
		template<class Index, class Value, class EqualFunc>
		typename graph<Index, Value, EqualFunc>::nodes_set_type 
			graph<Index, Value, EqualFunc>::adjacent_nodes(const Index& index){
			nodes_set_type s;
			for (auto it = begin(index); it != end(index); ++it){
				s.push_back(*it);
			}
			return s;
		}
		template<class Index, class Value, class EqualFunc>
		typename graph<Index, Value, EqualFunc>::nodes_set_type
			graph<Index, Value, EqualFunc>::adjacent_nodes(const node_type& n){
			return adjacent_nodes(n.first);
		}
		template<class Index, class Value, class EqualFunc>
		void graph<Index, Value, EqualFunc>::_DFS(node_type& node, 
			visiter_func_type func, Unordered_set<Index, std::hash<Index>, EqualFunc>& visited){
			auto nodes = adjacent_nodes(node.first);
			func(node);
			visited.insert(node.first);
			for (auto& n : nodes){
				if (visited.count(n.first) == 0)//has not visited
					_DFS(n, func, visited);
			}
		}
		template<class Index, class Value, class EqualFunc>
		void graph<Index, Value, EqualFunc>::DFS(const Index& index, visiter_func_type func){
			node_type start = (get_node(index));
			Unordered_set<Index, std::hash<Index>, EqualFunc> visited(7);
			_DFS(start, func, visited);
		}
		template<class Index, class Value, class EqualFunc>
		void graph<Index, Value, EqualFunc>::_BFS(node_type& node,
			visiter_func_type func, Unordered_set<Index, std::hash<Index>, EqualFunc>& visited){
			auto nodes = adjacent_nodes(node.first);
			func(node);
			visited.insert(node.first);
			do{
				nodes_set_type temp;
				for (auto it = nodes.begin(); it != nodes.end(); ++it){
					if (visited.count(it->first) == 0){//has not visited
						func(*it);
						visited.insert(it->first);
						auto s = adjacent_nodes(it->first);
						temp.insert(temp.end(), s.begin(), s.end());
					}
				}
				nodes = temp;
			} while (!nodes.empty());
		}
		template<class Index, class Value, class EqualFunc>
		void graph<Index, Value, EqualFunc>::BFS(const Index& index, visiter_func_type func){
			node_type start = (get_node(index));
			Unordered_set<Index, std::hash<Index>, EqualFunc> visited(7);
			_BFS(start, func, visited);
		}
		template<class Index, class Value, class EqualFunc>
		string graph<Index, Value, EqualFunc>::to_string(){
			string str;
			std::ostringstream oss;
			for (auto oit = begin(); oit != end(); ++oit){
				
				oss << "[" << oit->first << "," << oit->second << "]" << ":";
				auto eit = end(oit->first);
				for (auto iit = begin(oit->first); iit != eit; ++iit){
					oss << "[" << iit->first << "," << iit->second << "]" << "->";
				}
				oss << "[nil]" << std::endl << std::setw(4) << "|" << std::endl;
			}
			oss << "[nil]" << std::endl;
			str.append(oss.str().c_str());
			return str;
		}
		template<class Index, class Value, class EqualFunc>
		typename graph<Index, Value, EqualFunc>::equal_func_type
			graph<Index, Value, EqualFunc>::get_equal_func()const{
			return equal_func;
		}
		//********************************************************************************
		template<class Index, class Value, class EqualFunc>
		inner_iterator<Index, Value, EqualFunc>& inner_iterator<Index, Value, EqualFunc>::operator ++(){
			++inner_it_;
			return *this;
		}
		template<class Index, class Value, class EqualFunc>
		const inner_iterator<Index, Value, EqualFunc> inner_iterator<Index, Value, EqualFunc>::operator ++(int){
			auto temp = *this;
			++*this;
			return temp;
		}
		template<class Index, class Value, class EqualFunc>
		bool operator ==(const inner_iterator<Index, Value, EqualFunc>& lhs,
			const inner_iterator<Index, Value, EqualFunc>& rhs){
			return lhs.container_ == rhs.container_ && lhs.inner_it_ == rhs.inner_it_;
		}
		template<class Index, class Value, class EqualFunc>
		bool operator !=(const inner_iterator<Index, Value, EqualFunc>& lhs,
			const inner_iterator<Index, Value, EqualFunc>& rhs){
			return !(lhs == rhs);
		}
		//*********************************************************************************
		template<class Index, class Value, class EqualFunc>
		outter_iterator<Index, Value, EqualFunc>& outter_iterator<Index, Value, EqualFunc>::operator ++(){
			++outter_it_;
			return *this;
		}
		template<class Index, class Value, class EqualFunc>
		const outter_iterator<Index, Value, EqualFunc> outter_iterator<Index, Value, EqualFunc>::operator ++(int){
			auto temp = *this;
			++*this;
			return temp;
		}
		template<class Index, class Value, class EqualFunc>
		bool operator ==(const outter_iterator<Index, Value, EqualFunc>& lhs,
			const outter_iterator<Index, Value, EqualFunc>& rhs){
			return lhs.container_ == rhs.container_ && lhs.outter_it_ == rhs.outter_it_;
		}
		template<class Index, class Value, class EqualFunc>
		bool operator !=(const outter_iterator<Index, Value, EqualFunc>& lhs,
			const outter_iterator<Index, Value, EqualFunc>& rhs){
			return !(lhs == rhs);
		}
	}//end of Detail

	template<class Index, class Value, class EqualFunc>
	directed_graph<Index, Value, EqualFunc>::directed_graph():graph(){}
	template<class Index, class Value, class EqualFunc>
	void directed_graph<Index, Value, EqualFunc>::add_node_helper(const Index& index, const nodes_set_type& nodes){
		if (nodes.empty())
			return;
		//find node n's list
		list<typename graph::node_type>* l;
		for (auto& pair : nodes_){
			if (equal_func(pair.first.first, index))
				l = &(pair.second);
		}
		for (const auto& item : nodes){
			l->push_front(item);
			if (!is_contained(item.first)){
				add_node(item, empty_node_set());
			}
		}
	}
	template<class Index, class Value, class EqualFunc>
	void directed_graph<Index, Value, EqualFunc>::add_node(const node_type& n, const nodes_set_type& nodes){
		if (!is_contained(n.first)){
			nodes_.push_front(make_pair(n, list<typename graph::node_type>()));
			++size_;
		}
		add_node_helper(n.first, nodes);
	}
	template<class Index, class Value, class EqualFunc>
	void directed_graph<Index, Value, EqualFunc>::add_node(const Index& index, const nodes_set_type& nodes){
		add_node_helper(index, nodes);
	}
	template<class Index, class Value, class EqualFunc>
	void directed_graph<Index, Value, EqualFunc>::delete_node(const Index& index){
		for (auto oit = nodes_.begin(); oit != nodes_.end();){
			auto& l = oit->second;
			if (equal_func((oit->first).first, index)){
				oit = nodes_.erase(oit);
			}else{
				for (auto iit = l.begin(); iit != l.end();){
					if (equal_func(iit->first, index))
						iit = l.erase(iit);
					else
						++iit;
				}
				++oit;
			}
		}
	}
	template<class Index, class Value, class EqualFunc>
	void directed_graph<Index, Value, EqualFunc>::delete_node(const node_type& item){
		delete_node(item.first);
	}
	template<class Index, class Value, class EqualFunc>
	void directed_graph<Index, Value, EqualFunc>::make_edge(const Index& index1, const Index& index2){
		auto node1 = get_node(index1), node2 = get_node(index2);
		for (auto it = nodes_.begin(); it != nodes_.end(); ++it){
			if (equal_func((it->first).first, index1))
				(it->second).push_front(node2);
		}
	}
}