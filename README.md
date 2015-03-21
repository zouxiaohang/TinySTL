TinySTL
=======
采用C++11实现一款简易的STL标准库，既是C++STL的一个子集（裁剪了一些容器和算法）又是一个超集（增加了一些容器和算法）

目的：练习数据结构与算法和C++ Template编程

编译环境：VS2013及以上版本

##开发计划：
  * STL的几大基本组件，如string、vector、list、deque、set、map、unordered_\*等
  * STL算法库中的大部分算法
  * circular buffer
  * bitmap
  * skip list
  * binary search tree
  * AVL tree
  * rbtree
  * segment tree
  * splay tree
  * rope
  * Van Emde Boas tree
  * treap
  * B-tree
  * trie
  * suffix array/tree
  * Disjoint-set data structure
  * k-d tree
  * R-tree
  * Matrix
  * Graph
  * bloom filter

##完成进度：
* STL的几大基本组件
    * type traits：100%  
    * 空间配置器：100%
    * iterator traits：100%
    * reverse_iterator：100%
    * vector：100%
    * string：100%
    * priority_queue：100%
    * stack：100%
    * deque：100%
    * queue：100%
    * pair：100%
    * list：100%
	* unordered_set：100%
	* unique_ptr：100%
	* shared_ptr：100%
	* cow_ptr：100%
* STL Algorithms:  
    * fill：100% 
    * fill_n：100% 
    * find：100%
    * is_heap：100%
    * min、max：100%
    * make_heap：100%
    * pop_heap：100%
    * push_heap：100%
    * sort_heap：100%
    * swap：100%
    * all_of：100%
    * any_of：100%
    * none_of：100%
    * find_if：100%
    * find_if_not：100%
    * adjacent_find：100%
    * count：100%
    * count_if：100%
    * mismatch：100%
    * equal：100%
	* is_permutation：100%
	* search：100%
	* advance：100%
	* sort：100%
	* generate：100%
	* generate_n：100%
	* distance：100%
	* copy：100%
* 其他组件：
    * circular_buffer：100%   
    * bitmap：100%
    * binary_search_tree：100%
    * avl_tree：100%
	* suffix_array：100%
	* directed_graph：100%
	* trie tree：100%
	* Disjoint-set data structure：100%

##TinySTL单元测试(原单元测试代码逐步)：
  * pair：100%
  * algorithm：20%
  * vector：100%
  * string：100%
  * priority_queue：100%
  * suffix_array：100%
  * queue：100%
  * stack：100%
  * bitmap：100%
  * circular_buffer：100%
  * deque：100%
  * list：100%
  * binary_search_tree：100%
  * avl_tree：100%
  * unordered_set：100%
  * directed_graph：100%
  * trie tree：100%
  * unique_ptr：100%
  * shared_ptr：100%
  * Disjoint-set data structure：100%

#TinySTL性能测试:
###测试环境：Windows 7 && VS2013 && release模式
###测试结果：
####(1):vector&lt;int>

    //std::vector<int> vec;
    TinySTL::vector<int> vec;
	ProfilerInstance::start();
	int i = 0;
	for (; i != 10000; ++i){
		vec.push_back(i);
	}
	ProfilerInstance::finish();
	ProfilerInstance::dumpDuringTime();
    
|container|quantity|time(ms)|  
|---------|--------|--------|  
|TinySTL::vector&lt;int>|10万|2|  
|TinySTL::vector&lt;int>|100万|11|  
|TinySTL::vector&lt;int>|1000万|129|  
|std::vector&lt;int>|10万|6|  
|std::vector&lt;int>|100万|16|  
|std::vector&lt;int>|1000万|210|    
####(2):vector&lt;string>

    //std::vector<std::string> vec;
    TinySTL::vector<std::string> vec;
	ProfilerInstance::start();
	int i = 0;
	for (; i != 100000; ++i){
		vec.push_back(std::string("zouxiaohang"));
	}
	ProfilerInstance::finish();
	ProfilerInstance::dumpDuringTime();
    
|container|quantity|time(ms)|  
|---------|--------|--------|  
|TinySTL::vector&lt;string>|10万|18|  
|TinySTL::vector&lt;string>|100万|181|  
|TinySTL::vector&lt;string>|1000万|2372|  
|std::vector&lt;string>|10万|29|  
|std::vector&lt;string>|100万|232|  
|std::vector&lt;string>|1000万|1972|
####(3):circular_buffer&lt;int, N>

    TinySTL::circular_buffer<int, 10000> cb(10000, 0);
    //boost::circular_buffer<int> cb(10000, 0);
	ProfilerInstance::start();
	for (int i = 0; i != 10000000; ++i){
		cb.push_back(i);
	}
	ProfilerInstance::finish();
	ProfilerInstance::dumpDuringTime();
    
