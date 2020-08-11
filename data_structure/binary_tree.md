
# 二叉树

## 知识点

### 二叉树遍历

**前序遍历**：**先访问根节点**，再前序遍历左子树，再前序遍历右子树
**中序遍历**：先中序遍历左子树，**再访问根节点**，再中序遍历右子树
**后序遍历**：先后序遍历左子树，再后序遍历右子树，**再访问根节点**

注意点

- 以根访问顺序决定是什么遍历
- 左子树都是优先右子树

#### 递归遍历
```c++
void preorderTraversal(TreeNode*root,vector<int>&res)
    {
    //end case
        if(root==nullptr)
            return;
	//root   
        res.push_back(root->val);
	//left child
        preorderTraversal(root->left,res);
	//right child
        preorderTraversal(root->right,res);
    }
```

```C++
 void inorderTraversal(TreeNode*root,vector<int>&res)
    {
        if(root==nullptr)
            return;
     	inorderTraversal(root->left,res);
        res.push_back(root->val);
        inorderTraversal(root->right,res);
    }
```

```C++
 void postorderTraversal(TreeNode*root,vector<int>&res)
    {
        if(root==nullptr)
            return;
     	postorderTraversal(root->left,res);
        postorderTraversal(root->right,res);
        res.push_back(root->val);
    }
```
#### 非递归遍历：利用栈模拟递归
```C++
class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
	if(root==nullptr)
		return {};
        stack<TreeNode*> stk;
        vector<int> res;
        TreeNode* temp = root;
        while(temp != nullptr || !stk.empty()){
            while(temp != nullptr) {
                res.push_back(temp -> val);
                stk.push(temp);
                temp = temp -> left;

            }
            temp = stk.top();
            stk.pop();
            temp = temp -> right; //！
        }
        return res;
    }
};

```
#### 中序非递归
```C++
// 思路：通过stack 保存已经访问的元素，用于原路返回
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
	if(root==nullptr)
		return {};
        stack<TreeNode*> stk;
        vector<int> res;
        TreeNode* temp = root;
        while(temp != nullptr || !stk.empty()){
            while(temp != nullptr) {
                stk.push(temp);
                temp = temp -> left;
            }
            temp = stk.top();
            stk.pop();
	    res.push_back(temp->val);
            temp = temp -> right; //！
        }
        return res;
    }
};
```
#### 后序非递归
```C++
// 通过lastVisit标识右子节点是否已经弹出

class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        if(root==nullptr)
            return {};
        vector<int>res;
        stack<TreeNode*>stk;
        TreeNode* temp=root;
        TreeNode* Lastvisited=nullptr;
        while(!stk.empty()||temp!=nullptr)
        {
            while(temp != nullptr) {
                stk.push(temp);
                temp = temp -> left;
            }
            temp = stk.top();
             //若右节点已经访问过或者没有右节点  则输出该节点值
            if(temp->right==nullptr||temp->right==Lastvisited)
            {
                stk.pop();
                res.push_back(temp->val);
                Lastvisited=temp;
                temp=nullptr;    //注意要置为空
            }
            else{
                temp=temp->right;
                Lastvisited=nullptr;
	        }
        }
        return res;
    }

};
```
注意点

- 核心就是：根节点必须在右节点弹出之后，再弹出

#### DFS 深度搜索-从上到下

```C++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
    vector<int> preorderTraversal(TreeNode* root) {
        if(root==nullptr)
            return {};
        vector<int>res;
        dfs(root,res);
        return res;
    }
    // V1：深度遍历，结果引用作为参数传入到函数内部
    void dfs(TreeNode*root,vector<int>&res)
    {
        if(root==nullptr)
            return;
        res.push_back(root->val);
        dfs(root->left,res);
        dfs(root->right,res);
    }
```

#### DFS 深度搜索-从下向上（分治法）

