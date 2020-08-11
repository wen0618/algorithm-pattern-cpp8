# 链表

## 基本技能

链表相关的核心点

- null异常处理
- dummy node 哑节点 [ˈdʌmi]   ListNode dummy(0)创建对象，可以不用delete，不会泄露内存
- 快慢指针
- 插入一个节点到排序链表
- 从一个链表中移除一个节点
- 翻转链表
- 合并两个链表
- 找到链表的中间节点

## 常见题型

###  1.[remove-duplicates-from-sorted-list](https://leetcode-cn.com/problems/remove-duplicates-from-sorted-list/)

> 给定一个排序链表，删除所有重复的元素，使得每个元素只出现一次。

```C++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if(head==nullptr)
            return nullptr;
        ListNode* pNode=head;
        while(pNode->next)    
        {
            //相等则删除，但是pNode不下移，继续判断接上的next；
            if(pNode->val==pNode->next->val)  
            {
                pNode->next=pNode->next->next;
            }
            //不相等则pNode后移判断下一个节点；
            else
                pNode=pNode->next;
        }
        return head;
    }
};
```

### 2.[remove-duplicates-from-sorted-list-ii](https://leetcode-cn.com/problems/remove-duplicates-from-sorted-list-ii/)

> 给定一个排序链表，删除所有含有重复数字的节点，只保留原始链表中   没有重复出现的数字。

思路：与链表的其他题目类似，为了防止删除头结点的极端情况发生，先创建空结点dummy，使dummy指向传入的head结点。
然后创建cur的指针，指向链表的头部（即dummy）。
接着对cur指针迭代，因为要对比cur(cur最初始的定义指向空结点)指针的下一个结点与下下一个结点的值是否相等，为了防止产生空指针异常，故退出迭代的条件为：cur.next != null && cur.next.next != null。
在迭代过程中，如果cur.next.val == cur.next.next.val说明此时有重复元素，此时创建一个临时指针temp，指向cur的下一个节点，即temp指向的第一个重复元素所在的位置。通过while循环去重，去重后，temp指向的是重复元素中的最后一个位置。最后cur.next = temp.next就实现了消除重复元素。
当然，如果为发现重复元素，则直接向后迭代即可。
迭代完成后，返回dummy的next。

```C++
//ListNode* dummy=new ListNode(0)创建需要delete，与下面对比
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode* dummy=new ListNode(-1);
        dummy->next=head;
        ListNode* cur=dummy;
        while(cur->next!=nullptr&&cur->next->next!=nullptr)
        {
            if(cur->next->val==cur->next->next->val)
            {
                ListNode* temp=cur->next;
		//此处一定要检测temp->next！=nullptr，否则后面==报错！！
                while(temp!=nullptr&&temp->next!=nullptr&&temp->val==temp->next->val)   
                    temp=temp->next;
                cur->next=temp->next;
            }
            else
                cur=cur->next;
        }
        return dummy->next;        
    }
};
```
```C++
//对节点指针的理解：List Node* pNode=head;
//节点head相当于一个具体“车厢',而指针相当于操作员，（可以代指它当前指向/负责的车厢），可以改变车厢前后连接的其他车厢（next的指向），可以用多个指针都来操纵同一个车厢，List Node temp=head；当temp->next改变后，pNode虽然还是指向原来的head车厢，但是head车厢的后续车厢已经变了，所以上次返回的时dummy->next。（dummy->next可以被cur移动过程中改变）
```
注意点
• A->B->C 删除 B，A.next = C
• 删除用一个 Dummy Node 节点辅助（允许头节点可变）
• 访问 X.next 、X.value 一定要保证 X != nil

### 3.[reverse-linked-list](https://leetcode-cn.com/problems/reverse-linked-list/)

> 反转一个单链表。

思路：用一个 prev 节点保存向前指针，temp 保存向后的临时指针

```C++
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        if(head==nullptr)
            return head;
        ListNode* pre=nullptr;
        ListNode* cur=head;
        while(cur!=nullptr)
        {
            ListNode* temp=cur->next;
            cur->next=pre;
            pre=cur;
            cur=temp;
        }
        return pre;
    }
};
```

