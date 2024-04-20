/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* mergeSort(ListNode* head){
        if(head == nullptr || head->next == nullptr) return head;
        ListNode* dummy = new ListNode(0);
        dummy->next = head;
        ListNode* fast = dummy, *slow = dummy;
        while(fast && fast->next){
            fast = fast->next->next;
            slow = slow->next;
        }
        ListNode* head2 = slow->next;
        slow->next = nullptr;
        head = mergeSort(head);
        head2 = mergeSort(head2);
        ListNode* p1 = head, *p2 = head2, *pre = dummy;
        while(p1 && p2){
            if(p1->val <= p2->val){
                pre->next = p1;
                p1 = p1->next;
            }else{
                pre->next = p2;
                p2 = p2->next;
            }
            pre = pre->next;
        }
        pre->next = p1 ? p1 : p2;
        return dummy->next;
    }

    ListNode* sortList(ListNode* head) {
        if(head == nullptr) return nullptr;
        return mergeSort(head);
    }
};
