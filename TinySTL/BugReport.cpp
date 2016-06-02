/*
	��ã�����ڸ������TinySTLѧϰ��Ŀǰ�ڻ���vector�������vector����һ���Ƚ��ش��bug����֪������������ʵ���Ƿ�Ҳ���������⣬��ʱ��û����
	����Ĵ���������insert_aux��������������ĵط��ұ�ע�����ˡ�	
*/


template<class T, class Alloc>
template<class InputIterator>
void vector<T, Alloc>::insert_aux(iterator position,
	InputIterator first,
	InputIterator last,
	std::false_type){
	difference_type locationLeft = endOfStorage_ - finish_; // the size of left storage
	difference_type locationNeed = last - first;			//	bug0��InputIterator��һ��֧��operator -, �����distance()

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
	����bug1�����ǽ�[postion, finish)��Ԫ�غ��ƣ��ؼ��� ��ʱ[finish,end_of_storage)Ϊδ��ʼ����uninitialized�����䡣
	��δ��ʼ���������operator =�������鷳��
	
	�������Զ���String�࣬����
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
	
	��δ��ʼ���������operator =,�����д���delete []m_data,Ȼ������ʱδ��ʼ�������m_dataָ��ΪҰָ�룬ֱ��delete��������
*/

/*
	����bug2��ͬ��ʹ���Զ���String����ԡ�
	��[first, last)Ԫ�ز��뵽����[postion, postion + locationNeed),���õ���uninitialized_copy()�������ڲ�������copy constructor,
	����ʱ[postion, postion + locationNeed)���ѳ�ʼ����initialzied�����䣬������������copy consructor�����ֽ�����ڴ�й¶��
*/

///////////////////////////////////////////////////////////
/*
	���������в��룬ɾ��Ԫ��ʱ�����뿼�������Ƿ��Ѿ���ʼ����
*/