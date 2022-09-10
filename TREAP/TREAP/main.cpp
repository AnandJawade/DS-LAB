#include <iostream>
#include <bits/stdc++.h>
#include <stdlib.h>
#include <cstdlib>
#include <fstream>
#include <ctime>

using namespace std;

//Node structure for treap
class Treap_Node
{
    private:
        int key;
        int priority;
        Treap_Node *left, *right;
        Treap_Node(int k,int p)
        {
            key = k;
            priority = p;
            left = NULL;
            right = NULL;
        }
        friend class Treap;
};

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
int total_rotations;
int key_comparison;
int final_tree_height;
int avg_node_height;
int node_count;

//Treap class
class Treap
{
    private:
        Treap_Node *root;
        unordered_set<int> set_priority;
        int ran_num;

    public:

//Constructors
        Treap()
        {
            root = NULL;
        }

        Treap(const Treap &T)
        {
            inorder_insert(T.root);
        }

    private:
        void inorder_insert(Treap_Node *temp)
        {
            if(temp == NULL)
            {
                return;
            }
            inorder_insert(temp -> left);
            Treap_Insert(root -> key, root -> priority);
            inorder_insert(temp -> right);
        }

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//Setting Priority of node
    public:
        int Set_priority_(int mm)
        {
            while(1)
            {
                ran_num = rand();
                ran_num = ran_num % mm;
                if(set_priority.find(ran_num) == set_priority.end())
                {
                    break;
                }
            }
            set_priority.insert(ran_num);
            return ran_num;
        }

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//ROTATIONS
    //Right rotation
    Treap_Node* Rotate_right(Treap_Node *temp)
    {
        total_rotations++;
        //temp variable
        Treap_Node* temp1;
        Treap_Node* rotate_temp;

        //Right Rotation
        rotate_temp = temp -> left;
        temp1 = rotate_temp -> right;
        rotate_temp -> right = temp;
        temp -> left = temp1;

        return rotate_temp;
    }

    //Left rotation
    Treap_Node* Rotate_left(Treap_Node *temp)
    {
        total_rotations++;
        //temp variable
        Treap_Node* temp1;
        Treap_Node* rotate_temp;

        //Left Rotation
        rotate_temp = temp -> right;
        temp1 = rotate_temp -> left;
        rotate_temp -> left = temp;
        temp -> right = temp1;

        return rotate_temp;
    }
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//INSERTION
    public:
        void Treap_Insert(int key,int priority)
        {
            root = Insert_helper(root, key, priority);
        }

    private:
        Treap_Node* Insert_helper(Treap_Node* temp, int key, int priority)
        {
            //Adding new node into the tree
            if (temp == NULL)
            {
                temp = new Treap_Node(key,priority);
                return temp;
            }

            if(key == temp -> key)
            {
                return temp;
            }

            //If key is smaller than key of temp
            if (key < temp -> key)
            {
                key_comparison++;
                // Insert in left subtree
                temp -> left = Insert_helper(temp -> left, key, priority);

                // Rotation if heap property violated
                if (temp -> left -> priority < temp -> priority)
                {
                    temp = Rotate_right(temp);
                }
            }
            else
            {
                key_comparison++;
                // Insert in right subtree
                temp -> right = Insert_helper(temp -> right, key, priority);

                // Rotation if heap property violated
                if (temp -> right -> priority < temp -> priority)
                {
                    temp = Rotate_left(temp);
                }
            }
            return temp;
        }

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//DELETION
    public:
        void Treap_Delete(int key,int priority)
        {
            root = Delete_helper(root, key, priority);
        }

