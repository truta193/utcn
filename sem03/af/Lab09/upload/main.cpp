#include <iostream>
#include "DisjointSet.h"
#include "Profiler.h"
#include "AdjList.h"
#define ENABLE_DEMO

#define MAX_SIZE 10000
#define NR_TESTS 5
#define STEP_SIZE 100
Profiler *profiler = new Profiler("Kruskal");

Edge *generateRandomGraph(int size, int minNode, int maxNode) {
    Edge *edges = new Edge[size];
    int *keys = new int[size+1];
    FillRandomArray(keys, size+1, minNode, maxNode, false, UNSORTED);
    //Guarantee all nodes are present
    for (int i = minNode; i < maxNode + 1; i++) {
        bool exists = false;
        for (int j = 0; j < size + 1; j++) {
            if (i == keys[j]) {
                exists = true;
                break;
            }
        }
        if (!exists) {
            keys[rand()%(size)] = i;
            i = -1;
        }
    }

    //Generate edges
    for (int i = 0; i < size; i++) {
        edges[i].src = keys[i];
        edges[i].dest = keys[i + 1];
        edges[i].weight = rand() % 100;
    }

    //Remove duplicates
    int initialSize = size;
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
                if ((edges[i].src == edges[j].src && edges[i].dest == edges[j].dest) ||
                    (edges[i].src == edges[j].dest && edges[i].dest == edges[j].src)) {
                    edges[j] = edges[size - 1];
                    size--;
                    j--;
                }
        }
    }

    //Remove self loops
    for (int i = 0; i < size; i++) {
        if (edges[i].src == edges[i].dest) {
            edges[i] = edges[size - 1];
            size--;
            i--;
        }
    }

    //Refill
    while (size < initialSize) {
        Edge edge;
        do {
            edge.src = rand() % (maxNode + 1);
            edge.dest = rand() % (maxNode + 1);
            std::cout << edge.src << " " << edge.dest << std::endl;
        } while (edge.src == edge.dest);
        edge.weight = rand() % 100;
        bool exists = false;
        for (int i = 0; i < size; i++) {
            if ((edges[i].src == edge.src && edges[i].dest == edge.dest) ||
                (edges[i].src == edge.dest && edges[i].dest == edge.src)) {
                exists = true;
                break;
            }
        }
        if (!exists) {
            edges[size] = edge;
            size++;
        }
    }

    return edges;
}

DisjointSet* Kruskal(Edge *edges, int edgeCount, int nodeCount) {
    DisjointSet *set = new DisjointSet(profiler, nodeCount);
    for (int i = 0; i < nodeCount; i++) {
        set->makeSet(i, "Make", nodeCount);
    }
    std::sort(edges, edges + edgeCount, compareEdges);
#if defined(ENABLE_DEMO)
    for (int i = 0; i < edgeCount; i++) {
        std::cout << edges[i].src << " " << edges[i].dest << " " << edges[i].weight << std::endl;
    }
#endif
    for (int i = 0; i < edgeCount; i++) {
        if (set->findSet(edges[i].src, "findAssign", "findComp", nodeCount) != set->findSet(edges[i].dest, "findAssign", "findComp", nodeCount)) {
            set->unionSets(edges[i].src, edges[i].dest, "unionAssign", "unionComp", nodeCount, "findComp", "findAssign");
#if defined(ENABLE_DEMO)
            std::cout << "Added edge " << edges[i].src << " " << edges[i].dest << " " << edges[i].weight << std::endl;
#endif
        }
    }
    return set;
}

void demoDisjointSet() {
    DisjointSet set(profiler, 10);
    for (int i = 0; i < 10; i++) {
        set.makeSet(i, "t", 0);
    }
    std::cout << "====================" << std::endl;
    set.unionSets(2, 3, "t", "t", 0, "t", "t");
    std::cout << "Set of 3:" << set.findSet(3, "t", "t", 0) << std::endl;
    std::cout << "====================" << std::endl;
    set.unionSets(4, 5, "t", "t", 0, "t", "t");
    std::cout << "Set of 5:" << set.findSet(5, "t", "t", 0) << std::endl;
    std::cout << "====================" << std::endl;
    set.unionSets(6, 7, "t", "t", 0, "t", "t");
    std::cout << "Set of 7:" << set.findSet(7, "t", "t", 0) << std::endl;
    std::cout << "====================" << std::endl;
    set.unionSets(1, 7, "t", "t", 0, "t", "t");
    std::cout << "Set of 1:" << set.findSet(1, "t", "t", 0) << std::endl;
    std::cout << "====================" << std::endl;
    set.unionSets(6, 4, "t", "t", 0, "t", "t");
    std::cout << "Set of 4:" << set.findSet(4, "t", "t", 0) << std::endl;
    std::cout << "====================" << std::endl;
    set.unionSets(1, 4, "t", "t", 0, "t", "t");
    std::cout << "Set of 4:" << set.findSet(4, "t", "t", 0) << std::endl;
    std::cout << "====================" << std::endl;

    set.printAllSets();
}

void demoKruskal() {
    Edge *edges = generateRandomGraph(9, 0, 4);
    DisjointSet *set = Kruskal(edges, 9, 5);
    set->printAllSets();
}

void report() {
    for (int i = STEP_SIZE; i <= MAX_SIZE; i += STEP_SIZE) {
        std::cout << i << std::endl;
        for (int test = 0; test < NR_TESTS; test++) {
            int edgeCount = 4 * i;
            Edge *edges = generateRandomGraph(edgeCount, 0, i);
            Kruskal(edges, edgeCount, i);
        }
    }

    profiler->divideValues("Make", NR_TESTS);
    profiler->addSeries("Find", "findAssign", "findComp");
    profiler->divideValues("Find", NR_TESTS);
    profiler->addSeries("Union", "unionAssign", "unionComp");
    profiler->divideValues("Union", NR_TESTS);
    profiler->createGroup("Total", "Make", "Find", "Union");
    profiler->addSeries("tt", "Make", "Find");
    profiler->addSeries("Kruskal", "tt", "Union");
    profiler->showReport();
}

int main() {
    //report();
    //demoDisjointSet();
    std::cout << "====================" << std::endl;
    demoKruskal();
    return 0;
}
