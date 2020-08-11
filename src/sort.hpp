//  C++������ʽ
//  https://blog.csdn.net/chen1234520nnn/article/details/82084700

#ifndef Demo5_2_sort_hpp
#define Demo5_2_sort_hpp

#include <stdio.h>
#include "Demo1_2_1_deleteArrRepeat.hpp"
#include "CommonTools.hpp"

void sortDemoTest();

void __swap(int& a, int& b);
void __merge(vector<int>& nums, int start, int mid, int end);
void __mergeGroups(vector<int>& nums, int len, int gap);

//��������
void insertSort(vector<int>& nums, int n);

//��������
void quickSort(vector<int>& nums, int n);
void __quickSort(vector<int>& nums, int start, int end); //ԭ�ؽ��������Դ��뽻������
int partition(vector<int>& nums, int start, int end); //����

//�鲢����(��������)
void mergeSortUpToDown(vector<int>& nums, int start, int end);
//�鲢����(��������)
void mergeSortDownToUp(vector<int>& nums, int n);

//������
void heapSort(vector<int>& nums);
void buildMaxHeap(vector<int>& nums);
void heapHelper(vector<int>& nums, int i, int length);

#endif /* Demo5_2_sort_hpp */