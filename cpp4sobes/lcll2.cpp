struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

#include <unordered_map>
#include <stdio.h>
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        std::unordered_map<int, ListNode*> m;
        m[0] = head;
        
        int curr=0;
        ListNode* tmp = head->next;
        ListNode* tsugi = tmp;
        while (tsugi) {
            tmp = tsugi->next;
            m[++curr] = tsugi;
			printf("i: %d, val: %d\n",curr,m[curr]->val);
            tsugi = tmp;
        }
		// printf("last noted: %d\n", tsugi);
		printf("size: %d\n", curr+1);
        if (curr==0) {
			return nullptr;
		}
        
        int idxToPop = (1+curr)-n;
		printf("n: %d\nitp: %d\n",n,idxToPop);

		if (idxToPop==0) return m[1];

		m[idxToPop-1]->next = m[idxToPop+1];
        
        return head;
    }
};

int main() {
	Solution s;
	ListNode* n = new ListNode(1, nullptr);
	printf("initial:\n1 ");
	ListNode* head = n;
	for (int i=2; i<=2; i++) {
		printf("%d ",i);
		ListNode* m = new ListNode(i, nullptr);
		n->next = m;
		n = m;
	}
	printf("\n\n");

	ListNode* q = s.removeNthFromEnd(head, 2);
	printf("new:\n");
	while (q) {  // Changed from q->next to q
		printf("%d ", q->val);
		q = q->next;
	}
	printf("\n");

	return 0;
}
