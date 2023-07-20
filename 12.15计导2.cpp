////给定⼀个由10个元素组成的整型数组，每个元素值由用户输入，对该数组排序后输入⼀个⽬标值，
//在数组中找到⽬标值，并返回其索引。如果⽬标值不存在于数组中，返回 - 1。
#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>

int compare(const void* a, const void* b)
{
    // 比较两个整数的大小
    int x = *(int*)a;
    int y = *(int*)b;
    if (x < y) 
    {
        return -1;
    }
    else if (x > y) 
    {
        return 1;
    }
    else 
    {
        return 0;
    }
}

int binary_search(int* array, int size, int target) {
    // 二分查找数组中的目标值
    int left = 0;
    int right = size - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (array[mid] == target) {
            return mid; // 找到目标值，返回索引
        }
        else if (array[mid] < target) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    return -1; // 未找到目标值，返回-1
}

int main(void) {
    int array[10];
    int i;
    printf("Enter 10 integers:\n");
    for (i = 0; i < 10; i++) {
        scanf("%d", &array[i]);
    }
    // 使用 qsort() 函数对数组进行排序
    qsort(array, 10, sizeof(int), compare);
    int target;
    printf("Enter the target value: ");
    scanf("%d", &target);
    int index = binary_search(array, 10, target);
    if (index >= 0) {
        printf("Target value found at index %d\n", index);
    }
    else {
        printf("Target value not found\n");
    }
    return 0;
}
