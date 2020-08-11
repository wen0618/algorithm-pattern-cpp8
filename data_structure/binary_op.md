# 二进制

## 常见二进制操作

### 基本操作
异或^：不同为一，相同为0；
a=0^a=a^0

### 0=a^a

由上面两个推导出：a=a^b^b

### 交换两个数

a=a^b

b=a^b

a=a^b

//temp =a;
  a = b;
  b = temp;

### 移除最后一个 1

a=n&(n-1)

### 获取最后一个 1

diff=(n&(n-1))^n

## 常见题目

1.[single-number](https://leetcode-cn.com/problems/single-number/)

> 给定一个**非空**整数数组，除了某个元素只出现一次以外，其余每个元素均出现两次。找出那个只出现了一次的元素。

```c++
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        if(nums.empty())
            return 0;
        //初始化！
	int res=0;
        for(int i: nums)
        {
            res^=i;
        }
        return res;

    }
};
```

2.[single-number-ii](https://leetcode-cn.com/problems/single-number-ii/)

> 给定一个**非空**整数数组，除了某个元素只出现一次以外，其余每个元素均出现了三次。找出那个只出现了一次的元素。
> 如果其他数都出现了 k 次，一个数出现了一次。那么如果 k是偶数，还是把所有的数异或起来就行了。如果 k是奇数，那么统计每一位是 1 的个数，然后模 k取余数就能得到那个单独的数了。

```c++
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        unordered_map<int, int> m;
        for(const auto i:nums) m[i] += 1;
        for(const auto i:m) if(i.second == 1) return i.first;
        return 0;
    }
}
//note:if(m.count(i)==1) x  :c.count(k)返回关键字等于k的元素数量，此（2，3），（3，1）都是1，因为muti_map的key才可以重复,故map慎用count
```
```c
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int res = 0;
        for (int i = 0; i < 32; ++i) {
            int cnt = 0;
            for (auto x : nums) {
                cnt += (x>>i)&1;
            }
            res |= (cnt%3)<<i;
        }
        return res;
    }
};
```

3.[single-number-iii](https://leetcode-cn.com/problems/single-number-iii/)

> 给定一个整数数组  `nums`，其中恰好有两个元素只出现一次，其余所有元素均出现两次。 找出只出现一次的那两个元素。

```c++
//思路：
[1,2,1,3,2,5]

1 = 001
2 = 010
1 = 001
3 = 011
2 = 010
5 = 101

把上边所有的数字异或，最后得到的结果就是 3 ^ 5 = 6 (110) 

然后对 110 调用 Integer.highestOneBit 方法就得到 100, 我们通过倒数第三位将原数组分类

倒数第三位为 0 的组
1 = 001
2 = 010
1 = 001
3 = 011
2 = 010

倒数第三位为 1 的组    
5 = 101
最后组内数字依次异或即可。

```
```c++
class Solution {
public:
    vector<int> singleNumber(vector<int>& nums) {
        if(nums.empty())
            return {};
        int diff=0;
        for(int i:nums)
            diff^=i;
	    //k = s & (-s) 就是保留s的最后一个1，并且将其他位变为0 
        diff = diff & (-diff);
        int a=0;int b=0;
        for(auto i:nums)
       if (diff & i) {
                a ^=i;
            } else {
                b ^= i;
            }            
        return {a,b};
    }
};
```

4，[number-of-1-bits](https://leetcode-cn.com/problems/number-of-1-bits/)

> 编写一个函数，输入是一个无符号整数，返回其二进制表达式中数字位数为 ‘1’  的个数（也被称为[汉明重量](https://baike.baidu.com/item/%E6%B1%89%E6%98%8E%E9%87%8D%E9%87%8F)）。

```c++
class Solution {
public:
    int hammingWeight(uint32_t n) {
        int sum=0;
        while(n !=0){
            sum++;
            n &= (n-1);//会去掉最后一个1
        }
        return sum;
    }
};
//
class Solution {
public:
    int hammingWeight(uint32_t n) {
        int res=0;
        for(int i=0;i<32;++i)
        {
            if(n>>i&1)
                res++;
        }
        return res;
        
    }
};
```

5.[counting-bits](https://leetcode-cn.com/problems/counting-bits/)

> 给定一个非负整数  **num**。对于  0 ≤ i ≤ num  范围中的每个数字  i ，计算其二进制数中的 1 的数目并将它们作为数组返回。

```c++
class Solution {
public:
    vector<int> countBits(int num) {
        vector<int>res;
        for(int n=0;n<=num;++n)
        {
            int sum=0;int temp=n;
            while(temp !=0)
            {
                sum++;
                temp &= (temp-1);//会去掉最后一个1
        }
            res.push_back(sum);
        }
        return res;
    }
};
```

```c++
vector<int> countBits(int num) {
        vector<int> result(num+1);
        result[0] = 0;
        for(int i = 1; i <= num; i++)
        {
	//奇数：二进制表示中，奇数一定比前面那个偶数多一个 1，因为多的就是最低位的 1。
            if(i % 2 == 1)
            {
                result[i] = result[i-1] + 1;
            }
	    //偶数：二进制表示中，偶数中 1 的个数一定和除以 2 之后的那个数一样多。因为最低位是 0，除以 2 就是右移一位，也就是把那个 0 抹掉而已，所以 1 的个数是不变的。
            else
            {
                result[i] = result[i/2];
            }
        }
        
        return result;
    }
```
另外一种动态规划解法:找递推关系式

```c++
class Solution {
public:
    vector<int> countBits(int num) {
        vector<int>res(num+1);
        //cout<<res[0]; 0
        for(int i=1;i<=num;++i)
        {
	 // 上一个缺1的元素+1即可
                res[i]=res[i&(i-1)]+1;
        }
        return res;

    }
};

```

6.[reverse-bits](https://leetcode-cn.com/problems/reverse-bits/)

> 颠倒给定的 32 位无符号整数的二进制位。

思路：依次颠倒即可

```c++
class Solution {
  public:
  uint32_t reverseBits(uint32_t n) {
    uint32_t ret = 0, power = 31;
    while (n != 0) {
    // 把最后一位取出来，左移之后累加到结果中
      ret += (n & 1) << power;
      n = n >> 1;
      power -= 1;
    }
    return ret;
  }
};
```

[bitwise-and-of-numbers-range](https://leetcode-cn.com/problems/bitwise-and-of-numbers-range/)

> 给定范围 [m, n]，其中 0 <= m <= n <= 2147483647，返回此范围内所有数字的按位与（包含 m, n 两端点）。

```c++
class Solution {
public:
    // m 5   1 0 1
    //   6   1 1 0
    // n 7   1 1 1
    // 把可能包含0的全部右移变成
    // m 5   1 0 0
    //   6   1 0 0
    // n 7   1 0 0
    // 所以最后结果就是m<<count
    int rangeBitwiseAnd(int m, int n) {
        int zeros=0;
        while(m<n){
            m=m>>1;
            n=n>>1;
            ++zeros;
        }
        return m<<zeros;

    }
};
//(others,un)https://leetcode-cn.com/problems/reverse-bits/solution/xiang-xi-tong-su-de-si-lu-fen-xi-duo-jie-fa-by-4-9/
```

## 练习

- [ ] [single-number](https://leetcode-cn.com/problems/single-number/)
- [ ] [single-number-ii](https://leetcode-cn.com/problems/single-number-ii/)
- [ ] [single-number-iii](https://leetcode-cn.com/problems/single-number-iii/)
- [ ] [number-of-1-bits](https://leetcode-cn.com/problems/number-of-1-bits/)
- [ ] [counting-bits](https://leetcode-cn.com/problems/counting-bits/)
- [ ] [reverse-bits](https://leetcode-cn.com/problems/reverse-bits/)
