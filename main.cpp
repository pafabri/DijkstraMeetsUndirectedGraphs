// Peter Fabri
// Coursera HW 2 -- Dijkstra's shortest path
// Professor Ira Pohl
// UCSC
// Compiled/tested with C++14 gcc in CLionv2020.1 on Trisquel

// Resources that I found supplemental to writing (at least
// my understanding of) Dijkstra's algorithm into this program (informal citation)
// https://www.softwaretestinghelp.com/graph-implementation-cpp/
// https://www.youtube.com/watch?v=pSqmAO-m7Lk
// https://www.youtube.com/watch?v=a1
// https://www.youtube.com/watch?v=FSm1zybd0Tk

/* First time using valgrind, so I hope this is good.
 * (Valgrind) Verdict of Memory Usage (still reachable... idk it's meaning tbh)
 * BUT my 3.679 GB of RAM are happy running this :)
==5585==
==5585== HEAP SUMMARY:
==5585==     in use at exit: 72,704 bytes in 1 blocks
==5585==   total heap usage: 15,276 allocs, 15,275 frees, 1,610,100 bytes allocated
==5585==
==5585== LEAK SUMMARY:
==5585==    definitely lost: 0 bytes in 0 blocks
==5585==    indirectly lost: 0 bytes in 0 blocks
==5585==      possibly lost: 0 bytes in 0 blocks
==5585==    still reachable: 72,704 bytes in 1 blocks
==5585==         suppressed: 0 bytes in 0 blocks
==5585== Reachable blocks (those to which a pointer was found) are not shown.
==5585== To see them, rerun with: --leak-check=full --show-leak-kinds=all
==5585==
==5585== For counts of detected and suppressed errors, rerun with: -v
==5585== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)

 */

#include <iostream>
#include <vector>
#include "ShortestPath.h"
using namespace std;

void printUndirectedGraph(ShortestPath &, vector<int> &);

int main()
{
    int num_vertices = 50;      // Number of vertices in the graph
    double density = 0.1;       // graph density
    double max_weight = 10.0;   // max_weight to scale Edge distances
    int n_graphs = 30;          // number of graphs

    int first = 0, last = num_vertices - 1; // assign first and last vertices we want to find the dijkstra path of
    double sum_shortest_paths = 0.0;        // init sum_shortest_path

    vector<int> dijkstra_path;

    cout << "Note: if a shortest path is 0, then there was no shortest path found..." << endl;

    cout << "For each graph in " << n_graphs << " graphs, we've populated " << num_vertices
         << " vertices with " << density << " density,\nsuch that " << static_cast<int>(density * 100)
         << "% of " << (num_vertices - 1) * num_vertices / 2  << " edges of a graph are expected to be inserted,"
         << "\nwherein for each inserted edge a pseudo-random distance between 1 and " << max_weight << " is generated."
         << "\nEach graph's shortest path follows, with an ending average shortest path." << endl;

    int i = 1; // basically a for loop, but while has a connotation of performing like a driver... *legibility*
    while (i <= n_graphs) {

        ShortestPath undirected_graph(num_vertices, density, max_weight); // declare and call init'r w graph attributes
        undirected_graph.generateGraph(); // randomly generate edges, insert 'em into graph
        dijkstra_path = undirected_graph.findShortestPath(first, last); // find each shortest path

        cout << "\nGraph " << i << ":" << flush;
        printUndirectedGraph(undirected_graph, dijkstra_path); // print undirected graph details

        sum_shortest_paths += undirected_graph.pathSize(); // accumulate shortest paths, prep to avg shortest paths
        ++i;
    }

    cout << "\n\nAverage of Shortest Paths: " << sum_shortest_paths / n_graphs << endl << endl;

    return 0;
}

