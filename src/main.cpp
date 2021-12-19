#include <iostream>
#include <memory>
#include <cmath>

class Node
{
private:
    int val;
public:
    std::shared_ptr<Node> left;
    std::shared_ptr<Node> right;

    Node()
    {
        this->val = 0;
        this->left = nullptr;
        this->right = nullptr;
        //std::cout << "\tCreating a node...\n";
    }
    Node(int _val)
    {
        this->val = _val;
        this->left = nullptr;
        this->right = nullptr;
        //std::cout << "\tCreating a node...\n";
    }
    
    int getVal()
    {
        return this->val;
    }
    void setVal(int _val)
    {
        this->val = _val;
    }
};

class Tree
{
private:
    int height;
    int numNodes;
public:
    std::shared_ptr<Node> root = std::shared_ptr<Node>(new Node(0));

    Tree() : height(1), numNodes(1)
    {
        //root = std::shared_ptr<Node>(new Node(0));
        int _val;
        std::cout << "What value should the root have?\n ~> ";
        std::cin >> _val;
        root->setVal(_val);
    }
    std::shared_ptr<Node> findNode(int _val, std::shared_ptr<Node> currNode = nullptr)
    {
        if (currNode == nullptr)
            currNode = root;
        std::shared_ptr<Node> result = nullptr;

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

    bool insertNode(int _val, std::shared_ptr<Node> currNode = nullptr, int currHeight = 2)
    {
        auto check = [](int x) { return (x+1 != 0 && (x+1 & (x)) == 0); }; // bit manipulation way to check if the number is a (power of 2)-1

        if (currNode == nullptr)
            currNode = root;

        int maxHeight = floor(log2(this->numNodes)) + 1; // this maximum (allowed) height is actually a minimum height of a binary tree with such number of nodes

        maxHeight = check(numNodes) ? maxHeight+1 : maxHeight; // if the number was 3, 7, 15, ... it was breaking the algorithm

        if (maxHeight == 1)
        {
            currNode->left = std::shared_ptr<Node>(new Node(_val));
            this->numNodes++;
            return true;
        }
        if (currHeight > maxHeight) 
        {
            return false;
        }
        
        if (currNode->left == nullptr && currHeight <= maxHeight)
        {
            currNode->left = std::shared_ptr<Node>(new Node(_val));
            this->numNodes++;
            return true;
        }
        else if (currNode->right == nullptr && currHeight <= maxHeight)
        {
            currNode->right = std::shared_ptr<Node>(new Node(_val));
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
        std::shared_ptr<Node> temp = nullptr;
        temp = findNode(_val);
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
    void printTree_helper(std::shared_ptr<Node> node, int level = 0)
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
    
}
