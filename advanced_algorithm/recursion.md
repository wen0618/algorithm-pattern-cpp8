# 递归

## 介绍

ori:将大问题转化为小问题，通过递归依次解决各个小问题

-> note bye wen://递归是一种具体的方法（methon），而不是一种思想（idea），一个idea可以用递归实现，也可以用迭代等方法实现。

-> //递归的特点是在函数内部代码中，调用这个函数本身。主要有base case 和recursive case两部分组成；

-> //循环效率可能更高，递归可能更能理解；
## 示例

[reverse-string](https://leetcode-cn.com/problems/reverse-string/)

> 编写一个函数，其作用是将输入的字符串反转过来。输入字符串以字符数组  `char[]`  的形式给出。

```c++
class Solution {
public:
    void reverse(vector<char> &s, int l, int r)
    {
        if(l>=r){
            return;
        }
        char temp = s[l];
        s[l] = s[r];
        s[r] = temp;
        l++;
        r--;
        reverse(s,l,r);
    }
    void reverseString(vector<char>& s) {
        reverse(s,0,s.size()-1);
    }
};//o(n),o(n)
循环;
class Solution {
public:
    void reverseString(vector<char>& s) {
        int begin=0,end=s.size()-1;
        while(begin<end)
        {
            char temp=s[begin];
            s[begin]=s[end];
            s[end]=temp;
            begin++,end--;
        }
        return;
    }
};//o(n),o(1)

////ori:
func reverseString(s []byte) {
	res := make([]byte, 0)
	reverse(s, 0, &res)
	for i := 0; i < len(s); i++ {
		s[i] = res[i]
	}
}
func reverse(s []byte, i int, res *[]byte) {
	if i == len(s) {
		return
	}
	reverse(s, i+1, res)
	*res = append(*res, s[i])
}
```

[swap-nodes-in-pairs](https://leetcode-cn.com/problems/swap-nodes-in-pairs/)

> 给定一个链表，两两交换其中相邻的节点，并返回交换后的链表。
> **你不能只是单纯的改变节点内部的值**，而是需要实际的进行节点交换。

```c++
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        //base case-递归出口
        if(head==nullptr||head->next==nullptr)
            return head;
        //recursive case
        // Nodes to be swapped
        ListNode* fristNode=head;
        ListNode* secondNode=head->next;
        //swapping
        fristNode->next=swapPairs(secondNode->next);
        secondNode->next=fristNode;
        // Now the head is the second node
        return secondNode;
        
    }
};
```
```c++
//循环
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        if(head==nullptr||head->next==nullptr)
            return head;
        // Dummy node acts as the prevNode for the head node
        // of the list and hence stores pointer to the head node.
        ListNode dummy(-1);
        dummy.next=head;
        ListNode* preNode=&dummy;
        while(head&&head->next)
        {
            // Nodes to be swapped
            ListNode* fistNode=head;
            ListNode* secondNode=head->next;
            //swapping
            preNode->next=secondNode;
            fistNode->next=secondNode->next;
            secondNode->next=fistNode;
            // Reinitializing the head and prevNode for next swap
            preNode=fistNode;
            head=fistNode->next;
        }
        // Return the new head node.
        return dummy.next;
        
    }
};
```

[unique-binary-search-trees-ii](https://leetcode-cn.com/problems/unique-binary-search-trees-ii/)

> 给定一个整数 n，生成所有由 1 ... n 为节点所组成的二叉搜索树。

```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
 //二叉搜索树关键的性质是根节点的值大于左子树所有节点的值，小于右子树所有节点的值，且左子树和右子树也同样为二叉搜索树。因此在生成所有可行的二叉搜索树的时候，假设当前序列长度为n，如果我们枚举根节点的值为 i，那么根据二叉搜索树的性质我们可以知道左子树的节点值的集合为 [1…i−1]，右子树的节点值的集合为[i+1…n]。而左子树和右子树的生成相较于原问题是一个序列长度缩小的子问题，因此我们可以想到用递归的方法来解决这道题目。
class Solution {
public:
    vector<TreeNode*> generateTrees(int n) {
        if(n==0)
            return {};
        return generate(1,n);        
    }
    vector<TreeNode*> generate(int start,int end)
    {
        if(start>end)
            return {nullptr};
        vector<TreeNode*>ans;
	 // 枚举可行根节点
        for(int i=start;i<=end;++i)
        {
            // 获得所有可行的左子树集合
            vector<TreeNode*>left=generate(start,i-1);
            vector<TreeNode*>right=generate(i+1,end);
        // 从左子树集合中选出一棵左子树，从右子树集合中选出一棵右子树，拼接到根节点上
            for(int j=0;j<left.size();j++){
                for(int k=0;k<right.size();++k){
                    TreeNode* root=new TreeNode(i);
                    root->left=left[j];
                    root->right=right[k];
                    ans.push_back(root);
                }
            }
        }
        return ans;
    }
};
//
 //首先BST的左边到右边数字递增。参考很常见的一个思路，1到n依次作为root，root的左边和右边生成以同样的方法递归生成subTree。
//值得注意的是：
//1.用for循环遍历拼接subTree
//2.如何拼接树
//3.考虑n=0
class Solution {
public:
    vector<TreeNode*> generateTrees(int n) {
        vector<TreeNode*> ans;
        if(n==0) return ans;
        return dfs(1,n);
    }
    vector<TreeNode*> dfs(int start,int end){
        vector<TreeNode*> ans;
        if(start>end) return {NULL};
        for(int i=start;i<=end;i++){
            
            vector<TreeNode*> left=dfs(start,i-1);
            vector<TreeNode*> right=dfs(i+1,end);
            for(auto root_left:left){
                for(auto root_right:right){
                    TreeNode* root=new TreeNode(i);
                    root->left=root_left;
                    root->right=root_right;
                    ans.push_back(root);
 
                }
            }

        }
        return ans;
```

## 递归+备忘录(记忆化缓存Memorization）

[fibonacci-number](https://leetcode-cn.com/problems/fibonacci-number/)

> 斐波那契数，通常用  F(n) 表示，形成的序列称为斐波那契数列。该数列由  0 和 1 开始，后面的每一项数字都是前面两项数字的和。也就是：
> F(0) = 0,   F(1) = 1
> F(N) = F(N - 1) + F(N - 2), 其中 N > 1.
> 给定  N，计算  F(N)。

```C++
0.recursion:
class Solution {
public:
    int fib(int N) {
        if(N<2)
            return N;
        return fib(N-1)+fib(N-2);

    }
};
//1.记忆化+dfs top down
class Solution {
public:
    int fibm(vector<int>&memo,int N)
    {
        
        if(memo[N]==0&&N>=2)
            memo[N]=fibm(memo,N-1)+fibm(memo,N-2);
        return memo[N];
    }
    int fib(int N) {
        if(N<2)
            return N;
        vector<int>memo(N+1);
        memo[0]=0;memo[1]=1;
        return fibm(memo,N);
    }
    
};
///ori
func fib(N int) int {
    return dfs(N)
}
var m map[int]int=make(map[int]int)
func dfs(n int)int{
    if n < 2{
        return n
    }
    // 读取缓存
    if m[n]!=0{
        return m[n]
    }
    ans:=dfs(n-2)+dfs(n-1)
    // 缓存已经计算过的值
    m[n]=ans
    return ans
}
```

## 练习

- [ ] [reverse-string](https://leetcode-cn.com/problems/reverse-string/)
- [ ] [swap-nodes-in-pairs](https://leetcode-cn.com/problems/swap-nodes-in-pairs/)
- [ ] [unique-binary-search-trees-ii](https://leetcode-cn.com/problems/unique-binary-search-trees-ii/)
- [ ] [fibonacci-number](https://leetcode-cn.com/problems/fibonacci-number/)