void printUndirectedGraph(ShortestPath & undirected_graph, vector<int> & dijkstra_path)
{
    cout << "\n\nMin Path Distance: " << undirected_graph.pathSize() << endl;
    cout << "Min Path Sequence: " << flush;
    for (auto & e: dijkstra_path) { cout << e << " " << flush; }

    cout << "\n\nDetailed Sequence: " << endl;
    int v0, v1;
    for (int i = 0; i < dijkstra_path.size() - 1; ++i) {
        v0 = dijkstra_path[i];
        v1 = dijkstra_path[i + 1];
        cout << v0 << " -> " << v1 << " : " << undirected_graph.get_edge_value(v0, v1) << endl;
    }
}

/// OUTPUT SAMPLE 1.0
/*
Note: if a shortest path is 0, then there was no shortest path found...
For each graph in 30 graphs, we've populated 50 vertices with 0.4 density,
such that 40% of 1225 edges of a graph are expected to be inserted,
wherein for each inserted edge a pseudo-random distance between 1 and 10 is generated.
Each graph's shortest path follows, with an ending average shortest path.

Graph 1:

Min Path Distance: 6.32355
Min Path Sequence: 0 29 23 49

Detailed Sequence:
0 -> 29 : 1.67326
29 -> 23 : 1.99106
23 -> 49 : 2.65923

Graph 2:

Min Path Distance: 3.5138
Min Path Sequence: 0 49

Detailed Sequence:
0 -> 49 : 3.5138

Graph 3:

Min Path Distance: 5.06872
Min Path Sequence: 0 11 49

Detailed Sequence:
0 -> 11 : 4.04859
11 -> 49 : 1.02013

Graph 4:

Min Path Distance: 7.32626
Min Path Sequence: 0 49

Detailed Sequence:
0 -> 49 : 7.32626

Graph 5:

Min Path Distance: 4.41006
Min Path Sequence: 0 37 49

Detailed Sequence:
0 -> 37 : 1.54008
37 -> 49 : 2.86998

Graph 6:

Min Path Distance: 2.71785
Min Path Sequence: 0 49

Detailed Sequence:
0 -> 49 : 2.71785

Graph 7:

Min Path Distance: 2.36072
Min Path Sequence: 0 49

Detailed Sequence:
0 -> 49 : 2.36072

Graph 8:

Min Path Distance: 5.79665
Min Path Sequence: 0 37 13 49

Detailed Sequence:
0 -> 37 : 1.52123
37 -> 13 : 2.5104
13 -> 49 : 1.76502

Graph 9:

Min Path Distance: 5.49497
Min Path Sequence: 0 32 9 49

Detailed Sequence:
0 -> 32 : 3.2253
32 -> 9 : 1.18688
9 -> 49 : 1.08279

Graph 10:

Min Path Distance: 3.47538
Min Path Sequence: 0 12 49

Detailed Sequence:
0 -> 12 : 1.65144
12 -> 49 : 1.82394

Graph 11:

Min Path Distance: 5.30201
Min Path Sequence: 0 40 49

Detailed Sequence:
0 -> 40 : 4.00166
40 -> 49 : 1.30036

Graph 12:

Min Path Distance: 4.65922
Min Path Sequence: 0 49

Detailed Sequence:
0 -> 49 : 4.65922

Graph 13:

Min Path Distance: 4.70505
Min Path Sequence: 0 31 38 49

Detailed Sequence:
0 -> 31 : 1.99565
31 -> 38 : 1.36651
38 -> 49 : 1.34289

Graph 14:

Min Path Distance: 6.30845
Min Path Sequence: 0 2 30 24 49

Detailed Sequence:
0 -> 2 : 1.40876
2 -> 30 : 1.97658
30 -> 24 : 1.11799
24 -> 49 : 1.80512

Graph 15:

Min Path Distance: 3.69819
Min Path Sequence: 0 49

Detailed Sequence:
0 -> 49 : 3.69819

Graph 16:

Min Path Distance: 2.89519
Min Path Sequence: 0 22 49

Detailed Sequence:
0 -> 22 : 1.28687
22 -> 49 : 1.60833

Graph 17:

Min Path Distance: 2.262
Min Path Sequence: 0 49

Detailed Sequence:
0 -> 49 : 2.262

Graph 18:

Min Path Distance: 5.70897
Min Path Sequence: 0 38 49

Detailed Sequence:
0 -> 38 : 2.20008
38 -> 49 : 3.5089

Graph 19:

Min Path Distance: 3.84943
Min Path Sequence: 0 45 23 49

Detailed Sequence:
0 -> 45 : 1.26523
45 -> 23 : 1.148
23 -> 49 : 1.4362

Graph 20:

Min Path Distance: 7.15377
Min Path Sequence: 0 22 31 49

Detailed Sequence:
0 -> 22 : 2.29017
22 -> 31 : 1.73448
31 -> 49 : 3.12912

Graph 21:

Min Path Distance: 4.81904
Min Path Sequence: 0 22 10 49

Detailed Sequence:
0 -> 22 : 1.82171
22 -> 10 : 1.94148
10 -> 49 : 1.05585

Graph 22:

Min Path Distance: 2.77783
Min Path Sequence: 0 49

Detailed Sequence:
0 -> 49 : 2.77783

Graph 23:

Min Path Distance: 4.17943
Min Path Sequence: 0 38 49

Detailed Sequence:
0 -> 38 : 2.15001
38 -> 49 : 2.02942

Graph 24:

Min Path Distance: 0
Min Path Sequence: 0

Detailed Sequence:

Graph 25:

Min Path Distance: 7.06444
Min Path Sequence: 0 12 43 13 49

Detailed Sequence:
0 -> 12 : 1.04873
12 -> 43 : 2.65344
43 -> 13 : 1.33063
13 -> 49 : 2.03164

Graph 26:

Min Path Distance: 3.73707
Min Path Sequence: 0 36 49

Detailed Sequence:
0 -> 36 : 2.31915
36 -> 49 : 1.41792

Graph 27:

Min Path Distance: 5.56678
Min Path Sequence: 0 29 17 49

Detailed Sequence:
0 -> 29 : 1.53489
29 -> 17 : 1.57497
17 -> 49 : 2.45693

Graph 28:

Min Path Distance: 5.25735
Min Path Sequence: 0 23 49

Detailed Sequence:
0 -> 23 : 1.95728
23 -> 49 : 3.30007

Graph 29:

Min Path Distance: 6.03825
Min Path Sequence: 0 44 49

Detailed Sequence:
0 -> 44 : 4.91136
44 -> 49 : 1.12689

Graph 30:

Min Path Distance: 6.62157
Min Path Sequence: 0 26 4 49

Detailed Sequence:
0 -> 26 : 4.44047
26 -> 4 : 1.00717
4 -> 49 : 1.17392


Average of Shortest Paths: 4.6364
*/

