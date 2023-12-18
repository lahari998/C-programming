#include <stdio.h>
#include <stdlib.h>

#define NO_OF_KEYS 1000
#define SELECTED_KEYS 100

struct TreeNode {
    int key;
    struct TreeNode* left;
    struct TreeNode* right;
    int height;
};

int max(int a, int b) {
    if (a > b) {
        return a;
    } else {
        return b;
    }
}

int height_of_AVL(struct TreeNode* n) {
    if (n == NULL) {
        return -1;
    }
    return n->height;
}

int getBalance(struct TreeNode* n) {
    if (n == NULL) {
        return 0;
    }
    return height_of_AVL(n->left) - height_of_AVL(n->right);
}

struct TreeNode* create(int a) {
    struct TreeNode* newnode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newnode->key = a;
    newnode->left = NULL;
    newnode->right = NULL;
    newnode->height = 0;
    return newnode;
}

struct TreeNode* rightRotate(struct TreeNode* y) {
    struct TreeNode* x = y->left;
    struct TreeNode* z = x->right;

    x->right = y;
    y->left = z;

    y->height = max(height_of_AVL(y->left), height_of_AVL(y->right)) + 1;
    x->height = max(height_of_AVL(x->left), height_of_AVL(x->right)) + 1;

    return x;
}

struct TreeNode* leftRotate(struct TreeNode* x) {
    struct TreeNode* y = x->right;
    struct TreeNode* z = y->left;

    y->left = x;
    x->right = z;

    x->height = max(height_of_AVL(x->left), height_of_AVL(x->right)) + 1;
    y->height = max(height_of_AVL(y->left), height_of_AVL(y->right)) + 1;

    return y;
}

int comparisons = 0;
int pointerOperations = 0;
struct TreeNode* insert(struct TreeNode* root, int a, int* counters) {
    if (root == NULL) {
        *counters += 1;  // Increment pointer operations
        return create(a);
    }

    *counters += 3;  // Increment pointer operations (for left/right comparison, plus a node creation)
    if (a < root->key) {
        root->left = insert(root->left, a, counters);
    } else if (a > root->key) {
        root->right = insert(root->right, a, counters);
    }

    root->height = 1 + max(height_of_AVL(root->left), height_of_AVL(root->right));

    int balance = getBalance(root);

    if (balance > 1 && a < root->left->key) {
        return rightRotate(root);
    }
    if (balance < -1 && a > root->right->key) {
        return leftRotate(root);
    }
    if (balance > 1 && a > root->left->key) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (balance < -1 && a < root->right->key) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

struct TreeNode* create_AVL(int keys[], int num_of_keys) {
    struct TreeNode* root = NULL;
    for (int i = 0; i < num_of_keys; i++) {
        root = insert(root, keys[i], &comparisons);
    }
    return root;
}

struct TreeNode* minValueNode(struct TreeNode* node) {
    struct TreeNode* current = node;
    while (current->left != NULL) {
        current = current->left;
    }
    return current;
}

struct TreeNode* deleteNode(struct TreeNode* root, int key, int* counters) {
    if (root == NULL) {
        *counters += 1;  // Increment pointer operations
        return root;
    }

    *counters += 3;  // Increment pointer operations (for left/right comparison, plus a node deletion)
    if (key < root->key) {
        root->left = deleteNode(root->left, key, counters);
    } else if (key > root->key) {
        root->right = deleteNode(root->right, key, counters);
    } else {
        if (root->left == NULL) {
            struct TreeNode* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct TreeNode* temp = root->left;
            free(root);
            return temp;
        }

        struct TreeNode* temp = minValueNode(root->right);
        root->key = temp->key;
        root->right = deleteNode(root->right, temp->key, counters);
    }
    root->height = 1 + max(height_of_AVL(root->left), height_of_AVL(root->right));

    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0) {
        return rightRotate(root);
    }
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (balance < -1 && getBalance(root->right) <= 0) {
        return leftRotate(root);
    }
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}


int main() {
    FILE* input_file = fopen("/home/lahari/input.txt", "r");
    if (input_file == NULL) {
        perror("Error opening input file");
        return 1;
    }

    int keys[NO_OF_KEYS];
    int num_of_keys = 0;
    int index = 0;

    while (index < 100) {
        for (int i = 0; i < NO_OF_KEYS; i++) {
            if (fscanf(input_file, "%d", &keys[i]) == EOF) {
                break;
            }
            num_of_keys++;
        }

        struct TreeNode* root = create_AVL(keys, num_of_keys);

        printf("\n");

        int h = height_of_AVL(root);
        printf("Height of AVL %d: %d\n", index, h);

        int selected_keys[SELECTED_KEYS];
        for (int i = 0; i < SELECTED_KEYS; i++) {
            selected_keys[i] = keys[i];
        }

        int num_keys_to_remove = SELECTED_KEYS;

        for (int i = 0; i < num_keys_to_remove; i++) {
            root = deleteNode(root, selected_keys[i], &comparisons);
        }

        int b = height_of_AVL(root);
        printf("Height of AVL after removal %d: %d\n", index, b);
        printf("Total comparisons: %d\n", comparisons);
        printf("Total pointer operations: %d\n", pointerOperations);

        num_of_keys = 0;
        index++;
    }

    fclose(input_file);
    return 0;
}

