struct ListNode* rotateRight(struct ListNode* head, int k) {
    struct ListNode *h = head, *t = NULL;
    int l = 0, n;
    for (struct ListNode *c = head ; c ; t = c, c = c->next, l++);
    for (h && (k %= l), n = l - k ; h && n-- > 1 ; h = h->next);
    return t && (t->next = head), h && (head = h->next, h->next = NULL), head;
}