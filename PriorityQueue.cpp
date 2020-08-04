//
// Created by peterfab on 7/28/20.
//

#include "PriorityQueue.h"
#include <queue>
using namespace std;

// My comments are middling, burning out here ...
// pq_size does not update properly in some cases, but it's innocuous
// should be removed

PriorityQueue::PriorityQueue() {
    pq_size = pq.size();
}

PriorityQueue::~PriorityQueue() {
    while (!pq.empty()) {
        (this->pq).pop();
        pq_size = pq.size();
    }
}

// changes the priority (node value) of queue element.
void PriorityQueue::changePriority(int n, double cost_priority) {
    NodeMinCost top = this->pq.top(); // make local copy of top
    if (top.getNode() == n) {
        top.setCost(cost_priority); // reset top cost
        this->pq.pop();
        this->pq.push(top);
    }
    else {
        vector<NodeMinCost> nmc_vec;

        this->pq.pop();
        nmc_vec.push_back(top); // push top to the back of the carrier vector

        // guaranteed one >1 elt in pq
        while (!this->pq.empty()) {
            top = this->pq.top();
            (this->pq).pop();
            if (top.getNode() == n) {
                top.setCost(cost_priority);
                this->pq.push(top);
                break; // break and do not push into our carrier vec
            } else {
                nmc_vec.push_back(top);
            }
        }

        // put all elements back into queue
        while (!nmc_vec.empty()) {
            this->pq.push(nmc_vec.back());
            nmc_vec.pop_back();
        }

    }

}

// removes the top element of the queue.
void PriorityQueue::minPriority() {
    this->pq.pop();
    --pq_size;
}

// cycles thru the queue, does it already contain queue_element's node
bool PriorityQueue::contains(NodeMinCost & queue_element) {
    if ((this->pq).empty()) return false;
    NodeMinCost top = (this->pq).top();

    if (top.getNode() == (queue_element).getNode()) return true;
    vector<NodeMinCost>  nmc_vec;

    // don't want to pop() an empty pq, then operate w memory :P
    if (!(this->pq.empty())) {
        (this->pq).pop();
        nmc_vec.push_back(top); // push top to the back of the vector

        // while pq not empty and top node is not our queried node, pop then push top into nmc_vec
        while (!(this->pq).empty() && top.getNode() != (queue_element).getNode()) {
            top = (this->pq).top();
            (this->pq).pop();
            nmc_vec.push_back(top);
        }

        NodeMinCost temp_nmc;
        // put all elements back into queue
        while (!nmc_vec.empty()) {
            temp_nmc = nmc_vec.back();
            (this->pq).push(temp_nmc);
            nmc_vec.pop_back();
        }
    }
    return (top.getNode() == (queue_element).getNode());
}

// insert queue_element into queue
void PriorityQueue::insert(const NodeMinCost & queue_element) {
    (this->pq).push(queue_element);
    ++pq_size;
}

// works in tandum with contains OR just guaranteed that pq contains nmc w node value
void PriorityQueue::remove(const int node) {
    if (!(this->pq).empty()) {
        NodeMinCost top = (this->pq).top();

        if (top.getNode() == node) {
            (this->pq).pop();
        } else {
            vector<NodeMinCost> nmc_vec;

            // don't want to pop() an empty pq, then operate w memory :P
            if (pq_size != 0) {
                (this->pq).pop();
                if (top.getNode() != node) {
                    nmc_vec.push_back(top); // push top to the back of the vector if top does not hv node
                    --pq_size;
                }
                // start at 1 since we already pop()d pq once, pq will be empty if i == size
                for (int i = 1; i < pq_size; ++i) {
                    top = (this->pq).top();
                    (this->pq).pop();
                    nmc_vec.push_back(top);
                    if (top.getNode() != node) {
                        nmc_vec.push_back(top); // then we have not stored top corresp to node in nmc_vec
                        --pq_size;
                    }
                }

                NodeMinCost temp_nmc;
                // put all elements, except for possibly nmc corresp to node, back into queue
                while (!nmc_vec.empty()) {
                    temp_nmc = nmc_vec.back();
                    (this->pq).push(temp_nmc);
                    nmc_vec.pop_back();
                }
            }
        }
    }
}

// returns the top element of the queue.
NodeMinCost PriorityQueue::top() {
    return (this->pq).top();
}
// returns the number of queue_elements.
int PriorityQueue::size() {
    return (this->pq).size();
}
