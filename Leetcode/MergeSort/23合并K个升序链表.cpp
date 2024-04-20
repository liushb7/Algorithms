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
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2){
        if(list1 == nullptr) return list2;
        if(list2 == nullptr) return list1;
        ListNode* dummy = new ListNode(0), *pre = dummy;
        ListNode* p1 = list1, *p2 = list2;
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

    ListNode* mergeSort(vector<ListNode*>& lists, int l, int r){
        if(l > r) return nullptr;
        if(l == r) return lists[l];
        int mid = (l + r) >> 1;
        ListNode* l1 = mergeSort(lists, l, mid);
        ListNode* l2 = mergeSort(lists, mid + 1, r);
        return mergeTwoLists(l1, l2);
    }

    ListNode* mergeKLists(vector<ListNode*>& lists) {
        int n = lists.size();
        return mergeSort(lists, 0, n - 1);
    }
};
