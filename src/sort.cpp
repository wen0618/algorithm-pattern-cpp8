#include "Demo5_2_sort.hpp"

void sortDemoTest() {
	vector<int> a{ 80,30,60,40,20,10,50,70 };
	int len = (sizeof(a)) / (sizeof(a[0]));

	//    insertSort(a, len);
	//    printf("\n����������:\n");
	//    printfIntArr(a);

	quickSort(a, len);
	printf("\n����������:\n");
	printfIntArr(a);

	//    mergeSortUpToDown(a, 0, len-1);        // �鲢����(��������)
	//    mergeSortDownToUp(a, len);            // �鲢����(��������)
	//    printf("\n�鲢������:\n");
	//    printfIntArr(a);
}

#pragma mark - ð������
void bubbleSort(vector<int>& nums, int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n - i - 1; j++) {
			if (nums[j] > nums[j + 1]) {
				__swap(nums[j], nums[j + 1]);
			}
		}
	}
}

#pragma mark - ѡ������
void selectSort(vector<int>& nums, int n) {
	for (int i = 0; i < n; i++) {
		int min = i;
		for (int j = i + 1; j < n; j++) {
			if (nums[j] < nums[min]) {
				min = j;
			}
		}

		if (min != i) {
			__swap(nums[i], nums[min]);
		}
	}
}

#pragma mark - ��������
void insertSort(vector<int>& nums, int n) {
	if (n <= 1) return;
	for (int i = 1; i < n; ++i) {
		for (int j = i; j > 0; j--) {
			if (nums[j] < nums[j - 1]) {
				__swap(nums[j], nums[j - 1]);
			}
			else {
				break;
			}
		}
	}
}

#pragma mark - ϣ������
void shellSort(vector<int>& nums, int n) {
	int temp;
	int gap = n;
	do {
		gap = gap / 3 + 1;
		for (int i = gap; i < n; i++)
		{
			if (nums[i] < nums[i - gap]) {
				temp = nums[i];
				int j;
				for (j = i; j >= gap && temp < nums[j - gap]; j -= gap) {
					nums[j] = nums[j - gap];
				}
				nums[j] = temp;
			}
		}
	} while (gap > 1);
}

#pragma mark - ��������
void quickSort(vector<int>& nums, int n) {
	// ˼·����һ�������Ϊ�������Σ����С���Ҷ�
	__quickSort(nums, 0, n - 1);
}

// ԭ�ؽ��������Դ��뽻������
void __quickSort(vector<int>& nums, int start, int end) {
	if (start < end) {
		int pivot = partition(nums, start, end);
		__quickSort(nums, start, pivot - 1);
		__quickSort(nums, pivot + 1, end);
	}
}

// ����
int partition(vector<int>& nums, int start, int end) {
	// ѡȡ���һ��Ԫ����Ϊ��׼pivot
	int p = nums[end];
	int i = start;
	// ���һ��ֵ���ǻ�׼���Բ��ñȽ�
	for (int j = start; j < end; j++) {
		if (nums[j] < p) {
			swap(nums[i], nums[j]);
			i++;
		}
	}
	// �ѻ�׼ֵ�����м�
	swap(nums[i], nums[end]);
	return i;
}

#pragma mark - �鲢����
//�鲢����(��������)
void mergeSortUpToDown(vector<int>& nums, int start, int end) {
	if (nums.empty() || start >= end) {
		return;
	}

	int mid = (end + start) / 2;
	mergeSortUpToDown(nums, start, mid);
	mergeSortUpToDown(nums, mid + 1, end);

	__merge(nums, start, mid, end);
}

//�鲢����
void __merge(vector<int>& nums, int start, int mid, int end) {
	vector<int>temp(end - start + 1, 0);     //temp�ǻ���2������������ʱ����
	int i = start;                       //��1��������������
	int j = mid + 1;                     //��2��������������
	int k = 0;                           //��ʱ���������

	//������С���ƶ���ǰ��
	while (i <= mid && j <= end) {
		temp[k++] = (nums[i] <= nums[j]) ? nums[i++] : nums[j++];
	}

	while (i <= mid)
		temp[k++] = nums[i++];

	while (j <= end)
		temp[k++] = nums[j++];

	//��������Ԫ�أ�ȫ�������ϵ�����nums��
	for (i = 0; i < k; i++)
		nums[start + i] = temp[i];
}

//������a�����ɴκϲ�������a���ܳ���Ϊlen��������Ϊ���ɸ�����Ϊgap�������飻��"ÿ2�����ڵ�������" ���кϲ�����
void __mergeGroups(vector<int>& nums, int len, int gap) {
	int i;
	//��"ÿ2�����ڵ�������" ���кϲ�����
	for (i = 0; i + 2 * gap - 1 < len; i += (2 * gap))
	{
		__merge(nums, i, i + gap - 1, i + 2 * gap - 1);
	}

	//��i+gap-1 < len-1����ʣ��һ��������û�����
	//����������ϲ����������������
	if (i + gap - 1 < len - 1)
	{
		__merge(nums, i, i + gap - 1, len - 1);
	}
}

//�鲢����(��������)
void mergeSortDownToUp(vector<int>& nums, int n)
{
	int first = 0;

	if (nums.empty() || n <= 0) {
		return;
	}

	for (n = 1; first < n; n *= 2) {
		__mergeGroups(nums, n, first);
	}
}

//��������Ԫ��
void __swap(int& a, int& b) {
	int temp = a;
	a = b;
	b = temp;
}


#pragma mark - ������
//������
void heapSort(vector<int>& nums) {
	// 1����������nums
	// 2������������nums����Ϊһ�������
	buildMaxHeap(nums);

	// 3������nums[0]��nums[nums.size()-1]
	// 4��Ȼ���ǰ�������������³����ֶѽṹ�����ѭ������
	int len = nums.size();  //�˴�len��Ҫ�任,���������
	for (int i = nums.size() - 1; i > 0; i--) {
		swap(nums[0], nums[i]);  // �Ӻ���ǰ���ֵ
		len--;                   // ǰ��ĳ���Ҳ��һ
		heapHelper(nums, 0, len);
	}
}

// �����󶥶�
void buildMaxHeap(vector<int>& nums) {
	int length = nums.size();
	for (int i = length / 2; i >= 0; i--) {
		heapHelper(nums, i, length);
	}
}

//�ѵ���
void heapHelper(vector<int>& nums, int i, int length) {
	int left = 2 * i + 1;  // ��ڵ�����(��0��ʼ��������ڵ�Ϊi*2+1)
	int right = 2 * i + 2; // �ҽڵ�����
	int largest = i;

	// largest���������������֮��ϴ�ֵ������
	// ������ڵ㣬��ڵ�ֵ�ϴ���ȡ��ڵ�
	if (left < length && nums[left] > nums[largest]) {
		largest = left;
	}
	// �����нڵ㣬��ֵ�ϴ�ȡ�ҽڵ�
	if (right < length && nums[right] > nums[largest]) {
		largest = right;
	}

	// ����Ǹ��ڵ�ϴ�������ݹ�
	if (largest != i) {
		swap(nums[i], nums[largest]);
		heapHelper(nums, largest, length);
	}
}