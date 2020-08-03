/*
 * @Author: shawn233
 * @Date: 2020-07-31 16:30:55
 * @LastEditors: shawn233
 * @LastEditTime: 2020-07-31 16:31:22
 * @Description: 141. Linked List Cycle
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
    // 20ms (21.57%) 9.8MB (12.61%) solution 2: hash set
    bool hasCycle2(ListNode *head) {
        unordered_set<ListNode *> visited;
        ListNode *ptr = head;
        
        while (ptr) {
            if (visited.find(ptr) != visited.end())
                return true;
            visited.insert(ptr);
            ptr = ptr->next;
        }
        
        return false;
    }
    
    // 12ms (71.37%) 7.8MB (51.14%) solution 1: two pointers
    bool hasCycle(ListNode *head) {
        ListNode *fast, *slow;
        fast = slow = head;
        
        do {
            if (fast == NULL || fast->next == NULL)
                return false;
            fast = fast->next->next;
            slow = slow->next;
        } while (fast != slow);
        
        return true;
    }
};