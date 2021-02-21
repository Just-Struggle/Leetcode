#include <iostream>
using namespace std;

#include <algorithm>
#include <numeric>
#include <string>
#include <vector>

// 455.分发饼干
int findContentChildren(vector<int>& g, vector<int>& s) {
    int n = s.size();
    if (n == 0) return 0;
    sort(g.begin(), g.end());
    sort(s.begin(), s.end());
    int cnt = 0;
    // i 遍历饼干
    for (int i = 0; i < n && cnt < g.size(); ++i) {
        if (s[i] >= g[cnt]) {
            ++cnt;  //找到能满足当前孩子的饼干才能给下一个孩子分配
        }
    }
    return cnt;
}

// 135.分发糖果
//两次遍历
//第一次从左向右，评分更高的孩子得到的糖果数 = 他左边的孩子得到的糖果数 + 1
//第二次从右向左，若评分更高的孩子得到的糖果数 <= 他右边的孩子得到的糖果数，
//令评分更高的孩子得到的糖果数 = 他右边的孩子得到的糖果数 + 1
int candy(vector<int>& ratings) {
    int n = ratings.size();
    if (n < 2) return n;
    vector<int> candies(n, 1);
    for (int i = 1; i < n; ++i) {
        if (ratings[i] > ratings[i - 1]) candies[i] = candies[i - 1] + 1;
    }
    for (int i = n - 2; i >= 0; --i) {
        if (ratings[i] > ratings[i + 1] && candies[i] <= candies[i + 1])
            candies[i] = candies[i + 1] + 1;
    }
    return accumulate(candies.begin(), candies.end(), 0);
}

// 435.无重叠区间
/* 找到需要移除区间的最小数量，使剩余区间互不重叠。 */
//贪心策略：优先保留终点小且不相交的区间
int eraseOverlapIntervals(vector<vector<int>>& intervals) {
    int n = intervals.size();
    if (n < 2) return 0;  //区间数 < 2，不需要移除
    //按终点从小到大排序
    sort(intervals.begin(), intervals.end(),
         [](const auto& a, const auto& b) { return a[1] < b[1]; });
    // cnt 记录需要移除的区间数，last_end 保存已判断过的无重叠区间的最后一个终点
    int cnt = 0, last_end = intervals[0][1];
    for (int i = 1; i < n; ++i) {
        if (intervals[i][0] < last_end)  //区间重叠，需要移除的区间数 + 1
            ++cnt;
        else  //区间不重叠，更新终点
            last_end = intervals[i][1];
    }
    return cnt;
}

// 605.种花问题
bool canPlaceFlowers(vector<int>& flowerbed, int n) {
    int i = 0, size = flowerbed.size();
    // i > 0 时，保证 flowerbed[i-1] == 0
    while (i < size && n > 0) {
        if (flowerbed[i] == 0) {
            if (i == size - 1 || flowerbed[i + 1] == 0) {
                --n;     // flowerbed[i] 可以种
                i += 2;  //更新后 flowerbed[i-1] 仍为 0
            } else
                ++i;
        } else       // flowerbed[i+1] 必为 0
            i += 2;  //更新后 flowerbed[i-1] 为 0
    }
    return n <= 0;
}

bool canPlaceFlowers(vector<int>& flowerbed, int n) {
    int size = flowerbed.size();
    // i = 0 时，只需要考虑右侧
    // i > 0 时，保证 flowerbed[i-1] == 0，，只需要考虑右侧
    for (int i = 0; i < size; i += 2) {
        if (flowerbed[i] == 0) {
            if (i == size - 1 || flowerbed[i + 1] == 0)
                n--;  //能种花
            else
                i++;  // 从 flowerbed[i + 1] = 1 开始走两步
        }
    }
    return n <= 0;
}

