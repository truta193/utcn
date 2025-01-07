#include <stdlib.h>
#include <string.h>
#include <queue>
#include <iostream>
#include "bfs.h"

int get_neighbors(const Grid *grid, Point p, Point neighb[]) {
    //TODO: When a point is on the wall, it does return it's neightbors, not sure if it's ok we'll see

    // TODO: fill the array neighb with the neighbors of the point p and return the number of neighbors
    // the point p will have at most 4 neighbors (up, down, left, right)
    // avoid the neighbors that are outside the grid limits or fall into a wall
    // note: the size of the array neighb is guaranteed to be at least 4

    if (grid == nullptr) {
        return 0;
    }

    if (p.row < 0 || p.row >= grid->rows || p.col < 0 || p.col >= grid->cols) {
        return 0;
    }

    int count = 0;

    if (p.row - 1 >= 0 && grid->mat[p.row - 1][p.col] == 0) {
        neighb[count].row = p.row - 1;
        neighb[count].col = p.col;
        neighb[count++] = Point {p.row - 1, p.col};
    }

    if (p.row + 1 < grid->rows && grid->mat[p.row + 1][p.col] == 0) {
        neighb[count].row = p.row + 1;
        neighb[count].col = p.col;
        neighb[count++] = Point {p.row + 1, p.col};
    }

    if (p.col - 1 >= 0 && grid->mat[p.row][p.col - 1] == 0) {
        neighb[count].row = p.row;
        neighb[count].col = p.col - 1;
        neighb[count++] = Point {p.row, p.col - 1};
    }

    if (p.col + 1 < grid->cols && grid->mat[p.row][p.col + 1] == 0) {
        neighb[count].row = p.row;
        neighb[count].col = p.col + 1;
        neighb[count++] = Point {p.row, p.col + 1};
    }

    return count;
}

void grid_to_graph(const Grid *grid, Graph *graph) {
    //we need to keep the nodes in a matrix, so we can easily refer to a position in the grid
    Node *nodes[MAX_ROWS][MAX_COLS];
    int i, j, k;
    Point neighb[4];

    //compute how many nodes we have and allocate each node
    graph->nrNodes = 0;
    for (i = 0; i < grid->rows; ++i) {
        for (j = 0; j < grid->cols; ++j) {
            if (grid->mat[i][j] == 0) {
                nodes[i][j] = (Node *) malloc(sizeof(Node));
                memset(nodes[i][j], 0, sizeof(Node)); //initialize all fields with 0/NULL
                nodes[i][j]->position.row = i;
                nodes[i][j]->position.col = j;
                ++graph->nrNodes;
            } else {
                nodes[i][j] = NULL;
            }
        }
    }
    graph->v = (Node **) malloc(graph->nrNodes * sizeof(Node *));
    k = 0;
    for (i = 0; i < grid->rows; ++i) {
        for (j = 0; j < grid->cols; ++j) {
            if (nodes[i][j] != NULL) {
                graph->v[k++] = nodes[i][j];
            }
        }
    }

    //compute the adjacency list for each node
    for (i = 0; i < graph->nrNodes; ++i) {
        graph->v[i]->adjSize = get_neighbors(grid, graph->v[i]->position, neighb);
        if (graph->v[i]->adjSize != 0) {
            graph->v[i]->adj = (Node **) malloc(graph->v[i]->adjSize * sizeof(Node *));
            k = 0;
            for (j = 0; j < graph->v[i]->adjSize; ++j) {
                if (neighb[j].row >= 0 && neighb[j].row < grid->rows &&
                    neighb[j].col >= 0 && neighb[j].col < grid->cols &&
                    grid->mat[neighb[j].row][neighb[j].col] == 0) {
                    graph->v[i]->adj[k++] = nodes[neighb[j].row][neighb[j].col];
                }
            }
            if (k < graph->v[i]->adjSize) {
                //get_neighbors returned some invalid neighbors
                graph->v[i]->adjSize = k;
                graph->v[i]->adj = (Node **) realloc(graph->v[i]->adj, k * sizeof(Node *));
            }
        }
    }
}

void free_graph(Graph *graph) {
    if (graph->v != NULL) {
        for (int i = 0; i < graph->nrNodes; ++i) {
            if (graph->v[i] != NULL) {
                if (graph->v[i]->adj != NULL) {
                    free(graph->v[i]->adj);
                    graph->v[i]->adj = NULL;
                }
                graph->v[i]->adjSize = 0;
                free(graph->v[i]);
                graph->v[i] = NULL;
            }
        }
        free(graph->v);
        graph->v = NULL;
    }
    graph->nrNodes = 0;
}

void bfs(Graph *graph, Node *s, Operation *op) {
    // TOOD: implement the BFS algorithm on the graph, starting from the node s
    // at the end of the algorithm, every node reachable from s should have the color BLACK
    // for all the visited nodes, the minimum distance from s (dist) and the parent in the BFS tree should be set
    // for counting the number of operations, the optional op parameter is received
    // since op can be NULL (when we are calling the bfs for display purposes), you should check it before counting:
    // if(op != NULL) op->count();

    for (int i = 0; i < graph->nrNodes; i++) {
        graph->v[i]->color = COLOR_WHITE;
        graph->v[i]->dist = -1;
        graph->v[i]->parent = nullptr;
    }

    s->color = COLOR_WHITE;
    s->dist = 0;
    s->parent = nullptr;

    std::queue q = std::queue<Node*>();

    q.push(s);

    while (!q.empty()) {
        Node *u = q.front();
        q.pop();

        for (int i = 0; i < u->adjSize; i++) {
            if (op != nullptr) {
                op->count();
            }

            if (u->adj[i]->color == COLOR_WHITE) {
                u->adj[i]->color = COLOR_GRAY;
                u->adj[i]->dist = u->dist + 1;
                u->adj[i]->parent = u;
                if (op != nullptr) {
                    op->count();
                    op->count();
                }
                q.push(u->adj[i]);
            }
        }
        u->color = COLOR_BLACK;
    }
}

