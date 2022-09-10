#include <iostream>
#include <bits/stdc++.h>
#include <math.h>
using namespace std;

//Graph node
class node
{
    int index;        //Graph node index
    int distance;     //weight of edge
    char edge_type;   //froward,backward,tree,cross
    node* next;
    node(int index1,int distance1)
    {
        index = index1;
        distance = distance1;
        edge_type = 't';
        next = NULL;
    }
    friend class Graph_directed;
};
//---------------------------------------------------------------------------------------------
class heap_node
{
    int index;        //Heap node index
    int distance;     //weight of edge of the graph
    heap_node(int distance1, int index1)
    {
        index = index1;
        distance = distance1;
    }
    friend class Graph_directed;
};
//---------------------------------------------------------------------------------------------
class Graph_directed
{
    private:
        vector<node*> Graph;
        vector<bool> visit;                  //To keep track of visited nodes in dfs
        vector<node*> DFS_tree;              //Used in dfs
        vector<int> vt,start_time,end_time;  //arrays used in dfs
        vector<int> scc;                     //strongly connected components
        vector<int> dist;
        vector<int> indegree;
        vector<int> visited;                 //Used for printing
        int timer;
        int scc_count;
    public:
        //Constructor
        Graph_directed(int vertices)
        {
            timer = 0;
            //Initialization
            for(int i=0; i<vertices; i++)
            {
                Graph.push_back(NULL);
                visit.push_back(false);
                DFS_tree.push_back(NULL);
                vt.push_back(0);
                start_time.push_back(0);
                end_time.push_back(0);
                scc.push_back(0);
                dist.push_back(10000000);
                indegree.push_back(0);
            }
        }
    //---------------------------------------------------------------------------------------------
    //---------------------------------------------------------------------------------------------
    //To add edge in graph
    void add_edge(int vertex1, int vertex2, int distance)
    {
        node* n = new node(vertex2, distance);
        n -> next = Graph[vertex1];
        Graph[vertex1] =  n;
    }

    //To check if graph is correct or not
    void print_graph(vector<node*> &G2)
    {
        for(int i=0; i<Graph.size(); i++)
        {
            cout << endl;
            node* temp = G2[i];
            cout << start_time[i] << " "  << i  << " " << end_time[i] << " " << " : ";
            while(temp)
            {
                cout  << temp -> index << temp -> edge_type  << " " ;
                temp = temp -> next;
            }
            cout << endl;
        }
    }

    //To create a copy of graph
    vector<node*> create_graph_copy()
    {
        vector<node*> G1;
        node* temp3;
        node* temp4;
        for(int i=0; i<Graph.size(); i++)
        {
            G1.push_back(NULL);
            temp3 = Graph[i];
            while(temp3)
            {
                temp4 = new node(temp3 -> index, 0);
                temp4 -> next = G1[i];
                G1[i] = temp4;
                temp3 = temp3 -> next;
            }
        }
        return G1;
    }

    //---------------------------------------------------------------------------------------------
    //---------------------------------------------------------------------------------------------
    //1. DFS part

    void DFS()
    {
        int t = 0;
        //DFS tree initialisation
        for(int i=0; i<Graph.size(); i++)
        {
            DFS_tree[i] = NULL;
            visit[i] = false;
        }

        //Traversing graph using dfs
        timer = 0;
        while(check_visited() && t < Graph.size())
        {
            DFS_helper(t++);

        }
        for(int i=0; i<Graph.size(); i++)
        {
            visit[i] = false;
        }
        visited.clear();
        visited.assign(Graph.size(),0);
        print_graph1();
    }

    private:
    //To check all nodes are visited or not
    bool check_visited()
    {
        for(int i=0; i<visit.size(); i++)
        {
            if(visit[i] == false)
            {
                return true;
            }
        }
        return false;
    }