### 4.[reverse-linked-list-ii](https://leetcode-cn.com/problems/reverse-linked-list-ii/)

> 反转从位置  *m*  到  *n*  的链表。请使用一趟扫描完成反转。

https://leetcode-cn.com/problems/reverse-linked-list-ii/solution/bu-bu-chai-jie-ru-he-di-gui-di-fan-zhuan-lian-biao/

思路：先遍历到 m 处，翻转，再拼接后续，注意指针处理
对于链表的问题，根据以往的经验一般都是要建一个dummy node，连上原链表的头结点，这样的话就算头结点变动了，我们还可以通过dummy->next来获得新链表的头结点。


```C++
class Solution {
public:
    ListNode* reverseBetween(ListNode* head, int m, int n) {
        ListNode dummy(0);
        ListNode* pre=&dummy;
        dummy.next=head;
        
        for(int i=0;i<m-1;i++)
            pre=pre->next;
        ListNode* cur=pre->next;
        for(int i=m;i<n;i++){
            ListNode* t=cur->next;
            cur->next=t->next;
            t->next=pre->next;
            pre->next=t;
        }
        return dummy.next;
    }
};
```

### 5.[merge-two-sorted-lists](https://leetcode-cn.com/problems/merge-two-sorted-lists/)

> 将两个升序链表合并为一个新的升序链表并返回。新链表是通过拼接给定的两个链表的所有节点组成的。

思路：通过 dummy node 链表，连接各个元素

```c++
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode dummy(0);
        ListNode* pNode=&dummy;
        while(l1!=NULL&&l2!=NULL){
            if(l1->val<l2->val){
                pNode->next=l1;
                l1=l1->next;
            }
            else{
                pNode->next=l2;
                l2=l2->next;
            }
            pNode=pNode->next;
        }
	//剩余节点的链接
        l1==nullptr?pNode->next=l2:pNode->next=l1;
        return dummy.next;
    }
};

```

### 6.[partition-list](https://leetcode-cn.com/problems/partition-list/)

> 给定一个链表和一个特定值 x，对链表进行分隔，使得所有小于  *x*  的节点都在大于或等于  *x*  的节点之前。

思路：将大于等于 x 的节点，放到另外一个链表，最后连接这两个链表

```C++
class Solution {
public:
    ListNode* partition(ListNode* head, int x) {
        if(head==nullptr)
            return nullptr;
        //每个链表都创建一个哑节点
        ListNode pNdummy(0);
        ListNode* pNew=&pNdummy;
        ListNode dummy(0);
        dummy.next=head;
        ListNode* pNode=&dummy;
        while(pNode->next)
        {
            
            if((pNode->next->val)>=x)
            {
                 // 移除>=x节点
                ListNode* temp=pNode->next;
                pNode->next=pNode->next->next;
                // 放到另外一个链表
                pNew->next=temp;
                pNew=pNew->next;
                

            }
            else
                pNode=pNode->next;
        }
        //拼接两个链表
        pNew->next=nullptr;
        pNode->next=pNdummy.next;
        return dummy.next;
    }
};
```

哑巴节点使用场景

> 当头节点不确定的时候，使用哑巴节点

###  7.[sort-list](https://leetcode-cn.com/problems/sort-list/)

> 在  *O*(*n* log *n*) 时间复杂度和常数级空间复杂度下，对链表进行排序。
O(nlogn)和O(1),原地操作

