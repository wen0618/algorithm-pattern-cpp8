# C++ base

## 基本语法

...

## 常用容器

### vector(un):

而对于数组，计算机会在内存中为其申请一段 连续 的空间，并且会记下索引为 0 处的内存地址。
假如我们想要访问索引为 2 处的元素 "D" 时，计算机会进行以下计算：

找到该数组的索引 0 的内存地址： 2008；
将内存地址加上索引值，作为目标元素的地址，即 2008 + 2 = 2010，对应的元素为 "D"，这时便找到了目标元素。


类似一维数组，对于一个二维数组 A = [[1, 2, 3, 4],[2, 4, 5, 6],[1, 4, 6, 8]]，计算机同样会在内存中申请一段 连续 的空间，并记录第一行数组的索引位置，即 A[0][0] 的内存地址，它的索引与内存地址的关系如下图所示。

v.back();
删除：
c.erase(p)//c.erase(b,e);
.

### 栈stack

```C++
// 创建栈
stack<int>s;
// push压入
s.push(val);
// pop弹出
s.pop();
//返回栈顶元素，但不弹出
s.top();
// 检查栈空
s.size()==0
s.empty();
```
题目待补充

### 队列list

```C++
// 创建队列
queue<int>q;
// enqueue入队
queue.push(item);
// dequeue出队
q.pop();
// 返回首元素或者尾元素，但不删除
q.front();
q.back();
```

### map、hash_map关联容器(un)

基本用法

```C++
.

// 创建
m:=make(map[string]int)
// 设置kv
m["hello"]=1
// 删除k
delete(m,"hello")
// 遍历
for k,v:=range m{
    println(k,v)
}
```
```C++
unordered_map<char,int>mymap;
1.mymap.size()
The number of elements in the container.
2.mymap.count(x)>0
return:1 if an element with a key equivalent to k is found, or zero otherwise.
//使用count，返回的是被查找元素的个数。如果有，返回1；否则，返回0。注意，map中不存在相同元素，所以返回值只能是1或0。
使用find，返回的是被查找元素的位置，没有则返回map.end()。
3.可以使用方括号访问键对应的值 map[key]。需要注意的是，如果该 key 不存在，C++ 会自动创建这个 key，并把 map[key] 赋值为 0。map[key]++
```
注意点

- map 键需要可比较，不能为 slice、map、function
- map 值都有默认值，可以直接操作默认值，如：m[age]++ 值由 0 变为 1
- 比较两个 map 需要遍历，其中的 kv 是否相同，因为有默认值关系，所以需要检查 val 和 ok 两个值

### 泛型算法（un)

sort

//
sort(intervals.begin(),intervals.end(),[](vector<int>& a,vector<int>& b){return a[0]<b[0];});
```go
// int排序
sort.Ints([]int{})
// 字符串排序
sort.Strings([]string{})
// 自定义排序
sort.Slice(s,func(i,j int)bool{return s[i]<s[j]})
```

math

```go
// int32 最大最小值
math.MaxInt32 // 实际值：1<<31-1
math.MinInt32 // 实际值：-1<<31
// int64 最大最小值（int默认是int64）
math.MaxInt64
math.MinInt64

```

copy

```go
// 删除a[i]，可以用 copy 将i+1到末尾的值覆盖到i,然后末尾-1
copy(a[i:],a[i+1:])
a=a[:len(a)-1]

// make创建长度，则通过索引赋值
a:=make([]int,n)
a[n]=x
// make长度为0，则通过append()赋值
a:=make([]int,0)
a=append(a,x)
```

### 常用技巧

类型转换

```go
// byte转数字
s="12345"  // s[0] 类型是byte
num:=int(s[0]-'0') // 1
str:=string(s[0]) // "1"
b:=byte(num+'0') // '1'
fmt.Printf("%d%s%c\n", num, str, b) // 111

// 字符串转数字
string:
int num=stoi(string s);
num,_:=strconv.Atoi()
str:=strconv.Itoa()

```

## 刷题注意点(un)

- leetcode 中，全局变量不要当做返回值，否则刷题检查器会报错？？
