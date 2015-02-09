#include "../Graph.h"

namespace TinySTL{
	namespace Detail{
		template<class Index, class Value, class EqualFunc>
		typename graph<Index, Value, EqualFunc>::node&
			graph<Index, Value, EqualFunc>::new_node(const Index& index, const Value& val){
			auto ptr = nodeAllocator::allocate();
			nodeAllocator::construct(ptr, node(index, val));
			return *ptr;
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
		typename graph<Index, Value, EqualFunc>::node_sets
			graph<Index, Value, EqualFunc>::empty_node_set(){
			return node_sets();
		}
		template<class Index, class Value, class EqualFunc>
		bool graph<Index, Value, EqualFunc>::empty()const{
			return nodes_.empty();
		}
		template<class Index, class Value, class EqualFunc>
		typename graph<Index, Value, EqualFunc>::bucket_iterator
			graph<Index, Value, EqualFunc>::begin(const Index& index){
			for (auto& pair : nodes_){
				if (equal_func(pair.first.first, index))
					return bucket_iterator(this, (pair.second).begin());
			}
			return end(index);
		}
		template<class Index, class Value, class EqualFunc>
		typename graph<Index, Value, EqualFunc>::bucket_iterator
			graph<Index, Value, EqualFunc>::end(const Index& index){
			for (auto& pair : nodes_){
				if (equal_func(pair.first.first, index))
					return bucket_iterator(this, (pair.second).end());
			}
			throw std::exception("return end error");
		}
		template<class Index, class Value, class EqualFunc>
		size_t graph<Index, Value, EqualFunc>::size()const{
			return size_;
		}
		//********************************************************************************
		template<class Index, class Value, class EqualFunc>
		graph_iterator<Index, Value, EqualFunc>& graph_iterator<Index, Value, EqualFunc>::operator ++(){
			++inner_it_;
			//if (inner_it_ == (outter_it_->second).end()){//to end
			//	++outter_it_;
			//	if (outter_it_ != container_->nodes_.end())//not to end
			//		inner_it_ = (outter_it_->second).begin();
			//}
			return *this;
		}
		template<class Index, class Value, class EqualFunc>
		const graph_iterator<Index, Value, EqualFunc> graph_iterator<Index, Value, EqualFunc>::operator ++(int){
			auto temp = *this;
			++*this;
			return temp;
		}
		template<class Index, class Value, class EqualFunc>
		bool operator ==(const graph_iterator<Index, Value, EqualFunc>& lhs,
			const graph_iterator<Index, Value, EqualFunc>& rhs){
			return lhs.container_ == rhs.container_ &&
				//lhs.outter_it_ == rhs.outter_it_ &&
				lhs.inner_it_ == rhs.inner_it_;
		}
		template<class Index, class Value, class EqualFunc>
		bool operator !=(const graph_iterator<Index, Value, EqualFunc>& lhs,
			const graph_iterator<Index, Value, EqualFunc>& rhs){
			return !(lhs == rhs);
		}
	}//end of Detail

	template<class Index, class Value, class EqualFunc>
	directed_graph<Index, Value, EqualFunc>::directed_graph():graph(){}
	template<class Index, class Value, class EqualFunc>
	void directed_graph<Index, Value, EqualFunc>::add_node(const node& n, const node_sets& nodes){
		if (!is_contained(n.first)){
			nodes_.push_front(make_pair(n, list<typename graph::node>()));
			++size_;
		}
		if (nodes.empty())
			return;
		//find node n's list
		list<typename graph::node>* l;
		for (auto& pair : nodes_){
			if (equal_func(pair.first.first, n.first))
				l = &(pair.second);
		}
		for (const auto& item : nodes){
			l->push_front(item);
			if (!is_contained(item.first)){
				add_node(item, empty_node_set());
			}
		}
	}
}