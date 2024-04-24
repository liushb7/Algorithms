/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    int start;
    // unordered_map<int, TreeNode*> father;
    TreeNode* father[100010];
    TreeNode* startNode;

    void dfs(TreeNode* root, TreeNode* from){
        if(root == nullptr) return;
        father[root->val] = from;
        if(root->val == start){
            startNode = root;
        }
        dfs(root->left, root);
        dfs(root->right, root);
    }

    int maxDepth(TreeNode* root, TreeNode* from){
        if(root == nullptr) return -1;
        int res = -1;
        if(root->left != from){
            res = max(res, maxDepth(root->left, root));
        }
        if(root->right != from){
            res = max(res, maxDepth(root->right, root));
        }
        if(father[root->val] != from){
            res = max(res, maxDepth(father[root->val], root));
        }
        return res + 1;
    }

    int amountOfTime(TreeNode* root, int start) {
        this->start = start;
        dfs(root, nullptr);
        return maxDepth(startNode, nullptr);
    }
};
