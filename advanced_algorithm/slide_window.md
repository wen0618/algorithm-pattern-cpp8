# 滑动窗口——双指针之一，解决子串问题

![gif](./slidewindow.gif)
## 模板

```cpp
/* 滑动窗口算法框架 */
void slidingWindow(string s, string t) {
    //用map来分别统计窗口window和子串t（need)中每个字符出现的频数，逐个比较来判断窗口中是否包含了T中的所有字符
    unordered_map<char, int> need, window;
    //统计子串字符频数
    for (char c : t) need[c]++;

    //滑动窗口[left,right)
    int left = 0, right = 0;
    //valid表示窗口中 满足子串need的字符个数，当valid==need.size()则说明窗口中已经完全包好了子串
    int valid = 0;
    while (right < s.size()) {
        // c 是将移入窗口的字符
        char c = s[right];
        // 右移窗口
        right++;
        // 进行窗口内数据的一系列更新
        ...

        /*** debug 输出的位置 ***/
        printf("window: [%d, %d)\n", left, right);
        /********************/

        // 判断左侧窗口是否要收缩(循环判断是否满足收缩条件，暂停向右滑动，左侧开始收缩，直至不满足继续右移）
        while (window needs shrink) {
            // d 是将移出窗口的字符
            char d = s[left];
            // 左移窗口
            left++;
            // 进行窗口内数据的一系列更新
            ...
        }
    }
}
```

需要变化的地方

- 1、右指针右移之后窗口数据更新
- 2、判断窗口是否要收缩
- 3、左指针右移之后窗口数据更新
- 4、根据题意计算结果

## 示例

1.inimum-window-substring](https://leetcode-cn.com/problems/minimum-window-substring/)
> 给你一个字符串 S、一个字符串 T，请在字符串 S 里面找出：包含 T 所有字母的最小子串
子串强调了连续性，T中可能包含重复字符
如何判断s的子串中包含了T中的所有字符：分别统计s、T中每个字符出现的次数，逐个比较
```c++
class Solution {
public:
    string minWindow(string s, string t) {
       if(s.size()==0||t.size()==0||s.size()<t.size())
            return "";
    	//用两个map来分别统计窗口window和子串need中每个字符出现的频数，逐个比较来判断窗口是否已经包含子串中的所有字符
        unordered_map<char,int>need,window;
	//循环前统计子串每个字符的频数
        for(char c:t)
            need[c]++;
	 //滑动窗口[left,right)
        int left=0,right=0;
	//valid表示窗口中满足need的字符的个数，当valid==need.size()时说明已经完全包含了子串
        int valid=0;
	//记录最小覆盖子串的起始索引和长度
        int start=0,len=INT_MAX;
        while(right<s.size())
        {
	    //c是将要移入窗口的字符
            char c=s[right];
	    //将c移入窗口进行判断
            right++;
	    //进行窗口内数据的一系列更新
            if(need.count(c)){
                window[c]++;
                if(window[c]==need[c])
                    valid++;
            }
	    
	    //判断左侧窗口是否要收缩，while
            while(valid==need.size()){
	    	//满足条件先更新最小子串数据再移动，因为是左闭右开区间，所以为r-l
                if(right-left<len){
                    start=left;
                    len=right-left;
                }
		//d是将要移除窗口的字符
                char d=s[left];
		//左移窗口，将d移出
                left++;
		//进行窗口内数据的一系列更新
                if(need.count(d)){
                    if(window[d]==need[d])
                        valid--;
                    window[d]--;
                }
            }
        }
	//返回最终结果
        return len==INT_MAX?"":s.substr(start,len);
        
    }
};
```

2.ermutation-in-string](https://leetcode-cn.com/problems/permutation-in-string/)

> 给定两个字符串  **s1**  和  **s2**，写一个函数来判断  **s2**  是否包含  **s1 **的排列。

```c++
class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        unordered_map<char,int>need,window;
        for(char i:s1)
            need[i]++;
        int left=0,right=0;
        int valid=0;
        while(right<s2.size())
        {
            char c=s2[right];
            right++;
	    //进行窗口内数据的一系列更新
            if(need.count(c)){
                window[c]++;
                if(window[c]==need[c])
                    valid++;
            }
	    //判断左侧窗口是否需要收缩：当窗口长度大于等于子串长度时，收缩判断
           while(right-left>=s1.size()){
	       //判断是否找找到了合法的子串
               if(valid==need.size())
                    return true;
                char d=s2[left];
                left++;
		//进行窗口内数据的一系列更新
                if(need.count(d)){
                    if(window[d]==need[d])
                        valid--;
                    window[d]--;
                }
           }
        }
        return false;

    }
};
```

3.ind-all-anagrams-in-a-string](https://leetcode-cn.com/problems/find-all-anagrams-in-a-string/)

> 给定一个字符串  **s **和一个非空字符串  **p**，找到  **s **中所有是  **p **的字母异位词的子串，返回这些子串的起始索引。

```c++
class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        unordered_map<char,int>need,windows;
        for(char c:p)
            need[c]++;
        int left=0,right=0;
        int valid=0;
        vector<int>res;
        while(right<s.size()){
            char c=s[right];
            right++;
	    //进行窗口内数据的更新
            if(need.count(c)){
                windows[c]++;
                if(windows[c]==need[c])
                    valid++;
            }
	    //判断左侧窗口是否要收缩
            while(right-left>=p.size()){
	    	//判断是否找到合法子串
                if(valid==need.size())
                    res.push_back(left);
                char d=s[left];
                left++;
		//进行窗口内数据的一系列更新
                if(need.count(d)){
                    if(windows[d]==need[d])
                        valid--;
                    windows[d]--;
                }
            }
        }
        return res;

    }
};

```

4.ongest-substring-without-repeating-characters](https://leetcode-cn.com/problems/longest-substring-without-repeating-characters/)

> 给定一个字符串，请你找出其中不含有重复字符的   最长子串   的长度。
> 示例  1:
>
> 输入: "abcabcbb"
> 输出: 3
> 解释: 因为无重复字符的最长子串是 "abc"，所以其长度为 3。

```c++
int lengthOfLongestSubstring(string s) {
    unordered_map<char, int> window;

    int left = 0, right = 0;
    int res = 0; // 记录结果
    while (right < s.size()) {
        char c = s[right];
        right++;
        // 进行窗口内数据的一系列更新
        window[c]++;
        // 判断左侧窗口是否要收缩
        while (window[c] > 1) {
            char d = s[left];
            left++;
            // 进行窗口内数据的一系列更新
            window[d]--;
        }
        // 在这里更新答案
        res = max(res, right - left);
    }
    return res;
}
```

## 总结

- 和双指针题目类似，更像双指针的升级版，滑动窗口核心点是维护一个窗口集，根据窗口集来进行处理
- 核心步骤
  - right 右移
  - 收缩
  - left 右移
  - 求结果
  

https://leetcode-cn.com/problems/minimum-window-substring/solution/hua-dong-chuang-kou-suan-fa-tong-yong-si-xiang-by-/
## 练习

- [ ] [minimum-window-substring](https://leetcode-cn.com/problems/minimum-window-substring/)
- [ ] [permutation-in-string](https://leetcode-cn.com/problems/permutation-in-string/)
- [ ] [find-all-anagrams-in-a-string](https://leetcode-cn.com/problems/find-all-anagrams-in-a-string/)
- [ ] [longest-substring-without-repeating-characters](https://leetcode-cn.com/problems/longest-substring-without-repeating-characters/)
