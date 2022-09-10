#include <bits/stdc++.h>
#include <cstdlib>
using namespace std;

//Defining node here
class node
{
    public:
        int data;
        int node_count;  //to count number of nodes in right subtree
        node *left,*right;  
        bool left_thread;    
        bool right_thread;
    node(int t)
    {
        data = t;
        node_count = 0;
        left = NULL;
        right = NULL;
        left_thread = true;
        right_thread = true;
    }

    node *root1;
    node(const node& N)
    {
        preorder(N.root1);

    }
    void preorder(node *r)
    {
        if(r == NULL)
        {
            return;
        }

        root1 = Insertion(root1,r->data);
        if (r->left_thread == false)
        {
            preorder(r->left);
        }
        cout << r-> data << " ";
        if (r->right_thread == false)
        {
            preorder(r->right);
        }
    }
    node* Insertion(node *root, int value)
    {
        node *temp = new node(value);
        //First element in the tree is added here
        if(root == NULL)
        {
            temp -> node_count++;
            return temp;
        }

        node *current = root;
        node *prev = NULL;
        //Traversing from root to leaf
        //Searching new position where new node can be added
        while(current != NULL)
        {
            prev = current ;
            if(value < current->data)
            {
                if(current -> left_thread == false)
                {
                    current = current -> left;
                }
                else
                {
                    break;
                }
            }

            else if(value > current->data)
            {
                if(current -> right_thread == false)
                {
                    current = current -> right;
                }
                else
                {
                    break;
                }
            }

            else if(value == current->data)
            {
                cout << "Error: " << value << " is already present in tree\n";
                return root;
            }
        }

        //New node is added here
        if(value < prev -> data)
        {
            temp -> left = prev -> left;
            temp -> right = prev;
            prev -> left_thread = false;
            prev -> left = temp;
        }
        else if(value > prev -> data)
        {
            temp -> right = prev -> right;
            temp -> left = prev;
            prev -> right_thread = false;
            prev -> right = temp;
        }
        if(temp -> right_thread == false)
        {
            temp -> node_count = temp -> node_count + temp -> right -> node_count;
        }
        return root;
    }
};

//Linked list
class list_node
{
    public:
        int data;
        list_node *next;

    list_node(int t)
    {
        data = t;
        next = NULL;
    }
};

//For printing tree
class print_node
{
    public:
        node *n;
        print_node *next;

    print_node(node *p)
    {
        n = p;
        next = NULL;
    }
};

/*
//For split function
class split_node
{
    public:
        node *left;
        node *right;

    split_node()
    {
        left = NULL;
        right = NULL;
    }
};
*/
//-------------------------------------------------------------------------------
//Most of the functions are present in BST class
int flag;

class BST
{
    public:
    //Part 1
    //Insertion into BST takes place here
    node* Insertion(node *root, int value)
    {
        node *temp = new node(value);
        //First element in the tree is added here
        if(root == NULL)
        {
            temp -> node_count++;
            return temp;
        }

        node *current = root;
        node *prev = NULL;
        //Traversing from root to leaf
        //Searching new position where new node can be added
        while(current != NULL)
        {
            prev = current ;
            if(value < current->data)
            {
                if(current -> left_thread == false)
                {
                    current = current -> left;
                }
                else
                {
                    break;
                }
            }

            else if(value > current->data)
            {
                if(current -> right_thread == false)
                {
                    current = current -> right;
                }
                else
                {
                    break;
                }
            }

            else if(value == current->data)
            {
                flag=0;
                cout << "Error: " << value << " is already present in tree\n";
                return root;
            }
        }

        //New node is added here
        if(value < prev -> data)
        {
            temp -> left = prev -> left;
            temp -> right = prev;
            prev -> left_thread = false;
            prev -> left = temp;
        }
        else if(value > prev -> data)
        {
            temp -> right = prev -> right;
            temp -> left = prev;
            prev -> right_thread = false;
            prev -> right = temp;
        }
        if(temp -> right_thread == false)
        {
            temp -> node_count = temp -> node_count + temp -> right -> node_count;
        }
        flag=1;
        return root;
    }

