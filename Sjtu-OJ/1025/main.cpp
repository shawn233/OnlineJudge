#include <iostream>
#include <cstdio>
#define LEFT -3e9
#define RIGHT 3e9

using namespace std;

struct Node {
    long long left, right;
    bool cover;
    Node * lnode, * rnode;
    Node (long long l, long long r): left(l), right(r), cover(false), lnode(NULL),
            rnode(NULL) {}
};

class Tree {
private:
    Node * root;

    void cleanTree(Node * node) {
        if(node->lnode != NULL)
            cleanTree(node->lnode);
        if(node->rnode != NULL)
            cleanTree(node->rnode);
        delete node;
    }

    void insertInterval(long long left, long long right, Node * node) {
        if (node->cover)
            return;
        if (left == node->left && right == node->right) {
            node->cover = true;
            return;
        }
        long long mid = (node->left+node->right)/2;
        if(right<=mid) {
            if(node->lnode == NULL)
                node->lnode = new Node(node->left, mid);
            return insertInterval(left, right, node->lnode);
        } else if(left > mid) {
            if(node->rnode == NULL)
                node->rnode = new Node(mid+1, node->right);
            return insertInterval(left, right, node->rnode);
        } else {
            if(node->lnode == NULL)
                node->lnode = new Node (node->left, mid);
            if(node->rnode == NULL)
                node->rnode = new Node (mid+1, node->right);
            insertInterval(left, mid, node->lnode);
            insertInterval(mid+1, right, node->rnode);
        }
    }

    long long getAns(Node * node) {
        if (node->cover) {
            //cout << "COVER --- " << endl << "l -- " << node->left << " r -- " << node->right << endl;
            return (node->right-node->left+1);
        }
        if (node->left == node->right)
            return 0;
        long long tmp = 0;
        if(node->lnode)
            tmp += getAns(node->lnode);
        if(node->rnode)
            tmp += getAns(node->rnode);
        return tmp;
    }

public:
    Tree() {
        root = new Node (LEFT+RIGHT, RIGHT+RIGHT);
    }

    ~Tree() {
        cleanTree(root);
    }

    void insertInterval(long long left, long long right) {
        insertInterval(left, right, root);
    }

    long long getAns() {
        return getAns(root);
    }
};

int main() {
    long long n, l, r;

    freopen("in", "r", stdin);

    scanf("%lld", &n);
    Tree tree;
    for (long long i = 0; i < n; ++ i) {
        scanf("%lld %lld", &l, &r);
        if (l == r)
            continue;
        tree.insertInterval(l+RIGHT, r+RIGHT-1);
    }
    printf("%lld\n", tree.getAns());

    fclose(stdin);

    return 0;
}
