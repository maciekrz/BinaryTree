#include "headers/node.hpp"

template <typename T>
Node<T>::Node()
{
    size = 1;
    this->val = new T[size];
    this->left = nullptr;
    this->right = nullptr;
}
template <typename T>
Node<T>::Node(const T _val)
{
    size = 1;
    this->val = new T[size];
    this->val[0] = _val;
    this->left = nullptr;
    this->right = nullptr;
}
template <typename T>
Node<T>::~Node()
{
    if (val != NULL && val != nullptr) {
        delete val;
    }
}

template <typename T>
size_t Node<T>::getSize() const
{
    return this->size;
}
template <typename T>
void Node<T>::incSize()
{
    this->size++;
    this->val = new T[size];
    return;
}
template <typename T>
void Node<T>::setSize(const size_t newSize)
{
    this->size = newSize;
}
template <typename T>
T Node<T>::getVal() const
{
    return val[0];
}
template <typename T>
void Node<T>::setVal(const T _val, size_t pos)
{
    this->val = new T[pos + 1];
    for (size_t i = 0; i <= pos; i++) {
        this->val[i] = _val;
    }
    return;
}

template <typename T>
bool Node<T>::operator>(const Node& node) const
{
    return this->val > node->val;
}
template <typename T>
bool Node<T>::operator<(const Node& node) const
{
    return this->val < node->val;
}
template <typename T>
bool Node<T>::operator==(const Node& node) const
{
    return this->val == node->val;
}
template <typename T>
Node<T> Node<T>::operator+(const Node& node)
{
    Node temp;
    temp->val = this->val + node->val;
    return temp;
}
template <typename T>
Node<T> Node<T>::operator=(const Node& node)
{
    return std::swap(node);
}
template <typename T>
Node<T> Node<T>::operator=(const std::shared_ptr<Node>& node)
{
    this->val = node->val;
    this->left = node->left;
    this->right = node->right;

    return *this;
}