    //DFS starts here
    int DFS_helper(int index2)
    {
        //Node is visited or not
        if(visit[index2] == true)
        {
            if(vt[index2] == 1)
            {
                return 3;
            }
            return 2;
        }
        //Timers
        timer++;
        start_time[index2] = timer;

        visit[index2] = true;
        vt[index2] = 1;
        visit[index2] = true;

        int temp1 = 0;
        node* temp2 = Graph[index2];
        //Traversing index2
        while(temp2)
        {
            int t = DFS_helper(temp2 -> index);
            node *n2 = new node(temp2 -> index,temp2 ->distance);
            n2 -> next = DFS_tree[index2];
            DFS_tree[index2] = n2;

            //Edge type of graph for part 1
            if(t == 1)
            {
                n2 -> edge_type = 't';
            }
            else if(t == 2)
            {
                if(start_time[index2] > start_time[temp2 -> index])
                {
                    n2 -> edge_type = 'c';
                }
                else
                {
                    n2 -> edge_type = 'f';
                }

            }
            else if(t == 3)
            {
                n2 -> edge_type = 'b';
            }
            temp2 = temp2 -> next;
        }
        timer++;
        end_time[index2] = timer;
        vt[index2] = 0;
        return 1;
    }

    //---------------------------------------------------------------------------------------------
    //---------------------------------------------------------------------------------------------
    //PART1 PRINT PART

    void print_nodes1(int i , FILE *fp)
    {
        fprintf(fp,"%d[label = \"%d[%d,%d]\"];\n" , i+1 , i+1,start_time[i],end_time[i]);
        visited[i] = 1;
        node* temp1 = DFS_tree[i];
        //Traversing graph to print
        while(temp1)
        {
            int val = temp1->index;
            if(!visited[val])
                print_nodes1(val , fp);
            fprintf(fp,"%d->%d[label = \"%d,%c\" ]\n" , i+1 , temp1->index+1  , temp1->distance , temp1->edge_type);

            temp1 = temp1->next;
        }
    }
    //Print part for graph 1 starts here
    void print_graph1()
{
        string filename = "image1" ;
        string df = "";
        df = df + filename + ".dot";
        string pngf = "" ;
        pngf =  pngf + filename + ".png";
        FILE *fp = fopen(df.c_str() , "w");

        fprintf(fp , "digraph G{\nedge[dir = forward]\nnode[shape = oval];\n" );
        for(int i = 0 ; i < visited.size() ; i++)
        {
            if(!visited[i])
                print_nodes1(i , fp);
        }
        // to add code

        fprintf(fp,"}");
        fclose(fp);

        string cmnd = "dot -Tpng " + df + " -o " + pngf ;
        system(cmnd.c_str());
        cout << "image1.png file is generated." << endl;
        cout << "Graph is printed in the file" << endl;
        cout << "Node structure is given in the document." << endl;
    }


    //---------------------------------------------------------------------------------------------
    //---------------------------------------------------------------------------------------------
    //PART 2 AND 4 (Strongly connected components using Tarjans algorithm and  semi-connected check)

    public:
        void Tarjan(int button)
        {
            timer = 0;
            scc_count = 0;
            //Initializing few temporary arrays
            vector<int> disc(Graph.size(), -1);
            vector<int> low(Graph.size(), -1);
            vector<bool> stackMember(Graph.size(), false);
            stack<int> st;

            //Reassigning values
            indegree.clear();
            indegree.assign(Graph.size(),0);
            scc.clear();
            scc.assign(Graph.size(),0);

            // Call the recursive helper function to find strongly
            // connected components in DFS tree with vertex 'i'
            for (int i = 0; i < Graph.size(); i++)
            {
                if (disc[i] == -1)
                {
                    Tarjan_helper(i, disc, low, st, stackMember);
                }
            }
            //pprint();
            if(button == 4)
            {
                semiconnected_check();
            }
            if(button == 3)
            {
                semi_connected();
            }
            if(button == 2)
            {
                visited.clear();
                visited.assign(Graph.size(),0);
                print_graph2();
            }
        }