思路：找到中点断开，翻转后面部分，然后合并前后两个链表
``c++
///链表里操作最难掌握的应该就是各种断链啊，然后再挂接啊。在这里，我们主要用到链表操作的两个技术：
///   merge(l1, l2)，双路归并，我相信这个操作大家已经非常熟练的，就不做介绍了。
///   cut(l, n)，可能有些同学没有听说过，它其实就是一种 split 操作，即断链操作。不过我感觉使用 cut 更准确一些，它表示，将链表 l 切掉前 n 个节点，并返回后半部分的链表头。
//额外再补充一个 dummyHead 大法，已经讲过无数次了，仔细体会吧。
///希望同学们能把双路归并和 cut 断链的代码烂记于心，以后看到类似的题目能够刷到手软。
```C++
//可能是因为你的dummyhead是new出来的，这样要记得delete,如果像答主这样不用new,直接声明一个ListNode变量(对象），这样系统为它分配的内存会随着函数的结束自动释放，这样也就没有内存泄漏了
//注意此时为ListNode对象，而不是ListNode*指针，访问其成员用L.next而非L*->next  ( (*p).mem==p->mem  )
大家都喜欢用的归并排序（事实上是对链表排序的最佳方案）
class Solution {
public:
    ListNode* sortList(ListNode* head) {
        ListNode dummyHead(0);
        dummyHead.next = head;
        auto p = head;
        int length = 0;
        while (p) {
            ++length;
            p = p->next;
        }
        
        for (int size = 1; size < length; size <<= 1) {
            auto cur = dummyHead.next;
            auto tail = &dummyHead;
            
            while (cur) {
                auto left = cur;
                auto right = cut(left, size);  // left->@->@  right->@->@->@...
                cur = cut(right, size);        // left->@->@   right->@->@   cur->@->...
                
                tail->next = merge(left, right);
                while (tail->next) {
                    tail = tail->next;
                }
            }
        }
        return dummyHead.next;
    }
    
    ListNode* cut(ListNode* head, int n) {
        auto p = head;
        //--n mean  return n=n-- ;   && !
        while (--n && p) {
            p = p->next;
        }
        
        if (!p) return nullptr;
        
        auto next = p->next;
       // 一定要把链表切断！！！注意数组和链表的差异。
	p->next = nullptr;
        return next;
    }
    
    ListNode* merge(ListNode* l1, ListNode* l2) {
        ListNode dummyHead(0);
        auto p = &dummyHead;
        while (l1 && l2) {
            if (l1->val < l2->val) {
                p->next = l1;
                p = l1;
                l1 = l1->next;       
            } else {
                p->next = l2;
                p = l2;
                l2 = l2->next;
            }
        }
        p->next = l1 ? l1 : l2;
        return dummyHead.next;
    }
};

链接：https://leetcode-cn.com/problems/sort-list/solution/148-pai-xu-lian-biao-bottom-to-up-o1-kong-jian-by-/
```

快排版本。（貌似提问频率还挺高的）,（交换结点版本，非伪排序只交换数值）与第六题类似。
```c++
class Solution {
public ListNode sortList(ListNode head) {
        if(head==null||head.next==null) return head;
        // 没有条件，创造条件。自己添加头节点，最后返回时去掉即可。
        ListNode newHead=new ListNode(-1);
        newHead.next=head;
        return quickSort(newHead,null);
    }
    // 带头结点的链表快速排序
    private ListNode quickSort(ListNode head,ListNode end){
        if (head==end||head.next==end||head.next.next==end) return head;
        // 将小于划分点的值存储在临时链表中
        ListNode tmpHead=new ListNode(-1);
        // partition为划分点，p为链表指针，tp为临时链表指针
        ListNode partition=head.next,p=partition,tp=tmpHead;
        // 将小于划分点的结点放到临时链表中
        while (p.next!=end){
            if (p.next.val<partition.val){
                tp.next=p.next;
                tp=tp.next;
                p.next=p.next.next;
            }else {
                p=p.next;
            }
        }
        // 合并临时链表和原链表，将原链表接到临时链表后面即可
        tp.next=head.next;
        // 将临时链表插回原链表，注意是插回！（不做这一步在对右半部分处理时就断链了）
        head.next=tmpHead.next;
        quickSort(head,partition);
        quickSort(partition,end);
        // 题目要求不带头节点，返回结果时去除
        return head.next;
    }
};
快拍排数组快的主要原因在于是原地排序，而链表排序不需要额外的开辟空间，这样归并排序优势很大，比较的次数会少很多
```

### 8.[reorder-list](https://leetcode-cn.com/problems/reorder-list/)

