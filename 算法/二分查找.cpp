#include <iostream>
using namespace std;

#include <algorithm>
#include <string>
#include <vector>

// 704.二分查找
int search(vector<int>& nums, int target) {
    int low = 0, high = nums.size() - 1;
    while (low <= high) {
        int mid = low + ((high - low) >> 1);
        if (nums[mid] == target)
            return mid;
        else if (nums[mid] < target)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1;
}

// 69.x 的平方根
int mySqrt(int x) {
    if (x < 1) return x;
    int low = 1, high = x / 2;
    while (low <= high) {
        int mid = low + ((high - low) >> 1);
        if (mid == x / mid)
            return mid;
        else if (mid < x / mid)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return high;

    /* if (x < 2) return x;
    int low = 1, high = x / 2, last_mid;
    while (low <= high) {
        int mid = low + ((high - low) >> 1);
        if (mid == x / mid)
            return mid;
        else if (mid < x / mid) {
            low = mid + 1;
            last_mid = mid;
        } else
            high = mid - 1;
    }
    return last_mid; */
}

// 34.在排序数组中查找元素的第一个和最后一个位置
vector<int> searchRange(vector<int>& nums, int target) {
    int n = nums.size();
    if (n == 0) return vector<int>{-1, -1};

    int lower = lower_bound(nums, n, target);
    int upper = upper_bound(nums, n, target);

    return vector<int>{lower, upper};
}

int lower_bound(vector<int>& nums, int n, int target) {
    int low = 0, high = n - 1;
    while (low <= high) {
        int mid = low + ((high - low) >> 1);
        if (target < nums[mid])
            high = mid - 1;
        else if (nums[mid] < target)
            low = mid + 1;
        else {
            if (mid == 0 || nums[mid - 1] != target)
                return mid;
            else
                high = mid - 1;
        }
    }
    return -1;
}

int upper_bound(vector<int>& nums, int n, int target) {
    int low = 0, high = n - 1;
    while (low <= high) {
        int mid = low + ((high - low) >> 1);
        if (target < nums[mid])
            high = mid - 1;
        else if (nums[mid] < target)
            low = mid + 1;
        else {
            if (mid == n - 1 || nums[mid + 1] != target)
                return mid;
            else
                low = mid + 1;
        }
    }
    return -1;
}

// 33.搜索旋转排序数组
int search(vector<int>& nums, int target) {
    int low = 0, high = nums.size() - 1;
    while (low <= high) {
        int mid = low + ((high - low) >> 1);
        if (nums[mid] == target) return mid;

        if (nums[low] <= nums[mid]) {  // left ordered
            if (nums[low] <= target && target < nums[mid])
                high = mid - 1;
            else
                low = mid + 1;
        } else {  // right ordered
            if (nums[mid] < target && target <= nums[high])
                low = mid + 1;
            else
                high = mid - 1;
        }
    }
    return -1;
}

// 81.搜索旋转排序数组II
bool search(vector<int>& nums, int target) {
    int low = 0, high = nums.size() - 1;
    while (low <= high) {
        int mid = low + ((high - low) >> 1);
        if (nums[mid] == target) return true;

        if (nums[low] == nums[mid])
            ++low;
        else if (nums[low] < nums[mid]) {
            if (nums[low] <= target && target < nums[mid])
                high = mid - 1;
            else
                low = mid + 1;
        } else {
            if (nums[mid] < target && target <= nums[high])
                low = mid + 1;
            else
                high = mid - 1;
        }
    }
    return false;
}

// 153.寻找旋转排序数组中的最小值
int findMin(vector<int>& nums) {
    int low = 0, high = nums.size() - 1;
    while (low < high) {  //区间里至少有两个数以比较大小，区间只包含一个数时退出
        int mid = low + ((high - low) >> 1);
        if (nums[mid] < nums[high])  // right ordered
            high = mid;
        else
            low = mid + 1;
    }
    return nums[low];
}

// 154.寻找旋转排序数组中的最小值II
int findMin(vector<int>& nums) {
    int low = 0, high = nums.size() - 1;
    while (low < high) {
        int mid = low + ((high - low) >> 1);
        if (nums[mid] == nums[high])
            --high;
        else if (nums[mid] < nums[high])
            high = mid;
        else
            low = mid + 1;
    }
    return nums[low];
}

// 540.有序数组中的单一元素
int singleNonDuplicate(vector<int>& nums) {
    int low = 0, high = nums.size() - 1;
    while (low < high) {
        int mid = low + ((high - low) >> 1);
        if (nums[mid] == nums[mid ^ 1])
            low = mid + 1;
        else
            high = mid;
    }
    return nums[low];
}

// 4.寻找两个正序数组的中位数
double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {}