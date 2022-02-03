#pragma once
#include <cstdio>
#include <memory>

template <typename T>
class Node {
private:
    size_t size;        // number of values in one node
    T val;              // node's value

public:
    std::shared_ptr<Node> left;     // left child
    std::shared_ptr<Node> right;    // right child

    Node();
    Node(const T _val);
    Node(const Node& node);
    ~Node();

    size_t getSize() const;

    void incSize();

    void decSize();

    void setSize(const size_t newSize);

    T getVal() const;

    void setVal(const T _val);

    bool operator>(const Node& node) const;

    bool operator<(const Node& node) const;

    bool operator==(const Node& node) const;

    Node operator+(const Node& node);

    Node operator=(const Node& node);

    Node operator=(const std::shared_ptr<Node>& node);
};
