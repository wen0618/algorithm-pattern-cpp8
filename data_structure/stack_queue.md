# 栈和队列

## Stack 栈

1.[min-stack](https://leetcode-cn.com/problems/min-stack/)

思路：用两个栈实现，一个最小栈始终保证最小值在顶部

```C++
class MinStack {
public:
    /** initialize your data structure here. */
    stack<int> sta;
    stack<int> minsta;
    MinStack() 
    {
        
    }
    
    void push(int x) 
    {
        sta.push(x);
        if(minsta.empty())
        {
            minsta.push(x);
        }
        else
        {
            if(x < minsta.top())
                minsta.push(x);
            else
                minsta.push(minsta.top());
        }
    }
    
    void pop() 
    {
        if(sta.empty() || minsta.empty())
            return;
        sta.pop();
        minsta.pop();
    }
    
    int top() 
    {
        return sta.top();
    }
    
    int getMin() 
    {
        return minsta.top();
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(x);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */
```

2.[evaluate-reverse-polish-notation](https://leetcode-cn.com/problems/evaluate-reverse-polish-notation/)

> **波兰表达式计算** > **输入:** ["2", "1", "+", "3", "*"] > **输出:** 9
> **解释:** ((2 + 1) \* 3) = 9

思路：适合用栈操作运算：遇到数字则入栈；遇到算符则取出栈顶两个数字进行计算，并将结果压入栈中。

```c++
class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        stack<int> sta;
        for (auto &t : tokens)
            if (t == "+" || t == "-" || t == "*" || t == "/")
            {
                if(sta.size()<2)
                    return -1;
                int a = sta.top();
                sta.pop();
                int b = sta.top();
                sta.pop();
                if (t == "+") sta.push(a + b);
                else if (t == "-") sta.push(b - a);
                else if (t == "*") sta.push(a * b);
                else sta.push(b / a);
            }
            //else sta.push(atoi(t.c_str()));
            else sta.push(stoi(t));
        return sta.top();
    }
};
```

3.[decode-string](https://leetcode-cn.com/problems/decode-string/)

> 给定一个经过编码的字符串，返回它解码后的字符串。
> s = "3[a]2[bc]", 返回 "aaabcbc".
> s = "3[a2[c]]", 返回 "accaccacc".
> s = "2[abc]3[cd]ef", 返回 "abcabccdcdcdef".

思路：题难点在于括号内嵌套括号，需要从内向外生成与拼接字符串，这与栈的先入后出特性对应,用栈去实现实质上是自己用栈去模拟递归的过程。

```c++
class Solution {
public:
    string decodeString(string s) {
        string res = "";
	//用栈来存储数字是为了适用于嵌套情况，去最近的数字作为倍数
        stack <int> nums;
        stack <string> strs;
        int num = 0;
        int len = s.size();
        for(int i = 0; i < len; ++ i)
        {
            if(s[i] >= '0' && s[i] <= '9')
            {
                num = num * 10 + s[i] - '0';
            }
            else if((s[i] >= 'a' && s[i] <= 'z') ||(s[i] >= 'A' && s[i] <= 'Z'))
            {
                res = res + s[i];
            }
            else if(s[i] == '[') //将‘[’前的数字压入nums栈内， 字母字符串压入strs栈内
            {
                nums.push(num);
                num = 0;
                strs.push(res); 
                res = "";
            }
            else //遇到‘]’时，操作与之相配的‘[’之间的字符，使用分配律
            {
                int times = nums.top();
                nums.pop();
                for(int j = 0; j < times; ++ j)
                    strs.top() += res;
                res = strs.top(); //之后若还是字母，就会直接加到res之后，因为它们是同一级的运算
                                  //若是左括号，res会被压入strs栈（上个else if)，作为上一层的运算
                strs.pop();
            }
        }
        return res;
    }
};

//链接：https://leetcode-cn.com/problems/decode-string/solution/ti-jie-czhan-by-youlookdeliciousc/
```
解法二:递归
递归解法（递归过程会重复扫描字符串，不推荐这种写法）：

```c++
string decodeString(string s) {
    int num = 0;
    string res;
    for (int i = 0; i < s.size(); i++) {
        if (isalpha(s[i])) {
            res.push_back(s[i]);
        } else if (isdigit(s[i])) {
            num = num * 10 + s[i] - '0';
        } else if (s[i] == '[') {
            int cnt = 0;
            i++;
            string innerS;
            while (s[i] != ']' || cnt != 0) {
                if (s[i] == '[') cnt++;
                else if (s[i] == ']') cnt--;
                innerS.push_back(s[i]);
                i++;
            }
            string innerRes = decodeString(innerS);
            while (num > 0) {
                res += innerRes;
                num--;
            }
        }
    }
    return res;
}
```
利用栈进行 DFS 递归搜索模板

```go
boolean DFS(int root, int target) {
    Set<Node> visited;
    Stack<Node> s;
    add root to s;
    while (s is not empty) {
        Node cur = the top element in s;
        return true if cur is target;
        for (Node next : the neighbors of cur) {
            if (next is not in visited) {
                add next to s;
                add next to visited;
            }
        }
        remove cur from s;
    }
    return false;
}
```

4.[binary-tree-inorder-traversal](https://leetcode-cn.com/problems/binary-tree-inorder-traversal/)
(同前）
> 给定一个二叉树，返回它的*中序*遍历。

```C++
// 思路：通过stack 保存已经访问的元素，用于原路返回
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        stack<TreeNode*> stk;
        vector<int> res;
        TreeNode* temp = root;
        while(temp != nullptr || !stk.empty()){
            while(temp != nullptr) {
                stk.push(temp);
                temp = temp -> left;// 一直向左
            } // 弹出
            temp = stk.top();
            stk.pop();
	        res.push_back(temp->val);
            temp = temp -> right;
        }
        return res;
    }
};
```

5.[clone-graph](https://leetcode-cn.com/problems/clone-graph/)

> 给你无向连通图中一个节点的引用，请你返回该图的深拷贝（克隆）。//深拷贝是指源对象与拷贝对象互相独立，其中任何一个对象的改动都不会对另外一个对象造成影响。
这道题就是遍历整个图，所以遍历时候要记录已经访问点，我们用一个字典记录。

所以，遍历方法就有两种。

思路一:DFS (深度遍历)

思路二:BFS (广度遍历)
```c++
/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> neighbors;
    
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};
*/
//BFS-queue
class Solution {
public:
     Node* cloneGraph(Node* node) {
        if (!node) return node;
        unordered_map<Node*, Node*> copies;
        copies[node] = new Node(node->val, {});
        queue<Node*> todo;
        todo.push(node);
        while (!todo.empty()) {
            Node* cur = todo.front();
            todo.pop();
            for (Node* neighbor : cur->neighbors) {
                if (copies.find(neighbor) == copies.end()) {
                    copies[neighbor] = new Node(neighbor->val, {});
                    todo.push(neighbor);        
                }
                copies[cur]->neighbors.push_back(copies[neighbor]);
            }
        }
        return copies[node];
    }
};

// dfs：recursive
    unordered_map<Node*, Node*> copies;
    Node* cloneGraph(Node* node) {
        if (!node) return node;
        if (copies.find(node) == copies.end()) {
            copies[node] = new Node(node->val, {});
            for (Node* neighbor : node->neighbors) {
                copies[node]->neighbors.push_back(cloneGraph(neighbor));
            }
        }
        return copies[node];
    }
};
```

6.[number-of-islands](https://leetcode-cn.com/problems/number-of-islands/)

> 给定一个由  '1'（陆地）和 '0'（水）组成的的二维网格，计算岛屿的数量。一个岛被水包围，并且它是通过水平方向或垂直方向上相邻的陆地连接而成的。你可以假设网格的四个边均被水包围。

！！//https://leetcode-cn.com/problems/number-of-islands/solution/dao-yu-lei-wen-ti-de-tong-yong-jie-fa-dfs-bian-li-/

思路：通过深度搜索遍历可能性（注意标记已访问元素）
DFS:深度优先遍历:
	遍历整个数组，遇到1，ans++，ans是记录岛的个数的
	运行一下dfs函数，把这个岛所有陆地给我沉喽，这个岛全部的1变成0(maybe 2 is better)
	等把grid全遍历完，grid就全是0了，再把ans输出，这个ans就是我们记录的岛的个数
	注意：grid竟然是char类型的，所有1和0都要加单引号
```c++

class Solution {
public:
    void findIsland(vector<vector<char>>& grid,int row,int col,int rowsize,int colsize)
                    {
                        if(row<0||row >= rowsize||col <0 || col >= colsize|| grid[row][col]=='0')
                        {
                            return;
                        }
                        else
                        {
                            grid[row][col] = '0';
                            findIsland(grid,row-1,col,rowsize,colsize);
                            findIsland(grid,row+1,col,rowsize,colsize);
                            findIsland(grid,row,col-1,rowsize,colsize);
                            findIsland(grid,row,col+1,rowsize,colsize);
                        }
                    }
    
    int numIslands(vector<vector<char>>& grid) {
        if(grid.empty()) return 0;
        
        int rowsize = grid.size();
        int colsize = grid[0].size();
        
        int i,j,res=0;
        for(i=0;i<rowsize;i++)
        {
            for(j=0;j<colsize;j++)
            {
                // cout<< grid[i][j] <<endl;
                if(grid[i][j]=='1')
                { 
                    res++;
                    findIsland(grid,i,j,rowsize,colsize);
                   
                }
            }
        }
        return res;
    }
};
```

**7.[largest-rectangle-in-histogram](https://leetcode-cn.com/problems/largest-rectangle-in-histogram/)

> 给定 _n_ 个非负整数，用来表示柱状图中各个柱子的高度。每个柱子彼此相邻，且宽度为 1 。
> 求在该柱状图中，能够勾勒出来的矩形的最大面积。

思路：1.暴力解法 o(n^2)
2.暴力解法的优化——单调栈！！（拓展：https://leetcode-cn.com/problems/largest-rectangle-in-histogram/solution/bao-li-jie-fa-zhan-by-liweiwei1419/）
求以当前柱子为高度的面积，即转化为寻找小于当前值的左右两边值
用栈保存小于当前值的左的元素


```c++
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

class Solution {
public:
    int largestRectangleArea(vector<int> &heights) {
        unsigned long size = heights.size();
        if (size == 1) {
            return heights[0];
        }
        int res = 0;
        stack<int> stk;
        for (int i = 0; i < size; ++i) {
            while (!stk.empty() && heights[stk.top()] > heights[i]) {
                int length = heights[stk.top()];
                stk.pop();
                int weight = i;
                if (!stk.empty()) {
                    weight = i - stk.top() - 1;
                }
                res = max(res, length * weight);
            }
            stk.push(i);
        }
        while (!stk.empty()) {
            int length = heights[stk.top()];
            stk.pop();
            int weight = size;
            if (!stk.empty()) {
                weight = size - stk.top() - 1;
            }
            res = max(res, length * weight);
        }
        return res;
    }
};
```

## Queue 队列

常用于 BFS 宽度优先搜索

8.[implement-queue-using-stacks](https://leetcode-cn.com/problems/implement-queue-using-stacks/)

> 使用栈实现队列

```c++
class MyQueue {
public:
   stack<int> inStack;
    stack<int> outStack;
    /** Initialize your data structure here. */
    MyQueue() {

    }
    
    /** Push element x to the back of queue. */
    void push(int x) {
        inStack.push(x);
    }
    
    /** Removes the element from in front of queue and returns that element. */
    int pop() {
         if(outStack.empty()){
            while(!inStack.empty()){
                outStack.push(inStack.top());
                inStack.pop();
            }
        }
        int a = outStack.top();
        outStack.pop();
        return a;
    }
    
    /** Get the front element. */
    int peek() {
         if(outStack.empty()){
            while(!inStack.empty()){
                outStack.push(inStack.top());
                inStack.pop();
            }
        }
        return outStack.top();
    }
    
    /** Returns whether the queue is empty. */
    bool empty() {
        return inStack.empty() && outStack.empty();
    }
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */
```

二叉树层次遍历（同前）
//omitted

**9.[01-matrix](https://leetcode-cn.com/problems/01-matrix/)

> 给定一个由 0 和 1 组成的矩阵，找出每个元素到最近的 0 的距离。
> 两个相邻元素间的距离为 1

>思路：1.dp
```c++
class Solution {
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& matrix) {
        int m = matrix.size(), n = matrix[0].size();
        // 初始化动态规划的数组，所有的距离值都设置为一个很大的数
        vector<vector<int>> dist(m, vector<int>(n, INT_MAX / 2));
        // 如果 (i, j) 的元素为 0，那么距离为 0
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (matrix[i][j] == 0) {
                    dist[i][j] = 0;
                }
            }
        }
        // 只有 水平向左移动 和 竖直向上移动，注意动态规划的计算顺序
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i - 1 >= 0) {
                    dist[i][j] = min(dist[i][j], dist[i - 1][j] + 1);
                }
                if (j - 1 >= 0) {
                    dist[i][j] = min(dist[i][j], dist[i][j - 1] + 1);
                }
            }
        }
        // 只有 水平向右移动 和 竖直向下移动，注意动态规划的计算顺序
        for (int i = m - 1; i >= 0; --i) {
            for (int j = n - 1; j >= 0; --j) {
                if (i + 1 < m) {
                    dist[i][j] = min(dist[i][j], dist[i + 1][j] + 1);
                }
                if (j + 1 < n) {
                    dist[i][j] = min(dist[i][j], dist[i][j + 1] + 1);
                }
            }
        }
        return dist;
    }
};
```
>2.多源广度优先搜索
```c++
// BFS 从0进队列，弹出之后计算上下左右的结果，将上下左右重新进队列进行二层操作
// 0 0 0 0
// 0 x 0 0
// x x x 0
// 0 x 0 0

// 0 0 0 0
// 0 1 0 0
// 1 x 1 0
// 0 1 0 0

// 0 0 0 0
// 0 1 0 0
// 1 2 1 0
// 0 1 0 0
class Solution {
private:
    static constexpr int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& matrix) {
        int m = matrix.size(), n = matrix[0].size();
        vector<vector<int>> dist(m, vector<int>(n));
        vector<vector<int>> seen(m, vector<int>(n));
        queue<pair<int, int>> q;
        // 将所有的 0 添加进初始队列中
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (matrix[i][j] == 0) {
                    q.emplace(i, j);
                    seen[i][j] = 1;
                }
            }
        }

        // 广度优先搜索
        while (!q.empty()) {
            auto [i, j] = q.front();
            q.pop();
            for (int d = 0; d < 4; ++d) {
                int ni = i + dirs[d][0];
                int nj = j + dirs[d][1];
                if (ni >= 0 && ni < m && nj >= 0 && nj < n && !seen[ni][nj]) {
                    dist[ni][nj] = dist[i][j] + 1;
                    q.emplace(ni, nj);
                    seen[ni][nj] = 1;
                }
            }
        }

    return dist;
    }
};
```

## 总结

- 熟悉栈的使用场景
  - 后出先出，保存临时值
  - 利用栈 DFS 深度搜索
- 熟悉队列的使用场景
  - 利用队列 BFS 广度搜索

## 练习

- [ ] [min-stack](https://leetcode-cn.com/problems/min-stack/)
- [ ] [evaluate-reverse-polish-notation](https://leetcode-cn.com/problems/evaluate-reverse-polish-notation/)
- [ ] [decode-string](https://leetcode-cn.com/problems/decode-string/)
- [ ] [binary-tree-inorder-traversal](https://leetcode-cn.com/problems/binary-tree-inorder-traversal/)
- [ ] [clone-graph](https://leetcode-cn.com/problems/clone-graph/)
- [ ] [number-of-islands](https://leetcode-cn.com/problems/number-of-islands/)
- [ ] [largest-rectangle-in-histogram](https://leetcode-cn.com/problems/largest-rectangle-in-histogram/)
- [ ] [implement-queue-using-stacks](https://leetcode-cn.com/problems/implement-queue-using-stacks/)
- [ ] [01-matrix](https://leetcode-cn.com/problems/01-matrix/)