    //-----------------------------------------------------------------------------
    //Part 2
    //Search Operation
    node* Search(node *temp,int value)
    {
        if(temp == NULL)
        {
            cout<<"\n Tree is empty \n";
            return NULL;
        }
        if(temp -> data == value)
        {
            return temp;
        }
        while(temp)
        {
            if(value == temp -> data)
            {
                return temp;
            }
            else if(value < temp -> data && temp -> left_thread == false)
            {
                temp = temp -> left;
            }
            else if(value > temp -> data && temp -> right_thread == false)
            {
                temp = temp -> right;
            }
            else
            {
                break;
            }
        }
        return NULL;
    }
    //------------------------------------------------------------------------------
    //Part 3
    //Delete operation

    void Search3(node *temp,int value)
    {
        if(temp == NULL)
        {
            cout<<"\n Tree is empty \n";
            return ;
        }
        if(temp -> data == value)
        {
            return ;
        }
        while(temp)
        {
            if(value == temp -> data)
            {
                temp -> node_count--;
                return ;
            }
            else if(value < temp -> data && temp -> left_thread == false)
            {
                temp = temp -> left;
            }
            else if(value > temp -> data && temp -> right_thread == false)
            {
                //Keeping the count of nodes in right subtree
                temp -> node_count--;
                temp = temp -> right;
            }
            else
            {
                break;
            }
        }
    }

    //Node with two children case
    node* case_1(node *root, node *temp, node *prev)
    {
        node *prev_succ = temp;
        node *succ = NULL;

        if(temp -> left_thread == false)
        {
            prev_succ = succ;
            succ = temp -> left;
            while(succ -> right_thread == false)
            {
                prev_succ = succ;
                succ = succ -> right;
            }
        }
        else if(temp -> right_thread == false)
        {
            prev_succ = succ;
            succ = temp -> right;
            while(succ -> left_thread == false)
            {
                prev_succ = succ;
                succ = succ -> left;
            }
        }
        else
        {
            return NULL;
        }

        temp -> data = succ -> data;

        if(succ -> left_thread == true && succ -> right_thread == true)
        {
            root = case_3(root, succ, prev_succ);
        }
        else
        {
            root = case_2(root, succ, prev_succ);
        }

        return root;
    }

    //Node with one child case
    node* case_2(node *root, node *temp, node *prev)
    {
        node *child;
        if (temp->left_thread == false)
        {
            child = temp->left;
        }
        else
        {
            child = temp->right;
        }

        if(prev == NULL)
        {
            root = child;
        }
        else if (temp == prev->left)
        {
            prev->left = child;
        }
        else
        {
            prev->right = child;
        }

        node *s = Successor(temp);
        node *p = predecessor(temp);
        if (temp->left_thread == false)
        {
            p->right = s;
        }
        else if(temp->right_thread == false)
        {
            s->left = p;
        }
        delete(temp);
        return root;
    }

    //Leaf node case
    node* case_3(node *root, node *temp, node*prev)
    {
        if(prev == NULL)
            {
                root = NULL;
            }
            else if(temp == prev -> left)
            {
                prev -> left = temp -> left;
                prev -> left_thread = true;
            }
            else if(temp == prev -> right)
            {
                prev -> right = temp -> right;
                prev -> right_thread = true;
            }
        delete(temp);
        return root;
    }

