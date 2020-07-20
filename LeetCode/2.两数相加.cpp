/*
 * @lc app=leetcode.cn id=2 lang=cpp
 *
 * [2] 两数相加
 */

// @lc code=start
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
	ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
		int f = 0;
		ListNode *res = new ListNode(0);
		ListNode *pr = res;
		while (l1 != NULL || l2 != NULL || f) {
			int va = l1 == NULL ? 0 : l1->val;
			int vb = l2 == NULL ? 0 : l2->val;
			int v = va + vb + f;
			pr->next = new ListNode(v % 10);
			pr = pr->next;
			f = v >= 10 ? 1 : 0;
			if (l1 != NULL)
				l1 = l1->next;
			if (l2 != NULL)
				l2 = l2->next;
		}
		return res->next == NULL ? res : res->next;
	}
};
// @lc code=end