```C++
// V2：通过分治法遍历
class Solution {
public:
   vector<int> preorderTraversal(TreeNode* root) {
    if(root==nullptr)
		return {};
	vector<int>res;
	res=divideAndConquer(root);
    return res;
}

vector<int> divideAndConquer(TreeNode* root) {
    vector<int>res;
	if(root==nullptr)
		return res;
      // 分治(Divide)
    vector<int>left=divideAndConquer(root->left);
    vector<int>right=divideAndConquer(root->right);
      // 合并结果(Conquer)
    res.push_back(root->val);
    res.insert(res.end(),left.begin(),left.end());
    res.insert(res.end(),right.begin(),right.end());
    return res;
}
};
```
注意点：

> DFS 深度搜索（从上到下） 和分治法区别：前者一般将最终结果通过指针参数传入，后者一般递归返回结果最后合并

#### BFS 层次遍历

```C++
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        if(root==nullptr)
            return {};
        vector<vector<int>>res;
         vector<int>level;
        queue<TreeNode*>q;
        q.push(root);
        while(!q.empty())
        {
            int len=q.size();
            for(int i=0;i<len;++i)
            {
                TreeNode* temp=q.front();
                q.pop();
                level.push_back(temp->val);
                if(temp->left)
                    q.push(temp->left);
                if(temp->right)
                    q.push(temp->right);
            }
            res.push_back(level);
            level.clear();//记得清空！！
        }
        return res;
```

### 分治法应用

先分别处理局部，再合并结果

适用场景

- 快速排序
- 归并排序
- 二叉树相关问题

分治法模板

- 递归返回条件
- 分段处理
- 合并结果

```C++
ResultType traversal(TreeNode* root)
{
    if(root==nullptr){
    	//do something and return
	return {};
    }
    //Divide
    ResultType left=traversal(root->left);
    ResultType right=travelsal(root->right);
    //Conquer
    ResultTtper=Merge from left and rigth
    
    return result;
}

```

#### 典型示例(同上）

```C++
// V2：通过分治法遍历二叉树
vector<int> preorderTraversal(TreeNode* root) {
    if(root==nullptr)
		return {};
	vector<int>res;
	res=divideAndConquer(root);
    return res;
}
vector<int> divideAndConquer(TreeNode* root) {
    vector<int>res;
	if(root==nullptr)
		return res;
      // 分治(Divide)
    vector<int>left=divideAndConquer(root->left);
    vector<int>right=divideAndConquer(root->right);
      // 合并结果(Conquer)
    res.push_back(root->val);
    res.insert(res.end(),left.begin(),left.end());
    res.insert(res.end(),right.begin(),right.end());
    return res;
}
```

#### 归并排序  

```C++
class Solution {
    vector<int> temp;
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
        int mid = l+((r-l)>>1);
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

注意点

> 递归需要返回结果用于合并

#### 快速排序  
// 思路：把一个数组以主元pivot为界分为左右两段，左段小于pivot，右段大于pivot，类似分治法没有合并过程
```C++
class Solution {
public:
    vector<int> sortArray(vector<int>& nums) 
    {
        quickSort(nums, 0, nums.size() - 1);
        return nums;
    }
    // 原地交换，所以传入交换索引
    void quickSort(vector<int>&nums, int left, int right)
    {
        if(left >= right) return; 
	//随意设置一个主元
        int pivot = nums[left];
	//分区
        int i = left, j = right; //i为左侧边界， j为右侧边界
        while(i <= j)
        {
            while(i <= j && nums[i] <= pivot) ++i;
            while(i <= j && nums[j] >= pivot) --j;
            if(i <= j)
            {
                swap(nums[i], nums[j]);
            }
        }
	// 把中间的值换为用于比较的主元pivot
        nums[left] = nums[j];
        nums[j] =pivot;
	// 分治法：divide
        quickSort(nums, left, j - 1 );
        quickSort(nums, j + 1, right );
        //return;
    }
};

