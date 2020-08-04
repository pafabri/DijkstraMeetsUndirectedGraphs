//
// Created by peterfab on 7/26/20.
//

#include "UndirectedGraph.h"
#include <random>
#include <iostream>
#include <tuple>

using namespace std;

void UndirectedGraph::generateGraph()
{
    random_device rd;           // cppreference.com/w/cpp/numeric/random/uniform_real_distribution
    mt19937 generator(rd());    // mersenne_twister_engine

    uniform_real_distribution<double> distributionChooseEdge(0.0, 1.0); // gen'e uniform distrib'ns
    uniform_real_distribution<double> distributionSetWeight(1.0, max_distance);

    // loop through all possible edges,
    // only pushing to back of edges_vector if rand gen'd double
    // distributionChooseEdge() in 0 to 1 is less than spec'd density
    for (int i = 0; i < n_vertices; ++i) {
        // i rep'ts array indices or beg_v
        for (int j = i + 1; j < n_vertices; ++j) {
            // j rep'ts end_v starting at i + 1 bc no loops or duplicates, just want combos
            // distributionSetWeight(generator) rep'ts distance
            if (distributionChooseEdge(generator) < density) {
                Edge edge0(i, j, distributionSetWeight(generator));
                this->edges_vector.push_back(edge0);
            }
        }
    }
    // dynamo for head as node ptrs arr of size n_vertices
    head = new Node* [n_vertices];

    // init head ptrs, per vertex in arr, to nullptr
    for (int i = 0; i < n_vertices; ++i)
        head[i] = nullptr;

    // insert randomly gen'd edges to undirected graph
    for (const auto e: edges_vector)  {
        insertNodeAtBeg(get<0>(e), get<1>(e), get<2>(e));
        insertNodeAtBeg(get<1>(e), get<0>(e), get<2>(e));
        // alternate beg_v and end_v ^here, since undirected ^
    }
}
/*
// Copy Ctor
// use case: to build another identical graph w different mem address to delete edges from
// as we traverse through the edges
UndirectedGraph::UndirectedGraph(UndirectedGraph) {

}
*/
// traverses through LL from last inserted node (rly first in LL) to first inserted, that pts to NULL
UndirectedGraph::~UndirectedGraph()
{
    Node *pCur = nullptr;   // To traverse the list
    Node *pNext = nullptr;  // To point to the next node

    for (int i = 0; i < n_vertices; i++) {
        // this can happen bc we might have not initialized a vertex head[i] with any adjacent nodes
        // in which case, the head would remain pointing at NULL
        if (head[i] != nullptr) {
            pCur = (head[i]->next); // assign *pCur the first node that head ptr points to
        }
        else {
            continue; // do not want to move into loop with a nullptr, and point to the "next" since it DNE for nullptr
        }
        // While pCur is not pointing to nullptr... delete node by node, couldn't find more direct way
        while (pCur != nullptr) {
            // Save a pointer to the next node.
            pNext = pCur->next; // assign the next pointer to pNext

            // Delete the current node.
            //cout << "DEBUG - Destructor: Now deleting " << i << " -> " << pCur->destVertex << endl;
            delete pCur; // delete object that pCur points to

            // Position pCur ptr's addy to the next node ptr addy.
            pCur = pNext;
        }
        delete head[i]; // delete each head ptr
    }
    delete [] head; // delete the allocated head array
}

void UndirectedGraph::insertNodeAtBeg(int beg_vertex, int end_vertex, double edge_distance)
{
    head[beg_vertex] = new Node(end_vertex, edge_distance, head[beg_vertex]);
}