        void pprint()
        {
            for(int i=0; i<Graph.size(); i++)
            {
                cout << scc[i] << "\n";
            }
        }

    private:
        //Finding scc here
        void Tarjan_helper(int u, vector<int> &disc, vector<int> &low, stack<int> &st, vector<bool> &stackMember)
        {
            disc[u] = low[u] = ++timer;
            st.push(u);
            stackMember[u] = true;

            node* temp5;
            temp5 = Graph[u];

            // Go through all vertices adjacent to u
            while(temp5)
            {
                int v = temp5 -> index;
                indegree[v]++;
                // If v is not visited yet, then recur for it
                if(disc[v] == -1)
                {
                    Tarjan_helper(v, disc, low, st, stackMember);
                    // Check if the subtree rooted with 'v' has a connection to one of the ancestors of 'u'
                    low[u] = min(low[u], low[v]);
                }
                else if (stackMember[v] == true)
                {
                    low[u] = min(low[u], disc[v]);
                }
                temp5 = temp5 -> next;
            }

            // head node found, pop the stack and print an SCC
            int popped = 0;
            if (low[u] == disc[u])
            {
                scc_count++;
                while (st.top() != u)
                {
                    popped = st.top();
                    //cout << popped << " ";
                    scc[popped] = scc_count;
                    stackMember[popped] = false;
                    st.pop();
                }
                popped = st.top();
                scc[popped] = scc_count;
                //cout << popped << "\n";
                stackMember[popped] = false;
                st.pop();
            }
        }
    //---------------------------------------------------------------------------------------------
    //---------------------------------------------------------------------------------------------
    //PART 2 PRINT

    void print_nodes2(int i , FILE *fp)
    {
        fprintf(fp,"%d[label = \"%d[%d]\"];\n" , i+1 , i+1,scc[i]);
        visited[i] = 1;
        node* temp1 = Graph[i];
        //Traversing graph to print
        while(temp1)
        {
            int val = temp1->index;
            if(!visited[val])
                print_nodes2(val , fp);
            fprintf(fp,"%d->%d[label = \"%d\" ]\n" , i+1 , temp1->index+1  , temp1->distance );

            temp1 = temp1->next;
        }
    }
    //Print part for graph 2 starts here
    void print_graph2()
    {
        string filename = "image2" ;
        string df = "";
        df = df + filename + ".dot";
        string pngf = "" ;
        pngf =  pngf + filename + ".png";
        FILE *fp = fopen(df.c_str() , "w");

        fprintf(fp , "digraph G{\nedge[dir = forward]\nnode[shape = oval];\n" );
        for(int i = 0 ; i < visited.size() ; i++)
        {
            if(!visited[i])
                print_nodes2(i , fp);
        }
        // to add code

        fprintf(fp,"}");
        fclose(fp);

        string cmnd = "dot -Tpng " + df + " -o " + pngf ;
        system(cmnd.c_str());
        cout << "image2.png file is generated." << endl;
        cout << "Graph is printed in the file" << endl;
        cout << "Node structure is given in the document." << endl;
    }

    //---------------------------------------------------------------------------------------------
    //---------------------------------------------------------------------------------------------
    //PART 3
    private:
        //Creating matrix to keep track of edges from one scc to another
        vector<vector<int>> matrix;
        void semi_connected()
        {
            matrix.clear();
            int max_num = scc[0];
            //To find number of scc
            for(int i=0;i<scc.size();i++)
            {
                if(scc[i] > max_num)
                {
                    max_num = scc[i];
                }
            }
            //Initializing matrix
            vector<int> temp(max_num+1,0);
            for(int i=0;i<=max_num;i++)
            {
                matrix.push_back(temp);
            }

            visit.clear();
            visit.assign(Graph.size(),false);
            visited.assign(Graph.size(),0);
            print_graph3();
        }

