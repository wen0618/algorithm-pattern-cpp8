# 回溯法——数组的子集、排列、组合问题模板

## 背景

回溯法（backtrack）常用于遍历列表所有子集，是 DFS 深度搜索一种，一般用于全排列，穷尽所有可能，遍历的过程实际上是一个决策树的遍历过程。时间复杂度一般 O(N!)，它不像动态规划存在重叠子问题可以优化，回溯算法就是纯暴力穷举，复杂度一般都很高。

## 模板

```c++
vector<vector<int>res;
vector<vector<int>main(vector<int>& nums){
	//记录走过的路径
	vector<int>track;
	backtrack(nums,track)
	return res;
}
void backtrack(路径, 选择列表):
    if 满足结束条件:
        result.add(路径)
        return
    for 选择 in 选择列表:
    	剪枝
        做选择
        backtrack(路径, 选择列表)
        撤销选择
```

核心就是从选择列表里做一个选择，然后一直递归往下搜索答案，如果遇到路径不通，就返回来撤销这次选择。

## 示例

### 1.[subsets](https://leetcode-cn.com/problems/subsets/)

> 给定一组不含重复元素的整数数组 nums，返回该数组所有可能的子集（幂集）。

遍历过程

![image.png](https://github.com/wen0618/algorithm-pattern/blob/master/advanced_algorithm/%E5%9B%9E%E6%BA%AF.png)

```c++
class Solution {
public:
    vector<vector<int>>res;
    vector<vector<int>> subsets(vector<int>& nums) {
        //记录走过的路程
        vector<int>track;
        backtrack(nums,0,track);
        return res;        
    }
    void backtrack(vector<int>&nums,int start,vector<int>&track)
    {
        //将上一步的结果添至答案中
        res.push_back(track);
        for(int i=start;i<nums.size();++i){
            //做出当前选择
            track.push_back(nums[i]);
            //递归调用继续下走
            backtrack(nums,i+1,track);
            //走到最后，回退
            track.pop_back();
        }
    }
};	
//递归
class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
    // base case，返回一个空集
    if (nums.empty()) return {{}};
    // 把最后一个元素拿出来
    int n = nums.back();
    nums.pop_back();
    // 先递归算出前面元素的所有子集
    vector<vector<int>> res = subsets(nums);

    int size = res.size();
    for (int i = 0; i < size; i++) {
        // 然后在之前的结果之上追加
        res.push_back(res[i]);
        res.back().push_back(n);
    }
    return res;
}
};
```

### 2.[subsets-ii](https://leetcode-cn.com/problems/subsets-ii/)

> 给定一个可能包含重复元素的整数数组 nums，返回该数组所有可能的子集（幂集）。说明：解集不能包含重复的子集。

```c++
//关键点在于如何在回溯中进行剪枝，这种需要去除解集中重复的子集的题目通常都需要先对输入的元素进行排序， 让相同的元素聚在一起， 这样就可以据此进行剪枝。
class Solution {
public:
    vector<vector<int>> res;
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        if(nums.empty())
            return {{}};
        vector<int>track;
        sort(nums.begin(),nums.end());
        backtrack(nums,0,track);
        return res;        
    }
    void backtrack(vector<int>&nums,int start,vector<int>&track)
    {
        //将上一步的结果添至答案中
        res.push_back(track);
        for(int i=start;i<nums.size();++i){
	     //剪枝，注意是i!=start而不是0，否则丢了1，2，2
            if(i!=start&&nums[i]==nums[i-1])
                continue;
            //做出当前选择
            track.push_back(nums[i]);
            //递归调用继续下走
            backtrack(nums,i+1,track);
            //走到最后，回退
            track.pop_back();
        }
    }
};
```

### 3.[permutations](https://leetcode-cn.com/problems/permutations/)

> 给定一个   没有重复   数字的序列，返回其所有可能的全排列。

思路：需要记录已经选择过的元素，满足条件的结果才进行返回

```c++
class Solution {
public:
    vector<vector<int>>res;
    
    vector<vector<int>> permute(vector<int>& nums) {
        if(nums.empty())
            return {{}};
        vector<int>track;
	//记录选择过的数据索引
        vector<bool>visited(nums.size(),false);
        backtrack(nums,visited,track);
        return res;
    }
    void backtrack(vector<int>& nums,vector<bool>& visited,vector<int>& track){
    	//触发结束条件
        if(track.size()==nums.size())
            res.push_back(track);
        for(int i=0;i<nums.size();++i){
            //排除不合法的选择
	    if(visited[i])
                continue;
            track.push_back(nums[i]);
            visited[i]=true;
            backtrack(nums,visited,track);
            visited[i]=false;
            track.pop_back();
        }
    }
};
//
class Solution {
public:
    vector<vector<int>> res;
    vector<vector<int>> permute(vector<int>& nums) {
        solve(nums, 0);
        return res;
    }
    void solve(vector<int> &nums, int idx) {
        if (idx == nums.size() - 1 || nums.size() == 0) {
            res.push_back(nums);
            return;
        }
        for (int i = idx; i < nums.size(); i++) {
            swap(nums[idx], nums[i]);
            solve(nums, idx + 1);
            swap(nums[idx], nums[i]);
        }
    }
};
```

### 4.[permutations-ii](https://leetcode-cn.com/problems/permutations-ii/)

> 给定一个可包含重复数字的序列，返回所有不重复的全排列。

```c++
class Solution {
public:
    vector<vector<int>>res;
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        if(nums.size()==0)
            return {{}};
        vector<int>track;
        vector<bool>visited(nums.size(),false);
        sort(nums.begin(),nums.end());
        backtrack(nums,visited,track);
        return res;        
    }
    void backtrack(vector<int>&nums,vector<bool>& visited,vector<int>track){
        if(track.size()==nums.size())
        {
            res.push_back(track);
            return;
        }
        for(int i=0;i<nums.size();++i){
		//剪枝
            if(visited[i]==true)
                continue;
            if(i>0&&visited[i-1]==false&&nums[i]==nums[i-1])
                continue;
            track.push_back(nums[i]);
            visited[i]=true;
            backtrack(nums,visited,track);
            visited[i]=false;
            track.pop_back();
        }

    }
};
```
### 5.[combinations](https://leetcode-cn.com/problems/combinations/)

> 给定两个整数 n 和 k，返回 1 ... n 中所有可能的 k 个数的组合。

```c++
vector<vector<int>>res;

vector<vector<int>> combine(int n, int k) {
    if (k <= 0 || n <= 0) return res;
    vector<int> track;
    backtrack(n, k, 1, track);
    return res;
}

void backtrack(int n, int k, int start, vector<int>& track) {
    // 到达树的底部
    if (k == track.size()) {
        res.push_back(track);
        return;
    }
    // 注意 i 从 start 开始递增
    for (int i = start; i <= n; i++) {
        // 做选择
        track.push_back(i);
        backtrack(n, k, i + 1, track);
        // 撤销选择
        track.pop_back();
    }
}

```
```c
回溯模板依然没有变，但是根据排列问题和组合问题画出的树来看，排列问题的树比较对称，而组合问题的树越靠右节点越少。

在代码中的体现就是，排列问题每次通过 visited 方法来排除在 track 中已经选择过的数字；而组合问题通过传入一个 start 参数，来排除 start 索引之前的数字。

以上，就是排列组合和子集三个问题的解法，总结一下：

子集问题可以利用数学归纳思想，假设已知一个规模较小的问题的结果，思考如何推导出原问题的结果。也可以用回溯算法，要用 start 参数排除已选择的数字。

组合问题利用的是回溯思想，结果可以表示成树结构，我们只要套用回溯算法模板即可，关键点在于要用一个 start 排除已经选择过的数字。

排列问题是回溯思想，也可以表示成树结构套用算法模板，关键点在于使用 contains 方法排除已经选择的数字，前文有详细分析，这里主要是和组合问题作对比。

记住这几种树的形状，就足以应对大部分回溯算法问题了，无非就是 start 或者visited剪枝，也没啥别的技巧了。
```

链接：https://leetcode-cn.com/problems/subsets/solution/hui-su-si-xiang-tuan-mie-pai-lie-zu-he-zi-ji-wen-t/
## 练习

- [ ] [subsets](https://leetcode-cn.com/problems/subsets/)
- [ ] [subsets-ii](https://leetcode-cn.com/problems/subsets-ii/)
- [ ] [permutations](https://leetcode-cn.com/problems/permutations/)
- [ ] [permutations-ii](https://leetcode-cn.com/problems/permutations-ii/)

挑战题目

- [ ] [combination-sum](https://leetcode-cn.com/problems/combination-sum/)
- [ ] [letter-combinations-of-a-phone-number](https://leetcode-cn.com/problems/letter-combinations-of-a-phone-number/)
- [ ] [palindrome-partitioning](https://leetcode-cn.com/problems/palindrome-partitioning/)
- [ ] [restore-ip-addresses](https://leetcode-cn.com/problems/restore-ip-addresses/)
- [ ] [permutations](https://leetcode-cn.com/problems/permutations/)
