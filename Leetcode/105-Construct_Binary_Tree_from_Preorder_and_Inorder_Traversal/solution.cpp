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
    // 12ms (98%) solution 1
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        if (preorder.empty()) 
            return NULL;
        else {
            unordered_map<int, int> mp;
            for (int i = 0; i < inorder.size(); ++ i)
                // note: make_pair gets types implicitly
                mp.insert(make_pair(inorder[i], i));
            return buildTree_(
                        preorder, 0, preorder.size()-1,
                        inorder, 0, inorder.size()-1, mp);
        }
    }
    
    TreeNode* buildTree_(vector<int>& preorder, int pre_l, int pre_r, 
                         vector<int>& inorder, int in_l, int in_r,
                         unordered_map<int, int>& mp) {
        //printf("pre_l: %d pre_r: %d in_l: %d in_r: %d\n", pre_l, pre_r, in_l, in_r);
        if (pre_l == pre_r)
            return new TreeNode(preorder[pre_l]);
        // root is `preorder[pre_l]`
        // find it in `inorder`    
        int in_root = mp[preorder[pre_l]];
        //printf("in_root: %d\n", in_root);
        
        TreeNode* root = new TreeNode(preorder[pre_l]);
        if (in_root - in_l > 0)
            root->left = buildTree_(
                            preorder, pre_l+1, in_root-in_l+pre_l,
                            inorder, in_l, in_root-1, mp);
        if (in_r - in_root > 0)
            root->right = buildTree_(
                            preorder, in_root-in_l+pre_l+1, pre_r,
                            inorder, in_root+1, in_r, mp);
        return root;
    }
};