/// OUTPUT SAMPLE 1.1 (same density, number of vertices, maximum distance as above)
/*
Note: if a shortest path is 0, then there was no shortest path found...
For each graph in 30 graphs, we've populated 50 vertices with 0.4 density,
such that 40% of 1225 edges of a graph are expected to be inserted,
wherein for each inserted edge a pseudo-random distance between 1 and 10 is generated.
Each graph's shortest path follows, with an ending average shortest path.

Graph 1:

Min Path Distance: 5.69249
Min Path Sequence: 0 38 49

Detailed Sequence:
0 -> 38 : 4.31055
38 -> 49 : 1.38194

Graph 2:

Min Path Distance: 5.2022
Min Path Sequence: 0 39 49

Detailed Sequence:
0 -> 39 : 1.81501
39 -> 49 : 3.3872

Graph 3:

Min Path Distance: 4.96156
Min Path Sequence: 0 30 48 49

Detailed Sequence:
0 -> 30 : 1.11441
30 -> 48 : 1.01471
48 -> 49 : 2.83244

Graph 4:

Min Path Distance: 3.68533
Min Path Sequence: 0 33 49

Detailed Sequence:
0 -> 33 : 1.93776
33 -> 49 : 1.74757

Graph 5:

Min Path Distance: 3.98267
Min Path Sequence: 0 28 49

Detailed Sequence:
0 -> 28 : 2.3115
28 -> 49 : 1.67117

Graph 6:

Min Path Distance: 2.95281
Min Path Sequence: 0 49

Detailed Sequence:
0 -> 49 : 2.95281

Graph 7:

Min Path Distance: 5.448
Min Path Sequence: 0 40 26 49

Detailed Sequence:
0 -> 40 : 1.68077
40 -> 26 : 1.85916
26 -> 49 : 1.90807

Graph 8:

Min Path Distance: 3.71315
Min Path Sequence: 0 25 17 49

Detailed Sequence:
0 -> 25 : 1.01525
25 -> 17 : 1.6011
17 -> 49 : 1.0968

Graph 9:

Min Path Distance: 4.40878
Min Path Sequence: 0 38 28 49

Detailed Sequence:
0 -> 38 : 2.11384
38 -> 28 : 1.27704
28 -> 49 : 1.0179

Graph 10:

Min Path Distance: 4.65911
Min Path Sequence: 0 41 33 49

Detailed Sequence:
0 -> 41 : 2.4614
41 -> 33 : 1.01532
33 -> 49 : 1.18238

Graph 11:

Min Path Distance: 7.57512
Min Path Sequence: 0 4 20 49

Detailed Sequence:
0 -> 4 : 3.00292
4 -> 20 : 1.55434
20 -> 49 : 3.01787

Graph 12:

Min Path Distance: 4.53938
Min Path Sequence: 0 26 49

Detailed Sequence:
0 -> 26 : 1.73952
26 -> 49 : 2.79987

Graph 13:

Min Path Distance: 1.8138
Min Path Sequence: 0 49

Detailed Sequence:
0 -> 49 : 1.8138

Graph 14:

Min Path Distance: 4.19177
Min Path Sequence: 0 49

Detailed Sequence:
0 -> 49 : 4.19177

Graph 15:

Min Path Distance: 4.31652
Min Path Sequence: 0 24 49

Detailed Sequence:
0 -> 24 : 1.6189
24 -> 49 : 2.69762

Graph 16:

Min Path Distance: 3.46442
Min Path Sequence: 0 39 12 49

Detailed Sequence:
0 -> 39 : 1.12431
39 -> 12 : 1.32254
12 -> 49 : 1.01757

Graph 17:

Min Path Distance: 7.46371
Min Path Sequence: 0 49

Detailed Sequence:
0 -> 49 : 7.46371

Graph 18:

Min Path Distance: 5.83109
Min Path Sequence: 0 49

Detailed Sequence:
0 -> 49 : 5.83109

Graph 19:

Min Path Distance: 5.04503
Min Path Sequence: 0 37 8 49

Detailed Sequence:
0 -> 37 : 1.09537
37 -> 8 : 2.27267
8 -> 49 : 1.67699

Graph 20:

Min Path Distance: 4.09227
Min Path Sequence: 0 5 49

Detailed Sequence:
0 -> 5 : 1.77678
5 -> 49 : 2.31549

Graph 21:

Min Path Distance: 4.78014
Min Path Sequence: 0 28 49

Detailed Sequence:
0 -> 28 : 2.74347
28 -> 49 : 2.03666

Graph 22:

Min Path Distance: 8.06843
Min Path Sequence: 0 35 17 49

Detailed Sequence:
0 -> 35 : 3.00594
35 -> 17 : 2.80103
17 -> 49 : 2.26146

Graph 23:

Min Path Distance: 0
Min Path Sequence: 0 0

Detailed Sequence:
0 -> 0 : 0

Graph 24:

Min Path Distance: 5.38614
Min Path Sequence: 0 12 25 49

Detailed Sequence:
0 -> 12 : 1.2495
12 -> 25 : 2.77795
25 -> 49 : 1.35869

Graph 25:

Min Path Distance: 0
Min Path Sequence: 0 0

Detailed Sequence:
0 -> 0 : 0

Graph 26:

Min Path Distance: 6.29957
Min Path Sequence: 0 49

Detailed Sequence:
0 -> 49 : 6.29957

Graph 27:

Min Path Distance: 7.6312
Min Path Sequence: 0 49

Detailed Sequence:
0 -> 49 : 7.6312

Graph 28:

Min Path Distance: 6.69737
Min Path Sequence: 0 47 26 49

Detailed Sequence:
0 -> 47 : 1.53652
47 -> 26 : 2.97372
26 -> 49 : 2.18714

Graph 29:

Min Path Distance: 3.03607
Min Path Sequence: 0 23 49

Detailed Sequence:
0 -> 23 : 1.43156
23 -> 49 : 1.60451

Graph 30:

Min Path Distance: 4.33613
Min Path Sequence: 0 14 36 49

Detailed Sequence:
0 -> 14 : 1.60771
14 -> 36 : 1.46561
36 -> 49 : 1.2628


Average of Shortest Paths: 4.64247
 */

