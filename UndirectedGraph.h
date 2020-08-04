//
// Created by peterfab on 7/26/20.
//
#ifndef ADJLISTSEX_UNDIRECTEDGRAPH_H
#define ADJLISTSEX_UNDIRECTEDGRAPH_H

#include <vector>
#include <tuple>
#include "Node.h"
/* NOTE
 * Replaced the following hw criteria method
set_edge_value (G, x, y, v): sets the value associated to the Edge (x,y) to v, if DNE
 * with
 Node* insertNodeAtBeg(int end_vertex, double edge_distance, Node *head); // Setter

 Also, I do not understand what this criteria method is intending to set.
 Sounds like circular reasoning since I'm using the array index as the node value or vertex value:
set_node_value( G, x, a): sets the value associated with the node x to a. Can't a non-number vertex-val
be replaced by an enum?
 */
using namespace std;

// Adjacency List
class UndirectedGraph : public Node {
public:
    typedef tuple<int, int, double> Edge; // a borderline Edge class relying on tuple STL container
    vector<Edge> edges_vector;          // I'm aware these are accessible to ShortestPath since public
    Node **head;

    // Ctor Init'r
    UndirectedGraph(int n = 50, double d = 0.1, double md = 10.0) :
    n_vertices(n), density(d), max_distance(md)
    {}

    void generateGraph();
    //UndirectedGraph(UndirectedGraph& G); // Copy Ctor
    virtual ~UndirectedGraph();                 // Dtor

    int V() const { return this->n_vertices; }              // Getters
    int E() const { return edges_vector.size(); }
    double get_edge_value(int, int);
    // get_node_value (G, x): returns the value associated with the node x. // no ty, arr index is node_val :)

    bool adjacent(int, int);                  // Exist-er
    vector<int> neighbors(int);               // Printer and returns vector<int> of neighbor vertices (mem hefty)
    void displayVerticesPerEdge() const;

    void insertNodeAtBeg(int beg_vertex, int end_vertex, double edge_distance); // Setters
    void add(int, int); // suppose these might be used for another assignment
    bool deleteEdge(int, int);


protected:
    int n_vertices;
    double density, max_distance;
};

#endif //ADJLISTSEX_UNDIRECTEDGRAPH_H
