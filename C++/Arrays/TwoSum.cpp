#include <unordered_map>

// Given an array of integers nums and an integer target, return indices of the two numbers such that they add up to target.

// You may assume that each input would have exactly one solution, and you may not use the same element twice.

// You can return the answer in any order.

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        std::unordered_map<int, int> sumMap;

        for (int i = 0; i < nums.size(); i++) {
            int remainingDifference = target - nums[i];
            if (sumMap.contains(remainingDifference)) {
                std::vector<int> output = {sumMap.at(remainingDifference), i};
                return output;
            }

            sumMap[nums[i]] = i;
        }

        std::vector<int> output = {0, 0};

        return output;
    }
};
