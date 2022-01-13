#include "headers/node.hpp"
#include "headers/tree.hpp"

template <typename T>
std::string Tree<T>::spacing(const size_t n) const
{
    std::string spc = "";
    for (size_t i = 0; i < n; i++)
        spc += "  ";
    return spc;
}

template <typename T>
void Tree<T>::printTree_helper(std::shared_ptr<Node<T>> currNode, size_t level) const
{
    if (currNode == nullptr) {
        std::cout << "-*-\n";
        return;
    }
    if (level == 0)
        std::cout << "root: ";
    std::cout << currNode->getVal() << " (" << currNode->getSize() << ")"
              << "\n";

    std::cout << spacing(level) << "  left: ";
    printTree_helper(currNode->left, level + 1);

    std::cout << spacing(level) << "  right: ";
    printTree_helper(currNode->right, level + 1);
}

template <typename T>
std::shared_ptr<Node<T>> Tree<T>::pop_helper(const T _val, std::shared_ptr<Node<T>> root)
{
    if (root == nullptr)
        root = this->root;

    std::shared_ptr<Node<T>> currNode = root;

    if (root == nullptr)
        return root;

    if (root->getVal() > _val) {
        root->left = this->pop_helper(_val, root->left);
        return root;
    } else if (root->getVal() < _val) {
        root->right = this->pop_helper(_val, root->right);
        return root;
    }

    if (currNode != nullptr) {
        if (currNode->left == nullptr && currNode->right == nullptr) {
            currNode = nullptr;
            return nullptr;
        } else if (currNode->left == nullptr) {
            currNode->setSize(currNode->right->getSize());
            currNode = currNode->right;
            return currNode;
        } else if (currNode->right == nullptr) {
            currNode->setSize(currNode->left->getSize());
            currNode = currNode->left;
            return currNode;
        } else {
            currNode->setSize(this->min(root->right)->getSize());
            currNode = this->min(root->right);

            root->setVal(currNode->getVal());
            root->right = this->pop_helper(currNode->getVal(), root->right);

            return root;
        }
    }
    return nullptr;
}

template <typename T>
void Tree<T>::valArr(std::shared_ptr<bool[]> isInitialized, std::shared_ptr<T[]> values, std::shared_ptr<size_t[]> number, std::shared_ptr<Node<T>> currNode, size_t index) const
{
    if (currNode == nullptr)
        currNode = this->root;

    if (currNode != nullptr) {
        isInitialized[index - 1] = true;
        values[index - 1] = currNode->getVal();
        number[index - 1] = currNode->getSize();
    } else {
        isInitialized[index - 1] = false;
        return;
    }

    if (currNode->left != nullptr)
        valArr(isInitialized, values, number, currNode->left, index * 2);

    if (currNode->right != nullptr)
        valArr(isInitialized, values, number, currNode->right, index * 2 + 1);
}

template <typename T>
void Tree<T>::nodeArr(std::shared_ptr<Node<T>[]> values, std::shared_ptr<Node<T>> currNode, size_t index) const
{
    if (currNode == nullptr)
        currNode = this->root;

    if (currNode != nullptr) {
        values[index - 1] = currNode;
    } else {
        values[index - 1] = nullptr;
        return;
    }

    if (currNode->left != nullptr)
        nodeArr(values, currNode->left, index * 2);

    if (currNode->right != nullptr)
        nodeArr(values, currNode->right, index * 2 + 1);
}

template <typename T>
Tree<T>::Tree(const T _val)
{
    this->root = std::shared_ptr<Node<T>>(new Node<T>(_val));
}

template <typename T>
Tree<T>::Tree()
{
    this->root = nullptr;
}

template <typename T>
std::shared_ptr<Node<T>> Tree<T>::find(const T _val) const
{
    std::shared_ptr<Node<T>> currNode = this->root;
    while (currNode != nullptr && _val != currNode->getVal()) {
        if (currNode == nullptr)
            return nullptr;
        if (_val < currNode->getVal()) {
            currNode = currNode->left;
        } else if (_val > currNode->getVal()) {
            currNode = currNode->right;
        }
    }
    if (currNode == nullptr) {
        return nullptr;
    } else if (currNode->getVal() == _val) {
        return currNode;
    } else {
        return nullptr;
    }
}