    //---------------------------------------------------------------------------------------------
    //---------------------------------------------------------------------------------------------
    //PART 3 PRINT
        //Dfs to traverse the graph
        void print_nodes3(int i , FILE *fp)
        {
            visited[i] = 1;
            node* temp7 = Graph[i];

            fprintf(fp,"%d[label = \"%d\"];\n" , i+1 , i+1);
            while(temp7)
            {
                int val = temp7->index;
                //Checking matrix
                if(matrix[scc[i]][scc[val]] == 0)
                {
                    matrix[scc[i]][scc[val]] =1;
                }
                else if(scc[i] == scc[val])
                {

                }
                else
                {
                    temp7 = temp7->next;
                    continue;
                }

                if(!visited[val])
                {
                    print_nodes3(val , fp);
                }
                fprintf(fp,"%d->%d[label = \"%d\" ]\n" , i+1 , val+1  , temp7 -> distance );

                temp7 = temp7->next;
            }
        }

        void print_graph3()
        {
            string filename = "image3" ;
            string df = "";
            df = df + filename + ".dot";
            string pngf = "" ;
            pngf =  pngf + filename + ".png";
            FILE *fp = fopen(df.c_str() , "w");
            fprintf(fp , "digraph G{\nedge[dir = forward]\nnode[shape = oval];\n" );
            for(int i = 0 ; i < Graph.size() ; i++)
            {
                if(!visited[i])
                    print_nodes3(i , fp);
            }
            fprintf(fp,"}");
            fclose(fp);
            string cmnd = "dot -Tpng " + df + " -o " + pngf ;
            system(cmnd.c_str());
            cout << "image3.png file is generated." << endl;
            cout << "Graph is printed in the file" << endl;
            cout << "Node structure is given in the document." << endl;
        }

    //---------------------------------------------------------------------------------------------
    //---------------------------------------------------------------------------------------------
    //DFS to traverse the graph
        void dfs1(int v)
        {
            if(visit[v] == true)
            {
                return;
            }
            visit[v] = true;

            int temp1 = 0;
            node* temp2 = Graph[v];
            while(temp2)
            {
                dfs1(temp2 -> index);
                temp2 = temp2 -> next;
            }
        }

        //To check ig graph is semi-connected or not
        void semiconnected_check()
        {
            visit.clear();
            visit.assign(Graph.size(),false);
            //dfs1(0);
            int i=0;
            //Traversing graph and checking if graph is semi-connected or not
            for( i=0; i<Graph.size();i++)
            {
                visit.clear();
                visit.assign(Graph.size(),false);
                dfs1(i);
                int j=0;
                for(j=0; j<visit.size(); j++)
                {
                    if(visit[j] == false)
                    {
                        break;
                    }
                }
                if(j == visit.size())
                {
                    cout << "YES graph is semiconnected\n";
                    break;
                }
            }
            for(i=0; i<visit.size(); i++)
            {
                if(visit[i] == false)
                {
                   cout << "NO graph is not semiconnected\n";
                   break;
                }
            }
        }

    //---------------------------------------------------------------------------------------------
    //---------------------------------------------------------------------------------------------
    //5. Dijkstra algorithm
    public:
        void Dijkstra(int src)
        {
            if(src >= Graph.size() || src < 0)
            {
                cout << "Node does not exist" << endl;
                return;
            }
            //min heap
            priority_queue<heap_node*> pq;
            heap_node* h = new heap_node(0, src);
            pq.push(h);
            dist.clear();
            dist.assign(Graph.size(),1000000);
            dist[src] = 0;
            while (!pq.empty())
            {
                // The first vertex in pair is the minimum distance vertex, extract it from priority queue.
                // vertex index is stored in second of heap_node
                int u = pq.top()->index;
                pq.pop();

                node* temp6 = Graph[u];
                while (temp6)
                {
                    // Get vertex label and weight of current adjacent of u.
                    int v = temp6 -> index;
                    int weight =  temp6 -> distance;

                    //  If there is shorted path to v through u.
                    if (dist[v] > dist[u] + weight)
                    {
                        // Updating distance of v
                        dist[v] = dist[u] + weight;
                        h = new heap_node(dist[v], v);
                        pq.push(h);
                    }
                    temp6 = temp6 -> next;
                }
            }
            visited.clear();
            visited.assign(Graph.size(),0);
            print_graph5();
            //for (int i = 0; i < Graph.size(); ++i)
                //printf("%d \t\t %d\n", i+1, dist[i]);
        }

