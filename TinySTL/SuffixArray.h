#ifndef _SUFFIX_ARRAY_H_
#define _SUFFIX_ARRAY_H_

#include <vector>
#include <memory>

namespace TinySTL{
	
	class suffix_array{
	private:
		//typedef std::unique_ptr<std::vector<int>> vecPtr;
	private:
		std::vector<int> _array;
	public:
		template<class InputIterator>
		//arr - 源数组
		//len - 源数组长度
		//max_len - max_len代表字符串中字符的取值范围，是基数排序的一个参数，
		//          如果原序列都是字母可以直接取128，如果原序列本身都是整数的话，则m可以取比最大的整数大1的值。
		suffix_array(InputIterator arr, int len, int max_len = 128){
			//采用了罗穗骞论文中实现的倍增算法
			_array.resize(len);
			int wa[1024], wb[1024], wv[1024], ws[1024];

			int i, j, p, *x = wa, *y = wb, *t;
			for (i = 0; i < max_len; i++) ws[i] = 0;
			for (i = 0; i < len; i++) ws[x[i] = arr[i]]++;
			for (i = 1; i < max_len; i++) ws[i] += ws[i - 1];
			for (i = len - 1; i >= 0; i--) _array[--ws[x[i]]] = i;
			for (j = 1, p = 1; p < len; j *= 2, max_len = p)
			{
				for (p = 0, i = len - j; i < len; i++) y[p++] = i;
				for (i = 0; i < len; i++) if (_array[i] >= j) y[p++] = _array[i] - j;
				for (i = 0; i < len; i++) wv[i] = x[y[i]];
				for (i = 0; i < max_len; i++) ws[i] = 0;
				for (i = 0; i < len; i++) ws[wv[i]]++;
				for (i = 1; i < max_len; i++) ws[i] += ws[i - 1];
				for (i = len - 1; i >= 0; i--) _array[--ws[wv[i]]] = y[i];
				for (t = x, x = y, y = t, p = 1, x[_array[0]] = 0, i = 1; i < len; i++)
					x[_array[i]] = cmp(y, _array[i - 1], _array[i], j) ? p - 1 : p++;
			}
			return;
		}

		const std::vector<int> suffixArray()const{
			return _array;
		}
	private:
		bool cmp(int *arr, int a, int b, int l){
			return arr[a] == arr[b] && arr[a + l] == arr[b + l];
		}
	};
}

#endif