class Solution {
public:
	vector<int> sortArray(vector<int>& nums) {
		QuickSort(nums, 0, nums.size() - 1);
		return nums;
	}
	void QuickSort(vector<int>& nums, int l, int r) {
		if (l < r)
		{
			int mid = partition(nums, l, r);
			QuickSort(nums, l, mid - 1);//注意
			QuickSort(nums, mid + 1, r);//注意
		}
	}
	int partition(vector<int>& nums, int l, int r)//分割函数，返回主元下标
	{
	//pivot任意选取，此选择左边界
		int pivot = nums[l];
		int i = l + 1, j = r;
		while (true)
		{
			while (i <= j && nums[i] <= pivot) i++;//寻找比pivot大的元素
			while (i <= j && nums[j] >= pivot) j--;//寻找比pivot小的元素
			if(i>j) break;
			swap(nums[i], nums[j]);
		}
		//把arr[j]和主元交换
		swap(nums[j], nums[l]);
		return j;//为什么返回j而不是i，因为swap是先执行i++的while语句，如果和下面的替换顺序，则返回i
	}
};
```

注意点：

> 快排由于是原地交换所以没有合并过程
> 传入的索引是存在的索引（如：0、length-1 等），越界可能导致崩溃

常见题目示例

#### 1.maximum-depth-of-binary-tree

[maximum-depth-of-binary-tree](https://leetcode-cn.com/problems/maximum-depth-of-binary-tree/)

> 给定一个二叉树，找出其最大深度。

思路：分治法

```c++
class Solution {
public:
    int dfs(TreeNode* root)
    {
        if(root==nullptr)
            return 0;
	 // divide：分左右子树分别计算
        int left=dfs(root->left);
        int right=dfs(root->right);
	 // conquer：合并左右子树结果
        return (left>right)?(left+1):(right+1);
    }
    int maxDepth(TreeNode* root) {
        if(root==nullptr)
            return 0;
        return dfs(root); 
    }
};
```

#### balanced-binary-tree

[balanced-binary-tree](https://leetcode-cn.com/problems/balanced-binary-tree/)

> 给定一个二叉树，判断它是否是高度平衡的二叉树。
本题中，一棵高度平衡二叉树定义为：
一个二叉树每个节点 的左右两个子树的高度差的绝对值不超过1。

思路：分治法，左边平衡 && 右边平衡 && 左右两边高度 <= 1.
因为需要返回是否平衡及高度，要么返回两个数据，要么合并两个数据，
所以用-1 表示不平衡，>0 表示树高度（二义性：一个变量有两种含义）。
```c++
class Solution {
public:
    bool isBalanced(TreeNode* root) {
      int h = height(root);
	  return is_balance;
    }

private:
    int height(TreeNode* node) 
   {
	  if (!node) 
	    return 0;

	  int l = height(node->left);
	  int r = height(node->right);

	  if (abs(l - r) > 1)
		is_balance = false;
		
	  return std::max(l, r) + 1;
   }
   
   bool is_balance = true;
};
```
```go
func isBalanced(root *TreeNode) bool {
    if maxDepth(root) == -1 {
        return false
    }
    return true
}
func maxDepth(root *TreeNode) int {
    // check
    if root == nil {
        return 0
    }
    left := maxDepth(root.Left)
    right := maxDepth(root.Right)

    // 为什么返回-1呢？（变量具有二义性）
    if left == -1 || right == -1 || left-right > 1 || right-left > 1 {
        return -1
    }
    if left > right {
        return left + 1
    }
    return right + 1
}
```

注意

> 一般工程中，结果通过两个变量来返回，不建议用一个变量表示两种含义

#### binary-tree-maximum-path-sum

[binary-tree-maximum-path-sum](https://leetcode-cn.com/problems/binary-tree-maximum-path-sum/)

> 给定一个**非空**二叉树，返回其最大路径和。
//递归分治，首先，考虑实现一个简化的函数 maxGain(node)，该函数计算二叉树中的一个节点的最大贡献值，
具体而言，就是在以该节点为根节点的子树中寻找 **以该节点为起点的**一条路径，使得该路径上的节点值之和最大。
具体而言，该函数的计算如下:
	空节点的最大贡献值等于 0;
	非空节点的最大贡献值等于节点值与其子节点中的最大贡献值之和（对于叶节点而言，最大贡献值等于节点值）;
根据函数 maxGain 得到每个节点的最大贡献值之后，如何得到二叉树的最大路径和？对于二叉树中的一个节点，该节点的最大路径和取决于该节点的值与该节点的左右子节点的最大贡献值，
如果子节点的最大贡献值为正，则计入该节点的最大路径和，否则不计入该节点的最大路径和。维护一个全局变量 maxSum 存储最大路径和，在递归过程中更新 maxSum 的值，
最后得到的 maxSum 的值即为二叉树中的最大路径和。

```c++
class Solution {
private:
    int maxSum = INT_MIN;

public:
    int maxGain(TreeNode* node) {
        if (node == nullptr) {
            return 0;
        }
        
        // 递归计算左右子节点的最大贡献值
        // 只有在最大贡献值大于 0 时，才会选取对应子节点
        int leftGain = max(maxGain(node->left), 0);
        int rightGain = max(maxGain(node->right), 0);

        // 节点的最大路径和取决于该节点的值与该节点的左右子节点的最大贡献值
        int priceNewpath = node->val + leftGain + rightGain;

        // 更新答案
        maxSum = max(maxSum, priceNewpath);

        // 返回节点的最大贡献值
        return node->val + max(leftGain, rightGain);
    }

