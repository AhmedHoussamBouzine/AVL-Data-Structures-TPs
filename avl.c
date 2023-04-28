//Ahmed houssam BOUZINE  II-BDCC1

#include <stdio.h>
#include <string.h>
#include <malloc.h>

typedef struct Etudiant
{
    char nom[25];
    int matricule;
    float moyenne;
} Etudiant;

typedef struct Node
{
    struct Node *left, *right;
    Etudiant *etudiant;
    int height;
} Node;

Etudiant* createEtudiant()
{
    Etudiant *etudiant;
    printf("Entrez le nom de l'etudiant: ");
    fgets(etudiant->nom, 25, stdin);
    printf("Entrez le matricule de l'etudiant: ");
    scanf("%d", &etudiant->matricule);
    printf("Entrez la moyenne de l'etudiant: ");
    scanf("%f", &etudiant->moyenne);
    return etudiant;
}

Node* createNode(Etudiant* etudiant)
{
    Node* node;
    node->etudiant = malloc(sizeof(Etudiant));
    node->etudiant->matricule = etudiant->matricule;
    node->etudiant->moyenne = etudiant->moyenne;
    for (int i = 0; i < 25; i++)
    {
        node->etudiant->nom[i] = etudiant->nom[i];
    }
    node->left = malloc(sizeof(Node));
    node->right = malloc(sizeof(Node));
    node->height = 0;
    return node;
}

int height(Node *Node)
{
    if (Node == NULL)
        return -1;
    return Node->height;
}
int max(int a, int b)
{
    return (a > b) ? a : b;
}
int getBalance(Node *node)
{
    if (node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}

Node *rightRotate(Node *y)
{
    Node *x = y->left, *t = x->right;
    x->right = y;
    y->left = t;
    y->height = 1 + max(height(y->left), height(y->right));
    x->height = 1 + max(height(x->left), height(x->right));
    return x;
}

Node *leftRotate(Node *x)
{
    Node *y = x->right, *t = y->left;
    y->left = x;
    x->right = t;
    x->height = 1 + max(height(x->left), height(x->right));
    y->height = 1 + max(height(y->left), height(y->right));
    return y;
}

Node *insertNode(Node *node, Etudiant *etudiant)
{
    if (node == NULL)
        return createNode(etudiant);
    if (etudiant->moyenne < node->etudiant->matricule)
    node->left = insertNode(node->left, etudiant);
    else if (etudiant->moyenne > node->etudiant->matricule)
        node->right = insertNode(node->right, etudiant);
    else return node;
    node->height = 1 + max(height(node->left), height(node->right));
    int balance = getBalance(node);
    // Left Left Case
    if (balance > 1 && etudiant->matricule < node->left->etudiant->matricule)
        return rightRotate(node);
    if (balance > 1 && etudiant->matricule > node->left->etudiant->matricule)
    { // Left Right Case
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    // Right Right Case
    if (balance < -1 && etudiant->matricule > node->right->etudiant->matricule)
        return leftRotate(node);
    if (balance < -1 && etudiant->matricule < node->right->etudiant->matricule)
    { // Right Left Case
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}

Node *minValueNode(Node *node)
{
    Node *current = node;
    while (current->left != NULL)
        current = current->left;

    return current;
}

Node *deleteNode(Node *root, Etudiant *etudiant)
{
    // Comme pour la suppression dans un ABR
    if (root == NULL)
        return root;
    if (etudiant->matricule < root->etudiant->matricule)
        root->left = deleteNode(root->left, etudiant);
    else if (etudiant->matricule > root->etudiant->matricule)
        root->right = deleteNode(root->right, etudiant);
    else
    {
        if ((root->left == NULL) || (root->right == NULL))
        { // Node with only one child or no child
            Node *temp = root->left ? root->left : root->right;
            if (temp == NULL)
            { // No child case
                free(root);
                root = NULL;
            }
            else
            { // One child case
                *root = *temp;
                free(temp);
            }
        }
        else
        { // Node with two children: Get the inorder successor
            Node *temp = minValueNode(root->right);
            root->etudiant->matricule = temp->etudiant->matricule;            // Copy the inorder successor's data to this node
            root->right = deleteNode(root->right, temp->etudiant);           // Delete the inorder successor
        }
    }
    if (root == NULL)
        return root;                                                 // If the tree had only one node then return
    root->height = 1 + max(height(root->left), height(root->right)); // Update height of the current node
    int balance = getBalance(root);                                  // Get balance factor of the current node
    // Les 4 cas de déséquilibre
    // Left Left Case
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);
    if (balance > 1 && getBalance(root->left) < 0)
    { // Left Right Case
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    // Right Right Case
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);
    if (balance < -1 && getBalance(root->right) > 0)
    { // Right Left Case
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}

Node **find(Node **node, Etudiant *etudiant)
{
    if (*node == NULL)
        return NULL;
    if ((*node)->etudiant->matricule < etudiant->matricule)
        return find(&(*node)->right, etudiant);
    if ((*node)->etudiant->matricule > etudiant->matricule)
        return find(&(*node)->left, etudiant);
    return node;
}


int main(){
    //test
}