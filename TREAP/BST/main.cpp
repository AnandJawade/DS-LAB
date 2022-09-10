#include <bits/stdc++.h>
using namespace std;

struct node {
    int key;
    struct node *left, *right;
};

int total_rotations3;
int key_comparison3;
int final_tree_height3;
int avg_node_height3;
int node_count3;

// A utility function to create a new BST node
struct node* newNode(int item)
{
    struct node* temp
        = (struct node*)malloc(sizeof(struct node));
    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;
}

//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------
void inorder(struct node* root)
{
    if (root != NULL) {
        inorder(root->left);
        cout << root->key << " ";
        inorder(root->right);
    }
}

//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------
struct node* insert(struct node* node, int key)
{
    /* If the tree is empty, return a new node */
    if (node == NULL )
        return newNode(key);
    if(key == node->key)
    {
        return node;
    }
    /* Otherwise, recur down the tree */
    if (key < node->key)
    {
        key_comparison3++;
        node->left = insert(node->left, key);
    }

    else
    {
        key_comparison3++;
        node->right = insert(node->right, key);
    }


    /* return the (unchanged) node pointer */
    return node;
}
//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------
struct node* minValueNode(struct node* node)
{
    struct node* current = node;
    /* loop down to find the leftmost leaf */
    while (current && current->left != NULL)
        current = current->left;

    return current;
}

//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------
struct node* deleteNode(struct node* root, int key)
{
    // base case
    if (root == NULL)
        return root;

    // If the key to be deleted is
    // smaller than the root's
    // key, then it lies in left subtree
    if (key < root->key)
    {
        key_comparison3++;
        root->left = deleteNode(root->left, key);
    }


    // key, then it lies in right subtree
    else if (key > root->key)
    {
        key_comparison3++;
        root->right = deleteNode(root->right, key);
    }


    // if key is same as root's key, then This is the node
    // to be deleted
    else {
        // node has no child
        if (root->left==NULL and root->right==NULL)
            return NULL;

        // node with only one child or no child
        else if (root->left == NULL) {
            struct node* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            struct node* temp = root->left;
            free(root);
            return temp;
        }
        // node with two children: Get the inorder successor
        // (smallest in the right subtree)
        struct node* temp = minValueNode(root->right);
        // Copy the inorder successor's content to this node
        root->key = temp->key;
        // Delete the inorder successor
        root->right = deleteNode(root->right, temp->key);
    }
    return root;
}
//-------------------------------------------------------------------------------
    //-------------------------------------------------------------------------------
    //HELPER FUNCTIONS

        int inorderk(node *temp, int h)
        {
            if(temp == NULL)
            {
                return 0;
            }
            node_count3++;

            int t1 = inorderk(temp -> left, h);

            //cout << temp -> key << " "  << h << endl ;
            int t2 = inorderk(temp -> right, h);
            avg_node_height3 = avg_node_height3+ max(t1,t2)+1;
            return max(t1,t2)+1;
        }
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//Height of tree
        void Calculate_height(node* root)
        {
            final_tree_height3 = inorderk(root,1);
            //cout << "\nHeight of the tree: " << final_tree_height2;
            //cout << "\nTotal number of rotations: " << total_rotations2;
            //cout << "\nKey comparisons: " << key_comparison2;
            //cout << "\nAverage node height: " << avg_node_height2/(double)node_count2 << endl;
            //cout << avg_node_height2 << " "  << node_count2;
            //return final_tree_height;
            cout << "BST" << ":\t\t";
            cout << final_tree_height3 <<"\t\t" << total_rotations3 << "\t\t" << key_comparison3 << "\t\t\t" << avg_node_height3/(double)node_count3 << endl;
        }


//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------

int main()
{
    struct node* root = NULL;
    int arr[] = {70, 75, 65, 60, 80};
    //tt.tra();
    FILE *f1;
    char ch[100];
    int i=1;
    int val = 0;
    int cnt = 0;

    for(i=1; i<=5; i++)
    {
        total_rotations3 = 0;
        key_comparison3 = 0;
        final_tree_height3 = 0;
        avg_node_height3 = 0;
        node_count3 = 0;


        sprintf(ch,"file%d.txt",i);
        cout << "Insert: " << arr[i-1] << "%" << "     ";
        cout << "Delete: " << 100-arr[i-1] << "%" << "     " << ch << endl;
        cout << "-------------------------------------------------------------------------------------------------------\n";
        cout << "File\t\tTree_height\tRotations\tkey_comparisons\t\tAvg_node_height\n";
        cout << "-------------------------------------------------------------------------------------------------------\n";

        f1 = fopen(ch,"r");

        while(fscanf(f1,"%d",&val) != EOF)
        {
            if(cnt %1000 < (arr[i-1]*10))
                root = insert(root, val);
            else
                root = deleteNode(root, val);

            cnt++;
        }

        Calculate_height(root);
        root = NULL;
        cout << endl << endl << endl;
        fclose(f1);
    }

    return 0;
}