    private:
        Treap_Node* Delete_helper(Treap_Node* temp, int key1, int priority)
        {
            if (temp == NULL)
            {
                //cout << "key not present\n";
                return temp;
            }

            if (key1 < temp -> key)
            {
                key_comparison++;
                temp -> left = Delete_helper(temp -> left, key1, priority);
            }

            else if (key1 > temp->key)
            {
                key_comparison++;
                temp -> right = Delete_helper(temp -> right, key1, priority);
            }

            // When key is at temp
            // If left child is NULL
            else if (temp -> left == NULL)
            {
                Treap_Node* delete_temp = temp -> right;
                set_priority.erase(temp -> priority);
                delete(temp);
                temp = delete_temp;
            }

            // If right child is NULL
            else if (temp -> right == NULL)
            {
                Treap_Node* delete_temp = temp->left;
                set_priority.erase(temp -> priority);
                delete(temp);
                temp = delete_temp;
            }

            // If key is at temp and both left and right are not NULL
            else if (temp -> left -> priority > temp -> right -> priority)
            {
                temp = Rotate_left(temp);
                temp -> left = Delete_helper(temp -> left, key1, priority);
            }
            else
            {
                temp = Rotate_right(temp);
                temp -> right = Delete_helper(temp -> right, key1, priority);
            }

            return temp;
        }

//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------
//SEARCH PART
    private:
        bool Treap_seacrch_helper(Treap_Node* temp2,int k)
        {
            bool t ;
            if(temp2 == NULL)
            {
                return false;
            }
            if(temp2 -> key == k)
            {
                //If we find the key
                return true;
            }
            //if key is less than k
            if(temp2 -> key > k && temp2 -> left!= NULL)
            {
                t = Treap_seacrch_helper(temp2 -> left,k);
            }
            //if key is greater than k
            if(temp2 -> key < k && temp2 -> right!= NULL)
            {
                t = Treap_seacrch_helper(temp2 -> right,k);
            }
            return t;
        }

    public:
        bool Treap_Search(int k)
        {
            if(Treap_seacrch_helper(root,k))
            {
                //cout << "key is present in tree " << endl;
                return true;
            }
            return false;
        }
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//PRINT PART
    private:
        // helper function to traverse the Treap in preorder fashion
        // and print the edges in the required format in the dot file
        void Treap_PrintHelper(const Treap_Node *temp, ofstream &fp)
        {
            if (!temp) // if temp is NULL
                return;
            if (temp == root) // add the label and root in the dot file
            {
                fp << "label = \" treap " << " \";\n";
                fp << temp->key << " [root = true]\n";
            }
            fp << temp->key << " [label=\"<f0>|<f1>" << temp->key << "|<f2> " << temp->priority << " |<f3> \"];\n";
            if (temp->left) // if left child exists
            {
                fp << temp->key << ":f0 -> " << temp->left -> key << ":f1\n";
                Treap_PrintHelper(temp->left, fp);
            }
            if (temp->right) // if right child exists
            {
                fp << temp->key << ":f3 -> " << temp->right->key << ":f1\n";
                Treap_PrintHelper(temp->right, fp);
            }
        }

    public:
        void Treap_Print(const char *filename)
        {
            if(root == NULL)
            {
                cout << "Treap is empty\n";
            }
            ofstream fp;
            string dot_file = "";
            dot_file = dot_file + filename + ".dot"; // name of graphviz file
            string png_file = "";
            png_file = png_file + filename + ".png"; // name of png file
            fp.open(dot_file.c_str()); // open dot file for writing
            fp << "digraph g {\n";
            fp << "node [shape=record, height=0.1];\n";
            Treap_PrintHelper(root, fp);
            fp << "}";
            fp.close(); // close dot file
            string str = "dot -Tpng "+ dot_file + " -o " + png_file;
            const char *command = str.c_str();
            system(command); // system call to run the dot file using graphviz
            //cout << "Tree Printed Successfully! Please check the " << png_file << " file.\n";
        }

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
    public:
        void tra()
        {
            postorder_delete(root);
            set_priority.clear();
            root = NULL;
        }
        int inorderk(Treap_Node *temp, int h)
        {
            if(temp == NULL)
            {
                return 0;
            }
            node_count++;

            int t1 = inorderk(temp -> left, h);

            //cout << temp -> key << " "  << h << endl ;
            int t2 = inorderk(temp -> right, h);
            avg_node_height = avg_node_height+ max(t1,t2)+1;
            return max(t1,t2)+1;
        }
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//Height of tree
        int Calculate_height()
        {
            final_tree_height = inorderk(root,1);
            //cout << "\nHeight of the tree: " << final_tree_height;
            //cout << "\nTotal number of rotations: " << total_rotations;
            //cout << "\nKey comparisons: " << key_comparison;
            //cout << "\nAverage node height: " << avg_node_height/(double)node_count << endl;
            //cout << avg_node_height << " "  << node_count;
            cout << "Treap" << ":\t\t";
            cout << final_tree_height <<"\t\t" << total_rotations << "\t\t" << key_comparison << "\t\t\t" << avg_node_height/(double)node_count << endl;
            return final_tree_height;
        }

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//Destructor
        void postorder_delete(Treap_Node* temp)
        {
            if(temp == NULL)
            {
                return;
            }
            postorder_delete(temp -> left);
            postorder_delete(temp -> right);
            Treap_Node* temp1=temp;
            delete temp1;
        }
    public:
        ~Treap()
        {
            postorder_delete(root);
        }
};

