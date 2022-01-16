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
private:
    std::string spacing(const size_t n) const;

    void printTree_helper(std::shared_ptr<Node<T>> currNode, size_t level = 0) const;

    std::shared_ptr<Node<T>> pop_helper(const T _val, std::shared_ptr<Node<T>> root = nullptr);

    void valArr(std::shared_ptr<bool[]> isInitialized, std::shared_ptr<T[]> values, std::shared_ptr<size_t[]> number, std::shared_ptr<Node<T>> currNode = nullptr, size_t index = 1) const;

    void nodeArr(std::shared_ptr<Node<T>[]> values, std::shared_ptr<Node<T>> currNode = nullptr, size_t index = 1) const;

public:
    std::shared_ptr<Node<T>> root = nullptr;        // the root of the tree

    Tree(const T _val);

    Tree(const Tree& tree);

    Tree();

    ~Tree() = default;

    std::shared_ptr<Node<T>> find(const T _val) const;

    void insert(const T _val);

    void printTree() const;

    Tree& operator=(const Tree& _tree);

    Node<T> operator[](const int index) const;

    std::shared_ptr<Node<T>> max(std::shared_ptr<Node<T>> root = nullptr) const;

    std::shared_ptr<Node<T>> min(std::shared_ptr<Node<T>> root = nullptr) const;

    void pop(const T _val);

    size_t height(std::shared_ptr<Node<T>> currNode = nullptr, size_t result = 0) const;

    void toFile(std::string fileName = "") const;

    void fromFile(std::string fileName = "");

    void sort();

    void rsort();
};