/// OUTPUT SAMPLE 2.0
/*
Note: if a shortest path is 0, then there was no shortest path found...
For each graph in 30 graphs, we've populated 50 vertices with 0.1 density,
such that 10% of 1225 edges of a graph are expected to be inserted,
wherein for each inserted edge a pseudo-random distance between 1 and 10 is generated.
Each graph's shortest path follows, with an ending average shortest path.

Graph 1:

Min Path Distance: 13.152
Min Path Sequence: 0 1 47 25 49

Detailed Sequence:
0 -> 1 : 2.54257
1 -> 47 : 5.65913
47 -> 25 : 2.86222
25 -> 49 : 2.08811

Graph 2:

Min Path Distance: 13.0973
Min Path Sequence: 0 19 1 17 49

Detailed Sequence:
0 -> 19 : 3.16495
19 -> 1 : 2.66331
1 -> 17 : 5.04155
17 -> 49 : 2.2275

Graph 3:

Min Path Distance: 13.4334
Min Path Sequence: 0 8 7 49

Detailed Sequence:
0 -> 8 : 3.75457
8 -> 7 : 2.78204
7 -> 49 : 6.89681

Graph 4:

Min Path Distance: 9.16514
Min Path Sequence: 0 4 49

Detailed Sequence:
0 -> 4 : 4.37037
4 -> 49 : 4.79477

Graph 5:

Min Path Distance: 10.5713
Min Path Sequence: 0 37 49

Detailed Sequence:
0 -> 37 : 7.06857
37 -> 49 : 3.5027

Graph 6:

Min Path Distance: 6.5649
Min Path Sequence: 0 33 49

Detailed Sequence:
0 -> 33 : 2.80315
33 -> 49 : 3.76176

Graph 7:

Min Path Distance: 5.00786
Min Path Sequence: 0 28 49

Detailed Sequence:
0 -> 28 : 1.64117
28 -> 49 : 3.36669

Graph 8:

Min Path Distance: 7.6557
Min Path Sequence: 0 28 49

Detailed Sequence:
0 -> 28 : 3.24899
28 -> 49 : 4.40671

Graph 9:

Min Path Distance: 8.56201
Min Path Sequence: 0 44 46 7 49

Detailed Sequence:
0 -> 44 : 1.25902
44 -> 46 : 1.13862
46 -> 7 : 4.14488
7 -> 49 : 2.01949

Graph 10:

Min Path Distance: 5.23892
Min Path Sequence: 0 49

Detailed Sequence:
0 -> 49 : 5.23892

Graph 11:

Min Path Distance: 8.76816
Min Path Sequence: 0 3 13 43 49

Detailed Sequence:
0 -> 3 : 2.0304
3 -> 13 : 2.04193
13 -> 43 : 3.23363
43 -> 49 : 1.4622

Graph 12:

Min Path Distance: 13.5059
Min Path Sequence: 0 17 8 27 32 49

Detailed Sequence:
0 -> 17 : 5.85632
17 -> 8 : 2.6441
8 -> 27 : 2.04644
27 -> 32 : 1.56026
32 -> 49 : 1.39881

Graph 13:

Min Path Distance: 0
Min Path Sequence: 0 0

Detailed Sequence:
0 -> 0 : 0

Graph 14:

Min Path Distance: 10.514
Min Path Sequence: 0 31 14 49

Detailed Sequence:
0 -> 31 : 5.12411
31 -> 14 : 2.81212
14 -> 49 : 2.57776

Graph 15:

Min Path Distance: 21.4753
Min Path Sequence: 0 46 5 49

Detailed Sequence:
0 -> 46 : 7.46793
46 -> 5 : 7.93982
5 -> 49 : 6.0675

Graph 16:

Min Path Distance: 8.9073
Min Path Sequence: 0 20 49

Detailed Sequence:
0 -> 20 : 4.85482
20 -> 49 : 4.05248

Graph 17:

Min Path Distance: 20.2872
Min Path Sequence: 0 13 31 1 49

Detailed Sequence:
0 -> 13 : 8.76112
13 -> 31 : 2.4693
31 -> 1 : 5.17905
1 -> 49 : 3.87772

Graph 18:

Min Path Distance: 0
Min Path Sequence: 0 0

Detailed Sequence:
0 -> 0 : 0

Graph 19:

Min Path Distance: 0
Min Path Sequence: 0 0

Detailed Sequence:
0 -> 0 : 0

Graph 20:

Min Path Distance: 15.3496
Min Path Sequence: 0 1 43 47 6 49

Detailed Sequence:
0 -> 1 : 1.28704
1 -> 43 : 2.25026
43 -> 47 : 7.47569
47 -> 6 : 1.30348
6 -> 49 : 3.03317

Graph 21:

Min Path Distance: 0
Min Path Sequence: 0 0

Detailed Sequence:
0 -> 0 : 0

Graph 22:

Min Path Distance: 11.8042
Min Path Sequence: 0 4 45 29 49

Detailed Sequence:
0 -> 4 : 1.07615
4 -> 45 : 4.15847
45 -> 29 : 2.36273
29 -> 49 : 4.20686

Graph 23:

Min Path Distance: 11.2023
Min Path Sequence: 0 19 31 44 49

Detailed Sequence:
0 -> 19 : 1.22866
19 -> 31 : 1.82506
31 -> 44 : 6.7946
44 -> 49 : 1.354

Graph 24:

Min Path Distance: 7.28324
Min Path Sequence: 0 3 49

Detailed Sequence:
0 -> 3 : 5.75471
3 -> 49 : 1.52853

Graph 25:

Min Path Distance: 0
Min Path Sequence: 0 0

Detailed Sequence:
0 -> 0 : 0

Graph 26:

Min Path Distance: 12.5656
Min Path Sequence: 0 7 49

Detailed Sequence:
0 -> 7 : 5.01568
7 -> 49 : 7.54994

Graph 27:

Min Path Distance: 6.48853
Min Path Sequence: 0 26 22 49

Detailed Sequence:
0 -> 26 : 1.14078
26 -> 22 : 2.25099
22 -> 49 : 3.09676

Graph 28:

Min Path Distance: 0
Min Path Sequence: 0 0

Detailed Sequence:
0 -> 0 : 0

Graph 29:

Min Path Distance: 9.41176
Min Path Sequence: 0 21 12 49

Detailed Sequence:
0 -> 21 : 6.66357
21 -> 12 : 1.33984
12 -> 49 : 1.40835

Graph 30:

Min Path Distance: 12.9176
Min Path Sequence: 0 44 49

Detailed Sequence:
0 -> 44 : 4.55482
44 -> 49 : 8.36281


Average of Shortest Paths: 8.76431
 */

