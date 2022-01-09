#include <iostream>
#include <memory>
#include <cmath>
#include <string>
#include <typeinfo>

template<typename T>
class Node
{
private:
    size_t size;
    T *val;
public:
    std::shared_ptr<Node> left;
    std::shared_ptr<Node> right;

    Node()
    {
        size = 1;
        this->val = new T [size];
        this->left = nullptr;
        this->right = nullptr;
    }
    Node(T _val)
    {
        size = 1;
        this->val = new T [size];
        this->val[0] = _val;
        this->left = nullptr;
        this->right = nullptr;
    }
    ~Node()
    {
        if (val != NULL && val != nullptr)
        {
            std::cout << "deleting " << *val << " -- " << val << "\n";
            delete val;
        }
    }
    
    size_t getSize()
    {
        return size;
    }
    void incSize()
    {
        this->size++;
        return;
    }
    T getVal()
    {
        return *val;
    }
    void setVal(T _val, size_t pos = 0)
    {
        this->val[pos] = _val;
        return;
    }

    bool operator > (const Node& node) {
        return this->val > node->val;
    }
    bool operator < (const Node& node) {
        return this->val < node->val;
    }
    bool operator == (const Node& node) {
        return this->val == node->val;
    }
    Node operator + (const Node& node) {
        Node temp;
        temp->val = this->val + node->val;
        return temp;
    }
};

template<typename T>
class Tree
{
private:
    int height;
    int numNodes;

    std::string spacing(int n)
    {
        std::string spc = "";
        for (int i = 0; i < n; i++)
            spc += "  ";
        return spc;
    }
    void printTree_helper(std::shared_ptr<Node<T>> node, int level = 0)
    {
        if (node == nullptr)
        {
            std::cout << "-*-\n";
            return;
        }
        if (level == 0) std::cout << "root: ";
        std::cout << node->getVal() << " (" << node->getSize() << ")" << "\n";
        std::cout << spacing(level) << "  left: ";
        printTree_helper(node->left, level+1);
        std::cout << spacing(level) << "  right: ";
        printTree_helper(node->right, level+1);
    }

public:
    std::shared_ptr<Node<T>> root = nullptr;

    Tree(T _val)     
    {
        numNodes = 1;
        root = std::shared_ptr<Node<T>>(new Node<T>(_val));
    }
    Tree() 
    {
        numNodes = 0;
        root = nullptr;
    }

    std::shared_ptr<Node<T>> find(T _val)
    {
        std::shared_ptr<Node<T>> currNode = root;
        while ( currNode != nullptr && _val != currNode->getVal() )
        {
            if (_val < currNode->getVal())
            {
                currNode = currNode->left;
            }
            else
            {
                currNode = currNode->right;
            }
        }
        if (currNode->getVal() == _val)
            return currNode;
        else
            return nullptr;
    }

    void insert(T _val)
    {
        if (root == nullptr)
        {
            root = std::shared_ptr<Node<T>>(new Node<T>(_val));
            return;
        }

        std::shared_ptr<Node<T>> temp = nullptr;
        std::shared_ptr<Node<T>> currNode = root;
        T currVal;
        while ( currNode != nullptr )
        {
            currVal = currNode->getVal();
            temp = currNode;
            if (_val < currVal)
            {
                currNode = currNode->left;
            }
            else if (_val > currVal)
            {
                currNode = currNode->right;
            }
            else
            {
                currNode = currNode;
                break;
            }
        }
        currVal = temp->getVal();
        if (_val < currVal)
        {
            temp->left = std::shared_ptr<Node<T>>(new Node<T>(_val));
        }
        else if (_val > currVal)
        {
            temp->right = std::shared_ptr<Node<T>>(new Node<T>(_val));
        }
        else
        {
            temp->incSize();
            temp->setVal(_val, (temp->getSize())-1);
        }
        numNodes++;
        return;
    }

    void printTree()
    {
        std::cout << "\n";
        printTree_helper(this->root);
    }

    Tree& operator=(Tree _tree)
    {
        this->root = _tree.root;
        return *this;
    }

    std::shared_ptr<Node<T>> max()
    {
        std::shared_ptr<Node<T>> currNode = root;
        while ( currNode->right != nullptr)
        {
            currNode = currNode->right;
        }
        return currNode;
    }
    std::shared_ptr<Node<T>> min()
    {
        std::shared_ptr<Node<T>> currNode = root;
        while ( currNode->left != nullptr)
        {
            currNode = currNode->left;
        }
        return currNode;
    }
    
    void sort()
    {
        Tree<T> newTree;
    }
    
};

int main()
{
    
    Tree<int> tree;

    tree.insert(10);
    tree.insert(5);
    tree.insert(40);
    tree.insert(6);
    tree.insert(6);
    tree.insert(10);
    tree.insert(10);
    tree.insert(70);
    tree.insert(15);
    tree.insert(15);
    tree.insert(20);
    tree.insert(1);
    tree.insert(20);
    tree.insert(10);

    tree.printTree();

    std::shared_ptr<Node<int>> temp = tree.max();
    std::cout << temp->getVal() << "\n";
    temp = tree.min();
    std::cout << temp->getVal() << "\n";

}
