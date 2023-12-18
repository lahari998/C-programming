#include <stdio.h>
#include <stdlib.h>


#define NO_OF_KEYS 1000
#define SELECTED_KEYS 100

struct TreeNode {
    int key;
    struct TreeNode* left;
    struct TreeNode* right;
};

struct TreeNode* create_node(int a) {
    struct TreeNode* newnode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newnode->key = a;
    newnode->left = NULL;
    newnode->right = NULL;
    return newnode;
}

struct TreeNode* insert_node(struct TreeNode* root, int a, int counters[2]) {
    if (root == NULL) {
        counters[1]++; // Pointer operation
        return create_node(a);
    }

    if (a < root->key) {
        counters[0]++; // Comparison
        root->left = insert_node(root->left, a, counters);
    } else if (a > root->key) {
        counters[0]++; // Comparison
        root->right = insert_node(root->right, a, counters);
    }

    counters[1]++; // Pointer operation
    return root;
}

struct TreeNode* BST(int keys[], int a) {
    struct TreeNode* root = NULL;
    for (int i = 0; i < a; i++) {
        int counters[2] = {0, 0}; // Initialize comparison and pointer operation counters
        root = insert_node(root, keys[i], counters);
    }
    return root;
}

int height_of_BST(struct TreeNode* root) {
    if (root == NULL) {
        return -1;
    } else {
        int left_height = height_of_BST(root->left);
        int right_height = height_of_BST(root->right);
        if (left_height >= right_height) {
            return (left_height + 1);
        } else {
            return (right_height + 1);
        }
    }
}

struct TreeNode* minValueNode(struct TreeNode* node) {
    struct TreeNode* current = node;
    while (current->left != NULL) {
        current = current->left;
    }
    return current;
}

struct TreeNode* deleteNode(struct TreeNode* root, int key) {
    if (root == NULL) {
        return root;
    }

    if (key < root->key) {
        root->left = deleteNode(root->left, key);
    } else if (key > root->key) {
        root->right = deleteNode(root->right, key);
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
        root->right = deleteNode(root->right, temp->key);
    }
    return root;
}

void measureWork(int keys[], int n) {
    struct TreeNode* root = NULL;
    int comparisonCount = 0;
    int pointerOperationCount = 0;

    for (int i = 0; i < n; i++) {
        int counters[2] = {0, 0};
        root = insert_node(root, keys[i], counters);
        comparisonCount += counters[0];
        pointerOperationCount += counters[1];
    }

    printf("Total comparisons: %d\n", comparisonCount);
    printf("Total pointer operations: %d\n", pointerOperationCount);
}
int main() {
    FILE* input_file = fopen("/home/lahari/input.txt", "r");
    if (input_file == NULL) {
        perror("Error opening input file");
        return 1;
    }

    int keys[NO_OF_KEYS];
    int num_of_keys = 0;
    int Count = 0;
   

    while (Count < 100) {
        for (int i = 0; i < NO_OF_KEYS; i++) {
            if (fscanf(input_file, "%d", &keys[i]) == EOF) {
                break;
            }
            num_of_keys++;
        }

        struct TreeNode* root = BST(keys, num_of_keys);

        printf("\n");

        int h = height_of_BST(root);
        printf("Height of BST %d: %d\n", Count, h);

        int selected_keys[SELECTED_KEYS];
        for (int i = 0; i < SELECTED_KEYS; i++) {
            selected_keys[i] = keys[i];
        }

        int num_keys_to_remove = SELECTED_KEYS;

        for (int i = 0; i < num_keys_to_remove; i++) {
            root = deleteNode(root, selected_keys[i]);
        }

        int l = height_of_BST(root);
        printf("Height of BST after removal %d: %d\n", Count, l);

        num_of_keys = 0;
          measureWork(keys, NO_OF_KEYS);
        Count++;
    }

    fclose(input_file);
    return 0;
}



