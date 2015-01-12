#ifndef _SUFFIX_ARRAY_H_
#define _SUFFIX_ARRAY_H_

#include <vector>

namespace TinySTL{

	class suffix_array{
	public:
		using array_type = std::vector < int > ;
	private:
		array_type _suffix_array;
		array_type _height_array;
		array_type _rank_array;
	public:
		template<class InputIterator>
		//arr - 源数组
		//len - 源数组长度
		//max_len - max_len代表字符串arr中字符的取值范围，是基数排序的一个参数，原序列都是字母所以可以直接取256
		suffix_array(const InputIterator arr, size_t len, size_t max_len = 256){
			if (max_len > 256)
				throw std::exception("out of the range");
			calSuffix(arr, len, max_len);
			calRank();
			calHeight(arr, len);
		}

		array_type suffixArray()const{ return _suffix_array; }
		array_type heightArray()const{ return _height_array; }
		array_type rankArray()const{ return _rank_array; }
	private:
		template<class InputIteraotr>
		bool cmp(const InputIteraotr arr, size_t a, size_t b, size_t l);
		void calRank(){
			_rank_array.resize(_suffix_array.size());
			for (auto i = 0; i != _suffix_array.size(); ++i){
				_rank_array[_suffix_array[i]] = i;
			}
		}
		template<class InputIterator>
		void calSuffix(const InputIterator arr, size_t len, size_t max_len);
		template<class InputIteraotr>
		void calHeight(const InputIteraotr arr, size_t len);
	};

	template<class InputIteraotr>
	bool suffix_array::cmp(const InputIteraotr arr, size_t a, size_t b, size_t l){
		return arr[a] == arr[b] && arr[a + l] == arr[b + l];
	}
	template<class InputIteraotr>
	void suffix_array::calHeight(const InputIteraotr arr, size_t len){
		_height_array.resize(_suffix_array.size() - 1);
		for (auto i = 0; i != _suffix_array.size() - 1; ++i){
			auto n = 0;
			for (auto j = _suffix_array[i], k = _suffix_array[i + 1];
				arr[j] == arr[k] && (arr + j) != (arr + len) && (arr + k) != (arr + len);
				++j, ++k)
				++n;
			_height_array[i] = n;
		}
	}
	template<class InputIterator>
	void suffix_array::calSuffix(const InputIterator arr, size_t len, size_t max_len){
		//采用了罗穗骞论文中实现的倍增算法
		//算法时间复杂度 = O(nlg(n))
		_suffix_array.resize(len);
		int wa[256], wb[256], wv[256], ws[256];
		int i, j, p, *x = wa, *y = wb, *t;

		//以下四行代码是把各个字符（也即长度为1的字符串）进行基数排序
		for (i = 0; i < max_len; i++) ws[i] = 0;
		//x[]里面本意是保存各个后缀的rank值的，但是这里并没有去存储rank值，因为后续只是涉及x[]的比较工作，因而这一步可以不用存储真实的rank值，能够反映相对的大小即可。
		for (i = 0; i < len; i++) ws[x[i] = arr[i]]++;
		for (i = 1; i < max_len; i++) ws[i] += ws[i - 1];
		//i之所以从len-1开始循环，是为了保证在当字符串中有相等的字符串时，默认靠前的字符串更小一些。
		for (i = len - 1; i >= 0; i--) _suffix_array[--ws[x[i]]] = i;

		//下面这层循环中p代表rank值不用的字符串的数量，如果p达到len，那么各个字符串的大小关系就已经明了了。
		//j代表当前待合并的字符串的长度，每次将两个长度为j的字符串合并成一个长度为2*j的字符串，当然如果包含字符串末尾具体则数值应另当别论，但思想是一样的。
		//max_len同样代表基数排序的元素的取值范围
		for (j = 1, p = 1; p < len; j *= 2, max_len = p){
			//以下两行代码实现了对第二关键字的排序
			for (p = 0, i = len - j; i < len; i++) y[p++] = i;
			for (i = 0; i < len; i++) if (_suffix_array[i] >= j) y[p++] = _suffix_array[i] - j;
			//第二关键字基数排序完成后，y[]里存放的是按第二关键字排序的字符串下标
			//这里相当于提取出每个字符串的第一关键字（前面说过了x[]是保存rank值的，也就是字符串的第一关键字），放到wv[]里面是方便后面的使用
			//以下四行代码是按第一关键字进行的基数排序
			for (i = 0; i < len; i++) wv[i] = x[y[i]];
			for (i = 0; i < max_len; i++) ws[i] = 0;
			for (i = 0; i < len; i++) ws[wv[i]]++;
			for (i = 1; i < max_len; i++) ws[i] += ws[i - 1];
			for (i = len - 1; i >= 0; i--) _suffix_array[--ws[wv[i]]] = y[i];
			//下面两行就是计算合并之后的rank值了，而合并之后的rank值应该存在x[]里面，但我们计算的时候又必须用到上一层的rank值，也就是现在x[]里面放的东西，如果我既要从x[]里面拿，又要向x[]里面放，怎么办？
			//当然是先把x[]的东西放到另外一个数组里面，省得乱了。这里就是用交换指针的方式，高效实现了将x[]的东西“复制”到了y[]中。
			for (t = x, x = y, y = t, p = 1, x[_suffix_array[0]] = 0, i = 1; i < len; i++)
				x[_suffix_array[i]] = cmp(y, _suffix_array[i - 1], _suffix_array[i], j) ? p - 1 : p++;
		}
	}
}

#endif