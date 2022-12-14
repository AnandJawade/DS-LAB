#include <iostream>
#include <stack>
#include <fstream>
using namespace std;

class AVL_Node
{
    private:
        int key;
        int bf; // balance factor bf = height(left subtree) ? height(right subtree)
        AVL_Node *LChild, *RChild;
        AVL_Node(int k)
        {
            key = k;
            bf = 0;
            LChild = NULL;
            RChild = NULL;
        }
        friend class AVL_Tree;
};

class AVL_Tree
{
    private:
        AVL_Node *root;

    //-------------------------------------------------------------------------------
        //Helper functions

        AVL_Node* Rotate_right(AVL_Node *temp)
        {
            //Temp is the node where we are going to perform rotate operation
            //rotate-temp is the left child of temp
            AVL_Node *rotate_temp = temp -> LChild;

            //Here we are rearranging the pointers for balancing temp
            temp -> LChild = rotate_temp -> RChild;
            rotate_temp -> RChild = temp;

            //Balance factor of both nodes now will become zero
            temp -> bf = 0;
            rotate_temp -> bf = 0;

            return rotate_temp;
        }
    //-------------------------------------------------------------------------------
        AVL_Node* Rotate_left_right(AVL_Node *temp)
        {
            //Temp is the node where we are going to perform rotate operation
            //Below are two temp pointers
            AVL_Node *rot_left, *rot_right;

            rot_right = temp;
            rot_left = temp -> LChild;
            temp = rot_left -> RChild;

            //Rotate left operation
            rot_left -> RChild = temp -> LChild;
            temp -> LChild = rot_left;

            //Balancing bf
            if(temp -> bf >= 0)
            {
                rot_left -> bf = 0;
            }
            else
            {
                rot_left -> bf = 1;
            }

            //Rotate right operation
            rot_right -> LChild = temp -> RChild;
            temp -> RChild = rot_right;

            //Balancing bf
            if(temp -> bf <= 0)
            {
                rot_right -> bf = 0;
            }
            else
            {
                rot_right -> bf = -1;
            }
            temp -> bf = 0;
            return temp;
        }
    //-------------------------------------------------------------------------------
        AVL_Node* Rotate_left(AVL_Node *temp)
        {
            //Temp is the node where we are going to perform rotate operation
            //rotate-temp is the right child of temp
            AVL_Node *rotate_temp = temp -> RChild;

            //Here we are rearranging the pointers for balancing temp
            temp -> RChild = rotate_temp -> LChild;
            rotate_temp -> LChild = temp;

            //Balance factor of both nodes now will become zero
            temp -> bf = 0;
            rotate_temp -> bf =0;

            return rotate_temp;
        }
    //-------------------------------------------------------------------------------
         AVL_Node* Rotate_right_left(AVL_Node *temp)
        {
            //Temp is the node where we are going to perform rotate operation
            //Below are two temp pointers
            AVL_Node *rot_left, *rot_right;

            rot_right = temp -> RChild;
            rot_left = temp;
            temp = rot_right -> LChild;

            //Rotate left operation
            rot_right -> LChild = temp -> RChild;
            temp -> RChild = rot_right;

            //Balancing factor
            if(temp -> bf <= 0)
            {
                rot_right -> bf = 0;
            }
            else
            {
                rot_right -> bf = -1;
            }

            //Rotate right operation
            rot_left -> RChild = temp -> LChild;
            temp -> LChild = rot_left;

            //Balancing factor
            if(temp -> bf >= 0)
            {
                rot_left -> bf = 0;
            }
            else
            {
                rot_left -> bf = 1;
            }
            temp -> bf = 0;
            return temp;
        }
    //-------------------------------------------------------------------------------
    //-------------------------------------------------------------------------------

    public:
        //Constructors
        AVL_Tree()
        {
            root = NULL;
        }

        AVL_Tree(const AVL_Tree &T)
        {
            inorder_insert(T.root);
        }
        void inorder_insert(AVL_Node *temp)
        {
            if(temp == NULL)
            {
                return;
            }
            inorder(temp -> LChild);
            AVL_Insert(root -> key);
            inorder(temp -> RChild);
        }

    //-------------------------------------------------------------------------------
    //-------------------------------------------------------------------------------
    //INSERT PART