/// OUTPUT SAMPLE 2.1
/*
Note: if a shortest path is 0, then there was no shortest path found...
For each graph in 30 graphs, we've populated 50 vertices with 0.1 density,
such that 10% of 1225 edges of a graph are expected to be inserted,
wherein for each inserted edge a pseudo-random distance between 1 and 10 is generated.
Each graph's shortest path follows, with an ending average shortest path.

Graph 1:

Min Path Distance: 14.4656
Min Path Sequence: 0 7 28 49

Detailed Sequence:
0 -> 7 : 3.16552
7 -> 28 : 5.15687
28 -> 49 : 6.14321

Graph 2:

Min Path Distance: 18.2308
Min Path Sequence: 0 40 10 26 49

Detailed Sequence:
0 -> 40 : 6.27219
40 -> 10 : 4.09426
10 -> 26 : 1.05305
26 -> 49 : 6.8113

Graph 3:

Min Path Distance: 6.69777
Min Path Sequence: 0 29 25 49

Detailed Sequence:
0 -> 29 : 1.97681
29 -> 25 : 3.53214
25 -> 49 : 1.18882

Graph 4:

Min Path Distance: 8.63803
Min Path Sequence: 0 28 31 49

Detailed Sequence:
0 -> 28 : 5.51358
28 -> 31 : 1.74939
31 -> 49 : 1.37506

Graph 5:

Min Path Distance: 10.4112
Min Path Sequence: 0 40 7 19 17 39 49

Detailed Sequence:
0 -> 40 : 1.50455
40 -> 7 : 1.62064
7 -> 19 : 1.34643
19 -> 17 : 1.47334
17 -> 39 : 2.59133
39 -> 49 : 1.87496

Graph 6:

Min Path Distance: 6.04923
Min Path Sequence: 0 25 49

Detailed Sequence:
0 -> 25 : 1.56526
25 -> 49 : 4.48397

Graph 7:

Min Path Distance: 0
Min Path Sequence: 0 0

Detailed Sequence:
0 -> 0 : 0

Graph 8:

Min Path Distance: 0
Min Path Sequence: 0 0

Detailed Sequence:
0 -> 0 : 0

Graph 9:

Min Path Distance: 7.19958
Min Path Sequence: 0 26 49

Detailed Sequence:
0 -> 26 : 3.58894
26 -> 49 : 3.61063

Graph 10:

Min Path Distance: 13.6806
Min Path Sequence: 0 29 5 31 33 49

Detailed Sequence:
0 -> 29 : 1.84963
29 -> 5 : 4.15138
5 -> 31 : 2.75621
31 -> 33 : 1.19735
33 -> 49 : 3.72604

Graph 11:

Min Path Distance: 9.40877
Min Path Sequence: 0 41 28 49

Detailed Sequence:
0 -> 41 : 1.32972
41 -> 28 : 6.29626
28 -> 49 : 1.78278

Graph 12:

Min Path Distance: 12.2267
Min Path Sequence: 0 34 31 49

Detailed Sequence:
0 -> 34 : 5.26568
34 -> 31 : 5.4884
31 -> 49 : 1.47258

Graph 13:

Min Path Distance: 0
Min Path Sequence: 0 0

Detailed Sequence:
0 -> 0 : 0

Graph 14:

Min Path Distance: 0
Min Path Sequence: 0 0

Detailed Sequence:
0 -> 0 : 0

Graph 15:

Min Path Distance: 0
Min Path Sequence: 0 0

Detailed Sequence:
0 -> 0 : 0

Graph 16:

Min Path Distance: 12.747
Min Path Sequence: 0 6 49

Detailed Sequence:
0 -> 6 : 9.58583
6 -> 49 : 3.16117

Graph 17:

Min Path Distance: 9.03399
Min Path Sequence: 0 49

Detailed Sequence:
0 -> 49 : 9.03399

Graph 18:

Min Path Distance: 10.6693
Min Path Sequence: 0 31 40 49

Detailed Sequence:
0 -> 31 : 6.00661
31 -> 40 : 1.78171
40 -> 49 : 2.88094

Graph 19:

Min Path Distance: 8.56477
Min Path Sequence: 0 37 15 49

Detailed Sequence:
0 -> 37 : 2.81361
37 -> 15 : 1.99475
15 -> 49 : 3.75641

Graph 20:

Min Path Distance: 6.37989
Min Path Sequence: 0 1 49

Detailed Sequence:
0 -> 1 : 3.94785
1 -> 49 : 2.43204

Graph 21:

Min Path Distance: 0
Min Path Sequence: 0 0

Detailed Sequence:
0 -> 0 : 0

Graph 22:

Min Path Distance: 9.61184
Min Path Sequence: 0 27 21 31 49

Detailed Sequence:
0 -> 27 : 4.12671
27 -> 21 : 2.01977
21 -> 31 : 1.94721
31 -> 49 : 1.51815

Graph 23:

Min Path Distance: 10.026
Min Path Sequence: 0 26 23 49

Detailed Sequence:
0 -> 26 : 5.08775
26 -> 23 : 1.26462
23 -> 49 : 3.67362

Graph 24:

Min Path Distance: 0
Min Path Sequence: 0 0

Detailed Sequence:
0 -> 0 : 0

Graph 25:

Min Path Distance: 0
Min Path Sequence: 0 0

Detailed Sequence:
0 -> 0 : 0

Graph 26:

Min Path Distance: 11.2272
Min Path Sequence: 0 2 5 49

Detailed Sequence:
0 -> 2 : 5.80626
2 -> 5 : 3.36735
5 -> 49 : 2.05357

Graph 27:

Min Path Distance: 0
Min Path Sequence: 0 0

Detailed Sequence:
0 -> 0 : 0

Graph 28:

Min Path Distance: 9.92241
Min Path Sequence: 0 22 49

Detailed Sequence:
0 -> 22 : 5.43266
22 -> 49 : 4.48976

Graph 29:

Min Path Distance: 13.9708
Min Path Sequence: 0 2 44 21 49

Detailed Sequence:
0 -> 2 : 5.23226
2 -> 44 : 1.44455
44 -> 21 : 1.75333
21 -> 49 : 5.5407

Graph 30:

Min Path Distance: 11.7709
Min Path Sequence: 0 36 27 49

Detailed Sequence:
0 -> 36 : 7.04025
36 -> 27 : 1.28187
27 -> 49 : 3.44882


Average of Shortest Paths: 7.36441

 */

