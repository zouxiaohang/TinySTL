#ifndef _BINARY_SEARCH_TREE_IMPL_H_
#define _BINARY_SEARCH_TREE_IMPL_H_

namespace TinySTL{
	namespace Detail{
		template<class T>
		bst_iter<T>::bst_iter(const T *ptr, cntrPtr container)
			:ptr_(ptr), container_(container){
			if (!ptr_)
				return;
			auto temp = container_->root_;
			while (temp && temp != ptr_ && temp->data_ != ptr_->data_){
				parent_.push(temp);
				if (temp->data_ < ptr_->data_){
					//temp向右走说明temo指向的父节点不需要再次访问了
					visited_.insert(temp);//add 2015.01.14
					temp = temp->right_;
				}
				else if (temp->data_ > ptr_->data_){
					temp = temp->left_;
				}
			}
		}
		template<class T>
		bst_iter<T>& bst_iter<T>::operator ++(){
			visited_.insert(ptr_);//此node被访问
			if (ptr_->right_){//此node还有右子树
				//rvisited_.insert(ptr_);
				parent_.push(ptr_);
				ptr_ = ptr_->right_;
				while (ptr_ && ptr_->left_){
					parent_.push(ptr_);
					ptr_ = ptr_->left_;
				}
			}else{//node无右子树则只能向父节点路径移动
				ptr_ = 0;//add 2015.01.14
				while (!parent_.empty()){
					ptr_ = parent_.top();
					parent_.pop();
					if (visited_.count(ptr_) == 0){//父节点尚未访问,此时ptr_指向此节点
						visited_.insert(ptr_);
						break;
					}
					ptr_ = 0;//设为哨兵
				}//end of while
			}//end of if
			return *this;
		}
		template<class T>
		bst_iter<T> bst_iter<T>::operator ++(int){
			auto res = *this;
			++*this;
			return res;
		}
		template<class T>
		bool operator ==(const bst_iter<T>& it1, const bst_iter<T>& it2){
			return it1.ptr_ == it2.ptr_;
		}
		template<class T>
		bool operator !=(const bst_iter<T>& it1, const bst_iter<T>& it2){
			return !(it1 == it2);
		}
	}//end of Detail namespace

