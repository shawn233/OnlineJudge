/*
 * @Author: shawn233
 * @Date: 2020-07-31 17:12:53
 * @LastEditors: shawn233
 * @LastEditTime: 2020-07-31 17:13:32
 * @Description: 142. Linked List Cycle II
 */ 

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    // 12ms (74.45%) 7.8MB (49.85%) solution 1: two pointes
    // perfect solution
    // Reference: https://leetcode.com/problems/linked-list-cycle-ii/discuss/44781/Concise-O(n)-solution-by-using-C%2B%2B-with-Detailed-Alogrithm-Description
    ListNode *detectCycle(ListNode *head) {
        ListNode *slow, *fast, *entry;        
        slow = fast = entry = head;
        
        while (fast && fast->next) {
            fast = fast->next->next;
            slow = slow->next;
            if (slow == fast) {
                // now this is math
                while (slow != entry) {
                    slow = slow->next;
                    entry = entry->next;
                }
                return entry;
            }
        }
        
        // if you're here, there's no cycle 
        return NULL;
    }
};