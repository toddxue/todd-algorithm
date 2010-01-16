#include "TAP.h"
#include "binary_tree.h"
#include <string.h>

bool check(int n) {
    Binary_Tree* root = new Binary_Tree[n];
    int* o1 = new int[n];
    int* o2 = new int[n];
    Binary_Tree_root(root, 0);
    for (int i = 1; i < n; ++i)
        Binary_Tree_parent_left(root+i-1, root+i, i);

    bool r = true;
    do {
        binary_tree_inorder(root, o1);
        binary_tree_inorder_recursive(root, o2);
        if (0 != memcmp(o1, o2, n * sizeof(n))) {
            r = false;
            root->print(); printf("\n");
            for (int i = 0; i < n; ++i) printf("%d ", o1[i]); printf("\n");
            for (int i = 0; i < n; ++i) printf("%d ", o2[i]); printf("\n");
            break;
        }
    } while (next_binary_tree(root));
    
    delete[] o2;
    delete[] o1;
    delete[] root;
    return r;
}

int main(int argc, char* argv[]) {
    OK_SUM();

    OK(check(1));
    OK(check(2));
    OK(check(3));
    OK(check(4));
    OK(check(5));
    OK(check(6));
    OK(check(7));
    OK(check(8));
    OK(check(9));
    OK(check(10));
    OK(check(11));
    OK(check(12));
    return 0;
}
