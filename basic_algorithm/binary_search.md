# 二分搜索

## 二分搜索模板
**题干关键词：有序数组/排序数组**
给一个**有序数组**和目标值，找第一次/最后一次/任何一次出现的索引，如果没有出现返回-1

模板四点要素

- 1、初始化：start=0、end=len-1
- 2、循环退出条件：start + 1 < end
- 3、比较中点和目标值：A[mid] ==、 <、> target
- 4、判断最后两个元素是否符合：A[start]、A[end] ? target

时间复杂度 O(logn)，使用场景一般是有序数组的查找
//summary：用[start,mid,end]三个元素验证正确性既可以

典型示例

[binary-search](https://leetcode-cn.com/problems/binary-search/)

> 给定一个  n  个元素有序的（升序）整型数组  nums 和一个目标值  target  ，写一个函数搜索  nums  中的 target，如果目标值存在返回下标，否则返回 -1。

```go
// 二分搜索最常用模板
func search(nums []int, target int) int {
    // 1、初始化start、end
    start := 0
    end := len(nums) - 1
    // 2、处理for循环
    for start+1 < end {
        mid := start + (end-start)/2
        // 3、比较a[mid]和target值
        if nums[mid] == target {
            end = mid
        } else if nums[mid] < target {
            start = mid
        } else if nums[mid] > target {
            end = mid
        }
    }
    // 4、最后剩下两个元素，手动判断
    if nums[start] == target {
        return start
    }
    if nums[end] == target {
        return end
    }
    return -1
}
```

大部分二分查找类的题目都可以用这个模板，然后做一点特殊逻辑即可

另外二分查找还有一些其他模板如下图，大部分场景模板#3 都能解决问题，而且还能找第一次/最后一次出现的位置，应用更加广泛

![binary_search_template](https://img.fuiboom.com/img/binary_search_template.png)

所以用模板#3 就对了，详细的对比可以这边文章介绍：[二分搜索模板](https://leetcode-cn.com/explore/learn/card/binary-search/212/template-analysis/847/)

如果是最简单的二分搜索，不需要找第一个、最后一个位置、或者是没有重复元素，可以使用模板#1，代码更简洁

```c++
// 无重复元素搜索时，更方便
class Solution {
public:
    int search(vector<int>& nums, int target) {
        if(nums.empty())
            return -1;
        int start=0,end=nums.size()-1;
        while(start<=end)
        {
        // Prevent (left + right) overflow
            int mid=start+(end-start)/2;
            if(nums[mid]==target)
                return mid;
            else if(nums[mid]>target)
                end=mid-1;
            else    
                start=mid+1;
        }
        return -1;
    }
};
//二分查找的最基础和最基本的形式。
//查找条件可以在不与元素的两侧进行比较的情况下确定（或使用它周围的特定元素）。
//不需要后处理，因为每一步中，你都在检查是否找到了元素。如果到达末尾，则知道未找到该元素。
    // 如果找不到，start 是第一个大于target的索引
    // 如果在B+树结构里面二分搜索，可以return start
    // 这样可以继续向子节点搜索，如：node:=node.Children[start]
    return -1
}
```
```c++
//模板三:target 可能存在于最后两个元素之中
int binarySearch(vector<int>& nums, int target){
    if (nums.size() == 0)
        return -1;

    int left = 0, right = nums.size() - 1;
    while (left + 1 < right){
        // Prevent (left + right) overflow
        int mid = left + (right - left) / 2;
        if (nums[mid] == target) {
            return mid;
        } else if (nums[mid] < target) {
            left = mid;
        } else {
            right = mid;
        }
    }

    // Post-processing:
    // End Condition: left + 1 == right
    if(nums[left] == target) return left;
    if(nums[right] == target) return right;
    return -1;
}
//实现二分查找的另一种方法。
//搜索条件需要访问元素的直接左右邻居。
//使用元素的邻居来确定它是向右还是向左。
//保证查找空间在每个步骤中至少有 3 个元素。
//需要进行后处理。 当剩下 2 个元素时，循环 / 递归结束。 需要评估其余元素是否符合条件。
```
对于二分查找，最主要的是边界的定位： 循环条件及左右边界的移动。一个方法是假定搜索范围只剩下两个元素（left/right），据此可推断出循环条件
## 常见题目

### 1.[search-for-range](https://www.lintcode.com/problem/search-for-a-range/description)||找左右边界

> 给定一个包含 n 个整数的排序数组，找出给定目标值 target 的起始和结束位置。
> 如果目标值不在数组中，则返回`[-1, -1]`

思路：核心点就是找第一个 target 的索引，和最后一个 target 的索引，所以用两次二分搜索分别找第一次和最后一次的位置，找range边界

```c++
class Solution {
public:
    vector<int> searchRange(vector<int> &A, int target) {
        if(A.empty())
            return {-1,-1};
        vector<int>res;
        int start=0,end=A.size()-1;
        while(start+1<end)
        {
            int mid=start+(end-start)/2;
            if(A[mid]>target)
                end=mid;
            else if(A[mid]<target)
                start=mid;
            else
            //// 如果相等，应该继续向左找，就能找到第一个目标值的位置
                end=mid;
        }
        //搜索左边第一个target
        //cout<<start<<" "<<end;
        if(A[start]==target)res.push_back(start);
        else if(A[end]==target)res.push_back(end);
        else{ res.push_back(-1);res.push_back(-1);return res;}
        //搜索右边最后一个target
        start=0;end=A.size()-1;
        while(start+1<end)
        {
            int mid=start+(end-start)/2;
            if(A[mid]>target)
                end=mid;
            else if(A[mid]<target)
                start=mid;
            else
            //如果相等继续找右边
                start=mid;
        }
        //搜索右边最后的target
        if(A[end]==target)res.push_back(end);
        else res.push_back(start);
        return res;        
    }  
};
```

### 2.[search-insert-position](https://leetcode-cn.com/problems/search-insert-position/)||找单边界

> 给定一个排序数组和一个目标值，在数组中找到目标值，并返回其索引。如果目标值不存在于数组中，返回它将会被按顺序插入的位置。

```c++
class Solution {
public:
// 思路：找到第一个 >= target 的元素位置
    int searchInsert(vector<int>& nums, int target) {
        if(nums.empty())
            return 0;
        int start=0,end=nums.size()-1;
        int res=0;
        while(start+1<end)
        {
            int mid=start+(end-start)/2;
            if(nums[mid]==target)
                return mid;
            else if(nums[mid]>target)
                end=mid;
            else 
                start=mid;
        }
        // >=!!
        if(nums[start]>=target) return start;
        else if(nums[end]==target)return end;
        else if(nums[end]>target)
            return end;
        else 
        // 目标值比所有值都大
            return end+1;
        return -1;
        
    }
};
```

### 3.[search-a-2d-matrix](https://leetcode-cn.com/problems/search-a-2d-matrix/)

> 编写一个高效的算法来判断  m x n  矩阵中，是否存在一个目标值。该矩阵具有如下特性：
>
> - 每行中的整数从左到右按升序排列。
> - 每行的第一个整数大于前一行的最后一个整数。

```c++
    // 思路：将二维数组转为1维数组 进行二分搜索
    class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if(matrix.size()==0||matrix[0].size()==0)
            return false;
        int rows=matrix.size(),cols=matrix[0].size();
        int start=0,end=rows*cols-1;
        while(start+1<end)
        {
            int mid=start+(end-start)/2;
             // 获取二维数组对应值
            if(matrix[mid/cols][mid%cols]==target)
                return true;
            else if(matrix[mid/cols][mid%cols]>target)
                end=mid;
            else 
                start=mid;
        }
        if(matrix[start/cols][start%cols]==target)return true;
        if(matrix[end/cols][end%cols]==target)return true;
        return false;
    }
};
```

### 4.[first-bad-version](https://leetcode-cn.com/problems/first-bad-version/)||找单边界

> 假设你有 n 个版本 [1, 2, ..., n]，你想找出导致之后所有版本出错的第一个错误的版本。
> 你可以通过调用  bool isBadVersion(version)  接口来判断版本号 version 是否在单元测试中出错。实现一个函数来查找第一个错误的版本。你应该尽量减少对调用 API 的次数。

```c++
// The API isBadVersion is defined for you.
// bool isBadVersion(int version);
///类似search for range
class Solution {
public:
    int firstBadVersion(int n) {
        if(n<=1)
            return n;
        int start=0,end=n;
        while(start+1<end)
        {
            int mid=start+(end-start)/2;
            if(isBadVersion(mid)==true)
                end=mid;
            else
                start=mid;
        }
        if(isBadVersion(start))
            return start;
        else
            return end;
        
    }
};
```

### 5.[find-minimum-in-rotated-sorted-array](https://leetcode-cn.com/problems/find-minimum-in-rotated-sorted-array/)||有序数组变形，无重复

> 假设按照升序排序的数组在预先未知的某个点上进行了旋转( 例如，数组  [0,1,2,4,5,6,7] 可能变为  [4,5,6,7,0,1,2] )。
> 请找出其中最小的元素。

```c++
    // 思路：旋转数组的目标值一定在右排序数组中（没旋转也可以看成是右排序数组），所以end为target
  class Solution {
public:
    int findMin(vector<int>& nums) {
        if(nums.empty())
            return -1;

        int start=0,end=nums.size()-1;
        while(start+1<end)
        {
            int mid=start+(end-start)/2;
            if(nums[mid]>nums[end])
                start=mid+1;
            else
                end=mid;
        }
        if(nums[start]<nums[end])return nums[start];
        else return nums[end];

    }
};
```

### 6.[find-minimum-in-rotated-sorted-array-ii](https://leetcode-cn.com/problems/find-minimum-in-rotated-sorted-array-ii/)||有序数组变形，有重复

> 假设按照升序排序的数组在预先未知的某个点上进行了旋转
> ( 例如，数组  [0,1,2,4,5,6,7] 可能变为  [4,5,6,7,0,1,2] )。
> 请找出其中最小的元素。(包含重复元素)

```c++
//仍旧只看右边数组，但是要降重，相等时直接去掉不影响找到最小值
class Solution {
public:
    int findMin(vector<int>& nums) {
        if(nums.empty())
            return -1;
        int start=0,end=nums.size()-1;
        while(start+1<end)
        {
            int mid=start+(end-start)/2;
            if(nums[mid]>nums[end])
                start=mid;
            else if(nums[mid]<nums[end])
                end=mid;
            else
                end--;
        }
         if(nums[start]<nums[end])return nums[start];
        else return nums[end];

    }
};
//origin:
class Solution {
public:
 // 思路：跳过重复元素，mid值和end值比较，分为两种情况进行处理
    int findMin(vector<int>& nums) {
        if(nums.empty())
            return -1;
        int start=0,end=nums.size()-1;
        while(start+1<end)
        {
            
            while(start<end&&nums[start]==nums[start+1])
                start++;
            while(start<end&&nums[end]==nums[end-1])
                end--;
               // 中间元素和最后一个元素比较（判断中间点落在左边上升区，还是右边上升区）
            int mid=start+(end-start)/2;
            if(nums[mid]>nums[end])
                start=mid;
            else
                end=mid;
        }
         if(nums[start]<nums[end])return nums[start];
        else return nums[end];

    }
};
//0ms
class Solution {
public:
    int findMin(vector<int>& nums) {
        if (1 == nums.size()) {
            return nums[0];
        }
        int left = 0;
        int right = nums.size()-1;
        while (left < right) {
            int mid = (left+right)/2;
            if (nums[left] == nums[mid] && nums[mid] == nums[right]) {
                left++;
                right--;
            } else {
                if (nums[left] <= nums[mid]) {
                    if (nums[mid] > nums[right]) {
                        left = mid+1;
                    } else if (nums[mid] < nums[right]) {
                        right = mid;
                    } else { //  (nums[mid] == nums[right])
                        right--;
                    } 
                } else { //  (nums[left] > nums[mid])
                    right = mid;
                }
            } 
        }
        return nums[left];
    }
};
```

### 7.[search-in-rotated-sorted-array](https://leetcode-cn.com/problems/search-in-rotated-sorted-array/)

> 假设按照升序排序的数组在预先未知的某个点上进行了旋转。
> ( 例如，数组  [0,1,2,4,5,6,7]  可能变为  [4,5,6,7,0,1,2] )。
> 搜索一个给定的目标值，如果数组中存在这个目标值，则返回它的索引，否则返回  -1 。
> 你可以假设数组中不存在重复的元素。

```c++
class Solution {
public:
 // 思路：/ / 两条上升直线，四种情况判断，并且处理重复数字
    int search(vector<int>& nums, int target) {
        if(nums.empty())
            return -1;
        int start=0,end=nums.size()-1;
        while(start+1<end)
        {
            int mid=start+(end-start)/2;
            //相等直接返回
            if(nums[mid]==target)
                return mid;
           //判断在哪个区间，分为四种情况
	   //后半部分有序。因此如果 nums[mid] <target<=nums[end]。则在后半部分找，否则去前半部分找。
            if(nums[mid]<nums[end]){
                if(nums[mid]<target&&nums[end]>=target)
                    start=mid;
                else
                    end=mid;
            }
	    //前半部分有序。因此如果 nums[start] <=target<nums[mid]，则在前半部分找，否则去后半部分找。
            else if(nums[mid]>nums[start])
            {
                if(nums[start]<=target&&nums[mid]>target)
                    end=mid;
                else
                    start=mid;
            }
        }
        if(nums[start]==target)return start;
        else if(nums[end]==target)return end;
        else 
            return -1;
        
    }
};
//
class Solution {
public:
    int search(vector<int>& nums, int target) {
        
        int l = 0,r = nums.size()-1;
        while(l <=r){
            int mid = (r - l)/2 + l;
            if(nums[mid] > target){
                if(nums[mid]> nums[r] && nums[l] > target){
                    l = mid+1;
                }else{
                    r = mid-1;
                }
            }else if(nums[mid] < target){
                if(nums[mid] < nums[l] && nums[r] < target){
                     r = mid-1;
                }else{
                   l = mid + 1;
                }
            }else{
                return mid;
            }
           
        }
         return -1;

    }
};
//
```

注意点

> 面试时，可以直接画图进行辅助说明，空讲很容易让大家都比较蒙圈

### 8.[search-in-rotated-sorted-array-ii](https://leetcode-cn.com/problems/search-in-rotated-sorted-array-ii/)

> 假设按照升序排序的数组在预先未知的某个点上进行了旋转。
> ( 例如，数组  [0,0,1,2,2,5,6]  可能变为  [2,5,6,0,0,1,2] )。
> 编写一个函数来判断给定的目标值是否存在于数组中。若存在返回  true，否则返回  false。(包含重复元素)

```c++
//第一类
//1011110111 和 1110111101 这种。此种情况下 nums[start] == nums[mid]，分不清到底是前面有序还是后面有序，此时 start++ 即可。相当于去掉一个重复的干扰项。
//第二类
//2 3 4 5 6 7 1这种，也就是 nums[start] < nums[mid]。此例子中就是 2 < 5；
//这种情况下，前半部分有序。因此如果 nums[start] <=target<nums[mid]，则在前半部分找，否则去后半部分找。
//第三类
//6 7 1 2 3 4 5 这种，也就是 nums[start] > nums[mid]。此例子中就是 6 > 2；
//这种情况下，后半部分有序。因此如果 nums[mid] <target<=nums[end]。则在后半部分找，否则去前半部分找。
class Solution {
public:
    bool search(vector<int>& nums, int target) {
        if (nums.size() < 1) return false;
		int start = 0, end = nums.size()-1;
        while(start +1<= end) {
            int mid = start+(end-start)/2;
            if(nums[mid] == target) return true;
            if(nums[mid] > nums[start]) {
                if(target >= nums[start] && target < nums[mid]) end =mid;
                else start = mid;
            }else if(nums[mid] < nums[start]) {
                if(target > nums[mid] && target <= nums[end]) start = mid;
                else end = mid;
            }else ++start;;
        }
        if(nums[start]==target||nums[end]==target)
            return true;
        return false;
	}
};
////
func search(nums []int, target int) bool {
    // 思路：/ / 两条上升直线，四种情况判断，并且处理重复数字
    if len(nums) == 0 {
        return false
    }
    start := 0
    end := len(nums) - 1
    for start+1 < end {
        // 处理重复数字
        for start < end && nums[start] == nums[start+1] {
            start++
        }
        for start < end && nums[end] == nums[end-1] {
            end--
        }
        mid := start + (end-start)/2
        // 相等直接返回
        if nums[mid] == target {
            return true
        }
        // 判断在那个区间，可能分为四种情况
        if nums[start] < nums[mid] {
            if nums[start] <= target && target <= nums[mid] {
                end = mid
            } else {
                start = mid
            }
        } else if nums[end] > nums[mid] {
            if nums[end] >= target && nums[mid] <= target {
                start = mid
            } else {
                end = mid
            }
        }
    }
    if nums[start] == target || nums[end] == target {
        return true
    }
    return false
}
```

## 总结

二分搜索核心四点要素（必背&理解）

- 1、初始化：start=0、end=len-1
- 2、循环退出条件：start + 1 < end
- 3、比较中点和目标值：A[mid] ==、 <、> target
- 4、判断最后两个元素是否符合：A[start]、A[end] ? target

## 练习题

- [ ] [search-for-range](https://www.lintcode.com/problem/search-for-a-range/description)
- [ ] [search-insert-position](https://leetcode-cn.com/problems/search-insert-position/)
- [ ] [search-a-2d-matrix](https://leetcode-cn.com/problems/search-a-2d-matrix/)
- [ ] [first-bad-version](https://leetcode-cn.com/problems/first-bad-version/)
- [ ] [find-minimum-in-rotated-sorted-array](https://leetcode-cn.com/problems/find-minimum-in-rotated-sorted-array/)
- [ ] [find-minimum-in-rotated-sorted-array-ii](https://leetcode-cn.com/problems/find-minimum-in-rotated-sorted-array-ii/)
- [ ] [search-in-rotated-sorted-array](https://leetcode-cn.com/problems/search-in-rotated-sorted-array/)
- [ ] [search-in-rotated-sorted-array-ii](https://leetcode-cn.com/problems/search-in-rotated-sorted-array-ii/)
