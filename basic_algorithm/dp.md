# 动态规划

## 背景

先从一道题目开始~

如题  [triangle](https://leetcode-cn.com/problems/triangle/)

> 给定一个三角形，找出自顶向下的最小路径和。每一步只能移动到下一行中相邻的结点上。

例如，给定三角形：

```text
[
     [2],
    [3,4],
   [6,5,7],
  [4,1,8,3]
]
```

自顶向下的最小路径和为  11（即，2 + 3 + 5 + 1 = 11）。

使用 DFS（遍历 或者 分治法）

遍历

![image.png](https://img.fuiboom.com/img/dp_triangle.png)
```c++
class Solution {
public:
    int best=INT_MAX;
    int minimumTotal(vector<vector<int>>& triangle) {
        if(triangle.size()==0||triangle[0].size()==0)
             return 0;
        dfs(triangle,0,0,0);
        return best;
    }
    void dfs(vector<vector<int>>&triangle,int row,int col,int sum){
        if(row==triangle.size()){
            if(sum<best)
                best=sum;
            return;
        }
        dfs(triangle,row+1,col,sum+triangle[row][col]);
        dfs(triangle,row+1,col+1,sum+triangle[row][col]);
    }
};
//超时
```
递归分治法

![image.png](https://img.fuiboom.com/img/dp_dc.png)

若定义f(i, j)为(i, j)点到底边的最小路径和，则易知递归求解式为:

f(i, j) = min(f(i + 1, j), f(i + 1, j + 1)) + triangle[i][j]

由此，我们将任一点到底边的最小路径和，转化成了与该点相邻两点到底边的最小路径和中的较小值，再加上该点本身的值。这样本题的递归解法就完成了。
```c++
class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        if(triangle.size()==0||triangle[0].size()==0)
            return 0;
        return dfs(triangle,0,0);
    }
    int dfs(vector<vector<int>>&triangle,int row,int col){
        if(row==triangle.size()){
            return 0;
        }
        return min(dfs(triangle,row+1,col),dfs(triangle,row+1,col+1))+triangle[row][col];
    }
};
//超时
```
优化 DFS，缓存已经被计算的值（称为：记忆化搜索 本质上：动态规划）--dp的自顶向下递归实现

![image.png](https://img.fuiboom.com/img/dp_memory_search.png)
```c++
class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        if(triangle.size()==0||triangle[0].size()==0)
            return 0;
        int rows=triangle.size();
        vector<vector<int>>memo(rows,vector<int>(rows,-1));
        return dfs(triangle,0,0,memo);
    }
    int dfs(vector<vector<int>>&triangle,int i,int j,vector<vector<int>>&memo){
        if(i==triangle.size())
            return 0;
        if(memo[i][j]!=-1)
            return memo[i][j];
        memo[i][j]=min(dfs(triangle,i+1,j+1,memo),dfs(triangle,i+1,j,memo))+triangle[i][j];
        return memo[i][j];
    }
};
```
动态规划就是把大问题变成小问题，并解决了小问题重复计算的方法称为动态规划

动态规划和 DFS 区别

- 二叉树 子问题是没有交集，所以大部分二叉树都用递归或者分治法，即 DFS，就可以解决
- 像 triangle 这种是有重复走的情况，**子问题是有交集**，所以可以用动态规划来解决

动态规划，自底向上bottom-up/table-fill迭代:dp[i][j] 表示从i,j出发，到达最后一层的最短路径

```c++
class Solution {
public:
    int best=INT_MAX;
    int minimumTotal(vector<vector<int>>& triangle) {
        if(triangle.size()==0||triangle[0].size()==0)
            return 0;
        int n=triangle.size();
        //1、状态定义：dp[i][j] 表示从i,j出发，到达最后一层的最短路径
        // 2、初始化
        //why+1:// 最底行各节点的最小路径和为节点值本身,用来在递推中之直接初始化最后一行
        vector<vector<int>>dp(n+1,vector<int>(n+1,0));
        // 3、递推求解
        for(int i=n-1;i>=0;--i){
            for(int j=0;j<=i;++j){
                 // (i,j)只能由(i+1,j)和(i+1,j+1)两个已被有效填充的节点倒推
                dp[i][j]=min(dp[i+1][j],dp[i+1][j+1])+triangle[i][j];
            }
        }
        // 4、答案
        return dp[0][0];
    }
};
//空间优化：计算dp[i][j]时，只用到了下一行的dp[i + 1][j]和 dp[i + 1][j + 1]。因此 dp数组不需要定义N行，只要定义1行。修改一下上述代码，将i所在的维度去掉，就可以将 O(N^2)的空间复杂度优化成 O(N) 
//链接：https://leetcode-cn.com/problems/triangle/solution/di-gui-ji-yi-hua-dp-bi-xu-miao-dong-by-sweetiee/
class Solution {
public:
    int best=INT_MAX;
    int minimumTotal(vector<vector<int>>& triangle) {
        if(triangle.size()==0||triangle[0].size()==0)
            return 0;
        int n=triangle.size();
        vector<int>dp(n+1,0);
        for(int i=n-1;i>=0;--i){
            for(int j=0;j<=i;++j){
                dp[j]=min(dp[j],dp[j+1])+triangle[i][j];
            }
        }
        return dp[0];
    }
};
```

动态规划，自顶向下top-down:dp[i][j]定义为从0，0出发，到达i，j的最短路径

```c++
class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        if(triangle.size()==0||triangle[0].size()==0)
            return 0;
        int n=triangle.size();
        //1.状态定义：dp[i][j]定义为从0，0出发，到达i，j的最短路径
        vector<vector<int>>dp(n,vector<int>(n));
        //2.初始化
        dp[0][0]=triangle[0][0];
        //3.递归求解，状态转移方程为dp[i][j]=min(dp[i−1][j−1],dp[i−1][j])+c[i][j]
        for(int i=1;i<n;++i)
        {
            //共分三种情况：
            //当j=0时，dp[i-1][j-1]没有意义，因此状态转移方程为：
            dp[i][0]=dp[i-1][0]+triangle[i][0];
            //中间点：
            for(int j=1;j<i;++j)
            {
                dp[i][j]=min(dp[i-1][j-1],dp[i-1][j])+triangle[i][j];
            }
            //当j=i时，dp[i-1][j]没有意义，因此状态转移方程为：
            dp[i][i]=dp[i-1][i-1]+triangle[i][i];
        }
        //4.找最后一行的最小值即为题解  
        int res=dp[n-1][0];
        for(int k=1;k<n;++k){
            if(dp[n-1][k]<res)
                res=dp[n-1][k];
        }
        return res;
    }
};
```

## 递归和动规关系

递归是一种程序的实现方式：函数的自我调用

```go
Function(x) {
	...
	Funciton(x-1);
	...
}
```

动态规划：是一种解决问 题的思想，大规模问题的结果，是由小规模问 题的结果运算得来的。动态规划可用递归来实现(Memorization Search)

## 使用场景

满足两个条件

- 满足以下条件之一
  - 求最大/最小值（Maximum/Minimum ）
  - 求是否可行（Yes/No ）
  - 求可行个数（Count(\*) ）
- 满足不能排序或者交换（Can not sort / swap ）

如题：[longest-consecutive-sequence](https://leetcode-cn.com/problems/longest-consecutive-sequence/)  位置可以交换，所以不用动态规划

## 四点要素

1. **状态 State**
   - 灵感，创造力，存储小规模问题的结果:1.dp[i][j]表示从起点走到 i,j 的最短路径;2.dp[i][j] 表示从i,j出发，到达终点的最短路径
2. 方程 Function
   - 状态之间的联系，怎么通过小的状态，来算大的状态
3. 初始化 Intialization
   - 最极限的小状态是什么, 起点
4. 答案 Answer
   - 最大的那个状态是什么，终点

## 常见四种类型

1. Matrix DP (10%)
1. Sequence (40%)
1. Two Sequences DP (40%)
1. Backpack (10%)

> 注意点
>
> - 贪心算法大多题目靠背答案，所以如果能用动态规划就尽量用动规，不用贪心算法

## 1、矩阵类型（10%）

### [minimum-path-sum](https://leetcode-cn.com/problems/minimum-path-sum/)

> 给定一个包含非负整数的  *m* x *n*  网格，请找出一条从左上角到右下角的路径，使得路径上的数字总和为最小。

思路：1.动态规划-top-down:dp[i][j]从起点走到 i,j 的最短路径
1、state: f[x][y]从起点走到 x,y 的最短路径
2、function: f[x][y] = min(f[x-1][y], f[x][y-1]) + A[x][y]
3、intialize: f[0][0] = A[0][0]、f[i][0] = sum(0,0 -> i,0)、 f[0][i] = sum(0,0 -> 0,i)
4、answer: f[n-1][m-1]

```c++
class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        if(grid.size()==0||grid[0].size()==0)
            return 0;
        int m=grid.size(),n=grid[0].size();
        vector<vector<int>>dp(m,vector<int>(n,-1));
        dp[0][0]=grid[0][0];
        for(int k=1;k<n;++k)
            dp[0][k]=dp[0][k-1]+grid[0][k];
        for(int l=1;l<m;++l)
            dp[l][0]=dp[l-1][0]+grid[l][0];
        for(int i=1;i<m;++i){
            for(int j=1;j<n;++j){
                dp[i][j]=min(dp[i-1][j],dp[i][j-1])+grid[i][j];
            }
        }
        return dp[m-1][n-1];        
    }
};
//复用原来的矩阵列表
class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        int row = grid.size();
        if(row == 0)return 0;
        int col = grid[0].size();
        if(col == 0)return 0;
        for(int i = 0; i < row; i++){
            for(int j = 0 ;j < col; j++){
                if( i == 0 &&j == 0)continue;
                if(i == 0){
                    grid[0][j] += grid[0][ j - 1];
                    continue;
                }
                if(j == 0){
                    grid[i][0] += grid[i - 1][0];
                    continue;
                }
                grid[i][j] = min(grid[i - 1][j],grid[i][j - 1]) + grid[i][j];
            }
        }
        return grid[row - 1][col - 1];
    }
};
//2.bottom-up: //dp[i][j]为从i，j出发到达终点的最短路径和
class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        if(grid.size()==0||grid[0].size()==0)
            return 0;
        int m=grid.size(),n=grid[0].size();
        //dp[i][j]为从i，j出发到达终点的最短路径和
        vector<vector<int>>dp(m,vector<int>(n,-1));
        dp[m-1][n-1]=grid[m-1][n-1];
        for(int k=m-2;k>=0;--k)
            dp[k][n-1]=dp[k+1][n-1]+grid[k][n-1];
        for(int l=n-2;l>=0;--l)
            dp[m-1][l]=dp[m-1][l+1]+grid[m-1][l];
        for(int i=m-2;i>=0;--i){
            for(int j=n-2;j>=0;--j){
                dp[i][j]=min(dp[i+1][j],dp[i][j+1])+grid[i][j];
            }
        }
        return dp[0][0];        
    }
};
```

### [unique-paths](https://leetcode-cn.com/problems/unique-paths/)

> 一个机器人位于一个 m x n 网格的左上角 （起始点在下图中标记为“Start” ）。
> 机器人每次只能向下或者向右移动一步。机器人试图达到网格的右下角（在下图中标记为“Finish”）。
> 问总共有多少条不同的路径？

```c++
class Solution {
public:
    int uniquePaths(int m, int n) {
        if(m<=0||n<=0)
            return 0;
        //dp[i][j]定义为从原点出发，到达i，j的路径个数和
        vector<vector<int>>dp(m,vector<int>(n,1));
        dp[0][0]=1;        
        for(int k=1;k<m;++k)
            dp[k][0]=dp[k-1][0];
        for(int l=1;l<n;++l)
            dp[0][l]=dp[0][l-1];    
        for(int i=1;i<m;++i){
            for(int j=1;j<n;++j){
                dp[i][j]=dp[i-1][j]+dp[i][j-1];
            }
        }
        return dp[m-1][n-1];
    }
};

//2:
class Solution {
public:
    int uniquePaths(int m, int n) {
        //dp[i][j]为从i，j出发到达终点的最短路径和
        vector<vector<int>>dp(m,vector<int>(n,-1));
        dp[m-1][n-1]=1;
        for(int k=m-2;k>=0;--k)
            dp[k][n-1]=dp[k+1][n-1];
        for(int l=n-2;l>=0;--l)
            dp[m-1][l]=dp[m-1][l+1];
        for(int i=m-2;i>=0;--i){
            for(int j=n-2;j>=0;--j){
                dp[i][j]=dp[i+1][j]+dp[i][j+1];
            }
        }
        return dp[0][0];        
        
    }
};
```

### [unique-paths-ii](https://leetcode-cn.com/problems/unique-paths-ii/)

> 一个机器人位于一个 m x n 网格的左上角 （起始点在下图中标记为“Start” ）。
> 机器人每次只能向下或者向右移动一步。机器人试图达到网格的右下角（在下图中标记为“Finish”）。
> 问总共有多少条不同的路径？
> 现在考虑网格中有障碍物。那么从左上角到右下角将会有多少条不同的路径？

```c++
class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int m=obstacleGrid.size(),n=obstacleGrid[0].size();
         if(m<=0||n<=0)
            return 0;
        //dp[i][j]定义为从原点出发，到达i，j的路径个数和
        vector<vector<int>>dp(m,vector<int>(n,0));
        if(obstacleGrid[0][0]==0)
            dp[0][0]=1;        
        for(int k=1;k<m;++k)
        {
            if(obstacleGrid[k][0]==0)
                dp[k][0]=dp[k-1][0];
        }
        for(int l=1;l<n;++l){
            if(obstacleGrid[0][l]==0)
                dp[0][l]=dp[0][l-1];
        }    
        for(int i=1;i<m;++i){
            for(int j=1;j<n;++j){
                if(obstacleGrid[i][j]==0)
                    dp[i][j]=dp[i-1][j]+dp[i][j-1];
            }
        }
        return dp[m-1][n-1];

    }
};
```

## 2、序列类型（40%）

### [climbing-stairs](https://leetcode-cn.com/problems/climbing-stairs/)

> 假设你正在爬楼梯。需要  *n*  阶你才能到达楼顶。

```c++
class Solution {
public:
    int climbStairs(int n) {
        if(n<=0)
            return 0;
        if(n<=2)
            return n;
        //dp[i]定义为跑到台阶i共有多少方法
        vector<int>dp(n+1,0);
        dp[1]=1;
        dp[2]=2;
        for(int i=3;i<=n;++i){
            dp[i]=dp[i-1]+dp[i-2];
        }
        return dp[n];

    }
};
```

### [jump-game](https://leetcode-cn.com/problems/jump-game/)

> 给定一个非负整数数组，你最初位于数组的第一个位置。
> 数组中的每个元素代表你在该位置可以跳跃的最大长度。
> 判断你是否能够到达最后一个位置。

```c++
//greedy
class Solution {
public:
    bool canJump(vector<int>& nums) {
        int n = nums.size();
        int rightmost = 0;
        for (int i = 0; i < n; ++i) {
            if (i <= rightmost) {
                rightmost = max(rightmost, i + nums[i]);
                if (rightmost >= n - 1) {
                    return true;
                }
            }
        }
        return false;
    }
}
//class Solution {
public:
    bool canJump(vector<int>& nums) {
        if(nums.empty())
            return true;
        int n=nums.size();
        //dp[i]代表索引i的位置能否到达
        vector<bool>dp(n,0);
        dp[0]=true;
        for(int i=1;i<n;++i){
            for(int j=0;j<i;++j)
            // 如果之前的j节点可达，并且从此节点可以到跳到i
                if(dp[j]==true&&nums[j]+j>=i)
                {
                    dp[i]=true;
                    break;
                }
        }
        return dp[n-1];

    }
};
//chao shi,****
```

### [jump-game-ii](https://leetcode-cn.com/problems/jump-game-ii/)

> 给定一个非负整数数组，你最初位于数组的第一个位置。
> 数组中的每个元素代表你在该位置可以跳跃的最大长度。
> 你的目标是使用最少的跳跃次数到达数组的最后一个位置。

```c++
//top-down(c++超时）
 // 状态：f[i] 表示从起点到当前位置最小次数
    // 推导：f[i] = f[j],a[j]+j >=i,min(f[j]+1)
    // 初始化：f[0] = 0
    // 结果：f[n-1]
class Solution {
public:
    int jump(vector<int>& nums) {
        if(nums.empty())
            return 0;
        //dp[i]表示从初始位置到索引i的最少跳跃次数
        vector<int>dp(nums.size(),0);
        dp[0]=0;
        for(int i=1;i<nums.size();++i){
            dp[i]=i;
            for(int j=0;j<i;++j){
                if(nums[j]+j>=i){
		// 取一个最小值+1
                    dp[i]=min(dp[i],dp[j]+1);
                }
            }
        }
        return dp[nums.size()-1];
    }
};
//greedy
class Solution {
//「贪心」地进行正向查找，每次找到可到达的最远位置，就可以在线性时间内得到最少的跳跃次数。
//在具体的实现中，我们维护当前能够到达的最大下标位置，记为边界。我们从左到右遍历数组，到达边界时，更新边界并将跳跃次数增加 1。
public:
    int jump(vector<int>& nums) {
        if(nums.empty())
            return 0;
        
        int maxpos=0,end=0,times=0;
        //在遍历数组时，我们不访问最后一个元素，这是因为在访问最后一个元素之前，我们的边界一定大于等于最后一个位置，否则就无法跳到最后一个位置了。
	//如果访问最后一个元素，在边界正好为最后一个位置的情况下，我们会增加一次「不必要的跳跃次数」，因此我们不必访问最后一个元素。
        for(int i=0;i<nums.size()-1;++i){
            if(maxpos>=i){
                maxpos=max(maxpos,nums[i]+i);
                if(i==end){
                    end=maxpos;
                    times++;
                }
            }
        }
        return times;
    }
};
```

### [palindrome-partitioning-ii](https://leetcode-cn.com/problems/palindrome-partitioning-ii/)

> 给定一个字符串 _s_，将 _s_ 分割成一些子串，使每个子串都是回文串。
> 返回符合要求的最少分割次数。

```c++
//超时
class Solution {
public:
    int minCut(string s) {
        if(s.size()<2)
            return 0;
	 //步骤 1：思考状态
        //dp[i]表示前缀子串 s[0:i] 分割成若干个回文子串所需要最小分割次数
	//步骤 2：思考状态转移方程
        //dp[i] = min([dp[j] + 1 for j in range(i) if s[j + 1, i] 是回文])
        vector<int>dp(s.size());
	//步骤 3：思考初始状态
        //初始状态：单个字符一定是回文串，因此 dp[0] = 0。
        dp[0]=0;
        for(int i=1;i<s.size();++i){
            dp[i]=i;
	    //如果 s[0:i] 本身就是一个回文串，那么不用分割，即 dp[i] = 0 ，这是首先可以判断的，否则就需要去遍历；
            if(ispalindrome(s,0,i)){
                dp[i]=0;
                continue;
            }
            // 当 j == i 成立的时候，s[i] 就一个字符，一定是回文
            // 因此，枚举到 i - 1 即可
            for(int j=0;j<i;++j){
                if(ispalindrome(s,j+1,i)){
                    dp[i]=min(dp[i],dp[j]+1);
                }
            }
        }
	//步骤 4：思考输出
//状态转移方程可以得到，并且状态就是题目问的，因此返回最后一个状态即可，即 dp[len - 1]。
        return dp[s.size()-1];
    }
//步骤 5：思考是否可以优化空间
//每一个状态值都与之前的状态值有关，因此不能优化空间。
    bool ispalindrome(string s,int i,int j){
        while(i<j){
            if(s[i]!=s[j])
                return false;
            ++i;--j;
        }
        return true;
    }
};
```

注意点

- 判断回文字符串时，可以提前用动态规划算好，减少时间复杂度

### [longest-increasing-subsequence](https://leetcode-cn.com/problems/longest-increasing-subsequence/)

> 给定一个无序的整数数组，找到其中最长上升子序列的长度。

```c++
//dp:定义 dp[i]为考虑前i个元素，以第i个数字结尾的最长上升子序列的长度，注意 nums[i] 必须被选取,否则为1。
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int n=(int)nums.size();
        if (n == 0) return 0;
        vector<int> dp(n, 0);
        for (int i = 0; i < n; ++i) {
            dp[i] = 1;
            for (int j = 0; j < i; ++j) {
                if (nums[j] < nums[i]) {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
        }
        return *max_element(dp.begin(), dp.end());
    }
};
//greedy：
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int len = 1, n = (int)nums.size();
        if (n == 0) return 0;
        vector<int> d(n + 1, 0);
        d[len] = nums[0];
        for (int i = 1; i < n; ++i) {
            if (nums[i] > d[len]) d[++len] = nums[i];
            else{
                int l = 1, r = len, pos = 0; // 如果找不到说明所有的数都比 nums[i] 大，此时要更新 d[1]，所以这里将 pos 设为 0
                while (l <= r) {
                    int mid = (l + r) >> 1;
                    if (d[mid] < nums[i]) {
                        pos = mid;
                        l = mid + 1;
                    }
                    else r = mid - 1;
                }
                d[pos + 1] = nums[i];
            }
        }
        return len;
    }
};
作者：LeetCode-Solution
链接：https://leetcode-cn.com/problems/longest-increasing-subsequence/solution/zui-chang-shang-sheng-zi-xu-lie-by-leetcode-soluti/
```

### [word-break](https://leetcode-cn.com/problems/word-break/)

> 给定一个**非空**字符串  *s*  和一个包含**非空**单词列表的字典  *wordDict*，判定  *s*  是否可以被空格拆分为一个或多个在字典中出现的单词。

```c++
//定义dp[i] 表示字符串s前 i 个字符组成的字符串 s[0..i-1]是否能被空格拆分成若干个字典中出现的单词。从前往后计算考虑转移方程，每次转移的时候我们需要枚举包含位置 i-1的最后一个单词，看它是否出现在字典中以及除去这部分的字符串是否合法即可
//dp[i] 表示前i个字符是否可以被切分
// dp[i] = dp[j] && s[j+1~i] in wordDict
// dp[0] = true
// return dp[len]

class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        auto wordDictSet = unordered_set <string> ();
	//用于剪枝
        int maxlen=0;
        for (auto word: wordDict) {
            maxlen=max(maxlen,(int)word.size());
            wordDictSet.insert(word);
            
        }

        auto dp = vector <bool> (s.size() + 1);
        dp[0] = true;
        for (int i = 1; i <= s.size(); ++i) {
            for (int j = 0; j < i; ++j) {
                if (dp[j] && i-j<=maxlen&&wordDictSet.find(s.substr(j, i - j)) != wordDictSet.end()) {
                    dp[i] = true;
                    break;
                }
            }
        }

        return dp[s.size()];
    }
};

```

小结

常见处理方式是给 0 位置占位，这样处理问题时一视同仁，初始化则在原来基础上 length+1，返回结果 f[n]

- 状态可以为前 i 个
- 初始化 length+1
- 取值 index=i-1
- 返回值：f[n]或者 f[m][n]

## Two Sequences DP（40%）

### [longest-common-subsequence](https://leetcode-cn.com/problems/longest-common-subsequence/)

> 给定两个字符串  text1 和  text2，返回这两个字符串的最长公共子序列。
> 一个字符串的   子序列   是指这样一个新的字符串：它是由原字符串在不改变字符的相对顺序的情况下删除某些字符（也可以不删除任何字符）后组成的新字符串。
> 例如，"ace" 是 "abcde" 的子序列，但 "aec" 不是 "abcde" 的子序列。两个字符串的「公共子序列」是这两个字符串所共同拥有的子序列。

```c++
    // dp[i][j] a前i个和b前j个字符最长公共子序列
    // dp[m+1][n+1]
    // # ' a d c e
    // ' 0 0 0 0 0
    // a 0 1 1 1 1
    // c 0 1 1 2 1
    //
//用两个指针 i 和 j 从后往前遍历 s1 和 s2，如果 s1[i]==s2[j]，那么这个字符一定在 lcs 中；否则的话，s1[i] 和 s2[j] 这两个字符至少有一个不在 lcs 中，需要丢弃一个。
    class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        if(text1.empty()||text2.empty())
            return 0;
        int m=text1.size(),n=text2.size();
        vector<vector<int>>dp(m+1,vector<int>(n+1,0));
        for(int i=1;i<=m;++i){
            for(int j=1;j<=n;++j){
	     // t1第i个元素（索引为i-1）和t2第j个元素相等取左上元素+1，否则取左或上的较大值
                if(text1[i-1]==text2[j-1])
                    dp[i][j]=dp[i-1][j-1]+1;
                else 
                    dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
            }
        }
        return dp[m][n];

    }
};
```

- 从 1 开始遍历到最大长度
- 索引需要减一

### [edit-distance](https://leetcode-cn.com/problems/edit-distance/)

> 给你两个单词  word1 和  word2，请你计算出将  word1  转换成  word2 所使用的最少操作数  
> 你可以对一个单词进行如下三种操作：
> 插入一个字符
> 删除一个字符
> 替换一个字符

思路：和上题很类似，相等则不需要操作，否则取删除、插入、替换最小操作次数的值+1

```c++

    // dp[i][j] 表示a字符串的前i个字符编辑为b字符串的前j个字符最少需要多少次操作
    // dp[i][j] = OR(dp[i-1][j-1]，a[i]==b[j],min(dp[i-1][j],dp[i][j-1],dp[i-1][j-1])+1)
class Solution {
public:
    int minDistance(string word1, string word2) {
       
        int m=word1.size(),n=word2.size();
        vector<vector<int>>dp(m+1,vector<int>(n+1,0));
        for(int k=0;k<=m;++k)
            dp[k][0]=k;
        for(int l=0;l<=n;++l)
            dp[0][l]=l;
        for(int i=1;i<=m;++i){
            for(int j=1;j<=n;++j){
	     // 相等则不需要操作
                if(word1[i-1]==word2[j-1])
                    dp[i][j]=dp[i-1][j-1];
                else 
		// 否则取删除、插入、替换最小操作次数的值+1
                    dp[i][j]=min(min(dp[i-1][j],dp[i][j-1]),dp[i-1][j-1])+1;
            }
        }
        return dp[m][n];

    }
};
```

说明

> 另外一种做法：MAXLEN(a,b)-LCS(a,b)

## 零钱和背包（10%）

### [coin-change](https://leetcode-cn.com/problems/coin-change/)

> 给定不同面额的硬币 coins 和一个总金额 amount。编写一个函数来计算可以凑成总金额所需的最少的硬币个数。如果没有任何一种硬币组合能组成总金额，返回  -1。

思路：和其他 DP 不太一样，i 表示钱或者容量

```c++
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        // 状态 dp[i]表示金额为i时，组成的最小硬币个数
        // 推导 dp[i]  = min(dp[i-1], dp[i-2], dp[i-5])+1, 前提 i-coins[j] > 0
        // 初始化为最大值 dp[i]=amount+1
        // 返回值 dp[n] or dp[n]>amount =>-1
        vector<int>dp(amount+1,amount+1);
        dp[0]=0;
        for(int i=1;i<=amount;++i){
            for(int j=0;j<coins.size();++j){
                if(i-coins[j]>=0){
                    dp[i]=min(dp[i],dp[i-coins[j]]+1);
                }
            }
        }
        if(dp[amount]>amount)
            return -1;
        return dp[amount];

    }
};
```

注意

> dp[i-a[j]] 决策 a[j]是否参与

### [backpack](https://www.lintcode.com/problem/backpack/description)

> 在 n 个物品中挑选若干物品装入背包，最多能装多满？假设背包的大小为 m，每个物品的大小为 A[i]

```c++
class Solution {
public:
    /**
     * @param m: An integer m denotes the size of a backpack
     * @param A: Given n items with size A[i]
     * @return: The maximum size
     */
    int backPack(int m, vector<int> &A) {
        // write your code here
        // dp[i][j] 用任意数量的前i种物品，是否能装j的大小
        // dp[i][j] =dp[i-1][j] || dp[i-1][j-a[i]] j>a[i]
       // dp[0][0]=true dp[...][0]=true(取0件）
       // dp[n][X]
        vector<vector<bool>>dp(A.size()+1,vector<bool>(m+1));
        dp[0][0]=true;
        for(int i=1;i<=A.size();++i){
            for(int j=0;j<=m;++j){
                dp[i][j]=dp[i-1][j];
                if(j-A[i-1]>=0&&dp[i-1][j-A[i-1]])
                    dp[i][j]=true;
            }
        }
        for(int k=m;k>=0;--k){
            if(dp[A.size()][k]==true)
                return k;
        }
        return 0;
        
    }
};

```

### [backpack-ii](https://www.lintcode.com/problem/backpack-ii/description)

> 有 `n` 个物品和一个大小为 `m` 的背包. 给定数组 `A` 表示每个物品的大小和数组 `V` 表示每个物品的价值.
> 问最多能装入背包的总价值是多大?

思路：dp[i][j] 前 i 个物品，装入 j 背包 最大价值

```c++
class Solution {
public:
    /**
     * @param m: An integer m denotes the size of a backpack
     * @param A: Given n items with size A[i]
     * @param V: Given n items with value V[i]
     * @return: The maximum value
     */
    int backPackII(int m, vector<int> &A, vector<int> &V) {
        // write your code here
         // dp[i][j] 用任意数量的前i种物品，装入背包为 j大小，价值最大
        // dp[i][j] =max(dp[i-1][j] , dp[i-1][j-a[i]]+v[i])  , j>a[i]  是否加入A[i]物品
       // dp[0][0]=0  dp[...][0]=0
       // dp[n][X]
        vector<vector<int>>dp(A.size()+1,vector<int>(m+1));
        dp[0][0]=0;
        for(int i=1;i<=A.size();++i){
            for(int j=0;j<=m;++j){
                dp[i][j]=dp[i-1][j];
                if(j-A[i-1]>=0)
                    dp[i][j]=max(dp[i-1][j],dp[i-1][j-A[i-1]]+V[i-1]);
            }
        }
        return dp[A.size()][m];
    }
};
```

## 练习

Matrix DP (10%)

- [ ] [triangle](https://leetcode-cn.com/problems/triangle/)
- [ ] [minimum-path-sum](https://leetcode-cn.com/problems/minimum-path-sum/)
- [ ] [unique-paths](https://leetcode-cn.com/problems/unique-paths/)
- [ ] [unique-paths-ii](https://leetcode-cn.com/problems/unique-paths-ii/)

Sequence (40%)

- [ ] [climbing-stairs](https://leetcode-cn.com/problems/climbing-stairs/)
- [ ] [jump-game](https://leetcode-cn.com/problems/jump-game/)
- [ ] [jump-game-ii](https://leetcode-cn.com/problems/jump-game-ii/)
- [ ] [palindrome-partitioning-ii](https://leetcode-cn.com/problems/palindrome-partitioning-ii/)
- [ ] [longest-increasing-subsequence](https://leetcode-cn.com/problems/longest-increasing-subsequence/)
- [ ] [word-break](https://leetcode-cn.com/problems/word-break/)

Two Sequences DP (40%)

- [ ] [longest-common-subsequence](https://leetcode-cn.com/problems/longest-common-subsequence/)
- [ ] [edit-distance](https://leetcode-cn.com/problems/edit-distance/)

Backpack & Coin Change (10%)

- [ ] [coin-change](https://leetcode-cn.com/problems/coin-change/)
- [ ] [backpack](https://www.lintcode.com/problem/backpack/description)
- [ ] [backpack-ii](https://www.lintcode.com/problem/backpack-ii/description)
