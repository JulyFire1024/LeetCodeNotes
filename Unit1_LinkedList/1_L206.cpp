#include<bits/stdc++.h>
#include"../DataStruct.cpp"
using namespace std;
class Solution {
public:
    ListNode* reverseList(ListNode* head) 
    {
        if(head==NULL ||head->next==NULL)
            return head;
        ListNode* res = reverseList(head->next);

        head->next->next = head;
        head->next = nullptr;
        return res;
    }

    ListNode* reverseList_2(ListNode* head)  //µü´ú
    {
        ListNode* prev = nullptr;
        ListNode* curr = head;
        while (curr) {
            ListNode* next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        return prev;
    }
};

int main()
{
    cout<<"First Leetcode"<<endl;
    vector<int> a={1,2,3,4,5};
    ListNode *head =CreateList(a);
    DispList(head);
    Solution mysolution;
    ListNode *res =mysolution.reverseList(head);
    DispList(res);
    int wait;
    cin>>wait;
}
