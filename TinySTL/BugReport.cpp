/*
	你好，最近在跟着你的TinySTL学习，目前在还在vector这里，发现vector存在一个比较重大的bug，不知道后面容器的实现是否也有类似问题，暂时还没看。
	下面的代码段是你的insert_aux函数，在有问题的地方我标注出来了。	
*/


template<class T, class Alloc>
template<class InputIterator>
void vector<T, Alloc>::insert_aux(iterator position,
	InputIterator first,
	InputIterator last,
	std::false_type){
	difference_type locationLeft = endOfStorage_ - finish_; // the size of left storage
	difference_type locationNeed = last - first;			//	bug0。InputIterator不一定支持operator -, 最好用distance()

	if (locationLeft >= locationNeed){
		iterator tempPtr = end() - 1;
		for (; tempPtr - position >= 0; --tempPtr){//move the [position, finish_) back
			*(tempPtr + locationNeed) = *tempPtr;		//	bug1
		}
		TinySTL::uninitialized_copy(first, last, position);		//	bug2
		finish_ += locationNeed;
	}
	else{
		reallocateAndCopy(position, first, last);
	}
}

/*
	关于bug1，你是将[postion, finish)的元素后移，关键是 此时[finish,end_of_storage)为未初始化（uninitialized）区间。
	在未初始化区间调用operator =将存在麻烦。
	
	假设有自定义String类，如下
	//  String has a pointer  
	class String
	{
	public:
	    //  constructor
	    String(const char *data = NULL)
	    {
	        if (NULL == data)
	        {
	            m_data = new char[1];
	            m_data[0] = '\0';       
	        }
	        else
	        {
	            int len = strlen(data);
	            m_data =  new char[len + 1];
	            strcpy(m_data, data);
	        }
	    }
	
	    //  copy
	    String(const String &lhs)
	    {
	        int len = strlen(lhs.m_data);
	        m_data = new char[len + 1];
	        strcpy(m_data, lhs.m_data);
	    }
	
	    //  assign
	    String & operator =(const String &lhs)
	    {
	        int len = strlen(lhs.m_data);
	        char *temp = new char[len + 1];
	        strcpy(temp, lhs.m_data);
	
	        delete []m_data;
	        m_data = temp;
	        return *this;
	    }
	    //  destroy
	    ~String()
	    {
	        delete []m_data;
	    }
	public:
	    char *m_data;
	
	};
	
	在未初始化区间调用operator =,其中有代码delete []m_data,然而，此时未初始化区间的m_data指针为野指针，直接delete它将报错。
*/

/*
	关于bug2，同样使用自定义String类测试。
	将[first, last)元素插入到区间[postion, postion + locationNeed),调用的是uninitialized_copy()函数，内部将调用copy constructor,
	而此时[postion, postion + locationNeed)是已初始化（initialzied）区间，在这个区间调用copy consructor，发现将造成内存泄露。
*/

///////////////////////////////////////////////////////////
/*
	综述，进行插入，删除元素时，必须考虑区间是否已经初始化。
*/