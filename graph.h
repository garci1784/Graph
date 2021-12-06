/****************************
Templated created by Kazumi Slott
CS311

Your name: Jorge Ezequiel Garcia Lopez
Your programmer number:8
Any difficulties?: This assignment was challenging.
 I could not figure out how to display properly the
 shortest path when both currDist and predecessor
 have the same value.
*****************************/
#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <queue>
#include <list>
using namespace std;

class edge
{
    friend class graph;  //## You want to access the private members of edge class from graph class
    int neighbor; //adjacent vertex
    int wt; //weight of the edge
public:
    edge() { neighbor = -999, wt = -999;};
    edge(int u, int w) {neighbor = u; wt = w;};
};

class graph
{
    int num_ver; //the total number of vertices in the graph
    list<edge*>* ver_ar; //(list<edge*>)*//pointer to the dynamic array that holds linked lists. The element of a node in a linked list is a pointer to an edge object
    //Let's use the library's list class. It is actually a doubly linked list.
    int nextUnvisitedNodes(int* num);
    void DFT_helper(int v, int i, int* num, string& edges);
public:
    graph(int V);
    ~graph();
    void addEdge(int v, int u, int w=1);  //If the weight is not given, 1 is used for wt.
    void BFT(int start);
    void DFT(int start);
    void shortestPath(int start);
};

//constructor: num is the number of vertices
graph::graph(int num)
{
    num_ver = num; // sets the number of vertices
    ver_ar = new list<edge*>[num]; //make a dynamic array with num slots where each slot holds a list object.
    //ver_ar = new list<edge*>[num]; //make a dynamic array with num slots where each slot holds a list object.
    //The element of a node in the linked list is a pointer to an edge object
}

graph::~graph()
{
    //destroy all the edge objects created in heap
    //For each vertex in ver_ar
    //    go through each node in the linked list. The element field of each node points to an edge object created with "new". You need to delete these.
    for (list<edge*>::iterator u = ver_ar[0].begin(); u != ver_ar[0].end(); u++)
        delete (*u);

    //The library's list class has a destructor. All nodes belonging to the list will be destroyed by the destructor.
    //https://www.cplusplus.com/reference/list/list/~list/

    //destroy the ver_ar dynamic array
    delete [] ver_ar;
}


//add an edge from v to u with weight w into the graph
void graph::addEdge(int v, int u, int w)
{
    //We are using the list class from the library. Which member function do you need to use to add a node at the end of the list?
    //https://www.cplusplus.com/reference/list/list/
    //Don't create an edge object statically, then it would get destroyed as soon as you leave this function. You need to create an edge object dymamically in heap, which will remain in heap even after you leave this function.. Remember "new" operator returns the memory address of the newly created object.
    //I have one line of code in this function.
    ver_ar[v].push_back(new edge(u, w));
    //ver_ar->push_back(new edge(u, w));
}

//start Traversal at start
void graph::DFT(int start)
{
    //I made dynamic array called "num"
    int *num = new int[num_ver];

    // for all vertices v
    for (int i = start; i < num_ver; i++)
    {
        // num(v) = 0
        num[i] = 0;
    }
    // edges = null
    string edges = "";

    // i = 1
    int i = 1;
    int nextVertex = start;

    // while there is a vertex v such that num(v) is 0 <- enable to visit disconnected graphs
    //I used do-while
    do {
        // DFT_helper(v)
        DFT_helper(nextVertex, i, num, edges);
        //I am calling nextUnvisitedNodes() to see if there are more unvisited nodes.
        nextVertex = nextUnvisitedNodes(num);
    } while (nextVertex != -1);

    //output edges
    cout << "edges = " << edges << endl;

    //Don't forget to destroy the dynamic array
    delete[] num;
}

//I made the following function to see if there are still unvisited nodes
int graph::nextUnvisitedNodes(int* num)
{
    //go through the num array to see if you find a vertext with num=0. If so, return the index. If all visited, return -1.
    int index = -1;

    // num_ver is size of num
    for (int i = 0; i < num_ver; ++i) {
        if (num[i] == 0) // if unvisited
            return index = i;
    }

    return index;
}

void graph::DFT_helper(int v, int i, int* num, string& edges)
{
    //I have to use a c-string to make a string of edges. You don't need to use it if you know another way.
    char ar[5] = "v->u"; //v->u plus NULL character = size 5
    // num(v) = i++
    num[v] = i++;
    // output v
    cout << char(v + 'A') << " ";

    //The following shows how to iterate the library's linked list. You use an iterator.
    //https://www.cplusplus.com/reference/list/list/end/
    //iterator class is nested inside list class
    // for all vertices u adjacent to edges
    for (list<edge*>::iterator u = ver_ar[v].begin(); u != ver_ar[v].end(); u++)
    {
        //From the example on https://www.cplusplus.com/reference/list/list/end/
        //Notice *u gives you the element of the node pointed to by u. The element is a pointer to an edge object.
        //Between * and -> operator, -> has higher precedence. You need to use () around *u to get the element first.

        // if num(u) is 0
        if(num[(*u)->neighbor] == 0)
        {
            //u
            ar[0] = char(v + 'A');//replace index 0 by the name of v
            //v
            ar[3] = char((*u)->neighbor + 'A'); //replace index 3 by the name of u
            //Attach edge(uv) to edges
            edges += string(ar) + ","; //add v->u, to the end of edges
            //DFT_helper(u)
            DFT_helper((*u)->neighbor, i, num, edges);
        }


    }
}

