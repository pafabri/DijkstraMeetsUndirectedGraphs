//
// Created by peterfab on 7/28/20.
//

#ifndef ADJLISTSEX_SHORTESTPATH_H
#define ADJLISTSEX_SHORTESTPATH_H

#include "UndirectedGraph.h"
#include "NodeMinCost.h"
#include <tuple>
#include <utility> // if you're curious, https://en.cppreference.com/w/cpp/utility/pair/pair
using namespace std;
/*
vertices(List): list of vertices in G(V,E).
path(u, w): find shortest path between u-w and returns the sequence of vertices
 representing shortest path u-v1-v2-…-vn-w.
path_size(u, w): return the path cost associated with the shortest path.
 */
/*
struct Edge {
    typedef tuple<int, int, double> edge; // a borderline Edge class relying on tuple STL container

    Edge() : edg(0,0,0.0) {}

    // Member
    edge edg;

    bool operator>(edge & e) const { return (get<2> (edg) > get<2> (e)); }
    bool operator<(edge & e) const { return (get<2> (edg) < get<2> (e)); }
};
*/
class ShortestPath: public UndirectedGraph {
public:
    // Public Member for ease of access
    vector<int> path;
    // Ctor Init'r
    ShortestPath(const int& n = 50, const double& d = 0.1, const double& md = 10.0) :
    UndirectedGraph::UndirectedGraph(n, d, md),
    shortest_path_distance(0.0), path(vector<int> (0))
    {}
    // Dtor
    ~ShortestPath() override;

    // Getters
    vector<int> findShortestPath(int, int);
    double pathSize() { return (this->shortest_path_distance); }

    // Setters
    void setShortestPathDistance(double spd) { this->shortest_path_distance = spd; }

    // in order to cmp() set values overload relational ops
    //bool operator>(const int & rhs) { return ;}
private:
    double shortest_path_distance;
    //vector<int> recursiveBackTrack(int *arr_prev_nodes, int begin, int end);
};


#endif //ADJLISTSEX_SHORTESTPATH_H
