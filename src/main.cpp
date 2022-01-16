#include "tree.cpp"

int main()
{
    std::cout << "\n";
    std::string pause;

    Tree<int> tree;

    std::cout << "\tINITIAL TREE:";
    tree.insert(10);
    tree.insert(5);
    tree.insert(5);
    tree.insert(5);
    tree.insert(15);
    tree.insert(2);
    tree.insert(1);
    tree.insert(7);
    tree.printTree();

    std::getline(std::cin, pause);
    
    std::cout << "\tDECREASING SORT:";
    tree.rsort();
    tree.printTree();

    std::getline(std::cin, pause);

    std::cout << "\tNEW ELEMENTS:";
    tree.insert(25);
    tree.insert(20);
    tree.insert(20);
    tree.insert(30);
    tree.insert(15);

    tree.printTree();

    std::getline(std::cin, pause);

    std::cout << "\tTREE WITH ELEMENTS FROM FILE:";
    tree.fromFile();
    tree.printTree();

    std::getline(std::cin, pause);

    std::cout << "\tPOPPING 15, 11, 6, 80, 5:";
    tree.pop(15);
    tree.pop(11);
    tree.pop(6);
    tree.pop(80);
    tree.pop(5);
    tree.printTree();

    std::getline(std::cin, pause);

    std::cout << "\tINCREASING SORT:";
    tree.sort();
    tree.printTree();
    tree.toFile();

    std::getline(std::cin, pause);

    std::cout << "\tA TREE USING STRINGS:";
    Tree<std::string> tree2;
    tree2.insert("first");
    tree2.insert("first");
    tree2.insert("first");
    tree2.insert("second");
    tree2.insert("third");
    tree2.insert("third");
    tree2.insert("fourth");
    tree2.insert("fifth");
    tree2.insert("fifth");
    tree2.insert("sixth");
    tree2.insert("sixth");
    tree2.insert("sixth");
    tree2.insert("sixth");
    tree2.insert("seventh");
    tree2.printTree();

    std::getline(std::cin, pause);

    std::cout << "\tREMOVING 'first':";
    tree2.pop("first");
    tree2.printTree();

    std::getline(std::cin, pause);

    std::cout << "\tSORTED:";
    tree2.sort();
    tree2.printTree();

    std::getline(std::cin, pause);

    std::cout << "\ttree3 CONSTRUCTED WITH tree2 AS CONSTRUCTOR PARAM:";
    Tree<std::string> tree3(tree2);
    tree3.printTree();


    std::getline(std::cin, pause);
    std::cout << "\n";
    return 0;
}
