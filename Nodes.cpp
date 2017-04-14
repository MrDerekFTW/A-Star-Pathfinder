#include "Nodes.h"

float distBtwnPnts(point one, point two)
{
    return sqrt(pow(one.x - two.x, 2) + pow(one.y - two.y, 2));
}

bool testAdjacency(point a, point b)
{
    int diffX = abs(a.x - b.x);
    int diffY = abs(a.y - b.y);
    if (diffX == 0) { diffX++; }
    if (diffY == 0) { diffY++; }
    if (diffX == 1 && diffY == 1)
    {
        return true;
    }
    return false;
}

void clearPointStack(std::stack<point> *pointStack)
{
    while (!pointStack->empty())
    {
        pointStack->pop();
    }
}

void printPointStack(std::stack<point> *pointStack)
{
    int step = 0;
    while (!pointStack->empty())
    {
        step++;
        std::cout << "Step " << step << ": ("  << pointStack->top().x << "," << pointStack->top().y << ")" << std::endl;
        pointStack->pop();
    }
}

point getMinPair(point one, point two)
{
    point minPair;
    minPair.x = one.x;
    if (one.x > two.x)
    {
        minPair.x = two.x;
    }
    minPair.y = one.y;
    if (one.y > two.y)
    {
        minPair.y = two.y;
    }
    return minPair;
}

point getMaxPair(point one, point two)
{
    point maxPair;
    maxPair.x = one.x;
    if (one.x < two.x)
    {
        maxPair.x = two.x;
    }
    maxPair.y = one.y;
    if (one.y < two.y)
    {
        maxPair.y = two.y;
    }
    return maxPair;
}