void printParentVectorTree(int* parentArray, int size, Point *repr, int parent, int indent)
{
    for (int i = 0; i != size; i++)
    {
        if (parentArray[i] == parent) {
            for (int j = 0; j < indent; j++) {
                std::cout << "    ";
            }
            std::cout<< "(" << repr[i].row << ", " << repr[i].col << ")" << std::endl;
            printParentVectorTree(parentArray, size, repr, i, indent + 1);
        }
    }
}

void print_bfs_tree(Graph *graph) {
    //first, we will represent the BFS tree as a parent array
    int n = 0; //the number of nodes
    int *p = NULL; //the parent array
    Point *repr = NULL; //the representation for each element in p

    //some of the nodes in graph->v may not have been reached by BFS
    //p and repr will contain only the reachable nodes
    int *transf = (int *) malloc(graph->nrNodes * sizeof(int));
    for (int i = 0; i < graph->nrNodes; ++i) {
        if (graph->v[i]->color == COLOR_BLACK) {
            transf[i] = n;
            ++n;
        } else {
            transf[i] = -1;
        }
    }
    if (n == 0) {
        //no BFS tree
        free(transf);
        return;
    }

    int err = 0;
    p = (int *) malloc(n * sizeof(int));
    repr = (Point *) malloc(n * sizeof(Node));
    for (int i = 0; i < graph->nrNodes && !err; ++i) {
        if (graph->v[i]->color == COLOR_BLACK) {
            if (transf[i] < 0 || transf[i] >= n) {
                err = 1;
            } else {
                repr[transf[i]] = graph->v[i]->position;
                if (graph->v[i]->parent == NULL) {
                    p[transf[i]] = -1;
                } else {
                    err = 1;
                    for (int j = 0; j < graph->nrNodes; ++j) {
                        if (graph->v[i]->parent == graph->v[j]) {
                            if (transf[j] >= 0 && transf[j] < n) {
                                p[transf[i]] = transf[j];
                                err = 0;
                            }
                            break;
                        }
                    }
                }
            }
        }
    }
    free(transf);
    transf = NULL;

    if (!err) {
        // TODO: pretty print the BFS tree
        // the parrent array is p (p[k] is the parent for node k or -1 if k is the root)
        // when printing the node k, print repr[k] (it contains the row and column for that point)
        // you can adapt the code for transforming and printing multi-way trees from the previous labs

        int root = -1;
        for (int i = 0; i < n; i++) {
            if (p[i] == -1) {
                root = i;
                break;
            }
        }
        std::cout<< "(" << repr[root].row << ", " << repr[root].col << ")" << std::endl;
        printParentVectorTree(p, n, repr, root, 1);
    }

    if (p != NULL) {
        free(p);
        p = NULL;
    }
    if (repr != NULL) {
        free(repr);
        repr = NULL;
    }
}

int shortest_path(Graph *graph, Node *start, Node *end, Node *path[]) {
    // TODO: compute the shortest path between the nodes start and end in the given graph
    // the nodes from the path, should be filled, in order, in the array path
    // the number of nodes filled in the path array should be returned
    // if end is not reachable from start, return -1
    // note: the size of the array path is guaranteed to be at least 1000

    if (start == end) {
        path[0] = start;
        return 1;
    }

    bfs(graph, start);

    if (end->parent != nullptr) {
        int i = 0;
        while (end->parent != nullptr) {
            path[i++] = end;
            end = end->parent;
        }
        path[i] = start;

        for (int j = 0; j < i / 2; j++) {
            Node *temp = path[j];
            path[j] = path[i - 1 - j];
            path[i - 1 - j] = temp;
        }

        return i + 1;
    }

    return -1;
}


void performance() {
    int n, i;
    Profiler p("bfs");

    // vary the number of edges
    for (n = 1000; n <= 4500; n += 100) {
        Operation op = p.createOperation("bfs-edges", n);
        Graph graph;
        graph.nrNodes = 100;
        //initialize the nodes of the graph
        graph.v = (Node **) malloc(graph.nrNodes * sizeof(Node *));
        for (i = 0; i < graph.nrNodes; ++i) {
            graph.v[i] = (Node *) malloc(sizeof(Node));
            memset(graph.v[i], 0, sizeof(Node));
        }
        // TODO: generate n random edges
        // make sure the generated graph is connected

        bfs(&graph, graph.v[0], &op);
        free_graph(&graph);
    }

    // vary the number of vertices
    for (n = 100; n <= 200; n += 10) {
        Operation op = p.createOperation("bfs-vertices", n);
        Graph graph;
        graph.nrNodes = n;
        //initialize the nodes of the graph
        graph.v = (Node **) malloc(graph.nrNodes * sizeof(Node *));
        for (i = 0; i < graph.nrNodes; ++i) {
            graph.v[i] = (Node *) malloc(sizeof(Node));
            memset(graph.v[i], 0, sizeof(Node));
        }
        // TODO: generate 4500 random edges
        // make sure the generated graph is connected

        bfs(&graph, graph.v[0], &op);
        free_graph(&graph);
    }

    p.showReport();
}