// May place the below in main() before return 0; if you wish to debug and follow along all paths
// to manually, by hand, verify that the shortest path was truly taken (rec'd 8-12 vertices, 0.1-0.4 density)
/*
vector<int> i_neighbors;
ShortestPath undirected_graph(num_vertices, density, max_weight); // init'e graph attributes
undirected_graph.generateGraph(); // randomly generate edges, insert 'em into graph

int first = 0, last = num_vertices - 1;

vector<int> dijkstra_path = undirected_graph.findShortestPath(first, last);

cout << "Min Path Distance: " << undirected_graph.pathSize() << endl;
cout << "Min Path Sequence: " << flush;
for (auto & e: dijkstra_path) { cout << e << " " << flush; }

cout << "\n\nDetailed Sequence: " << endl;
int v0, v1;
for (int i = 0; i < dijkstra_path.size() - 1; ++i) {
    v0 = dijkstra_path[i];
    v1 = dijkstra_path[i + 1];
    cout << v0 << " -> " << v1 << " : " << undirected_graph.get_edge_value(v0, v1) << endl;
}
*/
// Uncomment Below For Excessive Debuggy Info
/*
    cout << "\t\t  adjacency list" << endl;
    cout << "\nedge count: " << undirected_graph.E() << endl << endl;
    undirected_graph.displayVerticesPerEdge();

    for (int i = 0; i < num_vertices; ++i) {
        i_neighbors = undirected_graph.neighbors(i);
        cout << i << " connects to " << i_neighbors.size() << " nodes" << endl << endl;
    }
*/