// 452.用最少数量的箭引爆气球
int findMinArrowShots(vector<vector<int>>& points) {
    int n = points.size();
    if (n < 2) return n;
    sort(points.begin(), points.end(),
         [](const auto& a, const auto& b) { return a[1] < b[1]; });
    int cnt = 1, last_end = points[0][1];
    for (int i = 1; i < n; ++i) {
        if (points[i][0] > last_end) {
            ++cnt;
            last_end = points[i][1];
        }
    }
    return cnt;
}

// 763.划分字母区间
vector<int> partitionLabels(string S) {  // 1<=n<=500
    int n = S.length();
    vector<int> last_pos(26, -1);  //记录每个字母最后一次出现的位置
    for (int i = 0; i < n; ++i) last_pos[S[i] - 'a'] = i;

    vector<int> slices;      //保存每个字符串片段的长度
    int start = 0, end = 0;  //记录当前划分区间的位置
    for (int i = 0; i < n; ++i) {
        //每次循环都用 S[i] 最后一次出现的位置更新 end
        //因为每个字符最后一次出现的位置是唯一的,
        //只有当 i 走到 end 时，才会有 i == end
        end = max(last_pos[S[i] - 'a'], end);
        if (i == end) {
            slices.push_back(end - start + 1);
            start = end + 1;
        }
    }
    return slices;
}

// 121.买卖股票的最佳时机
int maxProfit(vector<int>& prices) {
    int n = prices.size();
    if (n < 2) return 0;
    int buy = prices[0], sell = buy, profit = 0;
    for (int i = 1; i < n; ++i) {
        if (prices[i] < buy) {
            buy = prices[i];
            sell = buy;
        } else if (prices[i] > sell) {
            sell = prices[i];
            profit = max(profit, sell - buy);
        }
    }
    return profit;
}

// 122.买卖股票的最佳时机II
//可以当天卖后再买，这样只要第二天价格比第一天高，就在第一天买入，第二天卖出
//利润 = 所有正的价格差求和
int maxProfit(vector<int>& prices) {
    int n = prices.size();
    if (n < 2) return 0;
    int profit = 0;
    for (int i = 1; i < n; ++i) {
        if (prices[i] > prices[i - 1]) profit += prices[i] - prices[i - 1];
    }
    return profit;
}

// 406.根据身高重建队列
vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
    int n = people.size();
    if (n == 1)
        return vector<vector<int>>(1, vector<int>{people[0][0], people[0][1]});
    // 1.按身高从高到矮排序  2.按 k 从小到大排序
    //这样每个人前面都是比他高或一样高的人，
    //在插入队列的时候只需要根据 k 就可以快速确定插入位置
    sort(people.begin(), people.end(), [](const auto& p1, const auto& p2) {
        if (p1[0] != p2[0]) return p1[0] > p2[0];
        return p1[1] < p2[1];
    });
    vector<vector<int>> queue{people[0]};
    for (int i = 1; i < n; ++i)  //因为题目数据满足要求，一定能找到合理位置插入
        queue.insert(queue.begin() + people[i][1], people[i]);
    return queue;
}

// 665.非递减数列
bool checkPossibility(vector<int>& nums) {
    int n = nums.size();
    if (n <= 2) return true;
    int cnt = 0;
    for (int i = 1; i < n; ++i) {
        if (nums[i - 1] > nums[i]) {
            ++cnt;
            if (cnt > 1) return false;
            //根据 nums[i - 2] 和 nums[i] 的大小关系可以判断要修改的是哪个值
            //保证修改后 nums[i] 左侧是非递减数列
            // 1.使 nums[i] 变大
            // 2.使 nums[i - 1] 变小
            if (i >= 2 && nums[i - 2] > nums[i]) {
                nums[i] = nums[i - 1];
            } else {
                // 1. i = 1，向下修改
                // 2. i >= 2 && nums[i - 2] = nums[i]，向下修改
                // 3. i >= 2 && nums[i - 2] < nums[i]
                nums[i - 1] = nums[i];
            }
        }
    }
    return true;
}