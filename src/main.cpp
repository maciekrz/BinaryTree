#include <iostream>
#include <memory>
#include <string>
//#include <typeinfo>

template<typename T>
class Node
{
private:
    size_t size;
    //T *val;
    std::shared_ptr<T[]> val;
public:
    std::shared_ptr<Node> left;
    std::shared_ptr<Node> right;

    Node()
    {
        size = 1;
        //this->val = new T [size];
        this->val = std::make_shared<T[]>();
        this->left = nullptr;
        this->right = nullptr;
    }
    Node(T _val)
    {
        size = 1;
        //this->val = new T [size];
        //this->val[0] = _val;
        this->val = std::make_shared<T[]>(_val);
        this->left = nullptr;
        this->right = nullptr;
    }
    ~Node() = default;
    
    size_t getSize()
    {
        return this->size;
    }
    void incSize()
    {
        this->size++;
        return;
    }
    T getVal()
    {
        return val[0];
    }
    void setVal(T _val, size_t pos = 0)
    {
        this->val = std::shared_ptr<T[]>(new T[pos+1]);
        for (size_t i = 0; i < pos; i++)
            this->val[i] = _val;
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
    std::shared_ptr <Node<T>> pop_helper(T _val, std::shared_ptr<Node<T>> root = nullptr)
    {
        if (root == nullptr)
            root = this->root;

        std::shared_ptr<Node<T>> currNode = root;

    if (root == nullptr)
        return root;
    if (root->getVal() > _val) 
    {
        root->left = this->pop_helper(_val, root->left);
        return root;
    }
    if (root->getVal() < _val) 
    {
        root->right = this->pop_helper(_val, root->right);
        return root;
    }

        std::shared_ptr<Node<T>> popped = nullptr;
        if (currNode != nullptr)
        {
            if (currNode->left == nullptr && currNode->right == nullptr)
            {
                popped = currNode;
                currNode = nullptr;
                return nullptr;
            }
            else if (currNode->left == nullptr)
            {
                popped = currNode;
                currNode = currNode->right;
                return currNode;
            }
            else if (currNode->right == nullptr)
            {
                popped = currNode;
                currNode = currNode->left;
                return currNode;
            }
            else
            {
                currNode = this->min(root->right);
                root->setVal(currNode->getVal());
                root->right = pop_helper(currNode->getVal(), root->right);
                return root;
            }
        }
        return root;
    }

public:
    std::shared_ptr<Node<T>> root = nullptr;

    Tree(T _val)     
    {
        numNodes = 1;
        root = std::make_shared<Node<T>>(_val);
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
            if (currNode == nullptr)
                return nullptr;
            if (_val < currNode->getVal())
            {
                currNode = currNode->left;
            }
            else if (_val > currNode->getVal())
            {
                currNode = currNode->right;
            }
        }
        if (currNode == nullptr)
        {
            return nullptr;
        }
        else if (currNode->getVal() == _val)
        {
            return currNode;
        }
        else
        {
            return nullptr;
        }
    }

    void insert(T _val)
    {
        if (root == nullptr)
        {
            root = std::make_shared<Node<T>>(_val);
            return;
        }

        std::shared_ptr<Node<T>> temp = nullptr;
        auto currNode = root;
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
            temp->left = std::make_shared<Node<T>>(_val);
        }
        else if (_val > currVal)
        {
            temp->right = std::make_shared<Node<T>>(_val);
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

    std::shared_ptr<Node<T>> max(std::shared_ptr<Node<T>> root = nullptr)
    {
        if (root == nullptr)
            root = this->root;

        auto currNode = root;
        while ( currNode->right != nullptr)
        {
            currNode = currNode->right;
        }
        return currNode;
    }
    std::shared_ptr<Node<T>> min(std::shared_ptr<Node<T>> root = nullptr)
    {
        if (root == nullptr)
            root = this->root;

        auto currNode = root;
        while ( currNode->left != nullptr)
        {
            currNode = currNode->left;
        }
        return currNode;
    }
    
    void pop(T _val)
    {
        if (this->find(_val) != nullptr)
            this->root = this->pop_helper(_val);
        else
            return;
    }
    
};

int main()
{
    
    Tree<int> tree;

    tree.insert(30);
    tree.insert(30);
    tree.insert(30);
    tree.insert(15);
    tree.insert(15);
    tree.insert(45);
    tree.insert(45);
    tree.insert(45);
    tree.insert(45);
    tree.insert(30);

    tree.printTree();

    //tree.printTree();

    /*
     *  TO DO:
     *  * SORTING
     *  * INPUT/OUTPUT WITH FILES
     *  * MAYBE SOMETHING MORE
     */

}