	template<class T>
	binary_search_tree<T>::~binary_search_tree(){
		deallocateAllNodes(root_);
	}
	template<class T>
	void binary_search_tree<T>::deallocateAllNodes(node *ptr){
		if (ptr){
			deallocateAllNodes(ptr->left_);
			deallocateAllNodes(ptr->right_);
			nodeAllocator::destroy(ptr);
			nodeAllocator::deallocate(ptr);
		}
	}
	template<class T>
	size_t binary_search_tree<T>::height_aux(node *p)const{
		TinySTL::queue<node *> q/*存放下一层的node*/, level/*存放当前层的node*/;
		size_t nlevel = 0;
		if (p != 0){
			level.push(p);
			++nlevel;
			while (!(q.empty() && level.empty())){
				if (level.empty()){
					++nlevel;
					while (!q.empty()){//当前层为空，将下一层的node全部转移至当前层
						level.push(q.front());
						q.pop();
					}
				}
				auto temp = level.front();
				level.pop();
				if (temp->left_ != 0) q.push(temp->left_);
				if (temp->right_ != 0) q.push(temp->right_);
			}
		}
		return nlevel;
	}
	template<class T>
	void binary_search_tree<T>::erase_elem(const T& val, node *&ptr){
		if (ptr == 0)
			return;
		if (ptr->data_ != val){
			if (val < ptr->data_)
				return erase_elem(val, ptr->left_);
			else
				return erase_elem(val, ptr->right_);
		}
		else{ // found
			if (ptr->left_ != 0 && ptr->right_ != 0){// has two children
				size_t choose = size_ % 2;
				//随机选择删除左右，使得删除操作更平衡
				auto pos = (choose == 0 ?
					const_cast<node *>(find_min_aux(ptr->right_).ptr_) : const_cast<node *>(find_max_aux(ptr->left_).ptr_));
				ptr->data_ = pos->data_;
				return (choose == 0 ? erase_elem(pos->data_, ptr->right_) : erase_elem(pos->data_, ptr->left_));
			}
			else{ //has one or no child
				auto temp = ptr;
				if (ptr->left_ == 0)
					ptr = ptr->right_;
				else
					ptr = ptr->left_;
				nodeAllocator::destroy(temp);
				nodeAllocator::deallocate(temp);
				--size_;
			}
		}
	}
	template<class T>
	void binary_search_tree<T>::erase(const T& val){
		erase_elem(val, root_);
	}
	template<class T>
	void binary_search_tree<T>::insert_elem(const T& val, node *&ptr){//重复的元素不插入
		if (ptr == 0){
			ptr = nodeAllocator::allocate();
			nodeAllocator::construct(ptr);
			ptr->data_ = val;
			ptr->left_ = ptr->right_ = 0;
			++size_;
		}
		else{
			if (val < ptr->data_){
				return insert_elem(val, ptr->left_);
			}
			else if (val > ptr->data_){
				return insert_elem(val, ptr->right_);
			}
		}
	}
	template<class T>
	void binary_search_tree<T>::insert(const T& val){
		insert_elem(val, root_);
	}
	template<class T>
	template<class Iterator>
	void binary_search_tree<T>::insert(Iterator first, Iterator last){
		for (; first != last; ++first)
			insert(*first);
	}
	template<class T>
	void binary_search_tree<T>::print_levelorder(const string& delim, std::ostream& os)const{
		auto temp = root_;
		if (temp != 0){
			std::deque<node *> q;
			q.push_back(temp);
			while (!q.empty()){
				temp = q.front();
				q.pop_front();
				if (temp->left_ != 0) q.push_back(temp->left_);
				if (temp->right_ != 0) q.push_back(temp->right_);
				os << temp->data_ << delim;
			}
		}
	}
	template<class T>
	void binary_search_tree<T>::print_preorder_aux(const string& delim, std::ostream& os, const node *ptr)const{
		if (ptr){
			os << ptr->data_ << delim;
			print_preorder_aux(delim, os, ptr->left_);
			print_preorder_aux(delim, os, ptr->right_);
		}
	}
	template<class T>
	void binary_search_tree<T>::print_preorder(const string& delim, std::ostream& os)const{
		print_preorder_aux(delim, os, root_);
	}
	template<class T>
	void binary_search_tree<T>::print_inorder_aux(const string& delim, std::ostream& os, const node *ptr)const{
		if (ptr){
			print_inorder_aux(delim, os, ptr->left_);
			os << ptr->data_ << delim;
			print_inorder_aux(delim, os, ptr->right_);
		}
	}
	template<class T>
	void binary_search_tree<T>::print_inorder(const string& delim, std::ostream& os)const{
		print_inorder_aux(delim, os, root_);
	}
	template<class T>
	void binary_search_tree<T>::print_postorder_aux(const string& delim, std::ostream& os, const node *ptr)const{
		if (ptr){
			print_postorder_aux(delim, os, ptr->left_);
			print_postorder_aux(delim, os, ptr->right_);
			os << ptr->data_ << delim;
		}
	}
	template<class T>
	void binary_search_tree<T>::print_postorder(const string& delim, std::ostream& os)const{
		print_postorder_aux(delim, os, root_);
	}
	template<class T>
	typename binary_search_tree<T>::const_iterator binary_search_tree<T>::find_min_aux(const node *ptr)const{
		while (ptr && ptr->left_ != 0){
			ptr = ptr->left_;
		}
		return const_iterator(ptr, this);
	}
	template<class T>
	typename binary_search_tree<T>::const_iterator binary_search_tree<T>::find_min()const{
		return find_min_aux(root_);
	}
	template<class T>
	typename binary_search_tree<T>::const_iterator binary_search_tree<T>::find_max_aux(const node *ptr)const{
		while (ptr && ptr->right_ != 0){
			ptr = ptr->right_;
		}
		return const_iterator(ptr, this);
	}
	template<class T>
	typename binary_search_tree<T>::const_iterator binary_search_tree<T>::find_max()const{
		return find_max_aux(root_);
	}
	template<class T>
	typename binary_search_tree<T>::const_iterator binary_search_tree<T>::find_aux(const T& val, const node *ptr)const{
		while (ptr){
			if (val == ptr->data_)
				break;
			else if (val < ptr->data_)
				ptr = ptr->left_;
			else
				ptr = ptr->right_;
		}
		return const_iterator(ptr, this);
	}
	template<class T>
	typename binary_search_tree<T>::const_iterator binary_search_tree<T>::find(const T& val)const{
		return find_aux(val, root_);
	}
}

#endif