//start is the index for the start vertex
void graph::BFT(int start)
{
    //I have to use a c-string to make a string of edges. You don't need to use it if you know another way.
    char ar[5] = "v->u"; //v->u plus NULL character = size 5
    int *num = new int[num_ver];
    for(int i=0; i < num_ver; i++)
    { num[i] = 0;}

    string edges = "";
    //Use the queue class from the library
    queue<int> queue;

    int i = 1;
    int next = start;
    //I used do-while to visit all unconnected graphs
    do{
        num[next] = i++;
        queue.push(next);
        while(!queue.empty())
        {
            int z = queue.front();
            cout << (char)(z + 'A') << " ";
            queue.pop();
            for(list<edge*>::iterator u = ver_ar[z].begin(); u != ver_ar[z].end(); ++u)
            {
                if(num[(*u)->neighbor] == 0)
                {
                    num[(*u)->neighbor] = i++;
                    queue.push((*u)->neighbor);
                    ar[0] = char(z + 'A'); // v in "v->u"
                    ar[3] = char((*u)->neighbor + 'A'); // u in "v->u"
                    edges += string(ar) + ",";
                }
            }
        }
        next = nextUnvisitedNodes(num);
    }while(next != -1);


    cout << "edges = " << edges << endl;
    //Don't forget to destroy the dynamic array if you used one
    delete  []num;
}


void graph::shortestPath(int start)
{
    //I have 2 dynamic arrays here.
    int* currDist = new int[num_ver];
    int* predecessor = new int[num_ver];

    //I used a queue for toBeChecked
    queue<int> toBeChecked;

    // for all vertices v
    for (int v = 0; v < num_ver; ++v)
    {
        // currDist(v) = infinity  <- currDist(v) is the distance from first to v
        currDist[v] = INT_MAX;
        predecessor[v] = INT_MAX;
    }

    // currDist(first) = 0 <- distance from first to first is 0
    currDist[start] = 0;

    // initialize toBeChecked <- put first into this queue
    toBeChecked.push(start);

    // while toBeChecked is not empty
    while (!toBeChecked.empty())
    {
        // v = a vertex in toBeChecked
        int v = toBeChecked.front();
        // remove v from toBeChecked
        toBeChecked.pop();

        // for all vertices adjacent to v
        for (list<edge*>::iterator u = ver_ar[v].begin(); u != ver_ar[v].end(); u++)
        {
            // if currDist(u) > currDist(v) + weight(edge(vu))
            if ( currDist[(*u)->neighbor] > (currDist[v] + (*u)->wt) )
            {
                // currDist(u) = currDist(v) + weight(edge(vu))
                currDist[(*u)->neighbor] = (currDist[v] + (*u)->wt);
                // predecessor(u) = v
                predecessor[(*u)->neighbor] = v;
                // add u to toBeChecked if it is not there
                if (predecessor[(*u)->neighbor] == v)
                    toBeChecked.push((*u)->neighbor);
            }
        }
    }

    //After the each vertex gets the minimum distance from the start point and predecessor,
    //Show the information about each vertex and shortest path from origine to destination and total distance.
    //For expected outputs, please check /cs/slott/cs311/graph.out
    cout << "\nShowing the info on each vertex" << endl;
    for (int i = 0; i < num_ver; ++i)
        cout << char(i + 'A') << " " << currDist[i] << ", " << char(predecessor[i] + 'A') << endl;

    char dest;
    cout << "Enter the destination: ";
    cin >> dest;

    string path = "";//will have all paths from origine to destination

    int i = dest - 'A';
    char ar[4] = "i->";

    while ( i != start)
    {
        ar[0] = i + 'A';
        //path += string(ar);
        path = string(ar) + path;
        i = predecessor[i];
    }

    ar[0] = start + 'A';
    //path += string(ar);
    path = string(ar) + path;

    cout << "The shortest path from " << char(start + 'A') << " to " << dest << " is " << path << endl;
    cout << "The total distance is " << currDist[(dest - 'A')] << endl;

    //Don't forget to destroy the dynamic arrays
    delete[] currDist;
    delete[] predecessor;
}

/* This is not part of graph homework - part 1.
void graph::DijkstraShortestPath(int start)
{

}
*/


#endif
