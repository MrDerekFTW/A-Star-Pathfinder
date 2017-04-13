#ifndef NODES_H
#define NODES_H

//#define PRINT_DEBUG_INFO

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <stack>

/**
 * Structure: point
 * -----------------
 * Contains x and y coordinates.
 */

struct point
{
    int x;
    int y;
};

/**
 * Structure: pntCmpFn
 * -------------------
 * Defines comparison operator so that point can be used with
 * ordered stl classes.
 */

struct pntCmpFn
{
    bool operator() (point one, point two)
    {
        if ( one.x < two.x )
            return true;
        if ( one.y < two.y && one.x == two.x )
            return true;
        return false;
    }
};

/**
 * Structure: node
 * ---------------
 * Stores x and y coordinates, a parent node, as well as some
 * heuristics. moveCost is the overall value of the node, which
 * is simply the sum of distTravld and distToDest.
 *
 * Sample declaration:
 *      node origin = {NULL, xCoordinate, yCoordinate, 0, 0, 0};
 */

struct node
{
    const node *parent;
    point position;
    float moveCost, distTravld, distToDest;
};

/**
 * Structure: nodeCmpFn
 * --------------------
 * Defines comparison operator so that node can be used with
 * ordered stl classes.
 */

struct nodeCmpFn
{
    bool operator() (node one, node two)
    {
        if ( one.position.x < two.position.x )
            return true;
        if ( one.position.y < two.position.y && one.position.x == two.position.x )
            return true;
        return false;
    }
};

/**
 * Function: distBtwnPoints
 * ------------------------
 * Returns the distance between two points.
 */

float distBtwnPnts(point one, point two);

/**
 * Function: testAdjacency
 * -----------------------
 * Returns true if a and b are within one point of each other.
 */

bool testAdjacency(point a, point b);

/**
 * Function: clearNodeStack
 * ------------------------
 * Pops off all nodes from the provided node stack.
 */

void clearNodeStack(std::stack<node> *nodeStack);

/**
 * Function: printNodeStack
 * ------------------------
 * Pops off all elements of nodeStack and prints
 * each node's (x,y) values to the console.
 */

void printNodeStack(std::stack<node> *nodeStack);

#endif // NODES_H
