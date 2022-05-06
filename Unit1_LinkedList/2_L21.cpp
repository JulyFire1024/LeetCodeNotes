#include <bits/stdc++.h>
#include "../DataStruct.cpp"
using namespace std;

class Solution
{
public:
    ListNode *mergeTwoLists(ListNode *l1, ListNode *l2)
    {
        if (l1 == nullptr)
        {
            return l2;
        }
        else if (l2 == nullptr)
        {
            return l1;
        }
        else if (l1->val < l2->val)
        {
            l1->next = mergeTwoLists(l1->next, l2);
            return l1;
        }
        else
        {
            l2->next = mergeTwoLists(l1, l2->next);
            return l2;
        }
    }
    ListNode *mergeTwoLists2(ListNode *l1, ListNode *l2)
    {
        ListNode *head = new ListNode(-1);
        ListNode *cur = head;
        while(l1!=NULL&&l2!=NULL)
        {
            if(l1->val >l2->val)
            {   
                cur->next = l2;
                l2=l2->next;
            }
            else
            {
                cur->next = l1;
                l1=l1->next;
            }
            cur = cur->next;
        }
        if(l1!=NULL)
            cur->next = l1;
        if(l2!=NULL)
            cur->next = l2;

        return head->next;
    }
};

int main()
{
    vector<int> a={1,2,4};
    vector<int> b={1,3,4};
    ListNode *L1= CreateList(a);
    ListNode *L2= CreateList(b);
    Solution mysolution;
    ListNode *res =mysolution.mergeTwoLists2(L1,L2);
    DispList(res);
    int wait;
    cin>>wait;
}