    //---------------------------------------------------------------------------------------------
    //---------------------------------------------------------------------------------------------
    //PART5 PRINT
    void print_nodes5(int i , FILE *fp)
    {
        fprintf(fp,"%d[label = \"%d[%d]\"];\n" , i+1 , i+1,dist[i]);
        visited[i] = 1;
        node* temp1 = Graph[i];
        //Traversing graph to print
        while(temp1)
        {
            int val = temp1->index;
            if(!visited[val])
                print_nodes5(val , fp);
            fprintf(fp,"%d->%d[label = \"%d\" ]\n" , i+1 , temp1->index+1  , temp1->distance );

            temp1 = temp1->next;
        }
    }
    //Print part for graph 5 starts here
    void print_graph5()
    {
        string filename = "image5" ;
        string df = "";
        df = df + filename + ".dot";
        string pngf = "" ;
        pngf =  pngf + filename + ".png";
        FILE *fp = fopen(df.c_str() , "w");

        fprintf(fp , "digraph G{\nedge[dir = forward]\nnode[shape = oval];\n" );
        for(int i = 0 ; i < visited.size() ; i++)
        {
            if(!visited[i])
                print_nodes5(i , fp);
        }
        // to add code

        fprintf(fp,"}");
        fclose(fp);

        string cmnd = "dot -Tpng " + df + " -o " + pngf ;
        system(cmnd.c_str());
        cout << "image5.png file is generated." << endl;
        cout << "Graph is printed in the file." << endl;
        cout << "Node structure is given in the document." << endl;
    }
    //---------------------------------------------------------------------------------------------
    //---------------------------------------------------------------------------------------------
};

int main()
{
    int temp,vertices,edges;
    //Reading input file
    FILE *fp;
    fp = fopen("file.txt","r");
    fscanf(fp,"%d",&vertices);
    fscanf(fp,"%d\n",&edges);

    //Graph object
    Graph_directed G1(vertices);

    int vert1[edges],vert2[edges],edge_weight[edges];
    for(int i=0;i<edges;i++)
    {
        fscanf(fp,"%d",&vert1[i]);
        fscanf(fp,"%d",&vert2[i]);
        fscanf(fp,"%d\n",&edge_weight[i]);
        G1.add_edge(vert1[i]-1 ,vert2[i]-1,edge_weight[i]);
    }
    //for(int i=0;i<edges;i++)
    //{
        //cout << vert1[i] << " " << vert2[i] << " " << edge_weight[i] << endl;
    //}
    fclose(fp);

    int num = 0;
    while(1)
    {
        cout << "\nChoose the number from menu and press enter:" << endl;
        cout << "1. Print DFS tree and show edge types." << endl;
        cout << "2. Print strongly connected component graph." << endl;
        cout << "3. Print scc graph with minimum edges possible" << endl;
        cout << "4. Check if graph is semi-connected." << endl;
        cout << "5. Dijkstra's" << endl;
        cout << "6. Any other number to exit" << endl;
        cout << "Choose a number: ";
        cin >> num;
        cout << endl;
        if(num == 1)
        {
            G1.DFS();
        }
        else if(num == 2)
        {
            G1.Tarjan(2);
        }
        else if(num == 3)
        {
            G1.Tarjan(3);
        }
        else if(num == 4)
        {
            G1.Tarjan(4);
        }
        else if(num == 5)
        {
            int in_;
            cout << "Node label is from 1 to " << vertices <<endl;
            cout << "Enter the source : ";
            cin >> in_;
            G1.Dijkstra(in_ - 1);
        }
        else
        {
            break;
        }
    }
    return 0;
}
