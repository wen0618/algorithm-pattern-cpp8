# 排序
//https://leetcode-cn.com/problems/sort-an-array/solution/dang-wo-tan-pai-xu-shi-wo-zai-tan-xie-shi-yao-by-s/

[十大经典排序](https://www.cnblogs.com/onepixel/p/7674659.html)
![image.png](./sort.png)
## 常考排序

### 快速排序

```c++
class Solution {
public:
	vector<int> sortArray(vector<int>& nums) {
		QuickSort(nums, 0, nums.size() - 1);
		return nums;
	}
	//原地交换，所以传引用
	void QuickSort(vector<int>& nums, int l, int r) {
		if (l < r)
		{
		//分治法：divide
			int mid = partition(nums, l, r);
			QuickSort(nums, l, mid - 1);//注意l和r的值
			QuickSort(nums, mid + 1, r);//注意l和r的值
		}
	}
	//分区函数
	int partition(vector<int>& nums, int l, int r)
	{
	//主元pivot选取方式任意，此选择第一个元素作为主元
		int pivot = nums[l];
		//从第二个元素开始
		int i = l + 1, j = r;
		while (true)
		{
			while (i <= j && nums[i] <= pivot) i++;//寻找比pivot大的元素
			while (i <= j && nums[j] >= pivot) j--;//寻找比pivot小的元素
			if(i>j) break;
			swap(nums[i], nums[j]);
		}
		//把arr[j]和主元交换，把主元放到正确的位置上，并返回
		swap(nums[j], nums[l]);
		return j;//意味swap是原地交换，交换的是值，所以返回的是j
	}
};
```

### 归并排序

```c++
class Solution {
public:
    vector<int> sortArray(vector<int>& nums) {
        if(nums.empty()) return vector<int>();
        vector<int> temp(nums.size(),0);
        merge_sort(nums, temp, 0, nums.size()-1);
        return nums;
        
    }
    void merge_sort(vector<int>&nums, vector<int>&temp, int l, int r){
        if(l>=r) return;
         // 分治法：divide 分为两段
        int mid = l+(r-l)/2;
        merge_sort(nums,temp, l, mid);
        merge_sort(nums,temp, mid+1, r);
	// 合并两段数据
        int p1 = l;
        int p2 = mid+1;
        int i=l;
	 // 注意不能越界
        while(p1<=mid && p2<=r){
            if(nums[p1]<=nums[p2]){
                temp[i++] = nums[p1++];
            }else{
                temp[i++] = nums[p2++];
            }
        }
	// 剩余部分合并
        while(p1<=mid){
            temp[i++] = nums[p1++];
        }
        while(p2<=r){
            temp[i++] = nums[p2++];
        }
        for(int k=l;k<=r;++k){
            nums[k] = temp[k];
        }
    }
};
```

### 堆排序

用数组表示的完美二叉树 complete binary tree

> 完美二叉树 VS 其他二叉树

![image.png](https://img.fuiboom.com/img/tree_type.png)

[动画展示](https://www.bilibili.com/video/av18980178/)

![image.png](https://img.fuiboom.com/img/heap.png)

核心代码
```伪代码c
void heapsort(int arr[],int n)
{
    for(int i=n/2-1;i>=0;i--)
        heapify(arr,n,i);        //create a Max heap;
    for(int i=n;i>=0;i--)
    {
        swap(arr[0],arr[i]);   //swap first and last node
        heapify(arr,i,0);     //create max heap on reduced array
    }
}
```
```c++
class Solution {
    void maxHeapify(vector<int>& nums, int i, int len) {
        for (; (i << 1) + 1 <= len;) {
            int lson = (i << 1) + 1;
            int rson = (i << 1) + 2;
            int large;
            if (lson <= len && nums[lson] > nums[i]) {
                large = lson;
            }
            else {
                large = i;
            }
            if (rson <= len && nums[rson] > nums[large]) {
                large = rson;
            }
            if (large != i) {
                swap(nums[i], nums[large]);
                i = large;
            }
            else break;
        }
    }
    void buildMaxHeap(vector<int>& nums, int len) {
        for (int i = len / 2; i >= 0; --i) {
            maxHeapify(nums, i, len);
        }
    }
    void heapSort(vector<int>& nums) {
        int len = (int)nums.size() - 1;
        buildMaxHeap(nums, len);
        for (int i = len; i >= 1; --i) {
            swap(nums[i], nums[0]);
            len -= 1;
            maxHeapify(nums, 0, len);
        }
    }
public:
    vector<int> sortArray(vector<int>& nums) {
        heapSort(nums);
        return nums;
    }
};
//
package main

func HeapSort(a []int) []int {
    // 1、无序数组a
	// 2、将无序数组a构建为一个大根堆
	for i := len(a)/2 - 1; i >= 0; i-- {
		sink(a, i, len(a))
	}
	// 3、交换a[0]和a[len(a)-1]
	// 4、然后把前面这段数组继续下沉保持堆结构，如此循环即可
	for i := len(a) - 1; i >= 1; i-- {
		// 从后往前填充值
		swap(a, 0, i)
		// 前面的长度也减一
		sink(a, 0, i)
	}
	return a
}
func sink(a []int, i int, length int) {
	for {
		// 左节点索引(从0开始，所以左节点为i*2+1)
		l := i*2 + 1
		// 有节点索引
		r := i*2 + 2
		// idx保存根、左、右三者之间较大值的索引
		idx := i
		// 存在左节点，左节点值较大，则取左节点
		if l < length && a[l] > a[idx] {
			idx = l
		}
		// 存在有节点，且值较大，取右节点
		if r < length && a[r] > a[idx] {
			idx = r
		}
		// 如果根节点较大，则不用下沉
		if idx == i {
			break
		}
		// 如果根节点较小，则交换值，并继续下沉
		swap(a, i, idx)
		// 继续下沉idx节点
		i = idx
	}
}
func swap(a []int, i, j int) {
	a[i], a[j] = a[j], a[i]
}

```

## 参考

[十大经典排序](https://www.cnblogs.com/onepixel/p/7674659.html)

[二叉堆](https://labuladong.gitbook.io/algo/shu-ju-jie-gou-xi-lie/er-cha-dui-xiang-jie-shi-xian-you-xian-ji-dui-lie)

## 练习

- [ ] 手写快排、归并、堆排序
