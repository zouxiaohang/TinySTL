#ifndef _GRAPH_H_
#define _GRAPH_H_

#include "Iterator.h"
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
			typedef pair<Index, Value> node_type;
			typedef vector<node_type> nodes_set_type;
			typedef std::function<void(node_type&)> visiter_func_type;
			typedef outter_iterator<Index, Value, EqualFunc> iterator;
			typedef inner_iterator<Index, Value, EqualFunc> inner_iterator;
		public:
			graph() :size_(0){};
			virtual ~graph(){};

			//node can be not in the graph
			virtual void add_node(const node_type& item, const nodes_set_type& nodes) = 0;
			//node of the index must in the graph
			virtual void add_node(const Index& index, const nodes_set_type& nodes) = 0;
			virtual void make_edge(const Index& index1, const Index& index2) = 0;

			virtual void delete_node(const node_type& item) = 0;
			virtual void delete_node(const Index& index) = 0;

			void DFS(const Index& index, visiter_func_type func);
			void BFS(const Index& index, visiter_func_type func);

			node_type make_node(const Index& index, const Value& val);
			const node_type& get_node(const Index& index);

			bool is_contained(const Index& index);
			inline static nodes_set_type empty_node_set();
			nodes_set_type adjacent_nodes(const Index& index);
			nodes_set_type adjacent_nodes(const node_type& n);

			bool empty()const;
			size_t size()const;
			inner_iterator begin(const Index& index);
			inner_iterator end(const Index& index);
			iterator begin();
			iterator end();

			equal_func_type get_equal_func()const;
			string to_string();
		protected:
			void _DFS(node_type& node, visiter_func_type func, Unordered_set<Index, std::hash<Index>, EqualFunc>& visited);
			void _BFS(node_type& node, visiter_func_type func, Unordered_set<Index, std::hash<Index>, EqualFunc>& visited);
		protected:
			list<pair<node_type, list<node_type>>> nodes_;
			equal_func_type equal_func;
			size_t size_;
		};

		template<class Index, class Value, class EqualFunc = equal_to<Index>>
		class inner_iterator :public iterator<bidirectional_iterator_tag, 
			typename graph<Index, Value, EqualFunc>::node_type>{
		public:
			friend class graph < Index, Value, EqualFunc > ;
			typedef graph<Index, Value, EqualFunc>* cntrPtr;
			typedef graph<Index, Value, EqualFunc> graph_type;
			typedef typename list<typename graph_type::node_type>::iterator inner_it_type;
		public:
			explicit inner_iterator(cntrPtr c = nullptr, inner_it_type iit = inner_it_type())
				:container_(c), inner_it_(iit){}

			inner_iterator& operator ++();
			const inner_iterator operator ++(int);

			typename graph_type::node_type& operator*(){ return *inner_it_; }
			typename graph_type::node_type* operator ->(){ return &(operator*()); }
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
		class outter_iterator :public iterator<bidirectional_iterator_tag,
			typename graph<Index, Value, EqualFunc>::node_type>{
		public:
			friend class graph < Index, Value, EqualFunc >;
			typedef graph<Index, Value, EqualFunc>* cntrPtr;
			typedef graph<Index, Value, EqualFunc> graph_type;
			typedef typename list<pair<typename graph_type::node_type, list<typename graph_type::node_type>>>::iterator outter_it_type;
		private:
			cntrPtr container_;
			outter_it_type outter_it_;
		public:
			explicit outter_iterator(cntrPtr c = nullptr, outter_it_type oit = outter_it_type())
				:container_(c), outter_it_(oit){}

			outter_iterator& operator ++();
			const outter_iterator operator ++(int);

			typename graph_type::node_type& operator*(){ return outter_it_->first; }
			typename graph_type::node_type* operator ->(){ return &(operator*()); }
		public:
			template<class Index, class Value, class EqualFunc>
			friend bool operator ==(const outter_iterator<Index, Value, EqualFunc>& lhs,
				const outter_iterator<Index, Value, EqualFunc>& rhs);
			template<class Index, class Value, class EqualFunc>
			friend bool operator !=(const outter_iterator<Index, Value, EqualFunc>& lhs,
				const outter_iterator<Index, Value, EqualFunc>& rhs);
		};
	}//end of namespace Detail

	//directed graph
	template<class Index, class Value, class EqualFunc = equal_to<Index>>
	class directed_graph :public Detail::graph < Index, Value, EqualFunc > {
	public:
		directed_graph();
		~directed_graph(){}
		//node n -> every node_type in the nodes set
		void add_node(const node_type& n, const nodes_set_type& nodes) override final;
		void add_node(const Index& index, const nodes_set_type& nodes) override final;
		//node index1 -> node index2
		void make_edge(const Index& index1, const Index& index2) override final;

		void delete_node(const node_type& item) override final;
		void delete_node(const Index& index) override final;
	private:
		void add_node_helper(const Index& index, const nodes_set_type& nodes);
	};
}

#include "Detail\Graph.impl.h"
#endif