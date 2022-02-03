#include "headers/node.h"

/*
 * CONSTRUCTORS AND A DESTRUCTOR
 */
template <typename T>
Node<T>::Node()
{
    size = 0;
    //this->val;            // value doesn't really need to be initialized - nodes are always constructed with parameters or given values at creation
    this->left = nullptr;
    this->right = nullptr;
}

template <typename T>
Node<T>::Node(const T _val)
{
    size = 1;
    this->val = _val;
    this->left = nullptr;
    this->right = nullptr;
}

template <typename T>
Node<T>::Node(const Node& node)
{
    std::swap(node);
}

template <typename T>
Node<T>::~Node() = default;

/*
 * GETTERS AND SETTERS
 */
template <typename T>
size_t Node<T>::getSize() const
{
    return this->size;
}

template <typename T>
void Node<T>::setSize(const size_t newSize)
{
    this->size = newSize;
}

template <typename T>
T Node<T>::getVal() const
{
    return val;
}

template <typename T>
void Node<T>::setVal(const T _val)
{
    this->val = _val;
    return;
}

/*
 * A method for incrementing the size of a node when a duplicate occurs
 */
template <typename T>
void Node<T>::incSize()
{
    this->size++;
    return;
}

template <typename T>
void Node<T>::decSize()
{
    this->size--;
    return;
}

/*
 * OVERLOADED OPERATORS
 */
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
