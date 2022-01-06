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
    std::unique_ptr<T> val;
public:
    std::shared_ptr<Node> left;
    std::shared_ptr<Node> right;

    Node()
    {
        size = 1;
        this->val = new std::unique_ptr<T> [size];
        this->left = nullptr;
        this->right = nullptr;
        //std::cout << "\tCreating a node...\n";
    }
    Node(T _val)
    {
        size = 1;
        this->val = new std::unique_ptr<T> [size];
        this->val[0] = _val;
        this->left = nullptr;
        this->right = nullptr;
        //std::cout << "\tCreating a node...\n";
    }
    
    T getVal()
    {
        return this->val;
    }
    void setVal(int _val)
    {
        this->val = _val;
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
public:
    std::shared_ptr<Node<T>> root = std::shared_ptr<Node<T>>(new Node<T>(0));

    Tree() : height(1), numNodes(1)
    {
        //root = std::shared_ptr<Node>(new Node(0));
        T _val;
        std::cout << "What value should the root have?\n ~> ";
        std::cin >> _val;
        root->setVal(_val);
    }
    std::shared_ptr<Node<T>> find(T _val, std::shared_ptr<Node<T>> currNode = nullptr)
    {
        if (currNode == nullptr)
            currNode = root;
        std::shared_ptr<Node<T>> result = nullptr;

        if (currNode->getVal() == _val)
        {
            std::cout << "... found " << currNode->getVal() << " ...\n";
            return currNode;
        }
        else if (currNode->left != nullptr || currNode->right != nullptr)
        {
            if (currNode->left != nullptr)
            {
                result = findNode(_val, currNode->left);
            }
            if (result == nullptr && currNode->right != nullptr)
            {
                result = findNode(_val, currNode->right);
            }
            return result;
        }
        else return nullptr;
    }

    bool insertNode(int _val, std::shared_ptr<Node<T>> currNode = nullptr, int currHeight = 2)
    {
        auto check = [](int x) { return (x+1 != 0 && (x+1 & (x)) == 0); }; // bit manipulation way to check if the number is a (power of 2)-1

        if (currNode == nullptr)
            currNode = root;

        int maxHeight = floor(log2(this->numNodes)) + 1; // this maximum (allowed) height is actually a minimum height of a binary tree with such number of nodes

        maxHeight = check(numNodes) ? maxHeight+1 : maxHeight; // if the number was 3, 7, 15, ... it was breaking the algorithm

        if (maxHeight == 1)
        {
            currNode->left = std::shared_ptr<Node<T>>(new Node<T>(_val));
            this->numNodes++;
            return true;
        }
        if (currHeight > maxHeight) 
        {
            return false;
        }
        
        if (currNode->left == nullptr && currHeight <= maxHeight)
        {
            currNode->left = std::shared_ptr<Node<T>>(new Node<T>(_val));
            this->numNodes++;
            return true;
        }
        else if (currNode->right == nullptr && currHeight <= maxHeight)
        {
            currNode->right = std::shared_ptr<Node<T>>(new Node<T>(_val));
            this->numNodes++;
            return true;
        }
        else if (insertNode(_val, currNode->left, currHeight+1))
        {
            return true;
        }
        else if (insertNode(_val, currNode->right, currHeight+1))
        {
            return true;
        }
        
        return false;
    }
    void insert(int _val)
    {
        std::shared_ptr<Node<T>> temp = nullptr;
        temp = find(_val);
        if (temp != nullptr)
        {
            char c;
            std::cout << "A node with such value has been found in the tree. Do you want to continue?\n(two separate nodes with that value will be present in the tree) [y/N]";
            std::cin >> c;
            if (c == 'y' || c == 'Y') { insertNode(_val); }
            else return;
        }
        else insertNode(_val);
    }

    std::string spacing(int n)
    {
        std::string res = "";
        for (int i = 0; i < n; i++)
            res += "  ";
        return res;
    }
    void printTree_helper(std::shared_ptr<Node<T>> node, int level = 0)
    {
        if (node == nullptr)
        {
            std::cout << "--\n";
            return;
        }
        if (level == 0) std::cout << "root: ";
        std::cout << node->getVal() << "\n";
        std::cout << spacing(level) << "  left: ";
        printTree_helper(node->left, level+1);
        std::cout << spacing(level) << "  right: ";
        printTree_helper(node->right, level+1);
    }
    void printTree()
    {
        printTree_helper(this->root);
    }
    
};


int main()
{
    /*
    Tree T;

    std::shared_ptr<Node> someNode = nullptr;

    int n, m;
    for (int i = 0; i < 5; i++)
    {
        T.printTree();
        std::cout << " ~> ";
        std::cin >> n;
        T.insertNode(n);
    }
    std::cout << "look for what number? ";
    std::cin >> m;
    someNode = T.findNode(m);

    someNode->setVal(20);
    T.printTree();
    */

    int var1;
    std::string var2 = "abc";
    double var3;
    float var4;
    char var5;
    std::cout << typeid(var1).name() << "\n";
    std::cout << typeid(var2).name() << "\n";
    std::cout << typeid(var3).name() << "\n";
    std::cout << typeid(var4).name() << "\n";
    std::cout << typeid(var5).name() << "\n";

    std::cout << (var2 > "zzz") << "\n";
}
