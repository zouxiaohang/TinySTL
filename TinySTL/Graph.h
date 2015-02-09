#ifndef _GRAPH_H_
#define _GRAPH_H_

#include "Allocator.h"
#include "List.h"
#include "Utility.h"
#include "Vector.h"

#include <functional>

namespace TinySTL{
	namespace Detail{
		template<class Index, class Value, class EqualFunc>
		class graph_iterator;
		template<class Index, class Value, class EqualFunc = equal_to<Index>>
		class graph{
		public:
			friend class graph_iterator < Index, Value, EqualFunc >;
		public:
			typedef Index index_type;
			typedef Value value_type;
			typedef EqualFunc equal_func_type;
			typedef pair<Index, Value> node;
			typedef vector<node> node_sets;
			typedef graph_iterator<Index, Value, EqualFunc> bucket_iterator;
			typedef allocator<node> nodeAllocator;
			typedef std::function<void(node&)> visiter_func_type;
		public:
			graph() :size_(0){};
			virtual ~graph(){};
			virtual void add_node(const node& item, const node_sets& nodes) = 0;
			//virtual void delte_node(const node& item) = 0;
			//virtual void DFS(visiter_func_type func) = 0;
			//virtual void BFS(visiter_func_type func) = 0;

			static node& new_node(const Index& index, const Value& val);
			bool is_contained(const Index& index);
			inline static node_sets empty_node_set();
			node_sets adjacent_nodes(const Index& index);
			node_sets adjacent_nodes(const node& n);

			inline bool empty()const;
			inline size_t size()const;
			inline bucket_iterator begin(const Index& index);
			inline bucket_iterator end(const Index& index);
		protected:
			list<pair<node, list<node>>> nodes_;
			equal_func_type equal_func;
			size_t size_;
		};

		template<class Index, class Value, class EqualFunc = equal_to<Index>>
		class graph_iterator{
		public:
			friend class graph < Index, Value, EqualFunc > ;
			typedef graph<Index, Value, EqualFunc>* cntrPtr;
			typedef graph<Index, Value, EqualFunc> graph_type;
			typedef typename list<typename graph_type::node>::iterator inner_it_type;
		public:
			explicit graph_iterator(cntrPtr c = nullptr, inner_it_type iit = inner_it_type())
				:container_(c), inner_it_(iit){}
			graph_iterator& operator ++();
			const graph_iterator operator ++(int);
			typename graph_type::node& operator*(){ return *inner_it_; }
			typename graph_type::node* operator ->(){ return &(operator*()); }
		private:
			cntrPtr container_;
			inner_it_type inner_it_;
		public:
			template<class Index, class Value, class EqualFunc>
			friend bool operator ==(const graph_iterator<Index, Value, EqualFunc>& lhs,
				const graph_iterator<Index, Value, EqualFunc>& rhs);
			template<class Index, class Value, class EqualFunc>
			friend bool operator !=(const graph_iterator<Index, Value, EqualFunc>& lhs,
				const graph_iterator<Index, Value, EqualFunc>& rhs);
		};
	}//end of namespace Detail

	//ÓÐÏòÍ¼
	template<class Index, class Value, class EqualFunc = equal_to<Index>>
	class directed_graph :public Detail::graph < Index, Value, EqualFunc > {
	public:
		directed_graph();
		~directed_graph(){}
		//node n -> every node in the nodes set
		void add_node(const node& n, const node_sets& nodes) override;
	};
}

#include "Detail\Graph.impl.h"
#endif