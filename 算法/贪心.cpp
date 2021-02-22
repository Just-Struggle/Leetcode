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
                --n;  //能种花
            else
                ++i;  // 从 flowerbed[i + 1] = 1 开始走两步
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
//类似于求最大连续子序列和
int maxProfit(vector<int>& prices) {
    int n = prices.size();
    if (n < 2) return 0;
    int buy = prices[0], sell = prices[0], profit = 0;
    for (int i = 1; i < n; ++i) {
        if (prices[i] < buy) {
            buy = prices[i];
            sell = buy;  //买入价格变小，令卖出价格等于买入价格
        } else if (prices[i] > sell) {
            sell = prices[i];  //找到更高的卖出价格，更新最大利润
            profit = max(profit, sell - buy);
        }
    }
    return profit;
}

// 122.买卖股票的最佳时机II
//类似于求最大非连续子序列和
//可以卖后再买，这样只要第二天价格比第一天高，就在第一天买入，第二天卖出
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

vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
    sort(people.begin(), people.end(), [](const auto& p1, const auto& p2) {
        if (p1[0] != p2[0]) return p1[0] > p2[0];
        return p1[1] < p2[1];
    });
    list<vector<int>> que;  // list底层是链表实现，插入效率比vector高的多
    for (int i = 0; i < people.size(); i++) {
        int position = people[i][1];  // 插入到下标为position的位置
        std::list<vector<int>>::iterator it = que.begin();
        while (position--) {  // 寻找在插入位置
            it++;
        }
        que.insert(it, people[i]);
    }
    return vector<vector<int>>(que.begin(), que.end());
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

// 1005.K次取反后最大化的数组和
int largestSumAfterKNegations(vector<int>& A, int K) {
    int n = A.size();
    sort(A.begin(), A.end());  //数组按从小到大排列
    int i = 0;
    //有负数，先翻转负数
    while (K > 0 && A[i] < 0) {
        --K;
        A[i] = -A[i];
        if (++i == n) break;  //访问到数组结尾
    }
    int sum = accumulate(A.begin(), A.end(), 0);
    if (K == 0) return sum;
    //访问到数组结尾
    if (i == n) {
        if (K % 2 == 1)  //翻转当前最小数（原最大负数 or 最小正数）
            return sum - 2 * A[i - 1];
        else  //直接返回 sum
            return sum;
    }
    //数组有 0，只翻转 0，直接返回 sum
    if (A[i] == 0 && K >= 0) return sum;
    //数组中还有元素，说明数组中没有 0，
    //剩余元素均为正数
    //若当前 K 为偶数，翻转 K 次同一个数，直接返回 sum
    //若当前 K 为奇数，翻转一次当前最小正数，返回
    if (K % 2 == 1) {
        if (i == 0)  //数组只有正数，当前最小正数是 A[i]
            return sum - 2 * A[i];
        else  //当前最小正数是 A[i] 或 A[i-1]（原最大负数）
            return sum - 2 * min(A[i], A[i - 1]);
    } else
        return sum;
}
//按数组元素绝对值从大到小排序，遇到负数就翻转
//如果到最后一个元素还可以翻转，只需要翻转最后一个元素
int largestSumAfterKNegations(vector<int>& A, int K) {
    int n = A.size();
    sort(A.begin(), A.end(), [](const auto& a, const auto& b) {
        return abs(a) > abs(b);  //这里取等会溢出
    });
    for (int i = 0; i < n; ++i) {
        if (A[i] < 0) {
            A[i] = -A[i];
            --K;
            if (K == 0) break;
        }
    }
    int sum = accumulate(A.begin(), A.end(), 0);
    if (K % 2 == 1) return sum - 2 * A[n - 1];  // K 为奇数
    return sum;                                 // K 为 0 或 其他偶数
}

