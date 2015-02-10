#ifndef _GRAPH_H_
#define _GRAPH_H_

#include "Allocator.h"
#include "List.h"
#include "String.h"
#include "Unordered_set.h"
#include "Utility.h"
#include "Vector.h"

#include <functional>
#include <iomanip>
#include <sstream>

namespace TinySTL{
	namespace Detail{
		template<class Index, class Value, class EqualFunc>
		class inner_iterator;
		template<class Index, class Value, class EqualFunc>
		class outter_iterator;

		template<class Index, class Value, class EqualFunc = equal_to<Index>>
		class graph{//base class
		public:
			friend class inner_iterator < Index, Value, EqualFunc >;
			friend class outter_iterator < Index, Value, EqualFunc > ;
		public:
			typedef Index index_type;
			typedef Value value_type;
			typedef EqualFunc equal_func_type;
			typedef pair<Index, Value> node;
			typedef vector<node> node_sets;
			typedef inner_iterator<Index, Value, EqualFunc> inner_iterator;
			typedef outter_iterator<Index, Value, EqualFunc> iterator;
			typedef allocator<node> nodeAllocator;
			typedef std::function<void(node&)> visiter_func_type;
		public:
			graph() :size_(0){};
			virtual ~graph(){ cleanup(); };

			//node can be not in the graph
			virtual void add_node(const node& item, const node_sets& nodes) = 0;
			//virtual void delte_node(const node& item) = 0;

			//node of the index must in the graph
			virtual void add_node(const Index& index, const node_sets& nodes) = 0;
			//virtual void delte_node(const Index& index) = 0;

			void DFS(const Index& index, visiter_func_type func);
			void BFS(const Index& index, visiter_func_type func);

			node& new_node(const Index& index, const Value& val);
			void del_node(node *p);
			node& get_node(const Index& index);

			bool is_contained(const Index& index);
			inline static node_sets empty_node_set();
			node_sets adjacent_nodes(const Index& index);
			node_sets adjacent_nodes(const node& n);

			inline bool empty()const;
			inline size_t size()const;
			inline inner_iterator begin(const Index& index);
			inline inner_iterator end(const Index& index);
			inline iterator begin();
			inline iterator end();

			string to_string();
		protected:
			list<pair<node, list<node>>> nodes_;
			equal_func_type equal_func;
			size_t size_;
		protected:
			void cleanup();
		};

		template<class Index, class Value, class EqualFunc = equal_to<Index>>
		class inner_iterator{
		public:
			friend class graph < Index, Value, EqualFunc > ;
			typedef graph<Index, Value, EqualFunc>* cntrPtr;
			typedef graph<Index, Value, EqualFunc> graph_type;
			typedef typename list<typename graph_type::node>::iterator inner_it_type;
		public:
			explicit inner_iterator(cntrPtr c = nullptr, inner_it_type iit = inner_it_type())
				:container_(c), inner_it_(iit){}
			inner_iterator& operator ++();
			const inner_iterator operator ++(int);
			typename graph_type::node& operator*(){ return *inner_it_; }
			typename graph_type::node* operator ->(){ return &(operator*()); }
		private:
			cntrPtr container_;
			inner_it_type inner_it_;
		public:
			template<class Index, class Value, class EqualFunc>
			friend bool operator ==(const inner_iterator<Index, Value, EqualFunc>& lhs,
				const inner_iterator<Index, Value, EqualFunc>& rhs);
			template<class Index, class Value, class EqualFunc>
			friend bool operator !=(const inner_iterator<Index, Value, EqualFunc>& lhs,
				const inner_iterator<Index, Value, EqualFunc>& rhs);
		};
		template<class Index, class Value, class EqualFunc = equal_to<Index>>
		class outter_iterator{
		public:
			friend class graph < Index, Value, EqualFunc >;
			typedef graph<Index, Value, EqualFunc>* cntrPtr;
			typedef graph<Index, Value, EqualFunc> graph_type;
			typedef typename list<pair<typename graph_type::node, list<typename graph_type::node>>>::iterator outter_it_type;
		private:
			cntrPtr container_;
			outter_it_type outter_it_;
		public:
			explicit outter_iterator(cntrPtr c = nullptr, outter_it_type oit = outter_it_type())
				:container_(c), outter_it_(oit){}
			outter_iterator& operator ++();
			const outter_iterator operator ++(int);
			typename graph_type::node& operator*(){ return outter_it_->first; }
			typename graph_type::node* operator ->(){ return &(operator*()); }
		public:
			template<class Index, class Value, class EqualFunc>
			friend bool operator ==(const outter_iterator<Index, Value, EqualFunc>& lhs,
				const outter_iterator<Index, Value, EqualFunc>& rhs);
			template<class Index, class Value, class EqualFunc>
			friend bool operator !=(const outter_iterator<Index, Value, EqualFunc>& lhs,
				const outter_iterator<Index, Value, EqualFunc>& rhs);
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
		void add_node(const Index& index, const node_sets& nodes) override;
	private:
		void add_node_helper(const Index& index, const node_sets& nodes);
	};
}

#include "Detail\Graph.impl.h"
#endif