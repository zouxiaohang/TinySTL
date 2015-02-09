#include "../Graph.h"

namespace TinySTL{
	namespace Detail{
		template<class Index, class Value, class EqualFunc>
		typename graph<Index, Value, EqualFunc>::node&
			graph<Index, Value, EqualFunc>::new_node(const Index& index, const Value& val)const{
			auto ptr = nodeAllocator::allocate();
			nodeAllocator::construct(ptr, node(index, val));
			return *ptr;
		}
		template<class Index, class Value, class EqualFunc>
		bool graph<Index, Value, EqualFunc>::is_contained(const node& n){
			for (auto& pair : nodes_){
				if (equal_func(pair.first.first, n.first))
					return true;
			}
			return false;
		}
		template<class Index, class Value, class EqualFunc>
		typename graph<Index, Value, EqualFunc>::node_sets
			graph<Index, Value, EqualFunc>::empty_node_set(){
			return node_sets();
		}
	}//end of Detail

	template<class Index, class Value, class EqualFunc>
	directed_graph<Index, Value, EqualFunc>::directed_graph():graph(){}
	template<class Index, class Value, class EqualFunc>
	void directed_graph<Index, Value, EqualFunc>::add_node(const node& n, const node_sets& nodes){
		if (!is_contained(n))
			nodes_.push_front(make_pair(n, list<typename graph::node>()));
		if (nodes.empty())
			return;
		//find node n's list
		list<typename graph::node> l;
		for (auto& pair : nodes_){
			if (equal_func(pair.first.first, n.first))
				l = pair.second;
		}
		for (const auto& item : nodes){
			l.push_front(item);
			if (is_contained(item)){
				add_node(item, empty_node_set());
			}
		}
	}
}