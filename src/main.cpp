#include <iostream>
#include <memory>
#include <string>
#include <math.h>
#include <fstream>
#include <sstream>

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
    Node(const T _val)
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
            delete val;
        }
    }
    
    size_t getSize() const
    {
        return this->size;
    }
    void incSize()
    {
        this->size++;
        this->val = new T [size];
        return;
    }
    void setSize(const size_t newSize)
    {
        this->size = newSize;
    }
    T getVal() const
    {
        return val[0];
    }
    void setVal(const T _val, size_t pos = 0)
    {
        this->val = new T [pos+1];
        for (size_t i = 0; i <= pos; i++)
        {
            this->val[i] = _val;
        }
        return;
    }

    bool operator > (const Node& node) const
    {
        return this->val > node->val;
    }
    bool operator < (const Node& node) const
    {
        return this->val < node->val;
    }
    bool operator == (const Node& node) const
    {
        return this->val == node->val;
    }
    Node operator + (const Node& node) 
    {
        Node temp;
        temp->val = this->val + node->val;
        return temp;
    }
    Node operator = (const Node& node)
    {
        return std::swap(node);
    }
    Node operator = (const std::shared_ptr<Node>& node)
    {
        this->val = node->val;
        this->left = node->left;
        this->right = node->right;

        return *this;
    }
};

template<typename T>
class Tree
{
private:
    std::string spacing(const size_t n) const
    {
        std::string spc = "";
        for (size_t i = 0; i < n; i++)
            spc += "  ";
        return spc;
    }

    void printTree_helper(std::shared_ptr<Node<T>> currNode, size_t level = 0) const
    {
        if (currNode == nullptr)
        {
            std::cout << "-*-\n";
            return;
        }
        if (level == 0) std::cout << "root: ";
        std::cout << currNode->getVal() << " (" << currNode->getSize() << ")" << "\n";

        std::cout << spacing(level) << "  left: ";
        printTree_helper(currNode->left, level+1);

        std::cout << spacing(level) << "  right: ";
        printTree_helper(currNode->right, level+1);
    }

    std::shared_ptr<Node<T>> pop_helper(const T _val, std::shared_ptr<Node<T>> root = nullptr) 
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
        else if (root->getVal() < _val) 
        {
            root->right = this->pop_helper(_val, root->right);
            return root;
        }

        if (currNode != nullptr)
        {
            if (currNode->left == nullptr && currNode->right == nullptr)
            {
                currNode = nullptr;
                return nullptr;
            }
            else if (currNode->left == nullptr)
            {
                currNode->setSize(currNode->right->getSize());
                currNode = currNode->right;
                return currNode;
            }
            else if (currNode->right == nullptr)
            {
                currNode->setSize(currNode->left->getSize());
                currNode = currNode->left;
                return currNode;
            }
            else
            {
                currNode->setSize(this->min(root->right)->getSize());
                currNode = this->min(root->right);

                root->setVal(currNode->getVal());
                root->right = this->pop_helper(currNode->getVal(), root->right);

                return root;
            }
        }
        return nullptr;
    }
    
    void valArr(std::shared_ptr<bool[]> isInitialized, std::shared_ptr<T[]> values, std::shared_ptr<size_t[]> number, std::shared_ptr<Node<T>> currNode = nullptr, size_t index = 1) const
    {
        if (currNode == nullptr)
            currNode = this->root;

        if (currNode != nullptr)
        {
            isInitialized[index-1] = true;
            values[index-1] = currNode->getVal();
            number[index-1] = currNode->getSize();
        }
        else
        {
            isInitialized[index-1] = false;
            return;
        }

        if (currNode->left != nullptr)
            valArr(isInitialized, values, number, currNode->left, index*2);
        
        if (currNode->right != nullptr)
            valArr(isInitialized, values, number, currNode->right, index*2+1);
    }
    void nodeArr(std::shared_ptr<Node<T>[]> values, std::shared_ptr<Node<T>> currNode = nullptr, size_t index = 1) const
    {
        if (currNode == nullptr)
            currNode = this->root;

        if (currNode != nullptr)
        {
            values[index-1] = currNode;
        }
        else
        {
            values[index-1] = nullptr;
            return;
        }

        if (currNode->left != nullptr)
            nodeArr(values, currNode->left, index*2);
        
        if (currNode->right != nullptr)
            nodeArr(values, currNode->right, index*2+1);
    }


