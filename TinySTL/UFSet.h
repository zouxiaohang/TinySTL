#ifndef _UF_SET_H_
#define _UF_SET_H_

#include <cstring>

namespace TinySTL{
	template <size_t N>
	class uf_set{
	public:
		uf_set();

		int Find(int index);
		void Union(int index1, int index2);

		void Clear();
	private:
		int parent[N];//parent[i] = -n 表示节点i是根节点且以i为根的树中共有n个节点
	};

	template<size_t N>
	uf_set<N>::uf_set(){
		Clear();
	}
	template<size_t N>
	int uf_set<N>::Find(int index){
		auto root = index;
		for (; parent[root] >= 0; root = parent[root]){}
		while (root != index){//路径压缩
			auto t = parent[index];
			parent[index] = root;
			index = t;
		}
		return root;
	}
	template<size_t N>
	void uf_set<N>::Union(int index1, int index2){
		auto root1 = Find(index1), root2 = Find(index2);
		auto total_nodes = parent[root1] + parent[root2];//total nodes
		if (parent[root1] > parent[root2]){//加权合并
			parent[root1] = root2;
			parent[root2] = total_nodes;
		}else{
			parent[root2] = root1;
			parent[root1] = total_nodes;
		}
	}
	template<size_t N>
	void uf_set<N>::Clear(){
		memset(parent, -1, sizeof(int) * N);
	}
}

#endif