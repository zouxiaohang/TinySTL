#ifndef _GRAPH_H_
#define _GRAPH_H_

#include "Allocator.h"
#include "List.h"
#include "Utility.h"
#include "Vector.h"

namespace TinySTL{
	namespace Detail{
		template<class Index, class Value, class EqualFunc = equal_to<Index>>
		class graph{
		public:
			typedef Index index_type;
			typedef Value value_type;
			typedef EqualFunc equal_func_type;
			typedef pair<Index, Value> node;
			typedef vector<node> node_sets;
			typedef allocator<node> nodeAllocator;
		public:
			virtual ~graph(){};
			virtual void add_node(const node& item, const node_sets& nodes) = 0;

			node& new_node(const Index& index, const Value& val)const;
			bool is_contained(const node& n);
			inline static node_sets empty_node_set();
		protected:
			list<pair<node, list<node>>> nodes_;
			equal_func_type equal_func;
		};
	}//end of namespace Detail

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