    int maxPathSum(TreeNode* root) {
        maxGain(root);
        return maxSum;
    }
};
```

思路：分治法，分为三种情况：左子树最大路径和最大，右子树最大路径和最大，左右子树最大加根节点最大，需要保存两个变量：一个保存子树最大路径和，一个保存左右加根节点和，然后比较这个两个变量选择最大值即可
```go
type ResultType struct {
    SinglePath int // 保存单边最大值
    MaxPath int // 保存最大值（单边或者两个单边+根的值）
}
func maxPathSum(root *TreeNode) int {
    result := helper(root)
    return result.MaxPath
}
func helper(root *TreeNode) ResultType {
    // check
    if root == nil {
        return ResultType{
            SinglePath: 0,
            MaxPath: -(1 << 31),
        }
    }
    // Divide
    left := helper(root.Left)
    right := helper(root.Right)

    // Conquer
    result := ResultType{}
    // 求单边最大值
    if left.SinglePath > right.SinglePath {
        result.SinglePath = max(left.SinglePath + root.Val, 0)
    } else {
        result.SinglePath = max(right.SinglePath + root.Val, 0)
    }
    // 求两边加根最大值
    maxPath := max(right.MaxPath, left.MaxPath)
    result.MaxPath = max(maxPath,left.SinglePath+right.SinglePath+root.Val)
    return result
}
func max(a,b int) int {
    if a > b {
        return a
    }
    return b
}
```

#### lowest-common-ancestor-of-a-binary-tree

[lowest-common-ancestor-of-a-binary-tree](https://leetcode-cn.com/problems/lowest-common-ancestor-of-a-binary-tree/)

> 给定一个二叉树, 找到该树中两个指定节点的最近公共祖先。

思路：分治法，有左子树的公共祖先或者有右子树的公共祖先，就返回子树的祖先，否则返回根节点
////此处： lowestCommonAncestor这个函数不要理解为找公共祖先，而就理解为帮两个节点找祖先 传入的值是root, p, q，帮p和q找到一个祖先就行，找到两个就更好了，如果找不到就返回NULL 在root->left里/面找一次，root->right里面再找一次，如果某一边返回值是NULL， 那么说明两个值都在另一边 由于找的时候，一定是找的最近的祖先返回，所以这里直接返回前面的返回值就行了，可以保证是最近的公共祖先 如果左右的返回值都不是NULL，那说明p和q分别在两边，则当前节点就是最近公共祖先 左右都找不到就直接返回NULL////

```c++
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        //check
         if (root == nullptr || p == nullptr || q == nullptr)
            return nullptr;
        //相等，表示 root节点的子树中包含 p节点或 q节点,直接返回root节点即可
        if(root==p||root==q)
            return root;
	    
        //Devide
	//因为是递归，使用函数后可认为左右子树已经算出结果，这句话要记住，道出了递归的精髓!
        TreeNode* left=lowestCommonAncestor(root->left,p,q);
        TreeNode* right=lowestCommonAncestor(root->right,p,q);
        
	//conquer
        //两边都不为空，p和q在两侧，则根节点为祖先
        if(left!=nullptr&&right!=nullptr)
            return root;
        if(left!=nullptr)
            return left;
        if(right!=nullptr)
            return right;
        
	// 必须有返回值
        return nullptr;
        
    }
};
```

### BFS 层次应用(同上）

#### binary-tree-level-order-traversal

[binary-tree-level-order-traversal](https://leetcode-cn.com/problems/binary-tree-level-order-traversal/)

> 给你一个二叉树，请你返回其按  **层序遍历**  得到的节点值。 （即逐层地，从左到右访问所有节点）

思路：用一个队列记录一层的元素，然后扫描这一层元素添加下一层元素到队列（一个数进去出来一次，所以复杂度 O(logN)）

```C++
//略
```

#### binary-tree-level-order-traversal-ii

[binary-tree-level-order-traversal-ii](https://leetcode-cn.com/problems/binary-tree-level-order-traversal-ii/)

> 给定一个二叉树，返回其节点值自底向上的层次遍历。 （即按从叶子节点所在层到根节点所在的层，逐层从左向右遍历）

思路：在层级遍历的基础上，翻转一下结果即可

```C++
class Solution {
public:
/*BFS*/
    vector<vector<int>> levelOrderBottom(TreeNode* root) 
    {
        vector<vector<int>> res;
        if(!root)
            return res;
        stack<vector<int>> sta;
        queue<TreeNode*> qu;
        qu.push(root);
        while(!qu.empty())
        {
            int size=qu.size();
            vector<int> tmp;
            for(int i=0;i<size;i++)
            {
                TreeNode* node=qu.front();
                tmp.push_back(node->val);
                qu.pop();

                if(node->left)
                    qu.push(node->left);
                if(node->right)
                    qu.push(node->right);
            }
            sta.push(tmp);
        }
	//此处用栈反转，也可以用reverse（res.begin(),res.end())算法函数反转；
        while(!sta.empty())
        {
            res.push_back(sta.top());
            sta.pop();
        }
        return res;

        
    }
};
```

#### binary-tree-zigzag-level-order-traversal

[binary-tree-zigzag-level-order-traversal](https://leetcode-cn.com/problems/binary-tree-zigzag-level-order-traversal/)

> 给定一个二叉树，返回其节点值的锯齿形层次遍历。Z 字形遍历
//加一个flag记录层序即可
```c++
class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        if(root==nullptr)
            return{};
        vector<vector<int>>res;
        vector<int>level;
        bool ordered=true;
        int nums=0;
        queue<TreeNode*>q;
        q.push(root);
        while(!q.empty())
        {
            nums=q.size();
            for(int i=0;i<nums;++i)
            {
                TreeNode* pNode=q.front();
                level.push_back(pNode->val);
                if(pNode->left) q.push(pNode->left);
                if(pNode->right) q.push(pNode->right);
                q.pop();
            }
            if(!ordered)
                reverse(level.begin(),level.end());
            res.push_back(level);
            ordered=!ordered;
            level.clear();
        }
        return res;
        
    }
};
```

### 二叉搜索树应用

#### validate-binary-search-tree

[validate-binary-search-tree](https://leetcode-cn.com/problems/validate-binary-search-tree/)

> 给定一个二叉树，判断其是否是一个有效的二叉搜索树。

思路 1：中序遍历，检查结果列表是否已经有序
二叉搜索树「中序遍历」得到的值构成的序列一定是升序的
思路 2：分治法，判断左 MAX < 根 < 右 MIN

```c++
// v1 dfs inordertravel
class Solution {
public:
    long pre = LONG_MIN;
    bool isValidBST(TreeNode* root) {
        //end case
	if(!root) return true;
	//left child case // 访问左子树
        if(!isValidBST(root->left)) return false;
	//root case/ 访问当前节点：如果当前节点小于等于中序遍历的前一个节点，说明不满足BST，返回 false；否则继续遍历
        if(root->val <= pre) return false;

        pre = root->val;
	//right childe case // 访问右子树
        return isValidBST(root->right);
    }
};
```

要解决这道题首先我们要了解二叉搜索树有什么性质可以给我们利用，由题目给出的信息我们可以知道：如果该二叉树的左子树不为空，则左子树上所有节点的值均**小于**它的根节点的值； 若它的右子树不空，则右子树上所有节点的值均**大于**它的根节点的值；它的左右子树也为二叉搜索树。

这启示我们设计一个递归函数 helper(root, lower, upper) 来递归判断，函数表示考虑以 root 为根的子树，判断子树中所有节点的值是否都在 (l,r)的范围内（注意是开区间）。如果 root 节点的值 val 不在 (l,r)的范围内说明不满足条件直接返回，否则我们要继续递归调用检查它的左右子树是否满足，如果都满足才说明这是一棵二叉搜索树。

那么根据二叉搜索树的性质，在递归调用左子树时，我们需要把上界 upper 改为 root.val，即调用 helper(root.left, lower, root.val)，因为左子树里所有节点的值均小于它的根节点的值。同理递归调用右子树时，我们需要把下界 lower 改为 root.val，即调用 helper(root.right, root.val, upper)。

函数递归调用的入口为 helper(root, -inf, +inf)， inf 表示一个无穷大的值。
```c++
// v2递归分治
class Solution {
public:
    bool helper(TreeNode* root, long long lower, long long upper) {
        if (root == nullptr) return true;
        if (root -> val <= lower || root -> val >= upper) return false;
        return helper(root -> left, lower, root -> val) && helper(root -> right, root -> val, upper);
    }
    bool isValidBST(TreeNode* root) {
        return helper(root, LONG_MIN, LONG_MAX);
    }
};

