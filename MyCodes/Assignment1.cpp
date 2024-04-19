#include <iostream>
#include <queue>
#include <omp.h>

using namespace std;

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