        void AVL_Insert(int k)
        {
            stack<AVL_Node *> stk;
            //Insert key
            AVL_Node *current_node = root;
            AVL_Node *parent_node = NULL;
            AVL_Node *temp_node = NULL;
            //Traversing the tree from root to child where we want to insert key k
            while (current_node != NULL)
            {
                //If key is already present in tree then return
                if (k == current_node->key)
                {
                    cout << k <<" is already present in the tree" << endl;
                    return ;
                }

                parent_node = current_node;
                stk.push(parent_node);

                //If the value k is less than current node key then go to left child
                //Else goto right child
                if (k < current_node->key)
                {
                    current_node = current_node->LChild;
                }
                else
                {
                    current_node = current_node->RChild;
                }
            }
            current_node = new AVL_Node(k);

            //If tree is empty initially
            if (parent_node == NULL)
            {
                root = current_node;
                return;
            }

            //Add new node to the tree
            if (k < parent_node -> key)
            {
                parent_node -> LChild = current_node;  //LChild
            }
            else
            {
                parent_node -> RChild = current_node; //RChild
            }

            //Balance factor adjustment
            //Changing all the balance factors of nodes from root to new added node if necessary
            while (!stk.empty())
            {
                parent_node = stk.top();
                stk.pop();

                //If new node is in left of its parent node then increment balance factor else decrement
                if (parent_node -> LChild == current_node)
                {
                    parent_node -> bf++ ;
                }
                else
                {
                    parent_node -> bf-- ;
                }

                //If bf is zero of current node then no need to change the bf of parent node
                if (parent_node -> bf == 0)
                {
                    break;
                }

                //If bf is 1 or -1 then make current node equal to parent node
                if (parent_node -> bf == 1 || parent_node -> bf == -1)
                {
                    current_node = parent_node;
                }
                else
                {
                    //If bf is 2 or -2,
                    //Checking the balance factors of current node and parent node
                    //and applying rotation on parent node
                    if (parent_node -> bf < 0)
                    {
                        if (current_node -> bf < 0)
                        {
                            temp_node = Rotate_left(parent_node);
                            cout << "Rotate_left  " << endl;
                        }
                        else
                        {
                            temp_node = Rotate_right_left(parent_node);
                            cout << "Rotate_right_left  " << endl;
                        }
                    }
                    else
                    {
                        if (current_node -> bf > 0)
                        {
                            temp_node = Rotate_right(parent_node);
                            cout<<"Rotate_right  "<< endl;
                        }
                        else
                        {
                            temp_node = Rotate_left_right(parent_node);
                            cout<<"Rotate_left_right  "<< endl;
                        }
                    }

                    //Checking if stack is empty or not
                    if(!stk.empty())
                    {
                        AVL_Node *q = stk.top();
                        if (temp_node -> key < q -> key)
                        {
                            q -> LChild = temp_node;
                        }
                        else
                        {
                            q -> RChild = temp_node;
                        }
                    }
                    else
                    {
                        //If stack is empty then we will
                        root = temp_node;
                        return;
                    }
                    break;
                }
            }
            //End while
            if (stk.empty())
            {
                root = parent_node;
            }
        }

    //-------------------------------------------------------------------------------
    //-------------------------------------------------------------------------------
    //DELETE PART

