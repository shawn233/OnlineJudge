/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    // 12ms (97%) solution 1
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        if (inorder.empty())
            return NULL;
        else {
            unordered_map<int, int> mp;
            for (int i = 0; i < inorder.size(); ++ i)
                mp.insert(make_pair(inorder[i], i));
            return buildTree_(
                        inorder, 0, inorder.size()-1,
                        postorder, 0, postorder.size()-1, mp);
        }
    }
    
    TreeNode* buildTree_(vector<int>& inorder, int in_l, int in_r,
                            vector<int>& postorder, int post_l, int post_r,
                            unordered_map<int, int>& mp) {
        if (in_l == in_r)
            return new TreeNode(inorder[in_l]);
        
        int in_root = mp[postorder[post_r]];
        
        TreeNode* root = new TreeNode(inorder[in_root]);
        if (in_root != in_l)
            root->left = buildTree_(
                                inorder, in_l, in_root-1,
                                postorder, post_l, in_root-in_l+post_l-1, mp);
        if (in_root != in_r)
            root->right = buildTree_(
                                inorder, in_root+1, in_r,
                                postorder, in_root-in_l+post_l, post_r-1, mp);
        return root;
    }
};
