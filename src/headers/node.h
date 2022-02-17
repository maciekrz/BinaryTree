#pragma once
#include <cstdio>
#include <memory>

template <typename T>
class Node {
    typedef std::shared_ptr<Node> nodeptr;
private:
    size_t size;        // number of values in one node
    T val;              // node's value

public:
    nodeptr left;     // left child
    nodeptr right;    // right child

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

    Node operator=(const nodeptr& node);
};
