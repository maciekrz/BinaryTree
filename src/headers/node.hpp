#pragma once
#include <memory>

template <typename T>
class Node {
private:
    size_t size;
    T* val;

public:
    std::shared_ptr<Node> left;
    std::shared_ptr<Node> right;

    Node();
    Node(const T _val);
    ~Node();

    size_t getSize() const;

    void incSize();

    void setSize(const size_t newSize);

    T getVal() const;

    void setVal(const T _val, size_t pos = 0);

    bool operator>(const Node& node) const;

    bool operator<(const Node& node) const;

    bool operator==(const Node& node) const;

    Node operator+(const Node& node);

    Node operator=(const Node& node);

    Node operator=(const std::shared_ptr<Node>& node);
};
