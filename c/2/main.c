struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {

    struct ListNode* l3 = (struct ListNode*)malloc(sizeof(struct ListNode));
    struct ListNode* result = l3;
    int sum, tmp = 0;

    while ( l1 != NULL || l2 != NULL ) {

        if (l1 != NULL && l2 != NULL) {
            sum = l1->val + l2->val + tmp;
            l1 = l1->next;
            l2 = l2->next;
        } else if (l1 != NULL) {
            sum = l1->val + tmp;
            l1 = l1->next;
        } else if (l2 != NULL) {
            sum = l2->val + tmp;
            l2 = l2->next;
        }

        if (sum > 9) {
            tmp = 1;
            sum = sum % 10;
        } else {
            tmp = 0;
        }

        l3->val = sum;

        if (l1 != NULL || l2 != NULL) {
            l3->next = (struct ListNode*)malloc(sizeof(struct ListNode));
            l3 = l3->next;
        }

    }

    if (tmp != 0) {
        l3->next = (struct ListNode*)malloc(sizeof(struct ListNode));
        l3 = l3->next;
        l3->val = tmp;
    }

    l3->next = NULL;

    return result;
}