    //Delete function
    node* delete_element(node *root,int value)
    {
        int flag =0;
        node *prev = NULL;
        node *temp = root;
        Search3(root, value);

        //Search operation
        while(temp)
        {
            if(value == temp -> data)
            {
                flag = 1;
                break;
            }
            else if(value < temp -> data && temp -> left_thread == false)
            {
                prev = temp;
                temp = temp -> left;
            }
            else if(value > temp -> data && temp -> right_thread == false)
            {
                prev = temp;
                //temp -> node_count--;
                temp = temp -> right;
            }
            else
            {
                break;
            }
        }

        //If value is not present in tree
        if(flag == 0)
        {
            cout<< "\nElement not present in tree";
            return root;
        }

        //If value is present in tree
        //There are 3 cases here
        if(temp -> left_thread == false && temp -> right_thread == false)
        {
            // Case 1 : Node with 2 children
            root = case_1(root,temp,prev);
        }
        else if(temp -> left_thread == false || temp -> right_thread == false)
        {
            // Case 2 : Node with 1 child
            root = case_2(root,temp,prev);
        }
        else
        {
            // Case 3 : Leaf node
            root = case_3(root,temp,prev);
        }

        cout<< "\nElement is deleted successfully";
        return root;
    }
    //-------------------------------------------------------------------------------
    //Part 4
    //Reverse in-order traversal
    //Function to find predecessor
    node* predecessor(node *temp)
    {
        if(temp -> left_thread == true)
        {
            return temp -> left;
        }
        else
        {
            temp = temp -> left;
        }

        while(temp -> right_thread == false)
        {
            temp = temp -> right;
        }
        return temp;
    }

    //Reverse in-order traversal using threads
    list_node* reverse_inorder(node *root)
    {
        node *temp;
        temp = root;
        if(temp == NULL)
        {
            cout << "Currently the tree is empty\n";
            return NULL;
        }

        //To reach maximum element in tree
        while(temp -> right != NULL)
        {
            temp = temp -> right;
        }

        list_node *head = new list_node(temp -> data);

        list_node *temp2 = head;
        //Started printing from here
        while(temp != NULL)
        {
            temp = predecessor(temp);
            if(temp != NULL){
                cout << temp ->data << " " << temp << endl;
                temp2 -> next = new list_node(temp -> data);
                temp2 = temp2 -> next;
            }
        }
        return head;
    }
    //--------------------------------------------------------------------------------
    //Part 5
    //Finding Successor
    node* Successor(node *temp)
    {
        if(temp -> right_thread == true)
        {
            return temp -> right;
        }
        else
        {
            temp = temp -> right;
        }

        while(temp -> left_thread == false)
        {
            temp = temp -> left;
        }
        return temp;
    }

    //----------------------------------------------------------------------------------
    //Part 6
    //Split(k) function
    vector<node*> split_k(node *root, int k)
    {
        vector<node*> ans(2, NULL);
        if (root == NULL || root -> data == k)
        {
            return ans;
        }
        if (k < root->data)
        {
            if(root->left_thread == true)
            {
                ans[0]=NULL;
                ans[1]=root;
            }
            else
            {
                vector<node *> t(2, NULL);
                t = split_k(root->left, k);
                root->left = t[1];
                ans[1] = root;
                ans[0] = t[0];
            }
            return (ans);
        }
        if (k > root->data)
        {
            if(root->right_thread == true)
            {
                ans[1]=NULL;
                ans[0]=root;
            }
            else
            {
                vector<node *> t(2, NULL);
                t = split_k(root->right, k);
                ans[1] = t[1];
                root->right = t[0];
                ans[0] = root;
            }
            return ans;
        }
        else
        {
            ans[0] = root;
            ans[1] = root->right;
            root->right=NULL;
            return ans;
        }
    }

    vector<node*> Split(node *root,int k)
    {
        vector<node*> ans;
        ans = split_k(root, k);
        return ans;
    }

    void inorder(node *root)
    {
        if(root -> left_thread == false )
        {
            inorder(root -> left);
        }
        cout << root -> data << " ";
        if(root -> right_thread == false )
        {
            inorder(root -> right);
        }
    }

    //----------------------------------------------------------------------------------
    //Part 7
    //All elements between k1 and k2
    list_node* All_elements_between(node *root,int k1,int k2)
    {
        //Search k2 first
        node *temp = Search(root,k2);
        list_node *head = new list_node(temp -> data);
        int n = k2 - k1;
        //Traverse from k2 to k1
        while(temp -> data > k1)
        {
            temp = predecessor(temp);
            list_node *h = new list_node(temp -> data);
            h -> next = head;
            head = h;
            h = NULL;
            delete(h);
        }
        return head;
    }