public:
    std::shared_ptr<Node<T>> root = nullptr;

    Tree(const T _val)     
    {
        this->root = std::shared_ptr<Node<T>>(new Node<T>(_val));
    }
    Tree() 
    {
        this->root = nullptr;
    }
    ~Tree() = default;

    std::shared_ptr<Node<T>> find(const T _val) const
    {
        std::shared_ptr<Node<T>> currNode = this->root;
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

    void insert(const T _val)
    {
        if (this->root == nullptr)
        {
            root = std::shared_ptr<Node<T>>(new Node<T>(_val));
            return;
        }

        std::shared_ptr<Node<T>> temp = nullptr;
        std::shared_ptr<Node<T>> currNode = this->root;
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
        return;
    }

    void printTree() const
    {
        std::cout << "\n";
        printTree_helper(this->root);
    }

    Tree& operator=(Tree& _tree) noexcept
    {
        return std::swap(_tree);
    }

    Node<T> operator [](const int index) const
    {
        const size_t arrSize = pow(2, this->height());
        std::shared_ptr<Node<T>[]> values(new Node<T>[arrSize]);

        this->nodeArr(values);

        return values[index];
    }

    std::shared_ptr<Node<T>> max(std::shared_ptr<Node<T>> root = nullptr) const
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

    std::shared_ptr<Node<T>> min(std::shared_ptr<Node<T>> root = nullptr) const
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
    
    void pop(const T _val)
    {
        if (this->find(_val) != nullptr)
            this->root = this->pop_helper(_val);
        else
            return;
    }

    size_t height(std::shared_ptr<Node<T>> currNode = nullptr, size_t result = 0) const
    {
        if (this->root == nullptr)
            return 0;
        if (currNode == nullptr)
            currNode = this->root;

        size_t leftHeight = 0;
        size_t rightHeight = 0;

        if (currNode->left == nullptr && currNode->right == nullptr)
            return 1;
        leftHeight = (currNode->left == nullptr) ? 0 : height(currNode->left)+1;
        rightHeight = (currNode->right == nullptr) ? 0 : height(currNode->right)+1;

        auto greater = [](const size_t x, const size_t y) { return (x > y) ? x : y; };

        return greater(leftHeight, rightHeight);
    }

    void toFile(std::string fileName = "") const
    {
        fileName = (fileName == "") ? "./data/input.txt" : fileName;

        std::ofstream outFile;
        outFile.open(fileName);

        size_t arrSize = pow(2, this->height());
        std::shared_ptr<T[]> values(new T[arrSize]);
        std::shared_ptr<size_t[]> number(new size_t[arrSize]);
        std::shared_ptr<bool[]> isInitialized(new bool[arrSize]);

        this->valArr(isInitialized, values, number);

        for (size_t i = 0; i < arrSize; i++)
        {
            if (isInitialized[i])
                outFile << values[i] << " " << number[i] << "\n";
        }
    }
    void fromFile(std::string fileName = "")
    {
        fileName = (fileName == "") ? "./data/input.txt" : fileName;

        std::ifstream inFile;
        inFile.open(fileName);

        T input;
        size_t number = 0;
        std::string str;

        if(inFile)
        {
            while(std::getline(inFile, str))
            {
                std::stringstream(str) >> input >> number;
                for (size_t i = 0; i < number; i++)
                    this->insert(input);
                
            }
        }
    }

    void sort()
    {
        Tree<T> newTree;

        while (this->root != nullptr)
        {
            for (size_t i = 0; i < this->min()->getSize(); i++)
                newTree.insert(this->min()->getVal());
            this->pop(this->min()->getVal());
        }
        std::swap(this->root, newTree.root);
    }

    void rsort()
    {
        Tree<T> newTree;

        while (this->root != nullptr)
        {
            newTree.insert(this->max()->getVal());
            this->pop(this->max()->getVal());
        }
        std::swap(this->root, newTree.root);
    }
    
};

int main()
{
    
    Tree<int> tree;

    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(20);
    tree.insert(7);
    tree.insert(7);
    tree.insert(7);
    tree.insert(2);
    tree.insert(2);

    std::cout << tree[0].getVal();

    tree.printTree();



    /*
     *  TO DO:
     *  * SPLIT THE FILE INTO HEADERS
     */

}
