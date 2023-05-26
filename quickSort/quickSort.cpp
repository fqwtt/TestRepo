/*************************************************************************
  > File Name: quickSort.cpp
  > Author: fqwtt
  > Created Time: 2023年05月26日 星期五 08时53分32秒
 ************************************************************************/

#include <iostream>
using namespace std;

int partition(int nums[], int left, int right) {
	int target = nums[left];
	int i = left + 1;
	int j = right;
	while (i <= j) {
		while (i <= j && nums[i] <= target) {
			i++;
		}
		while (i <= j && nums[j] >= target) {
			j--;
		}
		if (i < j) {
			swap(nums[i], nums[j]);
			i++;
			j--;
		}
	}
	swap(nums[left], nums[j]);
	return j;
}

void quickSort(int nums[], int left, int right) {
	if (left >= right) {
		return;
	}
	int pos = partition(nums, left, right);
	quickSort(nums, left, pos - 1);
	quickSort(nums, pos + 1, right);
}

bool isSort(int nums[], int length) {
	for (int i = 1; i < length; i++) {
		if (nums[i] < nums[i - 1]) {
			return false;
		}
	}
	return true;
}

void test(int nums[], int length) {
	for (int i = 0; i < length; i++) {
		nums[i] = rand() % 100;
	}
	quickSort(nums, 0, length - 1);
	cout << (isSort(nums, length) ? "有序" : "无序") << endl;
}
int main() {
	int nums[1000];
	int length = sizeof(nums)/sizeof(nums[0]);
	test(nums, length);
	return 0;
}