    //--------------------------------------------------------------------------------------
    //Part 8
    //k-th largest element
    //node count of right subtree is stored in every node
     void Search2(node *temp,int value)
    {
        if(temp == NULL)
        {
            cout<<"\n Tree is empty \n";
            return ;
        }
        if(temp -> data == value)
        {
            return ;
        }
        while(temp)
        {
            if(value == temp -> data)
            {
                temp -> node_count++;
                return ;
            }
            else if(value < temp -> data && temp -> left_thread == false)
            {
                temp = temp -> left;
            }
            else if(value > temp -> data && temp -> right_thread == false)
            {
                //Keeping the count of nodes in right subtree
                temp -> node_count++;
                temp = temp -> right;
            }
            else
            {
                break;
            }
        }
    }

    //kth largest function starts here
    node* kth_largest_element(node *root,int k)
    {
        if(k < 1)
        {
            return NULL;
        }
        node *temp;
        temp = root;
        cout <<endl;
        int cnt = temp -> node_count;
        while(temp){
            if(cnt == k)
            {
                return temp;
            }
            if(temp -> left_thread == true && temp -> right_thread == true)
            {
                break;
            }

            if(cnt > k)
            {
                temp = temp -> right;
                cnt = temp -> node_count;
            }
            else if(cnt < k)
            {
                k = k - cnt;
                temp = temp -> left;
                cnt = temp -> node_count;
            }
        }
        return NULL;
    }

    //----------------------------------------------------------------------------------
    //Part 9
    //Print part
    void Print(node *root)
    {
        node *temp1;
        if(root == NULL)
        {
            cout << "\nTree is empty";
            return;
        }
        FILE *f;
        f = fopen("image.dot","w");
        fprintf(f,"digraph g{\n");
        fprintf(f,"label = tree  %d\n",root -> data);
        fprintf(f," %d[root = true]\n",root -> data);
        print_node *print;
        print_node *temp;
        print_node *print_end= new print_node(root);
        print = print_end;
        while(print)
        {
            temp1 = print -> n;
            if(temp1 -> left_thread == false)
            {
                fprintf(f,"%d",temp1 -> data);
                fprintf(f," -> ");
                fprintf(f,"%d;\n",temp1 -> left -> data);
                temp = new print_node(temp1 -> left);
                print_end -> next = temp;
                print_end =  temp;
            }
            if(temp1 -> left_thread == true && temp1 -> left != NULL)
            {
                fprintf(f,"%d",temp1 -> data);
                fprintf(f," -> ");
                fprintf(f,"%d",temp1 -> left -> data);
                fprintf(f," [style = dotted]; \n");
            }
            if(temp1 -> right_thread == false)
            {
                fprintf(f,"%d",temp1 -> data);
                fprintf(f," -> ");
                fprintf(f,"%d;\n",temp1 -> right -> data);
                temp = new print_node(temp1 -> right);
                print_end -> next = temp;
                print_end = temp;
            }
            if(temp1 -> right_thread == true && temp1 -> right != NULL)
            {
                fprintf(f,"%d",temp1 -> data);
                fprintf(f," -> ");
                fprintf(f,"%d",temp1 -> right -> data);
                fprintf(f," [style = dotted]; \n");
            }
            print_node *temp2 = print;
            print = print -> next;
            delete(temp2);
        }
        fprintf(f," } ");
        fclose(f);
    }
};

