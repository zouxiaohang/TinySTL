TinySTL
=======
采用C++11实现一款简易的STL标准库，既是C++STL的一个子集又是一个超集

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
  * 线段树
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
  * ThreadPool

##完成进度：
* STL的几大基本组件
    * type traits：100%  
    * 空间配置器：100%
    * iterator traits：100%
    * reverse_iterator：100%
    * vector：100%
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
* circular_buffer：100%   
* bitmap：100%
* string：100%
* priority_queue：100%
* stack：100%
* binary_search_tree：100%

#TinySTL测试:
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
    
######i = 100000 -> (TinySTL::vector&lt;int>：2ms \\ std::vector&lt;int>：6ms)
######i = 1000000 -> (TinySTL::vector&lt;int>：11ms \\ std::vector&lt;int>：16ms)
######i = 10000000 -> (TinySTL::vector&lt;int>：129ms \\ std::vector&lt;int>：210ms)  
####(2):vector&lt;string>

    //std::vector<std::string> vec;
    TinySTL::vector<std::string> vec;
	ProfilerInstance::start();
	int i = 0;
	for (; i != 10000; ++i){
		vec.push_back(std::string("zouxiaohang"));
	}
	ProfilerInstance::finish();
	ProfilerInstance::dumpDuringTime();
    
######i = 100000 -> (TinySTL::vector&lt;string>：18ms \\ std::vector&lt;string>：29ms)
######i = 1000000 -> (TinySTL::vector&lt;string>：181ms \\ std::vector&lt;string>：232ms)
######i = 10000000 -> (TinySTL::vector&lt;string>：2372ms \\ std::vector&lt;string>：1972ms)
####(3):circular_buffer&lt;int, N>

    TinySTL::circular_buffer<int, 10000> cb(10000, 0);
    //boost::circular_buffer<int> cb(10000, 0);
	ProfilerInstance::start();
	for (int i = 0; i != 10000000; ++i){
		cb.push_back(i);
	}
	ProfilerInstance::finish();
	ProfilerInstance::dumpDuringTime();
    
######i = 10000000 -> (TinySTL::circular_buffer：75ms \\ boost::circular_buffer：22ms)
######i = 100000000 -> (TinySTL::circular_buffer：604ms \\ boost::circular_buffer：252ms)
######i = 1000000000 -> (TinySTL::circular_buffer：5936ms \\ boost::circular_buffer：2241ms)
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
    
######i = 1000000 -> (TinySTL::string：7ms \\ std::string：37ms)
######i = 10000000 -> (TinySTL::string：39ms \\ std::string：229ms)
######i = 100000000 -> (TinySTL::string：484ms \\ std::string：1965ms)

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
    
######i = 100000 -> (TinySTL::priority_queue&lt;int>：13ms \\ std::priority_queue&lt;int>：12ms)
######i = 1000000 -> (TinySTL::priority_queue&lt;int>：97ms \\ std::priority_queue&lt;int>：67ms)
######i = 10000000 -> (TinySTL::priority_queue&lt;int>：1032ms \\ std::priority_queue&lt;int>：752ms)  

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
    
######i = 100000 -> (TinySTL::priority_queue&lt;int>：19ms \\ std::priority_queue&lt;int>：7ms)
######i = 1000000 -> (TinySTL::priority_queue&lt;int>：137ms \\ std::priority_queue&lt;int>：92ms)
######i = 10000000 -> (TinySTL::priority_queue&lt;int>：1532ms \\ std::priority_queue&lt;int>：1214ms)

####(7):binary_search_tree&lt;int>

    TinySTL::binary_search_tree<int> bst;
    const size_t max = 10000;
	std::random_device rd;
	ProfilerInstance::start();
	size_t i = 0;
	for (; i != max; ++i){
		bst.insert(rd());
		//rd();
	}
	ProfilerInstance::finish();
	ProfilerInstance::dumpDuringTime();
    
######i = 100000 -> TinySTL::binary_search_tree&lt;int>：5ms 
######i = 1000000 -> TinySTL::binary_search_tree&lt;int>：64ms 
######i = 10000000 -> TinySTL::binary_search_tree&lt;int>：828ms
#######注：真实的插入时间 = 总的插入时间 - C++11随机数生成器生成随机数的总的时间

