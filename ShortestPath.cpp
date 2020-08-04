//
// Created by peterfab on 7/28/20.
//

#include <queue>
#include <algorithm>
#include <iostream>
#include <set>
#include "ShortestPath.h"
#include "NodeMinCost.h"
#include "PriorityQueue.h"
using namespace std;

// Brief of Dijkstra Algo: walk thru all non-looping connected paths,
// storing min distance and intermed_v it takes to reach each intermed_v from beg_v,
// until we exhaust all paths connecting to end_v,
// returning the Edge-sum seq with minimum sum of Edge distances (easier said)

// takes: start vertex int, end vertex int
// returns: minimum node or vertex(used synonymously) sequence of vector<int>

// prepare for instructive rigor, yet some jumbled logic,
// as I learn Dijkstra's algo while coding my understanding of it
vector<int> ShortestPath::findShortestPath(int vertex_u, int vertex_w)
{
    vector<int> closed = {vertex_u}; // to disallow returning to nodes that have already found min path from vertex_u
    // trivially, closest path to vertex_u from vertex_u is vertex_u, w 0 cost, so init in closed
    PriorityQueue priority_q; // declare pq as our own PriorityQueue that will refer to hidden pq member
    // priority_q is basically an min heap alias for pq => pop() all of pq before priority_q destroyed

    int num_v = V();
    int node_prev_arr[num_v] = {0}; // stores node pairs, index = node, value = previous node nearest to vertex_u
    node_prev_arr[vertex_u] = vertex_u; // node index j stores prev node closest to vertex_u

    // FOR DEBUGGING/TRACKING number of EDGE considerations per VERTEX
    //int prev_considered_counts[num_v] = {0}; // counts number of unique prev nodes considered for a node index j
    // valuable to discover if neighbors(j).size() == deg(j) == prev_considered_counts[j] bc then case j closed

    double n_cost[num_v] = {0}; // stores node-min_cost pairs, index = node, value = min path cost from vertex_u
    for (int i = 0; i < num_v; ++i) n_cost[i] = 9999999; // outlier to allow setting minimum costs

    n_cost[vertex_u] = 0; // could also be a vector of node-min_cost pairs, but we're working w only 50-100 nodes

    PriorityQueue cur_neighbors;
    PriorityQueue next_neighbors;
    int nearest_neighbor;
    double nearest_distance;

    // populate cur_neighbors with vertex_u neighbors
    for (auto & neighbor: neighbors(vertex_u)) {
        // iterate thru neighbors and init each node-min_cost pair out of vertex_u
        NodeMinCost nmc(neighbor, get_edge_value(vertex_u, neighbor)); // defn nmc
        cur_neighbors.insert(nmc);             // insert each adjacent vertex-cost pair to cur_n pq
        priority_q.insert(nmc);             // insert each adjacent vertex-cost pair to cur_n pq
        node_prev_arr[neighbor] = vertex_u; // init each vertex corresp to closest dist to vertex_u trivially
        n_cost[neighbor] = get_edge_value(vertex_u, neighbor); // init each closest dist to vertex_u
        //prev_considered_counts[neighbor] += 1;
    }
    if (cur_neighbors.top().getNode() == vertex_w) return closed; // unlikely, but if done early, copious seconds saved

    // At this point cur_neighbors carries all neighbors of vertex_u
    double encountered_path_cost = 0.0, current_min_cost = 0.0; // just for clarity below in what we init'e
    int beg_vertex; // to hold the next vertex we intend to close after inserting all it's next_neighbors to pq

    // <3 of Dijkstra Algorithm is next, brace yourself, please follow vigilantly
    // continue to push NodeMinCost pairs into pq until vertex_w has been pushed to close or pq empty
    do {
        // if cur_neighbors not empty, update beg_vertex to top of cur_neighbors node that is not already in pq
        // else put top of priority_q into cur_neighbors, then into beg_vertex
        if (cur_neighbors.size() == 0) {
            cur_neighbors.insert(priority_q.top());
            priority_q.minPriority();
        }
        beg_vertex = cur_neighbors.top().getNode();
        for (auto & v: neighbors(beg_vertex)) {
            NodeMinCost nmc(v, get_edge_value(beg_vertex, v));
            if (find(closed.begin(), closed.end(), v) == closed.end()) // if v not closed
                next_neighbors.insert(nmc); // refill next_neighbors with next closest node's (from cur_n) neighbors
        }
        if (next_neighbors.size() == 0) {// if next_neighbors.size() is still 0, then we have reached a transient v
            // remove it from cur_neighbors and priority_q
            priority_q.remove(cur_neighbors.top().getNode());
            cur_neighbors.minPriority();
        }
        // loop til next_neighbors is empty (aka close push incurred) so that we may populate pq
        while (next_neighbors.size() != 0) {
            // if next_neighbors top is already in cur_neighbors, pop it out, continue loop
            NodeMinCost top = next_neighbors.top();
            if (cur_neighbors.contains(top)) {
                next_neighbors.minPriority();
            }
            if (next_neighbors.size() != 0) {
                // init unclosed next_neighbors parts for clarity, to insert into pq
                nearest_neighbor = top.getNode();
                nearest_distance = top.getCost();

                // HERE, we consider nearest_neighbor uniquely since it's unclosed => increment
                //prev_considered_counts[nearest_neighbor] += 1;

                // Since nearest_neighbor has not been pushed to closed/visited yet, nearest_neighbor not in closed:
                // if there's another route to nearest_neighbor already in priority_q
                // validate that it has lesser cost than current node in pq, then changePriority() cost
                // and update total cost and previous node
                if (priority_q.contains(top)) {
                    encountered_path_cost = n_cost[beg_vertex] + nearest_distance;
                    current_min_cost = n_cost[nearest_neighbor];
                    // since n_cost[nearest_neighbor] hasn't been updated yet, it's current, vs encountered=>next
                    if (current_min_cost > encountered_path_cost) {
                        priority_q.changePriority(nearest_neighbor, encountered_path_cost);
                        // same as below but in pq
                        n_cost[nearest_neighbor] = encountered_path_cost; // update total min cost to nearest_neighbor
                        node_prev_arr[nearest_neighbor] = beg_vertex; // change to intermediate vertex
                    } // else do nothing skip inserting current nmc or updating nearest_neighbor's cost
                } else { // if top not in pq
                    n_cost[nearest_neighbor] =
                            n_cost[beg_vertex] + nearest_distance; // asn cur total cost to nearest_neighbor
                    node_prev_arr[nearest_neighbor] = beg_vertex; // assign beg_vertex as prev v to nearest_neighbor
                    NodeMinCost nmc0(nearest_neighbor, n_cost[nearest_neighbor]);
                    priority_q.insert(nmc0); // insert initial nmc0 into priority_q
                }
                // rm top from next_neighbors, since it's been conditioned and inserted into pq
                next_neighbors.minPriority();
            }

            // if deg(beg_vertex) == number of iterations we considered inserting beg_vertex into pq
            // aka next_neighbors is empty (or neighbors(beg_vertex).size() == prev_considered_counts[beg_vertex]?)
            if (next_neighbors.size() == 0) {
                // inner checks for abs safety, don't want to pop/modify wrong elt from memory
                //first cond not guaranteed, in fact, we might've pushed an edge that has lower cost from vertex_u
                // so we need to search through priority_q and remove the nmc corresp to beg_vertex
                // assert (priority_q.top().getNode() == beg_vertex); and assert (cur_neighbors.top() == priority_q.top());
                // sometimes false, and DNE direct way to remove
                // a particular node from priority_q => write new method in PriorityQueue to delete a particular node
                if (priority_q.size() != 0) {
                    cur_neighbors.minPriority(); // by removing top of cur_n's simultaneously w pq,
                    // pq shd be clear of any cur_n's nmc's since cur_neighbors empty
                    priority_q.remove(beg_vertex); // remove nmc corresp to nearest_neighbor from pq
                    closed.push_back(beg_vertex); // append to back of closed vector
                    continue;
                }
            }
            // popped pq and cur_neighbors => need to add to cur_neighbors nearest n from next_neighbors
            // if priority_q does not contain any of cur_neighbors (and pq not empty?), then we can re-init
            // cur_neighbors with all of priority_q since pq only has next_neighbors, and we closed cur_n's
            if (cur_neighbors.size() == 0) {
                // populate cur_ns with pq by inserting the number of elts next_neighbors prev held:
                // deg (beg_vertex) - 1 (the prev closest node that we came from, which was closed)
                // assert(next_neighbors.size() == 0) verify, then break; to reinit beg_vertex
                vector<NodeMinCost> carrier;
                for (int i = 0; i < neighbors(beg_vertex).size() - 1; ++i) {
                    if (find(closed.begin(), closed.end(), priority_q.top().getNode()) == closed.end())
                        carrier.push_back(priority_q.top()); // hold top for transfer if not in closed
                    if (priority_q.size() != 0)
                        priority_q.minPriority(); // pop top regardless of whether it's in closed
                    cur_neighbors.insert(carrier.back()); // insert recently pushed into cur_n
                }
                // put all the pq elts inserted into cur_neighbors back into cur_neighbors
                for (int i = 0; i < cur_neighbors.size(); ++i) {
                    if (!carrier.empty()) {
                        if (find(closed.begin(), closed.end(), carrier.back().getNode()) == closed.end())
                            priority_q.insert(carrier.back()); // put each unclosed nmc elt back into pq
                        carrier.pop_back(); // rm it from our temporary vector
                    }
                }
                carrier.clear(); // good for memory
                // at this point, next_neighbors is empty, ready for refill,
                // cur_neighbors contains only those unclosed nmc's prev'ly in next_neighbors,
                // priority_q contains ALL unclosed nmc's
            }
        }
        // we've run dry of next_neighbors to insert to pq
        // but we've exhausted all paths to next_neighbors, and hence closed a new vertex to oblivion
    } while (closed.back() != vertex_w && priority_q.size() != 0);
    // priority_q.size() != 0 replaced by !dead_end_reached

    // if we still haven't reached vertex_w, then it must be unconnected, so we return
    // a vector of int vertices that start and end at vertex_u
    if (closed.back() != vertex_w) {
        this->path = {vertex_u, vertex_u};
        return (this->path);
    }

    // since vertex_u dead loop not returned above, set shortest_path_distance
    this->setShortestPathDistance(n_cost[vertex_w]);

    // from node_prev_arr, push back each nearest prev node that lead from vertex_w to vertex_u
    // populate the public ShortestPath vector member called path
    int index0 = vertex_w;
    for (int i = 0; i < num_v && index0 != vertex_u; ++i) {
        path.push_back(index0);
        index0 = node_prev_arr[index0];
    }
    path.push_back(vertex_u);
    reverse(path.begin(), path.end()); // since we backtracked, it's in reverse order

    // clear vectors except for shortest path vector, path
    //cur_neighbors.clear();
    closed.clear();

    return path;
}

ShortestPath::~ShortestPath() = default;