// since get_edge_value() had the same signature,
// it's only natural to generalize the type
// can be done w typeof(id).name() == 'i', 'b'
// despite it guaranteeing we hv to iterate through all neighbor nodes
// since we are working w a sparse graph
bool UndirectedGraph::adjacent(int vertex_x, int vertex_y)
{
    Node* cursor = head[vertex_x]; // point cursor to first node
    bool xy_neighbors = false; // to prep for generic re-typing w get_edge_value()
    // ride cursor ptr through all Nodes,
    // til destVertex matched, return true,
    // else, return false
    while (cursor != nullptr) {

        if (cursor->destVertex == vertex_y)
            xy_neighbors = true; // would have to just typeof(obj).name() == 'i' or 'b' here

        cursor = cursor->next;
    }
    return xy_neighbors;
}

vector<int> UndirectedGraph::neighbors(int vertex_x) {
    Node* cursor = head[vertex_x];  // point cursor to first node
    vector<int> neighbors;                      // to store neighbor vertices
    int current_neighbor;

    // uncomment cout's for interactive console
    //cout << "Neighbors of " << vertex_x << " are..." << endl;
    // ride cursor ptr through all neighbor Nodes,
    // printing 'em to std out
    while (cursor != nullptr) {

        current_neighbor = cursor->destVertex;
        neighbors.push_back(current_neighbor);
        //cout << current_neighbor << " " << flush;

        cursor = cursor->next;
    }
    //cout << endl;
    return neighbors;
}

double UndirectedGraph::get_edge_value(int vertex_x, int vertex_y) {
    Node* cursor = head[vertex_x]; // point cursor to first node
    double edge_distance = 0; // to prep for generic re-typing
    // ride cursor ptr through all Nodes,
    // til destVertex matched, update, then return edge_distance
    while (cursor != nullptr) {

        if (cursor->destVertex == vertex_y)
            edge_distance = cursor->distance;

        cursor = cursor->next;
    }
    return edge_distance;
}

// adds to G the Edge from x to y, if it is not there.
void UndirectedGraph::add(int vertex_x, int vertex_y)
{
    Node* cursor = head[vertex_x]; // point cursor to first node
    bool xy_neighbors = false; // to prep for generic re-typing
    // ride cursor ptr through all Nodes,
    // til destVertex matched, return true,
    // else, return false
    while (cursor != nullptr) {

        if (cursor->destVertex == vertex_y)
            xy_neighbors = true;

        cursor = cursor->next;
    }
    if (!xy_neighbors) {
        this->insertNodeAtBeg(vertex_x, vertex_y, 1.0);
        this->insertNodeAtBeg(vertex_y, vertex_x, 1.0);
    }
}

// removes the Edge from x to y, if it is there.
// expects to be called twice, with x, y then y, x
// as passed values in order to delete both Node instances
// from the adjacency list
bool UndirectedGraph::deleteEdge(int vertex_x, int vertex_y) {
    Node* precursor = head[vertex_x]; // point cursor to first node
    Node* cursor = precursor->next;
    bool deleted = false;

    // given that nodes were populated in ascending order,
    // ride cursor ptr through all nodes,
    // til (cursor->destVertex < vertex_y)
    // is false or cursor reaches nullptr
    while (cursor != nullptr && cursor->destVertex < vertex_y) {

        precursor = cursor;
        cursor = cursor->next;
    }

    // if cursor found vertex_y && didn't exit loop bc cursor reached nullptr
    if (cursor != nullptr && cursor->destVertex == vertex_y) {
        precursor->next = cursor->next; // precursor node pointee updated up to cursor node pointee
        delete cursor; // since cursor not nullptr, we may delete
        deleted = true;
    }
    return deleted;
}

// print all adjacent vertices of given vertex in head arr, node*
void UndirectedGraph::displayVerticesPerEdge() const
{
    cout << "\t" << "vertices" << "\t\t" << "Edge distance" << endl;
    cout << "\t" << "--------" << "\t\t" << "-------------" << endl;
    Node* ptr;
    for (int i = 0; i < n_vertices; i++) {
        ptr = head[i];
        // display adjacent vertices of vertex i
        while (ptr != nullptr) {
            cout << "\t" << i << " -> " << ptr->destVertex << "\t\t\t"
                 << ptr->distance << endl;
            ptr = ptr->next;
        }
        cout << endl;
    }

}
