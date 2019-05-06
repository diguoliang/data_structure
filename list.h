#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <stdexcept>
using namespace std;

template <typename T>
class List
{
public:
    List();
    ~List();
    List(const List& that);
    List& operator =(const List& that);

    T& back();
    const T& back() const;
    void push_back(const T& data);
    void pop_back();

    T& front();
    const T& front() const;
    void push_front(const T& data);
    void pop_front();

    void remove(const T& data);

    void clear();

    bool empty() const;

    size_t size() const;

    friend ostream& operator<<(ostream& os, const List& list)
    {
        for (Node* node = list._head; node; node = node->_next)
        {
            os << *node << " ";
        }
        return os;
    }

private:
    class Node
    {
    public:
        Node(const T& data, Node* prev = nullptr, Node* next = nullptr)
            : _data(data), _prev(prev), _next(next){}
        friend ostream& operator<<(ostream& os, const Node& node)
        {
            return os << node._data;
        }

        T     _data;
        Node* _prev;
        Node* _next;
    };

    bool equal(const T& a, const T& b) const
    {
        return a == b;
    }

    Node* _head;
    Node* _tail;
};

template <typename T>
List<T>::List() : _head(nullptr), _tail(nullptr){}

template <typename T>
List<T>::~List()
{
    clear();
}

template <typename T>
List<T>::List(const List& that) : _head(nullptr), _tail(nullptr)
{
    for (Node* node = that._head; node; node = node->_next)
    {
        push_back(node->_data);
    }
}

template <typename T>
List<T>& List<T>::operator =(const List<T>& that)
{
    if (&that != this)
    {
        List<T> list(that);
        swap(_head, list._head);
        swap(_tail, list._tail);
    }
    return *this;
}

template <typename T>
T& List<T>::back()
{
    if (empty())
    {
        throw std::underflow_error("list underflow !");
    }
    return _tail->_data;
}

template <typename T>
const T& List<T>::back()const
{
    return const_cast<List*>(this)->back();
}

template <typename T>
void List<T>::push_back(const T& data)
{
    _tail = new Node(data, _tail);
    if (_tail->_prev)
    {
        _tail->_prev->_next = _tail;
    }
    else
    {
        _head = _tail;
    }
}

template <typename T>
void List<T>::pop_back()
{
    if (empty())
    {
        throw std::underflow_error("list underflow !");
    }
    Node* prev = _tail->_prev;
    delete _tail;
    _tail = prev;
    if (_tail)
    {
        _tail->_next = nullptr;
    }
    else
    {
        _head = nullptr;
    }
}

template <typename T>
T& List<T>::front()
{
    if (empty())
    {
        throw std::underflow_error("list underflow !");
    }

    return _head->_data;
}

template <typename T>
const T& List<T>::front() const
{
    return const_cast<List*>(this)->front();
}

template <typename T>
void List<T>::push_front(const T& data)
{
    _head = new Node(data, nullptr, _head);
    if (_head->_next)
    {
        _head->_next->_prev = _head;
    }
    else
    {
        _tail = _head;
    }
}

template <typename T>
void List<T>::pop_front()
{
    if (empty())
    {
        throw std::underflow_error("list underflow !");
    }

    Node* next = _head->_next;
    delete _head;
    _head = next;

    if (_head)
    {
        _head->_prev = nullptr;
    }
    else
    {
        _tail = nullptr;
    }
}

template <typename T>
void List<T>::remove(const T& data)
{
    for (Node* node = _head, *next; node; node = next)
    {
        next = node->_next;
        if (equal(node->_data, data))
        {
            if (node->_prev)
            {
                node->_prev->_next = node->_next;
            }
            else
            {
                _head = node->_next;
            }
            if (node->_next)
            {
                node->_next->_prev = node->_prev;
            }
            else
            {
                _tail = node->_prev;
            }

            delete node;
        }
    }
}

template <typename T>
void List<T>::clear()
{
    for (Node* next; _head; _head = next)
    {
        next = _head->_next;
        delete _head;
    }
    _tail = nullptr;
}

template <typename T>
bool List<T>::empty()const
{
    return _head == nullptr && _tail == nullptr;
}

template <typename T>
size_t List<T>::size()const
{
    size_t counter = 0;
    for (Node* node = _head; node; node = node->_next)
    {
        counter++;
    }
    return counter;
}

#endif // LIST_H