|container|quantity|time(ms)|  
|---------|--------|--------|  
|TinySTL::circular_buffer|1000万|75|  
|TinySTL::circular_buffer|10000万|604|  
|TinySTL::circular_buffer|100000万|5936|  
|boost::circular_buffer|1000万|22|  
|boost::circular_buffer|10000万|252|  
|boost::circular_buffer|100000万|2241|  
####(4):题目：利用bitmap找出str中未出现的字母  

    std::string str("abcdefghijklmnpqrstuvwxyz");
    TinySTL::bitmap<26> bm;
	for (auto it = str.cbegin(); it != str.cend(); ++it){
		bm.set(*it - 'a');
	}
	cout << bm << endl;
	cout << bm.size() << endl;
	for (int i = 0; i != 26; ++i){
		if (!bm.test(i))
			cout << "字母" << (char)('a' + i) << "没出现！！！" << endl;
	}
输出结果：  

    111111111111110111111111111000000
    32  
    字母o没出现！！！
    
####(5):string

    //std::string str;
    TinySTL::string str;
	ProfilerInstance::start();
	int i = 0;
	for (; i != 1000000; ++i){
		str.push_back('x');
	}
	ProfilerInstance::finish();
	ProfilerInstance::dumpDuringTime();
    
|container|quantity|time(ms)|  
|---------|--------|--------|  
|TinySTL::string|100万|7|  
|TinySTL::string|1000万|39|  
|TinySTL::string|10000万|484|  
|std::string|100万|37|  
|std::string|1000万|229|  
|std::string|10000万|1965|  

####(6):priority_queue&lt;int>

    //std::priority_queue<int> pq;
    TinySTL::priority_queue<int> pq;
	ProfilerInstance::start();
	int i = 0;
	for (; i != 100000; ++i){
		pq.push(i);
	}
	ProfilerInstance::finish();
	ProfilerInstance::dumpDuringTime();
    
|container|quantity|time(ms)|  
|---------|--------|--------|  
|TinySTL::priority_queue&lt;int>|10万|13|  
|TinySTL::priority_queue&lt;int>|100万|97|  
|TinySTL::priority_queue&lt;int>|1000万|1032|  
|std::priority_queue&lt;int>|10万|12|  
|std::priority_queue&lt;int>|100万|67|  
|std::priority_queue&lt;int>|1000万|752|  

    TinySTL::vector<int> v;
    int i = 0;
	for (; i != 100000; ++i){
		v.push_back(i);
	}
	//std::priority_queue<int> pq(v.begin(), v.end());
	TinySTL::priority_queue<int> pq(v.begin(), v.end());
	ProfilerInstance::start();
	for (i = 0; i != 100000; ++i){
		pq.pop();
	}
	ProfilerInstance::finish();
	ProfilerInstance::dumpDuringTime();
    
|container|quantity|time(ms)|  
|---------|--------|--------|  
|TinySTL::priority_queue&lt;int>|10万|19|  
|TinySTL::priority_queue&lt;int>|100万|137|  
|TinySTL::priority_queue&lt;int>|1000万|1532|  
|std::priority_queue&lt;int>|10万|7|  
|std::priority_queue&lt;int>|100万|92|  
|std::priority_queue&lt;int>|1000万|1214|  

####(7):binary_search_tree&lt;string>

    ifstream f;
	//char buff[256] = { 0 };
	std::string word;
	f.open("C:\\Users\\zxh\\Desktop\\text.txt");
	TinySTL::vector<TinySTL::string> v;
	while (f.good()){
		f >> word;
		//std::copy(word.begin(), word.end(), buff);
		//v.push_back(TinySTL::string(buff, buff + word.size()));
		v.push_back(word);
	}
	TinySTL::binary_search_tree<TinySTL::string> sbst;
	ProfilerInstance::start();
	for (const auto& word : v){
		sbst.insert(word);
	}
	ProfilerInstance::finish();
	ProfilerInstance::dumpDuringTime();
	f.close();
    
|container|quantity|time(ms)|  
|---------|--------|--------|  
|TinySTL::binary_search_tree&lt;string>|44067|16|  
|TinySTL::binary_search_tree&lt;string>|169664|64|  
|TinySTL::binary_search_tree&lt;string>|438230|277|   

####(8):deque&lt;int>

    //std::deque<int> dq;
    TinySTL::deque<int> dq;
	ProfilerInstance::start();
	const int max = 10000000;
	int i = 0;
	for (; i != max / 2; ++i){
		dq.push_front(i);
	}
	for (; i != max; ++i){
		dq.push_back(i);
	}
	ProfilerInstance::finish();
	ProfilerInstance::dumpDuringTime();
    
