#include "Pathfinder.h"

Pathfinder::Pathfinder()
{
    //ctor
}

std::stack<point> Pathfinder::findPath(point origin, point destination,
                                      std::vector< std::vector<int> > *pathingMap)
{
    // using A* algorithm with small modifications

    node originNode = {NULL, origin.x, origin.y, 0, 0, 0};

    std::stack<point> finalPath;

    std::set<node, nodeCmpFn> open;
    std::set<node, nodeCmpFn> closed;
    open.insert(originNode);

    while (!open.empty())
    {
        node bestNode = this->findLowestCost(&open);
        open.erase(open.find(bestNode));
        closed.insert(bestNode);
        const node *parent = &(*closed.find(bestNode));

        std::vector<node> childNodes;

        this->makeNewNode(1, 0, parent, &destination, &childNodes, pathingMap); // East
        this->makeNewNode(-1, 0, parent, &destination, &childNodes, pathingMap); // West

        this->makeNewNode(0, 1, parent, &destination, &childNodes, pathingMap); // South
        this->makeNewNode(0, -1, parent, &destination, &childNodes, pathingMap); // North

        #ifdef ALLOW_DIAGONAL
        this->makeNewNode(1, 1, parent, &destination, &childNodes, pathingMap);  // SE
        this->makeNewNode(-1, -1, parent, &destination, &childNodes, pathingMap); // NW

        this->makeNewNode(-1, 1, parent, &destination, &childNodes, pathingMap); // SW
        this->makeNewNode(1, -1, parent, &destination, &childNodes, pathingMap); // SE
        #endif // ALLOW_DIAGONAL

        int numChildren = childNodes.size(); // use dummy because nodes may decrease in size

        for (int i = 0; i < numChildren; i++)
        {
            node curr = childNodes.back();
            childNodes.pop_back();

            if (curr.position.x == destination.x && curr.position.y == destination.y)
            {
                finalPath = this->constructPath(&curr); // path found!
                return finalPath;
            }

            curr = this->setHeuristicValues(curr, parent, &destination);
            bool addToOpen = true;

            if (open.find(curr) != open.end())
            {
                node currInSet = *(open.find(curr));
                if (currInSet.moveCost < curr.moveCost)
                    addToOpen = false;
            }

            if (closed.find(curr) != closed.end())
            {
                node currInSet = *(closed.find(curr));
                if (currInSet.moveCost < curr.moveCost)
                    addToOpen = false;
            }

            if (addToOpen == true)
            {
                open.insert(curr);
            }
        }
    }
    clearPointStack(&finalPath);
    return finalPath;
}


Pathfinder::~Pathfinder()
{
    //dtor
}

/*
 * Private Methods
 * ---------------
 */

void Pathfinder::makeNewNode(int changeX, int changeY, const node *parent,
                             point *destination, std::vector<node> *nodes,
                             std::vector< std::vector<int> > *pathingMap)
{
    node newNode = *(parent);
    newNode.parent = parent;
    newNode.position.x = newNode.position.x + changeX;
    newNode.position.y = newNode.position.y + changeY;
    #ifdef PRINT_DEBUG_INFO
    std::cout << "Pathfinder::makeNewNode -> Considering node: (" << newNode.x << "," << newNode.y << ")" << std::endl;
    #endif // PRINT_DEBUG_INFO
    if (newNode.position.x == destination->x
        && newNode.position.y == destination->y)
    {
        #ifdef PRINT_DEBUG_INFO
        std::cout << "Pathfinder::makeNewNode -> Exception made!" << std::endl;
        #endif // PRINT_DEBUG_INFO
        nodes->push_back(newNode);
        return;
    }
    if (newNode.position.x < (*pathingMap).size())
    {
        if (newNode.position.y < (*pathingMap)[newNode.position.x].size())
        {
            if ( (*pathingMap)[newNode.position.x][newNode.position.y] == OPEN)
            {
                nodes->push_back(newNode);
            }
        }
    }
}

node Pathfinder::setHeuristicValues(node curr, const node *parent, point *dest)
{
    curr.distTravld = parent->distTravld + distBtwnPnts(curr.position, (*parent).position);
    point currPoint = {curr.position.x, curr.position.y};
    curr.distToDest = distBtwnPnts(currPoint, *dest);
    curr.moveCost = curr.distTravld + curr.distToDest;
    return curr;
}


node Pathfinder::findLowestCost(std::set<node, nodeCmpFn> *s)
{
    node best = *(s->begin());
    std::set<node, nodeCmpFn>::iterator i;
    for (i = s->begin(); i != s->end(); i++)
    {
        node curr = *i;
        if (curr.moveCost < best.moveCost)
            best = curr;
    }
    return best;
}

std::stack<point> Pathfinder::constructPath(const node *root)
{
    std::stack<point> path;
    //std::stack<node> path;
    while (true)
    {
        #ifdef PRINT_DEBUG_INFO
        std::cout << "Pathfinder::constructPath -> Current: (" << root->x << "," << root->y << ")" << std::endl;
        #endif // PRINT_DEBUG_INFO
        point pt = {root->position.x, root->position.y};
        path.push(pt);
        if (root->parent == NULL)
        {
            break;
        }

        #ifdef PRINT_DEBUG_INFO
        std::cout << "Pathfinder::constructPath -> Parent: (" << root->parent->x << "," << root->parent->y << ")" << std::endl;
        #endif // PRINT_DEBUG_INFO

        root = root->parent;
    }
    return path;
}


