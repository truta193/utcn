#include <iostream>
#include <cstring>

typedef struct _treeNode {
    char val;
    struct _treeNode *left;
    struct _treeNode *right;
} TreeNodeT;

TreeNodeT *newNode(char key) {
    TreeNodeT *l = (TreeNodeT *) malloc(sizeof(TreeNodeT));
    l->val = key;
    return l;
}

int ind = 0;
TreeNodeT *interpretInput(char *input, int start, int end) {
    if (input[ind] == '\0') {
        return nullptr;
    }

    if (input[ind] == '#') {
        return nullptr;
    }

    TreeNodeT *n = newNode(input[ind]);
    ++ind;
    n->left = interpretInput(input, start, end - 1);
    ++ind;
    n->right = interpretInput(input, start + 1, end);


    return n;
}

int calculate(int a, int b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
    }
}

int solveExpr(TreeNodeT *root) {
    if (root == nullptr) {
        return 0;
    }

    if (root->val >= '0' && root->val <= '9')
        return root->val;

    int a = solveExpr(root->left) - '0';
    int b = solveExpr(root->right) - '0';

    printf("%d %c %d\n", a, root->val, b);
    return calculate(a,b, root->val);

}

int main() {
    TreeNodeT *root;
    char *expr = strdup("-9*4-54");
    root = interpretInput(expr);
    std::cout << solveExpr(root);
    return 0;
}
