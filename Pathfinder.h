/// Pathfinder class
/// Author: Derek Blankenship
/// Date: 4/12/17

#ifndef PATHFINDER_H
#define PATHFINDER_H

#define ALLOW_DIAGONAL

#include "Nodes.h"

#include <vector>
#include <set>
#include <stack>

enum pathState {CLOSED, OPEN};

/**
 * Class: Pathfinder
 * --------------
 * Finds shortest path between two points on a 2D coordinate plane.
 *
 * Methods:
 */


class Pathfinder
{
    public:
        Pathfinder();

/**
 * Method: findPath
 * ---------------------------------------------------------
 * Uses the A* pathfinding algorithm to find the shortest
 * path from the origin point to the destination point. User
 * must provide a pointer to a 2D array represented as a
 * vector of vectors that includes information on the
 * pathability of each point on the map. Closed points cannot
 * be passed through and are represented by the integer 0.
 * Open points can be passed through and are represented by
 * the integer 1. Returns a stack of nodes that represent the
 * path if a path is possible, otherwise returns an empty stack.
 */

        std::stack<point> findPath(point origin, point destination,
                                  std::vector< std::vector<int> > *pathingMap);

        virtual ~Pathfinder();
    protected:
    private:

/**
 * Private Method: makeNewNode
 * ---------------------------
 * A helper function for findPath. This function creates a new
 * node by copying a provided node and changing it's x and y
 * values by the provided amount. Thus one can make new nodes for
 * several different directions as seen in findPath.
 */

        void makeNewNode(int changeX, int changeY, const node *parent,
                             point *destination, std::vector<node> *nodes,
                             std::vector< std::vector<int> > *pathingMap);

/**
 * Private Method: setHeuristicValues
 * ----------------------------------
 * A helper function for findPath. Returns a node with values set
 * for distTravld, distToDest, and moveCost.
 */

        node setHeuristicValues(node curr, const node *parent, point *dest);

/**
 * Private Method: findLowestCost
 * ------------------------------
 * A helper function for findPath. This function uses linear
 * search to find the node with the lowest (best) moveCost value,
 * which is used to determine the next best node to move to in
 * my implementation of the A* pathfinding algorithm.
 */

        node findLowestCost(std::set<node, nodeCmpFn> *s);

/**
 * Private Method: constructPath
 * -----------------------------
 * A helper function for findPath. This function produces a path
 * by tracing back through the parents of the goal node found by
 * findPath.
 */

        std::stack<point> constructPath(const node *root);

};

#endif // PATHFINDER_H
