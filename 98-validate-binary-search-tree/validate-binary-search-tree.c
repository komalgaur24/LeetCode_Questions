/**
 * Definition for a binary tree node.
 * struct TreeNode {
 * int val;
 * struct TreeNode *left;
 * struct TreeNode *right;
 * };
 */

bool validate(struct TreeNode* node, long min_val, long max_val) {
    if (node == NULL) {
        return true;
    }
    if (node->val <= min_val || node->val >= max_val) {
        return false;
    }
    return validate(node->left, min_val, node->val) && validate(node->right, node->val, max_val);
}

bool isValidBST(struct TreeNode* root) {
    return validate(root, -2147483649L, 2147483648L); 
}