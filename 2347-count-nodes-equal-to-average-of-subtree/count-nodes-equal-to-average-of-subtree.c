typedef struct TreeNode TN_t;
typedef struct { int sum; int n; } sn_t;
sn_t traverse(TN_t* node, int* count) {
    sn_t l=(sn_t){0}, r=(sn_t){0};
    if(node->left){ l=traverse(node->left, count); }
    if(node->right){ r=traverse(node->right, count); }
    sn_t result=(sn_t){l.sum+r.sum+node->val, l.n+r.n+1};
    (*count)+=(result.sum/result.n)==node->val;
    return result;
}
int averageOfSubtree(TN_t* root) {
    int result=0;
    if(root){ traverse(root, &result); }
    return result;
}
 