|container|quantity|time(ms)|  
|---------|--------|--------|  
|TinySTL::deque&lt;int>|10万|15|  
|TinySTL::deque&lt;int>|100万|78|  
|TinySTL::deque&lt;int>|1000万|1186|  
|std::deque&lt;int>|10万|90|  
|std::deque&lt;int>|100万|1087|  
|std::deque&lt;int>|1000万|4835|  
#####ps：这个性能差距的原因1是内部实现的机制不同，我的deque是预先分配内存因此相同条件下占用的内存更多，而stl的deque是需要的时候再分配，更加节省内存；2是stl的deque实现了更多更灵活的插入删除操作，我只是实现了在头尾的插入和删除

####(9):avl_tree&lt;int> 
    TinySTL::binary_search_tree<int> bst;
    TinySTL::avl_tree<int> avlt;
	for (int i = 0; i != 10000; ++i){
		avlt.insert(i);
		bst.insert(i);
	}
	cout << "binary_search_tree height = " << bst.height() << endl;
	cout << "avl_tree height = " << avlt.height() << endl;
输出结果：  

    binary_search_tree height = 10000
    avl_tree height = 14


####(10):list&lt;int>

    TinySTL::list<int> list;
    //std::list<int> list;
	const size_t max = 100000;
	ProfilerInstance::start();
	for (size_t i = 0; i != max; ++i)
		list.push_back(i);
	ProfilerInstance::finish();
	ProfilerInstance::dumpDuringTime();
    
|container|quantity|time(ms)|  
|---------|--------|--------|  
|TinySTL::list&lt;int>|10万|4|  
|TinySTL::list&lt;int>|100万|33|  
|TinySTL::list&lt;int>|1000万|286|  
|std::list&lt;int>|10万|189|  
|std::list&lt;int>|100万|1774|  
|std::list&lt;int>|1000万|17571|  


####(11):list&lt;int>::sort()

    TinySTL::list<int> list1;
    std::list<int> list2;
	std::default_random_engine dre;
	std::uniform_int_distribution<int> id;
	const size_t max = 10000;
	for (int i = 0; i != max; ++i){
		auto n = id(dre);
		list1.push_back(n);
		list2.push_back(n);
	}
	double cost1 = 0.0, cost2 = 0.0;
	for (int i = 0; i != 100; ++i){
		ProfilerInstance::start();
		list1.sort();//TinySTL::list<int>
		ProfilerInstance::finish();
		cost1 += ProfilerInstance::millisecond();

		ProfilerInstance::start();
		list2.sort();//std::list<int>
		ProfilerInstance::finish();
		cost2 += ProfilerInstance::millisecond();
	}
	cout << "TinySTL time: " << cost1 / 100 << "ms" << endl;
	cout << "std time: " << cost2 / 100 << "ms" << endl;
    
|container|quantity|time(ms)|  
|---------|--------|--------|  
|TinySTL::list&lt;int>|1万|0.88|  
|TinySTL::list&lt;int>|10万|17.621|  
|TinySTL::list&lt;int>|100万|591.354|  
|std::list&lt;int>|1万|1.25|  
|std::list&lt;int>|10万|35.692|  
|std::list&lt;int>|100万|665.128|  


####(12):suffix_array

    char arr[] = { 'a', 'a', 'b', 'a', 'a', 'a', 'a', 'b' };
    TinySTL::suffix_array sa(arr, 8);
	auto suffixArray = sa.suffixArray();
	auto rankArray = sa.rankArray();
	auto heightArray = sa.heightArray();

	TinySTL::Test::print_container(suffixArray, "suffixArray");
	TinySTL::Test::print_container(rankArray, "rankArray");
	TinySTL::Test::print_container(heightArray, "heightArray");
    
