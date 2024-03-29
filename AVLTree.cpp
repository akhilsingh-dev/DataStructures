#include <iostream>

using namespace std;

//reference taken from geeks for geeks


class Node{
public:
    int key;
    Node *left;
    Node *right;
    int height;
};

int height(Node *N){
    if (N == NULL)
        return 0;
    return N->height;
}

int max(int a, int b){
    return (a > b)? a : b;
}

Node* newNode(int key){
    Node* node = new Node();
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return(node);
}

Node *rightRotate(Node *y){
    Node *x = y->left;
    Node *T2 = x->right;
    // Perform rotation
    x->right = y;
    y->left = T2;
    // Update heights
    y->height = max(height(y->left),height(y->right)) + 1;
    x->height = max(height(x->left),height(x->right)) + 1;
    // Return new root
    return x;
}

Node *leftRotate(Node *x){
    Node *y = x->right;
    Node *T2 = y->left;
    // Perform rotation
    y->left = x;
    x->right = T2;
    // Update heights
    x->height = max(height(x->left),height(x->right)) + 1;
    y->height = max(height(y->left),height(y->right)) + 1;
    // Return new root
    return y;
}

int getBalance(Node *N){
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

Node * minValueNode(Node* node){
    Node* current = node;

    while(current->left != NULL)
        current = current->left;

    return current;
}

void preOrder(Node *root){
    if(root != NULL){
        cout << root->key << " ";
        preOrder(root->left);
        preOrder(root->right);
    }
}



// INSERT AND DELETE...

Node* insert(Node* node, int key){
    /* 1. Perform the normal BST insertion */
    if (node == NULL)
        return(newNode(key));

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node;

    /* 2. Update height of this ancestor node */
    node->height = 1 + max(height(node->left),height(node->right));

    /* 3. Get the balance factor of this ancestor
        node to check whether this node became
        unbalanced */
    int balance = getBalance(node);
    // If this node becomes unbalanced, then
    // there are 4 cases

    // Left Left Case
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && key > node->left->key){
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && key < node->right->key)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    /* return the (unchanged) node pointer */
    return node;
}

Node* deleteNode(Node* root,int key){
    if(root == NULL){
        return root;
    }


    if(key < root->key){
        root->left = deleteNode(root->left,key);
        //return root->left;
    }
    else if(key > root->key){
        root->right = deleteNode(root->right,key);
        //return root->right;
    }
    else{
        if(root->left == NULL || root->right == NULL){
            Node *temp = root->left ? root->left : root->right;
            if(temp==NULL){
                temp = root;
                root = NULL;
            }
            else{
                *root = *temp;
            }
            delete(temp);
        }
        else{
            Node* temp = minValueNode(root->right);
            root->key = temp->key;
            root->right = deleteNode(root->right,temp->key);
        }
    }
    if(root==NULL){
        return root;
    }
    root->height = 1 + max(height(root->left),height(root->right));
    int balance = getBalance(root);


    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    // Left Right Case
    if (balance > 1 && getBalance(root->left) < 0)
    {
        root->left =  leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Right Case
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    // Right Left Case
    if (balance < -1 && getBalance(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;

}


// Driver Code
int main(){
    Node *root = NULL;

    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 25);

    /* The constructed AVL Tree would be
              30
            /   \
           20   40
          / \  /   \
        10 25 NULL 50
    */
    preOrder(root);
    root = deleteNode(root, 40);
    root = deleteNode(root, 50);
    cout<<endl;
    cout << getBalance(root) << endl << endl;
    preOrder(root);

    return 0;
}
