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
        std::cout << "\tCreating a node...\n";
    }
    Node(int _val)
    {
        this->val = _val;
        this->left = nullptr;
        this->right = nullptr;
        std::cout << "\tCreating a node...\n";
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
                std::cout << "checking left...\n";
                result = findNode(_val, currNode->left);
            }
            if (result == nullptr && currNode->right != nullptr)
            {
                std::cout << "checking right...\n";
                result = findNode(_val, currNode->right);
            }
            if (result == nullptr)
                std::cout << "Couldn't find such node!\n";
        }
        else return nullptr;

        return result;
    }

    void insertNode(int _val, std::shared_ptr<Node> currNode = nullptr, int currHeight = 1)
    {
        if (currNode == nullptr)
            currNode = root;

        this->numNodes = 5;

        int maxHeight = ceil(log2(numNodes)) + 1;
        if (maxHeight == 1) maxHeight++;
        std::cout << maxHeight << "\n";
    }
    
};


int main()
{
    std::shared_ptr<Node> root(new Node(5));
    root->setVal(10);
    std::cout << root->getVal() << "\n";
    root->left = std::shared_ptr<Node>(new Node(2));
    std::cout << root->left->getVal() << "\n";
    root->right = std::shared_ptr<Node>(new Node(3));
    std::cout << root->right->getVal() << "\n";

    
    Tree T;
    //std::cout << T.root->getVal() << "\n";
    T.root->left = std::shared_ptr<Node>(new Node(2));
    //std::cout << T.root->left->getVal() << "\n";
    T.root->right = std::shared_ptr<Node>(new Node(6));
    //std::cout << T.root->right->getVal() << "\n";

    T.root->right->right = std::shared_ptr<Node>(new Node(7));
    //std::cout << T.root->right->right->getVal() << "\n";

    std::shared_ptr<Node> someNode = nullptr;

    int k;
    std::cout << "look for what number? ";
    std::cin >> k;
    someNode = T.findNode(k);
    /*
    if (someNode != nullptr)
        std::cout << someNode->getVal() << "\n";
    */
    std::cout << "\n\n";

    T.insertNode(8);
    
}
