#pragma once
#include "node.h"
#include "../node.cpp"
#include <fstream>
#include <iostream>
#include <math.h>
#include <sstream>
#include <string>

template <typename T>
class Tree {
    using nodeptr = std::shared_ptr<Node<T>>;
private:
    std::string spacing(const size_t n) const;

    void printTree_helper(nodeptr currNode, size_t level = 0) const;

    nodeptr pop_helper(const T _val, nodeptr root = nullptr);

    //void valArr(std::shared_ptr<T[]> values, std::shared_ptr<size_t[]> number, nodeptr currNode = nullptr, size_t index = 1) const;

    std::string printLevelToFile(nodeptr currNode, size_t level) const;

public:

    nodeptr root = nullptr;        // the root of the tree

    Tree(const T _val);

    Tree(const Tree& tree);

    Tree();

    ~Tree() = default;

    nodeptr find(const T _val) const;

    void insert(const T _val);

    void printTree() const;

    Tree& operator=(const Tree& _tree);

    nodeptr max(nodeptr root = nullptr) const;

    nodeptr min(nodeptr root = nullptr) const;

    void pop(const T _val);

    size_t height(nodeptr currNode = nullptr, size_t result = 0) const;

    void toFile() const;

    //void toFileOld(std::string fileName = "") const;

    void fromFile(std::string fileName = "");

    void sort();

    void rsort();
};
