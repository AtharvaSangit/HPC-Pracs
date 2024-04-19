#include <iostream>
#include <queue>
#include <omp.h>

using namespace std;

// struct node {
//     node *left, *right;
//     int data;
// };

// node *insert(node *root, int data) {
//     if (!root) {
//         root = new node;
//         root->left = nullptr;
//         root->right = nullptr;
//         root->data = data;
//         return root;
//     }

//     queue<node *> q;
//     q.push(root);

//     while (!q.empty()) {
//         node *temp = q.front();
//         q.pop();

//         if (!temp->left) {
//             temp->left = new node;
//             temp->left->left = nullptr;
//             temp->left->right = nullptr;
//             temp->left->data = data;
//             return root;
//         } else {
//             q.push(temp->left);
//         }

//         if (!temp->right) {
//             temp->right = new node;
//             temp->right->left = nullptr;
//             temp->right->right = nullptr;
//             temp->right->data = data;
//             return root;
//         } else {
//             q.push(temp->right);
//         }
//     }

//     return root;
// }
struct node
{
    int data;
    node *left;
    node *right;
};

// Function to create a new node
node *createNode(int value)
{
    node *newNode = new node();
    newNode->data = value;
    newNode->left = nullptr;
    newNode->right = nullptr;
    return newNode;
}

// Function to insert a new node into the binary tree
void insertNode(node *&root, int value)
{
    if (root == nullptr)
    {
        root = createNode(value);
    }
    else
    {
        if (value <= root->data)
        {
            insertNode(root->left, value);
        }
        else
        {
            insertNode(root->right, value);
        }
    }
}

void bfs(node *head)
{
    if (!head)
        return;

    queue<node *> q;
    q.push(head);

    while (!q.empty())
    {
        int qSize = q.size();
#pragma omp parallel for
        for (int i = 0; i < qSize; i++)
        {
            node *currNode = nullptr;
#pragma omp critical
            {
                currNode = q.front();
                q.pop();
                cout << "\t" << currNode->data;
            }
#pragma omp critical
            {
                if (currNode->left)
                    q.push(currNode->left);
                if (currNode->right)
                    q.push(currNode->right);
            }
        }
    }
}

int main()
{
    // node *root = nullptr;
    // int data;
    // char ans;

    // do
    // {
    //     cout << "\n enter data=>";
    //     cin >> data;

    //     root = insert(root, data);

    //     cout << "do you want insert one more node?";
    //     cin >> ans;
    // } while (ans == 'y' || ans == 'Y');
    node *root = nullptr; // Initialize an empty binary tree

    // Insert nodes into the binary tree
    insertNode(root, 100);
    insertNode(root, 150);
    insertNode(root, 50);
    insertNode(root, 35);
    insertNode(root, 75);
    insertNode(root, 125);
    insertNode(root, 275);
    bfs(root);

    return 0;
}
