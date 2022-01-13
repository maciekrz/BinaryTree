#include "headers/node.hpp"
#include "headers/tree.hpp"

int main()
{

    Tree<int> tree;

    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(20);
    tree.insert(7);
    tree.insert(7);
    tree.insert(7);
    tree.insert(2);
    tree.insert(2);

    tree.printTree();

    /*
     *  TO DO:
     *  * SPLIT THE FILE INTO HEADERS
     */
}
