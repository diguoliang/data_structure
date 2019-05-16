#ifndef TREE_H
#define TREE_H

#include <iostream>

template <typename T>
class Tree
{
public:
    Tree();
    Tree(T data[], size_t n);
    ~Tree();

    void   insert(const T& data);

    void   removeAll(T data);
    bool   remove(T data);
    void   clear();

    void   update(T old_data, T new_data);

    bool   find(T data);

    void   travel() const;
    size_t size() const { return _size; }
    size_t height();

private:
    class Node
    {
    public:
        Node(const T& data, Node* left = nullptr, Node* right = nullptr)
            : _data(data), _left(left), _right(right){}
        Node* _left;
        Node* _right;
        T     _data;
    };

    void   insert(Node* node, Node*& tree);
    void   travel(Node* const & tree) const;
    void   clear(Node*& tree);
    size_t height(Node*& tree);
    Node*& find(const T& data, Node*& tree)
    {
        if (!tree) return tree;
        else if (tree->_data == data)
        {
            return tree;
        }
        else if (data < tree->_data)
        {
            find(data, tree->_left);
        }
        else
        {
            find(data, tree->_right);
        }
    }

    Node*   _root;
    size_t  _size;
};

template <typename T>
Tree<T>::Tree() : _root(nullptr), _size(0){}

template <typename T>
Tree<T>::Tree(T data[], size_t n)
    : _root(nullptr), _size(0)
{
    for (size_t i = 0; i < n; i++)
    {
        insert(new Node(data[i]), _root);
        _size++;
    }
}

template <typename T>
Tree<T>::~Tree()
{
    clear();
}

template <typename T>
void Tree<T>::insert(const T& data)
{
    insert(new Node(data), _root);
    _size++;
}

template <typename T>
void Tree<T>::insert(Node* node, Node*& tree)
{
    if (!tree)
    {
        tree = node;
    }
    else if (node)
    {
        if (node->_data < tree->_data)
        {
            insert(node, tree->_left);
        }
        else
        {
            insert(node, tree->_right);
        }
    }
}

template <typename T>
void Tree<T>::removeAll(T data)
{
    while(remove(data));
}

template <typename T>
bool Tree<T>::remove(T data)
{
    Node*& node = find(data, _root);
    if (node)
    {
        //将左子树插入右子树
        insert(node->_left, node->_right);

        //备份匹配节点
        Node* old = node;

        //右子树提升
        node = node->_right;

        //输出匹配节点
        delete old;
        _size--;

        return true;
    }

    return false;
}

template <typename T>
void Tree<T>::update(T old_data, T new_data)
{
    while(remove(old_data))
    {
        insert(new_data);
    }
}


template <typename T>
void Tree<T>::travel() const
{
    travel(_root);
    std::cout << std::endl;
}

template <typename T>
void Tree<T>::travel(Node* const & tree) const
{
    if (tree)
    {
        travel(tree->_left);
        std::cout << tree->_data << " ";
        travel(tree->_right);
    }
}

template <typename T>
void Tree<T>::clear()
{
    clear(_root);
}

template <typename T>
void Tree<T>::clear(Node*& tree)
{
    if (tree)
    {
        clear(tree->_left);
        clear(tree->_right);
        delete tree;
        tree = nullptr;
    }
}

template <typename T>
bool Tree<T>::find(T data)
{
    return find(data, _root) != nullptr;
}

template <typename T>
size_t Tree<T>::height()
{
    return height(_root);
}

template <typename T>
size_t Tree<T>::height(Node*& tree)
{
    if (tree)
    {
        size_t lh = height(tree->_left);
        size_t rh = height(tree->_right);
        return (lh > rh ? lh : rh) + 1;
    }
}

#endif // TREE_H
