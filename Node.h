//
// Created by peterfab on 7/28/20.
//

#ifndef ADJLISTSEX_NODE_H
#define ADJLISTSEX_NODE_H


// adjacency list object
class Node {
public:
    explicit Node(int v = 0, double d = 0.0, Node *p = nullptr): // def ctor
    destVertex(v), distance(d), next(p)
    {}
    ~Node() = default; // def dtor

    bool operator>(Node & n1) const { return (distance > n1.distance); } // for comparing nodes
    bool operator<(Node & n1) const { return (distance < n1.distance); }

    int destVertex; // all accessible members
    double distance;
    Node *next;
};

#endif //ADJLISTSEX_NODE_H