//----------------------------------------------------------------------------
//Main function
int main()
{
    node *root;
    root = NULL;
    flag=0;
    int arr[]={50,30,100,5,40,90,105,0,10,35,45,85,95};
    BST obj;
    for(int i=0;i<sizeof(arr)/sizeof(int);i++)
    {
        root = obj.Insertion(root,arr[i]);
        if(flag == 1)
        {
            obj.Search2(root,arr[i]);
        }
    }

    node *tree;
    tree = root;

    cout << "\nCurrently a tree is already present\n";
    cout << "If graphviz is already installed then you can see image in same folder\n\n";

    while(1)
    {
        cout << "To perform operations press number and enter \n";
        cout << "1. Insertion \n";
        cout << "2. Search \n";
        cout << "3. Delete \n";
        cout << "4. Reverse Inorder \n";
        cout << "5. Successor \n";
        cout << "6. Split \n";
        cout << "7. All element between k1 and k2 \n";
        cout << "8. kth largest element \n";
        cout << "9. Print Tree \n";
        cout << "0. Exit \n\n";

        int point;
        cin >> point ;
        if(point == 1)
        {
            int g;
            cout << "Enter number you want to insert in tree: ";
            cin >> g;
            root = obj.Insertion(root,g);
            if(flag == 1)
            {
                obj.Search2(root,g);
            }
            cout << "\nElement is inserted in tree";
            cout << "\n\n";
        }

        else if(point == 2)
        {
            node *temp;
            int g;
            cout << "Enter the element you want to search: ";
            cin >> g;
            temp = obj.Search(root,g);
            if(temp == NULL)
            {
                cout << "Element is not present\n";
            }
            else
            {
                cout << "\nValue found \nIs at address : " << temp;
            }
            cout <<"\n\n";
        }

        else if(point == 3)
        {
            cout << "Enter the element you want to delete: ";
            int g;
            cin >> g;
            obj.delete_element(root,g);
            cout << "\n\n";
        }

        else if(point == 4)
        {
            list_node *h;
            h = obj.reverse_inorder(root);
            cout << "\nReverse inorder traversal:\n";
            cout << "Head of linked list is at address: " << h << endl;
            cout << "Values : \n";
            while(h)
            {
                cout << h -> data << " ";
                h = h -> next;
            }
            cout << "\n\n";
        }


        else if(point == 5)
        {
            node *temp4;
            int g;
            cout << "Enter the element you want to find the successor to: ";
            cin >> g;
            temp4 = obj.Search(root,g);
            temp4 = obj.Successor(temp4);
            if(temp4 == NULL)
            {
                cout << "\nNo successor for this element\n";
            }
            else
            {
                cout << "\nSuccessor found : " << temp4->data;
            }
            cout << "\n\n";
        }

        else if(point == 6)
        {

            cout << "Enter the value of k :";
            int g;
            cin >> g;
            vector<node*> t = obj.Split(tree, g);
            cout << "\n";
            list_node *h;
            cout << "Tree 1\n";
            obj.inorder(t[0]);
            cout << "\nTree 2\n";
            obj.inorder(t[1]);
            cout << "\n\n";
        }

        else if(point == 7)
        {
            list_node *head1;
            int k1 ,k2 ;
            cout << "Enter k1 and k2\n";
            cout << "k1 and k2 should be present in tree\n";
            cout << "Enter k1 : ";
            cin >> k1;
            cout << "Enter k2 : ";
            cin >> k2;
            head1 = obj.All_elements_between(root,k1,k2);
            cout << "Values are: \n";
            while(head1)
            {
                cout << head1 -> data << " ";
                head1 = head1 -> next;
            }
            cout <<"\n\n";
        }

        else if(point == 8)
        {
            node* max_=0;
            int g;
            cout << "Enter the kth largest element you want to find : ";
            cin >> g;
            max_ = obj.kth_largest_element(root,g);
            if(max_ == NULL){
                cout << "\nLess than k elements present in tree\n";
            }
            else
            {
                cout << "Kth largest element is : "<< max_ -> data ;
            }
            cout <<"\n\n";
        }

        else if(point == 9)
        {
            obj.Print(root);
            system("dot -Tpng image.dot -o image.png");
            cout << "\nCheck the folder\nDotted lines are predecessor and successor \n\n";
        }

        else
        {
            break;
        }
    }

    return 0;
}