> 给定一个单链表  *L*：*L*→*L*→…→*L\_\_n*→*L*
> 将其重新排列后变为： *L*→*L\_\_n*→*L*→*L\_\_n*→*L*→*L\_\_n*→…
```c++
class Solution {
public:
    void reorderList(ListNode* head) {
        if (head == nullptr || head->next == nullptr)
            return;

        ListNode* fast = head, *slow = head;
        while (fast->next != nullptr && fast->next->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }

        ListNode* reverse = reverseList(slow->next);
        slow->next = nullptr;

        while (reverse) {
            ListNode* next = head->next;
            ListNode* next1 = reverse->next;
            reverse->next = next;
            head->next = reverse;
            head = next;
            reverse = next1;
        }

        return;
    }
private:
    ListNode* reverseList(ListNode* head) {
        ListNode* cur = nullptr;
        ListNode* pre = head;
        ListNode* tmp;
        while (pre != nullptr) {
            tmp = pre->next;
            pre->next = cur;
            cur = pre;
            pre = tmp;
        }
        return cur;
    }
};
```

### 9.[linked-list-cycle](https://leetcode-cn.com/problems/linked-list-cycle/)

> 给定一个链表，判断链表中是否有环。

思路：快慢指针，快慢指针相同则有环，证明：如果有环每走一步快慢指针距离会减 1
![fast_slow_linked_list](https://img.fuiboom.com/img/fast_slow_linked_list.png)

```c++
class Solution {
public:
    bool hasCycle(ListNode *head) {
        if(head==nullptr)
            return false;
        ListNode* fast=head;ListNode* slow=head;
        while(fast->next&&fast->next->next)
        {
            fast=fast->next->next;
            slow=slow->next;
            if(fast==slow)
            {
                return true;
            }
        }
        return false;        
    }
};
```
```java
java:
public boolean hasCycle(ListNode head) {
    if (head == null || head.next == null) {
        return false;
    }
    ListNode slow = head;
    ListNode fast = head.next;
    while (slow != fast) {
        if (fast == null || fast.next == null) {
            return false;
        }
        slow = slow.next;
        fast = fast.next.next;
    }
    return true;
}
```

### 10.[linked-list-cycle-ii](https://leetcode-cn.com/problems/linked-list-cycle-ii/)

> 给定一个链表，返回链表开始入环的第一个节点。  如果链表无环，则返回  `null`。

思路：快慢指针，快慢相遇之后，慢指针回到头，快慢指针步调一致一起移动，相遇点即为入环点
![cycled_linked_list](https://github.com/wen0618/algorithm-pattern/blob/master/images/loop2.png)

```C++
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        ListNode* fast = head, *slow = head;
        while (true) {
            if (fast == nullptr || fast->next == nullptr) 
                return nullptr;
            fast = fast->next->next;
            slow = slow->next;
            if (fast == slow) 
                break;
        }
	//slow指针位置不变 ，将fast指针重新指向链表头部节点 ；slow和fast同时每轮向前走 1步；
        fast = head;
        while (slow != fast) {
            slow = slow->next;
            fast = fast->next;
        }
        return fast;
    }
};
```
坑点

- 指针比较时直接比较对象，不要用值比较，链表中有可能存在重复值情况
- 第一次相交后，快指针需要从下一个节点开始和头指针一起匀速移动


[ori:]这两种方式不同点在于，**一般用 fast=head.Next 较多??**，因为这样可以知道中点的上一个节点，可以用来删除等操作。

- fast 如果初始化为 head.Next 则中点在 slow.Next
- fast 初始化为 head,则中点在 slow

### 11.[palindrome-linked-list](https://leetcode-cn.com/problems/palindrome-linked-list/)

> 请判断一个链表是否为回文链表。

```c++
class Solution {
public:
    bool isPalindrome(ListNode* head) {
        if(head==nullptr)
            return true;
	// fast初始化为head,则(靠左的）中点在slow
        ListNode* fast=head;ListNode* slow=head;
        while(fast->next&&fast->next->next)
        {
            fast=fast->next->next;
            slow=slow->next;
        }
        ListNode* tail=slow->next;
	 // 断开两个链表
        slow->next=nullptr;
        tail=reverse(tail);
        while(tail&&head)
        {
            if(tail->val!=head->val)
                return false;
            //勿忘移动节点
            head=head->next;
            tail=tail->next;
        }
        return true;

    }
    ListNode* reverse(ListNode* tail)
    {
        //pre是最后一个反转好的节点
        ListNode* pre=nullptr;
        ListNode* pNode=tail;
        while(pNode)
        {
            ListNode* temp=pNode->next;
            pNode->next=pre;
            pre=pNode;
            pNode=temp;
        }
        return pre;
    }
};
```
```c++
//简化版：.用快慢指针遍历的同时翻转前半部分，然后与后半部分比较即可
class Solution {
public:
    bool isPalindrome(ListNode* head) {
        if(!head||!head->next) return true;
        //pointers to find mid
	auto fast=head,slow=head;
	//reverse pointers
        ListNode* p,*pre=NULL;
        while(fast&&fast->next){
	//先反转再移动
            p=slow;
	    //快慢遍历
            slow=slow->next;
            fast=fast->next->next;
	     //翻转
            p->next=pre;
            pre=p;
        }
	/奇数个节点时跳过中间节点
        if(fast) slow=slow->next;
        while(p){
            if(p->val!=slow->val) return false;
            p=p->next;
            slow=slow->next;
        }
        return true;
    }
};
```
### 12.[copy-list-with-random-pointer](https://leetcode-cn.com/problems/copy-list-with-random-pointer/)

> 给定一个链表，每个节点包含一个额外增加的随机指针，该指针可以指向链表中的任何节点或空节点。
> 要求返回这个链表的 深拷贝。

思路：1、hash 表存储指针，2、复制节点跟在原节点后面

```C++
/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/

class Solution {
public:
    Node* copyRandomList(Node* head) {
        if(head==nullptr)
            return nullptr;
       // 复制节点，紧挨到到后面
	// 1->2->3  ==>  1->1'->2->2'->3->3'
        Node* cur=head;
        while(cur!=nullptr)
        {
            Node* clone=new Node(cur->val);
            clone->next=cur->next;
            Node* temp=cur->next;
            cur->next=clone;
            cur=temp;
        }
        //处理random指针
        cur=head;
        while(cur)
        {
            if(cur->random!=nullptr)
                cur->next->random=cur->random->next;
            cur=cur->next->next;
        }
        //分离两个链表
        cur=head;
        Node* cloneHead=cur->next;
        while(cur&&cur->next)
        {
            Node* temp=cur->next;
            cur->next=cur->next->next;
            cur=temp;
        }
	// 原始链表头：head 1->2->3
	// 克隆的链表头：cloneHead 1'->2'->3'
        return cloneHead;
        
    }
};
```

## 总结

链表必须要掌握的一些点，通过下面练习题，基本大部分的链表类的题目都是手到擒来~

- null/nil 异常处理
- dummy node 哑巴节点
- 快慢指针
- 插入一个节点到排序链表
- 从一个链表中移除一个节点
- 翻转链表
- 合并两个链表
- 找到链表的中间节点
//切记遍历时要移动节点
## 练习

- [ ] [remove-duplicates-from-sorted-list](https://leetcode-cn.com/problems/remove-duplicates-from-sorted-list/)
- [ ] [remove-duplicates-from-sorted-list-ii](https://leetcode-cn.com/problems/remove-duplicates-from-sorted-list-ii/)
- [ ] [reverse-linked-list](https://leetcode-cn.com/problems/reverse-linked-list/)
- [ ] [reverse-linked-list-ii](https://leetcode-cn.com/problems/reverse-linked-list-ii/)
- [ ] [merge-two-sorted-lists](https://leetcode-cn.com/problems/merge-two-sorted-lists/)
- [ ] [partition-list](https://leetcode-cn.com/problems/partition-list/)
- [ ] [sort-list](https://leetcode-cn.com/problems/sort-list/)
- [ ] [reorder-list](https://leetcode-cn.com/problems/reorder-list/)
- [ ] [linked-list-cycle](https://leetcode-cn.com/problems/linked-list-cycle/)
- [ ] [linked-list-cycle-ii](https://leetcode-cn.com/problems/linked-list-cycle-ii/)
- [ ] [palindrome-linked-list](https://leetcode-cn.com/problems/palindrome-linked-list/)
- [ ] [copy-list-with-random-pointer](https://leetcode-cn.com/problems/copy-list-with-random-pointer/)
