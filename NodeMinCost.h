//
// Created by peterfab on 7/30/20.
//

#ifndef ADJLISTSEX_NODEMINCOST_H
#define ADJLISTSEX_NODEMINCOST_H
#include <tuple>
using namespace std;

class NodeMinCost {
public:
    NodeMinCost(int n = -1, double c = 999) : node(n), cost(c) {} // def Ctor Init'r
    ~NodeMinCost() = default; // token Dtor

    // Setters
    void setCost(double d) { this->cost = d; }

    // Getters
    int getNode() const { return (this->node); }
    double getCost() { return (this->cost); }

    // Relational op overloading
    bool operator<(const NodeMinCost& rhs) const {
        return (this->cost > rhs.cost);
    }
    bool operator==(const NodeMinCost& rhs) const {
        return (this->cost == rhs.cost && this->node == rhs.node);
    }
    bool operator!=(const NodeMinCost& rhs) const {
        return (this->cost != rhs.cost || this->node != rhs.node);
    }
private:
    // Members
    int node;
    double cost;
};

#endif //ADJLISTSEX_NODEMINCOST_H