        void AVL_Delete(int k)
        {
            if(root == NULL)
            {
                cout << "Tree is empty";
                return ;
            }
            AVL_Node *parent_node = NULL;
            AVL_Node *current_node = root, *q;
            stack<AVL_Node*> st;

            //Searching for k key node
            while(current_node != NULL)
            {
                if(k == current_node -> key)
                    break;

                parent_node = current_node;
                st.push(parent_node); //Pushing nodes in stack from root to k value node

                if(k < current_node -> key)
                {
                    current_node = current_node -> LChild;
                }
                else
                {
                    current_node = current_node -> RChild;
                }
            }

            //If node is not present in tree
            if(current_node == NULL)
            {
                cout << k << " is not present in the tree" << endl;
                return ;
            }

            //If current node have both children
            if(current_node -> LChild != NULL && current_node -> RChild != NULL)
            {
                parent_node = current_node;
                st.push(parent_node);

                //Finding in-order successor
                q = current_node -> RChild;
                while(q -> LChild != NULL)
                {
                    parent_node = q;
                    st.push(parent_node);
                    q = q -> LChild;
                }
                //Interchanging in-order successor and current node
                current_node -> key = q -> key;
                current_node = q;
            }

            if(current_node -> LChild != NULL)
            {
                q = current_node -> LChild;
            }
            else
            {
                q = current_node -> RChild;
            }

            //current node is delete node, q is deleted nodes child node
            if(parent_node == NULL)
            {
                root = q;
            }
            else
            {
                if(current_node == parent_node -> LChild)
                {
                    parent_node -> LChild = q;
                }
                else
                {
                    parent_node -> RChild = q;
                }

                //Adjusting balance factor from the deleted node
                while(!st.empty())
                {
                    parent_node = st.top();
                    st.pop();


                    if(current_node -> key < parent_node -> key)
                    {
                        //If current node is left child
                        parent_node -> bf--;
                    }
                    else
                    {
                        //If current node is right child
                        parent_node -> bf++;
                    }

                    if(parent_node -> bf == -1 || parent_node -> bf == 1)
                    {
                        break;
                    }

                    if(parent_node -> bf != 0)
                    {
                        //Let q point be a higher subtree
                        if(parent_node -> bf > 0)
                            q = parent_node -> LChild;
                        else
                            q = parent_node -> RChild;

                        //Rotation on parent node depending on bf of parent node and q node
                        if(q -> bf == 0)
                        {
                            if(parent_node -> bf > 0)
                            {
                                AVL_Node *temp_node = Rotate_right(parent_node);
                                cout << "Rotate_right  " << endl;
                                temp_node -> bf = -1;
                                temp_node -> RChild -> bf = 1;
                                parent_node = temp_node;
                            }
                            else
                            {
                                AVL_Node *temp_node = Rotate_left(parent_node);
                                cout << "Rotate_left  " << endl;
                                temp_node -> bf = 1;
                                temp_node -> LChild -> bf = -1;
                                parent_node = temp_node;
                            }

                            if(!st.empty())
                            {
                                //p_pr is previous node of parent node
                                //Attaching p_pr and parent node after rotation
                                AVL_Node *p_pr = st.top();
                                if (p_pr -> key < parent_node -> key)
                                    p_pr -> RChild = parent_node;
                                else
                                    p_pr -> LChild = parent_node;
                            }
                            else
                            {
                                root = parent_node;
                            }
                            break;
                        }

                        //Rotation on parent node depending on bf of parent node and q node
                        if(parent_node -> bf > 0)
                        {
                            if(q -> bf > 0)
                            {
                                parent_node = Rotate_right(parent_node);
                                cout << "Rotate_right  " << endl;
                            }
                            else
                            {
                                parent_node = Rotate_left_right(parent_node);
                                cout << "Rotate_left_right  " << endl;
                            }
                        }
                        else
                        {
                            if(q -> bf < 0)
                            {
                                parent_node = Rotate_left(parent_node);
                                cout << "Rotate_left  " << endl;
                            }
                            else
                            {
                                parent_node = Rotate_right_left(parent_node);
                                cout << "Rotate_right_left  " << endl;
                            }
                        }

                        if (!st.empty())
                        {
                            //p_pr is previous node of parent node
                            //Attaching p_pr and parent node after rotation
                            AVL_Node *p_pr = st.top();
                            if (p_pr -> key < parent_node -> key)
                                p_pr -> RChild = parent_node;
                            else
                                p_pr -> LChild = parent_node;
                        }
                        else
                            root = parent_node;
                    }
                    //q becomes the new current node
                    q = parent_node;
                }
                //End while
            }
            delete current_node;
        }
    //-------------------------------------------------------------------------------
    //-------------------------------------------------------------------------------
    //SEARCH PART
        bool AVL_seacrch_helper(AVL_Node *temp2,int k)
        {

            if(temp2 == NULL)
            {
                return false;
            }
            if(temp2 -> key == k)
            {
                //If we find the key
                cout << "key is present in tree " << endl;
                return true;
            }
            //if key is less than k
            if(temp2 -> key > k && temp2 -> LChild!= NULL)
            {
                return AVL_seacrch_helper(temp2 -> LChild,k);
            }
            //if key is greater than k
            if(temp2 -> key < k && temp2 -> RChild!= NULL)
            {
                return AVL_seacrch_helper(temp2 -> RChild,k);
            }
            return false;
        }
        bool AVL_Search(int k)
        {
            if(!AVL_seacrch_helper(root,k))
            {
                cout << "key is not present in tree " << endl;
                return false;
            }
            return true;
        }