//---------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------
int main()
{
    srand(time(0));
    Treap tt;

    int arr[] = {70, 75, 65, 60, 80};
    int val = 0;
    int cnt = 0;
    unordered_set<int> set_pri;
    int ran_num1 = 0;
    FILE *f1;
    char ch[100];
    int i=1;

    cout << "Choose from below two options." <<endl;
    cout << "Press the number and enter" << endl;
    cout << "1. Check height,total rotations,avg node height,key comparisons for 5 test case files present in folder." <<endl;
    cout << "2. Perform insert, delete, search, print operation on empty treap." << endl;
    cout << "Press any other number to exit." << endl << endl;

    int in_;
    cin >> in_;

    if(in_ == 1)
    {
        for(int i=1; i<=5; i++)
        {
            total_rotations = 0;
            key_comparison = 0;
            final_tree_height = 0;
            avg_node_height = 0;
            node_count = 0;

            sprintf(ch,"file%d.txt",i);
            cout << "Insert: " << arr[i-1] << "%" << "     ";
            cout << "Delete: " << 100-arr[i-1] << "%" << "     " << ch << endl;
            cout << "-------------------------------------------------------------------------------------------------------\n";
            cout << "DS\t\tTree_height\tRotations\tkey_comparisons\t\tAvg_node_height\n";
            cout << "-------------------------------------------------------------------------------------------------------\n";

            f1 = fopen(ch,"r");

            while(fscanf(f1,"%d",&val) != EOF)
            {
                ran_num1 = tt.Set_priority_(30000);
                //if(!tt.Treap_Search(val))
                //{
                    if(cnt %1000 < (arr[i-1]*10))
                        tt.Treap_Insert(val,ran_num1);
                    else
                        tt.Treap_Delete(val,0);
                //}
                cnt++;
            }

            tt.Calculate_height();
            tt.tra();

            cout << endl << endl << endl;
            fclose(f1);
        }
    }

    if(in_ == 2)
    {
        while(1)
        {
            cout << "Press the number to perform operation and press enter:\n";
            cout << "1. Insertion \n";
            cout << "2. Deletion \n";
            cout << "3. Search \n";
            cout << "4. Print treap\n";
            cout << "Any other number to exit\n\n";

            cin >> in_;
            if(in_ == 1)
            {
                cout << "Enter the value you want to insert : ";
                cin >> val;
                ran_num1 = tt.Set_priority_(2000);
                if(tt.Treap_Search(val))
                {
                    cout << "Key is already present in tree\n";
                }
                else
                {
                    tt.Treap_Insert(val,ran_num1);
                    cout << "Key is inserted\n";
                }
                cout << endl;
            }
            else if(in_ == 2)
            {
                cout << "Enter the value you want to delete : ";
                cin >> val;
                if(tt.Treap_Search(val))
                {
                    tt.Treap_Delete(val,0);
                    cout << "Key is deleted\n";
                }
                else
                {
                    cout << "Key is not present in tree\n";
                }

                cout << endl;
            }
            else if(in_ == 3)
            {
                cout << "Enter the value you want to search : ";
                cin >> val;
                if(tt.Treap_Search(val))
                {
                    cout << "Key is present in tree\n";
                }
                else
                {
                    cout << "Key is not present in tree\n";
                }
                cout << endl;
            }
            else if(in_ == 4)
            {
                tt.Treap_Print("image");
                cout << "Image file is generated. Check the folder\n" << endl;
            }
            else
            {
                break;
            }
        }
    }


    cout<<endl;
    //cout << tt.Treap_Search(115);
    //tt.Treap_Print("image");
    //tt.tra();

    return 0;
}
