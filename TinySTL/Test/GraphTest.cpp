#include "GraphTest.h"

namespace TinySTL{
	namespace GraphTest{
		void testCase1(){
			dGraph<int, int> g;
			assert(g.empty());
			assert(g.size() == 0);

			g.add_node(g.make_node(0, 0), g.empty_node_set());
			assert(!g.empty());
			assert(g.size() == 1);
			assert(g.is_contained(0));

			auto node = g.get_node(0);
			assert(node.first == 0 && node.second == 0);
		}
		void testCase2(){
			dGraph<int, int> g;
			dGraph<int, int>::nodes_set_type set1, set2, set3;
			set1.push_back(g.make_node(1, 11));
			set1.push_back(g.make_node(2, 22));
			set1.push_back(g.make_node(3, 33));
			g.add_node(g.make_node(0, 0), set1);

			set2.push_back(g.make_node(5, 55));
			set2.push_back(g.make_node(6, 66));
			set2.push_back(g.make_node(7, 77));
			g.add_node(g.make_node(1, 11), set2);

			set3.push_back(g.make_node(12, 1212));
			set3.push_back(g.make_node(13, 1313));
			set3.push_back(g.make_node(14, 1414));
			g.add_node(7, set3);

			g.make_edge(12, 2);
			g.make_edge(12, 3);
			g.make_edge(12, 0);
			std::cout << "graph after add nodes:" << std::endl;
			std::cout << g.to_string();

			auto func = [](const dGraph<int, int>::node_type& node){
				std::cout << "[" << node.first << "," << node.second << "]" << std::endl;
			};
			std::cout << "graph DFS from node(1, 11):" << std::endl;
			g.DFS(1, func);
			std::cout << "graph BFS from node(1, 11):" << std::endl;
			g.BFS(1, func);

			std::cout << "graph after delete node(7, 77):" << std::endl;
			g.delete_node(dGraph<int, int>::node_type(7, 77));
			std::cout << g.to_string();
		}

		void testAllCases(){
			testCase1();
			testCase2();
		}
	}
}