template <typename T>
void Tree<T>::insert(const T _val)
{
    if (this->root == nullptr) {
        root = std::shared_ptr<Node<T>>(new Node<T>(_val));
        return;
    }

    std::shared_ptr<Node<T>> temp = nullptr;
    std::shared_ptr<Node<T>> currNode = this->root;
    T currVal;
    while (currNode != nullptr) {
        currVal = currNode->getVal();
        temp = currNode;
        if (_val < currVal) {
            currNode = currNode->left;
        } else if (_val > currVal) {
            currNode = currNode->right;
        } else {
            currNode = currNode;
            break;
        }
    }
    currVal = temp->getVal();
    if (_val < currVal) {
        temp->left = std::make_shared<Node<T>>(_val);
    } else if (_val > currVal) {
        temp->right = std::make_shared<Node<T>>(_val);
    } else {
        temp->incSize();
        temp->setVal(_val, (temp->getSize()) - 1);
    }
    return;
}

template <typename T>
void Tree<T>::printTree() const
{
    std::cout << "\n";
    printTree_helper(this->root);
}

template <typename T>
Tree<T>& Tree<T>::operator=(Tree& _tree) noexcept
{
    return std::swap(_tree);
}

template <typename T>
Node<T> Tree<T>::operator[](const int index) const
{
    const size_t arrSize = pow(2, this->height());
    std::shared_ptr<Node<T>[]> values(new Node<T>[arrSize]);

    this->nodeArr(values);

    return values[index];
}

template <typename T>
std::shared_ptr<Node<T>> Tree<T>::max(std::shared_ptr<Node<T>> root) const
{
    if (root == nullptr)
        root = this->root;

    auto currNode = root;
    while (currNode->right != nullptr) {
        currNode = currNode->right;
    }
    return currNode;
}

template <typename T>
std::shared_ptr<Node<T>> Tree<T>::min(std::shared_ptr<Node<T>> root) const
{
    if (root == nullptr)
        root = this->root;

    auto currNode = root;
    while (currNode->left != nullptr) {
        currNode = currNode->left;
    }
    return currNode;
}

template <typename T>
void Tree<T>::pop(const T _val)
{
    if (this->find(_val) != nullptr)
        this->root = this->pop_helper(_val);
    else
        return;
}

template <typename T>
size_t Tree<T>::height(std::shared_ptr<Node<T>> currNode, size_t result) const
{
    if (this->root == nullptr)
        return 0;
    if (currNode == nullptr)
        currNode = this->root;

    size_t leftHeight = 0;
    size_t rightHeight = 0;

    if (currNode->left == nullptr && currNode->right == nullptr)
        return 1;
    leftHeight = (currNode->left == nullptr) ? 0 : height(currNode->left) + 1;
    rightHeight = (currNode->right == nullptr) ? 0 : height(currNode->right) + 1;

    auto greater = [](const size_t x, const size_t y) { return (x > y) ? x : y; };

    return greater(leftHeight, rightHeight);
}

template <typename T>
void Tree<T>::toFile(std::string fileName) const
{
    fileName = (fileName == "") ? "./data/input.txt" : fileName;

    std::ofstream outFile;
    outFile.open(fileName);

    size_t arrSize = pow(2, this->height());
    std::shared_ptr<T[]> values(new T[arrSize]);
    std::shared_ptr<size_t[]> number(new size_t[arrSize]);
    std::shared_ptr<bool[]> isInitialized(new bool[arrSize]);

    this->valArr(isInitialized, values, number);

    for (size_t i = 0; i < arrSize; i++) {
        if (isInitialized[i])
            outFile << values[i] << " " << number[i] << "\n";
    }
}

template <typename T>
void Tree<T>::fromFile(std::string fileName)
{
    fileName = (fileName == "") ? "./data/input.txt" : fileName;

    std::ifstream inFile;
    inFile.open(fileName);

    T input;
    size_t number = 0;
    std::string str;

    if (inFile) {
        while (std::getline(inFile, str)) {
            std::stringstream(str) >> input >> number;
            for (size_t i = 0; i < number; i++)
                this->insert(input);
        }
    }
}

template <typename T>
void Tree<T>::sort()
{
    Tree<T> newTree;

    while (this->root != nullptr) {
        for (size_t i = 0; i < this->min()->getSize(); i++)
            newTree.insert(this->min()->getVal());
        this->pop(this->min()->getVal());
    }
    std::swap(this->root, newTree.root);
}

template <typename T>
void Tree<T>::rsort()
{
    Tree<T> newTree;

    while (this->root != nullptr) {
        newTree.insert(this->max()->getVal());
        this->pop(this->max()->getVal());
    }
    std::swap(this->root, newTree.root);
}