![image](https://raw.githubusercontent.com/zouxiaohang/TinySTL/master/TinySTL/ScreenShots/suffix_array.png)




####(13):unordered_set&lt;int>

    TinySTL::Unordered_set<int> ust(10);
	//std::unordered_set<int> ust(10);
	const size_t insert_count = 1000000;
	const uint64_t query_count = 100000000;
	//calculate total insert time
	ProfilerInstance::start();
	for (size_t i = 0; i != insert_count; ++i){
		ust.insert(i);//per insert time
	}
	ProfilerInstance::finish();
	ProfilerInstance::dumpDuringTime();

	//calculate total query time
	ProfilerInstance::start();
	for (uint64_t i = 0; i != query_count; ++i){
		ust.count(i);//per query time
	}
	ProfilerInstance::finish();
	ProfilerInstance::dumpDuringTime();
    
|container|quantity|insert time(ms)|query time(ms)|    
|---------|--------|--------|--------|    
|TinySTL::unordered_set&lt;int>|1万/1亿|8|97|      
|TinySTL::unordered_set&lt;int>|10万/10亿|139|1000|    
|TinySTL::unordered_set&lt;int>|100万/100亿|1214|9546|    
|std::unordered_set&lt;int>|1万/1亿|64|101|    
|std::unordered_set&lt;int>|10万/10亿|884|953|    
|std::unordered_set&lt;int>|100万/100亿|2781|9682|   




####(14):sort

    std::random_device rd;
	const int len = 10000000;
	int arr[len];
	std::generate(std::begin(arr), std::end(arr), [&rd](){return rd(); });
	ProfilerInstance::start();
	TinySTL::sort(std::begin(arr), std::end(arr));
	//std::sort(std::begin(arr), std::end(arr));
	ProfilerInstance::finish();
	ProfilerInstance::dumpDuringTime();
    
|algorithm|quantity|time(ms)|  
|---------|--------|--------|  
|TinySTL::sort|10万|11|  
|TinySTL::sort|100万|133|  
|TinySTL::sort|1000万|1547|  
|std::sort|10万|13|  
|std::sort|100万|147|  
|std::sort|1000万|1730| 




####(15):directed_graph

    template<class Index, class Value>
	using dGraph = TinySTL::directed_graph < Index, Value > ;
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
    
![image](https://raw.githubusercontent.com/zouxiaohang/TinySTL/master/TinySTL/ScreenShots/graph1.png)  
![image](https://raw.githubusercontent.com/zouxiaohang/TinySTL/master/TinySTL/ScreenShots/graph_dfs.png)  
![image](https://raw.githubusercontent.com/zouxiaohang/TinySTL/master/TinySTL/ScreenShots/graph_bfs.png)  
![image](https://raw.githubusercontent.com/zouxiaohang/TinySTL/master/TinySTL/ScreenShots/graph2.png)





####(16):trie tree

    TinySTL::trie_tree t;
	std::ifstream in;
	in.open("C:\\Users\\zxh\\Desktop\\trie_tree_test.txt");
	std::vector<std::string> v;
	std::string s;
	while (in){
		in >> s;
		v.push_back(s);
	}
	ProfilerInstance::start();
	for (const auto& str : v){
		t.insert(TinySTL::string(str.data()));
	}
	ProfilerInstance::finish();
	std::cout << "build trie tree costs " << ProfilerInstance::millisecond() << "ms" << std::endl;

	ProfilerInstance::start();
	auto res = t.get_word_by_prefix("v");
	ProfilerInstance::finish();
	std::cout << "get word by prefix \"v\" costs " << ProfilerInstance::millisecond() << "ms" << std::endl;
	auto i = 0;
	for (const auto& str : res){
		++i;
		if (i % 10 == 0) std::cout << std::endl;
		std::cout << str << " ";
	}
	std::cout << std::endl;
    
![image](https://raw.githubusercontent.com/zouxiaohang/TinySTL/master/TinySTL/ScreenShots/trie_tree.png)  



####(17):shared_ptr

    shared_ptr<string> sp1(new string("hello"));
	assert(sp1.use_count() == 1);
	assert(*sp1 == "hello");
	sp1->append(" world");
	assert(*sp1 == "hello world");

	{
		auto sp2 = sp1;
		assert(sp1.use_count() == 2);
	}
	assert(sp1.use_count() == 1);



####(18):unique_ptr

    auto up = make_unique<string>(10, '0');
	up->append("111");
	assert(*up == "0000000000111");

	up.release();
	assert(up == nullptr);

	up.reset(new string("hello"));
	assert(*up == "hello");



####(19):cow_ptr

    cow_ptr<string> cp1 = make_cow<string>("zouxiaohang");
	auto cp2 = cp1, cp3 = cp1;
	assert(cp1 == cp2 && cp2 == cp3);
	assert(*cp1 == *cp2 && *cp2 == *cp3 && *cp3 == "zouxiaohang");

	string s = *cp2;//read
	assert(s == "zouxiaohang");
	assert(cp1 == cp2 && cp2 == cp3);
	assert(*cp1 == *cp2 && *cp2 == *cp3 && *cp3 == "zouxiaohang");

	*cp2 = ("C++");//write
	assert(*cp1 == *cp3 && *cp3 == "zouxiaohang");
	assert(*cp2 == "C++");




####(19):union-find set

    uf_set<10> uf;
	uf.Union(0, 1);
	uf.Union(2, 3);
	uf.Union(3, 1);
	assert(uf.Find(0) == uf.Find(2));
    
 
    