    //-------------------------------------------------------------------------------
    //-------------------------------------------------------------------------------
    //PRINT PART

    private:
        // helper function to traverse the AVL tree in preorder fashion
        // and print the edges in the required format in the dot file
        void AVL_PrintHelper(const AVL_Node *temp, ofstream &fp)
        {
            if (!temp) // if temp is NULL
                return;

            if (temp == root) // add the label and root in the dot file
            {
                fp << "label = \" tree " << " \";\n";
                fp << temp->key << " [root = true]\n";
            }

            fp << temp->key << " [label=\"<f0>|<f1>" << temp->key << "|<f2> " << temp->bf << " |<f3> \"];\n";

            if (temp->LChild) // if left child exists
            {
                fp << temp->key << ":f0 -> " << temp->LChild -> key << ":f1\n";
                AVL_PrintHelper(temp->LChild, fp);
            }

            if (temp->RChild) // if right child exists
            {
                fp << temp->key << ":f3 -> " << temp->RChild->key << ":f1\n";
                AVL_PrintHelper(temp->RChild, fp);
            }
        }

    public:
        void AVL_Print(const char *filename)
        {
            ofstream fp;
            string dot_file = "";
            dot_file = dot_file + filename + ".dot"; // name of graphviz file
            string png_file = "";
            png_file = png_file + filename + ".png"; // name of png file

            fp.open(dot_file.c_str()); // open dot file for writing
            fp << "digraph g {\n";
            fp << "node [shape=record, height=0.1];\n";

            AVL_PrintHelper(root, fp);

            fp << "}";
            fp.close(); // close dot file

            string str = "dot -Tpng "+ dot_file + " -o " + png_file;

            const char *command = str.c_str();

            system(command); // system call to run the dot file using graphviz

            //cout << "Tree Printed Successfully! Please check the " << png_file << " file.\n";
        }
    //-------------------------------------------------------------------------------
    //-------------------------------------------------------------------------------
    //HELPER FUNCTIONS

        void tra(){inorder(root);}
    private:
        void inorder(AVL_Node *temp)
        {
            if(temp == NULL)
            {
                return;
            }
            inorder(temp -> LChild);
            cout << temp -> key << " " << temp -> bf << endl ;
            inorder(temp -> RChild);
        }
        void postorder_delete(AVL_Node *temp)
        {
            if(temp == NULL)
            {
                return;
            }
            postorder_delete(temp -> LChild);
            postorder_delete(temp -> RChild);
            AVL_Node *temp1=temp;
            delete temp1;
        }
    public:
        ~AVL_Tree()
        {
            postorder_delete(root);
        }
};

int main()
{
    //AVL_Tree object
    AVL_Tree tt;

    cout << "\nA tree is already created" << endl;
    cout << "Now you can perform operations on tree" << endl;
    cout << "All the rotations happened will be printed" << endl << endl;

    int arr[] = {14,17,11,7,53};
    int in_;
    for(int i=0;i<sizeof(arr)/sizeof(int);i++){
        tt.AVL_Insert(arr[i]);
    }

    while(1)
    {
        cout << "\nEnter the number to perform the operation given below:" << endl;
        cout << "1. Insertion" <<endl;
        cout << "2. Deletion " <<endl;
        cout << "3. Search   " <<endl;
        cout << "4. Print    " <<endl;
        cout << "5. Exit    " <<endl;
        cout << endl;
        int zz;
        cin >> zz;
        if(zz == 1)
        {
            cout << "Enter the value you want to insert: ";
            cin >> in_;
            tt.AVL_Insert(in_);
            cout << endl;
        }
        else if(zz == 2)
        {
            cout << "Enter the value you want to delete: ";
            cin >> in_;
            tt.AVL_Delete(in_);
            cout << endl;
        }
        else if(zz == 3)
        {
            cout << "Enter the value you want to search: ";
            cin >> in_;
            tt.AVL_Search(in_);
            cout << endl;
        }
        else if(zz == 4)
        {
            tt.AVL_Print("image");
            cout << "An image.png file is generated in same folder" << endl;
            cout << endl;
        }
        else if(zz == 5)
        {
            break;
        }
    }

    //tt.tra();

    return 0;
}