```

#### insert-into-a-binary-search-tree

[insert-into-a-binary-search-tree](https://leetcode-cn.com/problems/insert-into-a-binary-search-tree/)

> 给定二叉搜索树（BST）的根节点和要插入树中的值，将值插入二叉搜索树。 返回插入后二叉搜索树的根节点。

思路：找到最后一个叶子节点满足插入条件即可

```C++
// DFS查找插入位置
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
class Solution {
public:
    TreeNode* insertIntoBST(TreeNode* root, int val) {
        if(root==nullptr)
        {
            root=new TreeNode(val);
            return root;
        }
        if((root->val)>val)
            root->left=insertIntoBST(root->left,val);
        else
            root->right=insertIntoBST(root->right,val);
        return root;
    }
};
```
```c++
//非递归 迭代
class Solution 
{
public:
	TreeNode* insertIntoBST(TreeNode* root, int val) 
	{
		TreeNode* pNode=root;
        while(pNode)
        {
            // insert into the right subtree
            if((pNode->val)>val)
            {
                // insert right now
                if(!pNode->left)
                {
                    pNode->left=new TreeNode(val);
                    return root;
                }
                else
                    pNode=pNode->left;
            }
            // insert into the left subtree
            else{
                // insert right now
                if(!pNode->right)
                {
                    pNode->right=new TreeNode(val);
                    return root;
                }
                else
                    pNode=pNode->right;
            }
        }
            return new TreeNode(val);

	}
};
```
## 总结

- 掌握二叉树递归与非递归遍历
- 理解 DFS 前序遍历与分治法
- 理解 BFS 层次遍历

## 练习

- [ ] [maximum-depth-of-binary-tree](https://leetcode-cn.com/problems/maximum-depth-of-binary-tree/)
- [ ] [balanced-binary-tree](https://leetcode-cn.com/problems/balanced-binary-tree/)
- [ ] [binary-tree-maximum-path-sum](https://leetcode-cn.com/problems/binary-tree-maximum-path-sum/)
- [ ] [lowest-common-ancestor-of-a-binary-tree](https://leetcode-cn.com/problems/lowest-common-ancestor-of-a-binary-tree/)
- [ ] [binary-tree-level-order-traversal](https://leetcode-cn.com/problems/binary-tree-level-order-traversal/)
- [ ] [binary-tree-level-order-traversal-ii](https://leetcode-cn.com/problems/binary-tree-level-order-traversal-ii/)
- [ ] [binary-tree-zigzag-level-order-traversal](https://leetcode-cn.com/problems/binary-tree-zigzag-level-order-traversal/)
- [ ] [validate-binary-search-tree](https://leetcode-cn.com/problems/validate-binary-search-tree/)
- [ ] [insert-into-a-binary-search-tree](https://leetcode-cn.com/problems/insert-into-a-binary-search-tree/)
