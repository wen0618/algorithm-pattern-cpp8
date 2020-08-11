# 二叉搜索树

## 定义

- 每个节点中的值必须大于（或等于）存储在其左侧子树中的任何值。
- 每个节点中的值必须小于（或等于）存储在其右子树中的任何值。

**应用：二叉搜索树「中序遍历」得到的值构成的序列一定是升序的！**
## 应用

1.[validate-binary-search-tree](https://leetcode-cn.com/problems/validate-binary-search-tree/)

> 验证二叉搜索树

```c++
//1.递归：
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

//2.中序遍历-非递归
class Solution {
public:
    bool isValidBST(TreeNode* root) {
        if(root==nullptr)
            return true;
        stack<TreeNode*>s;
        long long inorder = (long long)INT_MIN - 1;
        TreeNode* temp=root;
        while(temp!=nullptr||!s.empty()){
            while(temp!=nullptr){
                s.push(temp);
                temp=temp->left;
            }
            temp=s.top();
            s.pop();
            if(temp->val<=inorder)
                return false;
            inorder=temp->val;
            temp=temp->right;
        }
        return true;
    }
};
//3.中序遍历递归
class Solution {
public:
    long long pre= LLONG_MIN;
    bool isValidBST(TreeNode* root) {
        if(root==nullptr)
            return true;
        return dfs(root);
    }
    bool dfs(TreeNode*& root){
        if(root==nullptr)
            return true;
        if(!dfs(root->left))
            return false;
        if(root->val<=pre)
            return false;
        pre=root->val;
        return dfs(root->right);
    }
};
```

2.[insert-into-a-binary-search-tree](https://leetcode-cn.com/problems/insert-into-a-binary-search-tree/)

> 给定二叉搜索树（BST）的根节点和要插入树中的值，将值插入二叉搜索树。 返回插入后二叉搜索树的根节点。 保证原始二叉搜索树中不存在新值。

```C++
//递归
class Solution {
public:
    TreeNode* insertIntoBST(TreeNode* root, int val) {
        if(root==nullptr)
            return new TreeNode(val);
  
        if(root->val<val)
            root->right=insertIntoBST(root->right,val);
        else
            root->left=insertIntoBST(root->left,val);
        return root;   
    }
};
//迭代
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

3.[delete-node-in-a-bst](https://leetcode-cn.com/problems/delete-node-in-a-bst/)

> 给定一个二叉搜索树的根节点 root 和一个值 key，删除二叉搜索树中的  key  对应的节点，并保证二叉搜索树的性质不变。返回二叉搜索树（有可能被更新）的根节点的引用。

```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode* deleteNode(TreeNode* root, int key) {
     // 删除节点分为三种情况：
    // 1、只有左节点 替换为右
    // 2、只有右节点 替换为左
    // 3、有左右子节点 左子节点连接到右边最左节点即可
        if(root==nullptr)
            return root;
        if(root->val<key){
            root->right=deleteNode(root->right,key);
        }
        else if(root->val>key)
            root->left=deleteNode(root->left,key);
        //root->val==key
        else{           
            if(root->left==nullptr)
                return root->right;
            else if(root->right==nullptr)
                return root->left;
            else{
                TreeNode* cur=root->right;
                //一直向左找到最后一个左节点即可
                while(cur->left!=nullptr)
                    cur=cur->left;
                cur->left=root->left;
                return root->right;
            }
          
        }
        return root;

    }
};

```

4.[balanced-binary-tree](https://leetcode-cn.com/problems/balanced-binary-tree/)

> 给定一个二叉树，判断它是否是高度平衡的二叉树。

```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    bool flag=true;
    int helper(TreeNode* root)
    {
        if(root==nullptr)
            return 0;
        int left=helper(root->left)+1;
        int right=helper(root->right)+1;
        if(abs(left-right)>1)
            flag=false;
        return (left>right)?left:right;   
    }
    bool isBalanced(TreeNode* root) {
        if(root==nullptr)
            return true;
        helper(root);
        return flag;
        
    }
};

```

## 练习

- [ ] [validate-binary-search-tree](https://leetcode-cn.com/problems/validate-binary-search-tree/)
- [ ] [insert-into-a-binary-search-tree](https://leetcode-cn.com/problems/insert-into-a-binary-search-tree/)
- [ ] [delete-node-in-a-bst](https://leetcode-cn.com/problems/delete-node-in-a-bst/)
- [ ] [balanced-binary-tree](https://leetcode-cn.com/problems/balanced-binary-tree/)
