
#include "Pathfinder.h"
#include "Nodes.h"

#include <vector>
#include <stack>
#include <iostream>

int main()
{
    Pathfinder myPathfinder;
    std::vector< std::vector<int> > myMap(10, std::vector<int>(10));

    point myOrigin = {0, 0};
    point myDestination = {9, 0};
    std::stack<node> mySolution;

    //***********TEST 1***********//

    for (int x = 0; x < 10; x++)
    {
        for (int y = 0; y < 10; y++)
        {
            myMap[x][y] = OPEN;
        }
    }

    std::cout << std::endl << "Test #1" << std::endl; // all spaces open
    std::cout << "All spaces open..." << std::endl;

    mySolution = myPathfinder.findPath(&myOrigin, &myDestination, &myMap);

    if (mySolution.empty() == true)
    {
        std::cout << "Path not found!" << std::endl;
    }
    else
    {
        std::cout << "Path found!" << std::endl;
        printNodeStack(&mySolution);
    }

    //***********TEST 2***********//

    myMap[5][0] = CLOSED;
    myMap[5][1] = CLOSED;
    myMap[5][2] = CLOSED;
    myMap[5][3] = CLOSED;
    myMap[5][4] = CLOSED;
    myMap[5][5] = OPEN;
    myMap[5][6] = CLOSED;
    myMap[5][7] = CLOSED;
    myMap[5][8] = CLOSED;
    myMap[5][9] = CLOSED;

    std::cout << std::endl << "Test #2" << std::endl; // partial wall in center
    std::cout << "Partial wall in center..." << std::endl;

    mySolution = myPathfinder.findPath(&myOrigin, &myDestination, &myMap);

    if (mySolution.empty() == true)
    {
        std::cout << "Path not found!" << std::endl;
    }
    else
    {
        std::cout << "Path found!" << std::endl;
        printNodeStack(&mySolution);
    }

    //***********TEST 3***********//

    myMap[5][5] = CLOSED;

    std::cout << std::endl << "Test #3" << std::endl; // full wall in center
    std::cout << "Full wall in center..." << std::endl;

    mySolution = myPathfinder.findPath(&myOrigin, &myDestination, &myMap);

    if (mySolution.empty() == true)
    {
        std::cout << "Path not found!" << std::endl;
    }
    else
    {
        std::cout << "Path found!" << std::endl;
        printNodeStack(&mySolution);
    }

    //***********TEST 4***********//

    myMap[5][5] = OPEN;
    myMap[9][0] = CLOSED;

    std::cout << std::endl << "Test #4" << std::endl; // partial wall in center and final point closed
    std::cout << "Partial wall in center and final point closed..." << std::endl;

     mySolution = myPathfinder.findPath(&myOrigin, &myDestination, &myMap);

    if (mySolution.empty() == true)
    {
        std::cout << "Path not found!" << std::endl;
    }
    else
    {
        std::cout << "Path found!" << std::endl;
        printNodeStack(&mySolution);
    }

    //***********TEST 5***********//

    for (int x = 0; x < 10; x++)
    {
        for (int y = 0; y < 10; y++)
        {
            myMap[x][y] = OPEN;
        }
    }

    myDestination = {9,9};

    std::cout << std::endl << "Test #5" << std::endl; // Diagonal preference
    std::cout << "Diagonal preference..." << std::endl;

     mySolution = myPathfinder.findPath(&myOrigin, &myDestination, &myMap);

    if (mySolution.empty() == true)
    {
        std::cout << "Path not found!" << std::endl;
    }
    else
    {
        std::cout << "Path found!" << std::endl;
        printNodeStack(&mySolution);
    }

    return 0;
}
