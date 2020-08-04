//
// Created by peterfab on 7/28/20.
//

#ifndef ADJLISTSEX_PRIORITYQUEUE_H
#define ADJLISTSEX_PRIORITYQUEUE_H

#include <queue>
#include <vector>
#include <tuple>
#include "NodeMinCost.h"
using namespace std;
/*
chgPrioirity(PQ, priority): changes the priority (node value) of queue element.
minPrioirty(PQ): removes the top element of the queue.
contains(PQ, queue_element): does the queue contain queue_element, returns cost of
Insert(PQ, queue_element): insert queue_element into queue
top(PQ):returns the top element of the queue.
size(PQ): return the number of queue_elements.
 */
/*
struct Cmp {
    bool operator()(const NodeMinCost & lhs, const NodeMinCost & rhs) {
        return  (lhs.nc > rhs.nc);
    }
};
*/
class PriorityQueue {
public:
    PriorityQueue(); // def ctor not init'r
    // only needs end_vertex vector since we have get_edge_value() in UndirectedGraph
    ~PriorityQueue();

    void changePriority(int n, double cost_priority); // given node n exists,
    // changes the priority (of node value n) of a queue element.
    void minPriority(); // removes the top element of the queue.
    // cycles thru the queue, does it contain queue_element
    void insert(const NodeMinCost & queue_element); // insert queue_element into queue
    void remove(int node); // delete queue elt that matches node value

    bool contains(NodeMinCost & queue_element);
    NodeMinCost top(); // returns the top element of the queue.
    int size(); // returns the number of queue_elements.
private:
    // Member
    priority_queue<NodeMinCost> pq;
    int pq_size;
};



#endif //ADJLISTSEX_PRIORITYQUEUE_H
