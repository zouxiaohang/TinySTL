#include "GraphTest.h"

#include <sstream>
#include <fstream>

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
			std::ostringstream os;
			os << g.to_string();
			std::string res(R"([14,1414]:[nil]
   |
[13,1313]:[nil]
   |
[12,1212]:[0,0]->[3,33]->[2,22]->[nil]
   |
[7,77]:[14,1414]->[13,1313]->[12,1212]->[nil]
   |
[6,66]:[nil]
   |
[5,55]:[nil]
   |
[3,33]:[nil]
   |
[2,22]:[nil]
   |
[1,11]:[7,77]->[6,66]->[5,55]->[nil]
   |
[0,0]:[3,33]->[2,22]->[1,11]->[nil]
   |
[nil]
)");
			assert(os.str() == res);

			std::ostringstream os1, os2;
			auto func1 = [&os1](const dGraph<int, int>::node_type& node){
				os1 << "[" << node.first << "," << node.second << "]";
			};
			auto func2 = [&os2](const dGraph<int, int>::node_type& node){
				os2 << "[" << node.first << "," << node.second << "]";
			};
			res = R"([1,11][7,77][14,1414][13,1313][12,1212][0,0][3,33][2,22][6,66][5,55])";
			g.DFS(1, func1);
			assert(os1.str() == res);

			res = R"([1,11][7,77][6,66][5,55][14,1414][13,1313][12,1212][0,0][3,33][2,22])";
			g.BFS(1, func2);
			assert(os2.str() == res);

			std::ostringstream os3;
			g.delete_node(dGraph<int, int>::node_type(7, 77));
			os3 << g.to_string();
			res = R"([14,1414]:[nil]
   |
[13,1313]:[nil]
   |
[12,1212]:[0,0]->[3,33]->[2,22]->[nil]
   |
[6,66]:[nil]
   |
[5,55]:[nil]
   |
[3,33]:[nil]
   |
[2,22]:[nil]
   |
[1,11]:[6,66]->[5,55]->[nil]
   |
[0,0]:[3,33]->[2,22]->[1,11]->[nil]
   |
[nil]
)";
			assert(os3.str() == res);
		}
		void testCase3(){
			dGraph<int, int> g;
			dGraph<int, int>::nodes_set_type set1, set2;
			set1.push_back(g.make_node(1, 11));
			set1.push_back(g.make_node(2, 22));
			set1.push_back(g.make_node(3, 33));
			g.add_node(g.make_node(0, 0), set1);

			auto nodes = g.adjacent_nodes(0);
			std::reverse(set1.begin(), set1.end());
			assert(TinySTL::Test::container_equal(nodes, set1));

			for (auto it = g.begin(0); it != g.end(0); ++it){
				set2.push_back(*it);
			}
			assert(TinySTL::Test::container_equal(nodes, set2));
		}
		void testCase4(){
			dGraph<int, int> g;
			dGraph<int, int>::nodes_set_type set;
			for (auto i = 0; i != 10; ++i){
				auto node = g.make_node(i, i);
				g.add_node(node, g.empty_node_set());
				set.push_back(node);
			}
			std::reverse(set.begin(), set.end());
			auto it2 = set.begin();
			for (auto it1 = g.begin(); it1 != g.end() && it2 != set.end(); ++it1, ++it2){
				assert(*it1 == *it2);
			}
		}

		void testAllCases(){
			testCase1();
			testCase2();
			testCase3();
			testCase4();
		}
	}
}