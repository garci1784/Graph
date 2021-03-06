#include <iostream>
#include <fstream>
using namespace std;
#include "graph.h"

int main()
{
    cout << "testing unweighted graph--------------------" << endl;

    graph g(9); //a to i

    ifstream fin;
    fin.open("/Users/ezzz/CLionProjects/Graph/graph.in");
    int v, u, w; //v --> u
    //  w

    if(!fin)
        cout << "graph.in doesn't exist" << endl;
    else
    {
        fin >> v >> u;
        int temp = 0;
        while(fin)
        {
            g.addEdge(v,u);
            fin >> v >> u;
        }

        cout << "BFS: ";
        g.BFT(0);
        cout << "DFS: ";
        g.DFT(0);
    }
    fin.close();

    cout << "testing weighted graph--------------------" << endl;
    graph g2(10); //a to j
    fin.open("/Users/ezzz/CLionProjects/Graph/graph2.in");
    if(!fin)
        cout << "graph2.in doesn't exist" << endl;
    else
    {
        fin >> v >> u >> w;
        while(fin)
        {
            g2.addEdge(v,u, w);
            fin >> v >> u >> w;
        }

        cout << "BFS: ";
        g2.BFT(0);
        cout << "DFS: ";
        g2.DFT(0);
        cout << "Shortest Path: ";
        g2.shortestPath(3);

        ///* //You don't need to make Dijkstra's algo for homework on graph - part 1
        /*
      //cout << "Dijkstra's algo: ";
      //g2.DijkstraShortestPath(3);
        //*/

    }
    fin.close();

    return 0;
}