// 55.跳跃游戏
bool canJump(vector<int>& nums) {
    int n = nums.size();
    if (n == 1) return true;
    int can_reach = 0;  //保存能到达的最远位置
    for (int i = 0; i < n - 1; ++i) {
        can_reach = max(can_reach, i + nums[i]);
        if (can_reach >= n - 1)  //能到达最后一个下标
            return true;
        if (i == can_reach)  //当前位置就是能到达的最远位置，无法向前走
            return false;
    }
    return false;
}
bool canJump(vector<int>& nums) {
    int n = nums.size();
    if (n == 1) return true;
    int can_reach = 0;  //保存能到达的最远位置
    for (int i = 0; i <= can_reach; ++i) {
        can_reach = max(can_reach, i + nums[i]);
        if (can_reach >= n - 1)  //能到达最后一个下标
            return true;
    }
    return false;  //已到达最远位置，无法向前走
}

// 45.跳跃游戏II
//相当于求“最小覆盖区间”
//每次在当前区间的覆盖范围内找到下一区间的最大终点
int jump(vector<int>& nums) {
    int n = nums.size();
    if (n == 1) return 0;
    int can_reach = 0;  //保存当前能到达的最远位置
    int next_end = 0;   //保存下一跳能到的最远位置
    int cnt = 0;
    for (int i = 0; i < n - 1; ++i) {
        //在当前覆盖范围内寻找能到达的最远位置，作为下一区间的终点
        next_end = max(next_end, i + nums[i]);
        if (next_end >= n - 1)  //下一区间能覆盖最后一个位置，
            return cnt + 1;     //返回 当前区间数+1
        //进入下一区间
        if (i == can_reach) {
            can_reach = next_end;
            ++cnt;
        }
    }
    return cnt;
}

// 134.加油站
int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
    // cur_left 记录从 start 开始，油箱剩余油量
    // total_left 计算总剩余油量
    int cur_left = 0, total_left = 0, start = 0;
    for (int i = 0; i < gas.size(); ++i) {
        cur_left += gas[i] - cost[i];
        total_left += gas[i] - cost[i];
        if (cur_left < 0) {  //油量不足，说明之前选的出发点不能跑一圈
            start = i + 1;  //将下一位置作为出发点
            cur_left = 0;
        }
    }
    return (total_left < 0) ? -1 : start;
}

// 860.柠檬水找零
bool lemonadeChange(vector<int>& bills) {
    int n = bills.size();
    if (n == 0) return true;
    int cnt5 = 0, cnt10 = 0;
    for (int i = 0; i < n; ++i) {
        switch (bills[i]) {
            case 5:
                ++cnt5;
                break;
            case 10:
                if (cnt5) {
                    --cnt5;
                    ++cnt10;
                } else
                    return false;
                break;
            case 20:
                if (cnt10 && cnt5) {
                    --cnt10;
                    --cnt5;
                } else if (cnt5 >= 3) {
                    cnt5 -= 3;
                } else
                    return false;
                break;
        }
    }
    return true;
}

// 56.合并区间
vector<vector<int>> merge(vector<vector<int>>& intervals) {
    // todo
    int n = intervals.size();
    if (n < 2) return 0;  //区间数 < 2，不需要移除
    //按终点从小到大排序
    sort(intervals.begin(), intervals.end(),
         [](const auto& a, const auto& b) { return a[1] < b[1]; });
    vector<vector<int>> ans;
    int start = intervals[0][0], end = intervals[0][1];
    for (int i = 1; i < n; ++i) {
        if (intervals[i][0] <= end) {
            start = min(start, intervals[i][0]);
            end = max(end, intervals[i][1]);
        } else {
            ans.push_back(vector<int>{start, end});
            start = intervals[i][0];
            end = intervals[i][1];
        }
    }
    return ans;
}

// 738.单调递增的数字
int monotoneIncreasingDigits(int N) {
    int digits = 1, tmp = N;
    while (tmp / 10) {
        tmp /= 10;
        ++digits;
    }
}