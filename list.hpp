#ifndef LIST_HPP
#define LIST_HPP

#include <iostream>
#include <stdexcept>
using namespace std;

template <class T>
class List
{
public:
    List() : _head(nullptr), _tail(nullptr){}
    ~List()
    {
        clear();
    }
    List(const List& that) : _head(nullptr), _tail(nullptr)
    {
        for (Node* node = that._head; node; node = node->_next)
        {
            push_back(node->_data);
        }
    }
    List& operator =(const List& that)
    {
        if (&that != this)
        {
            List list(that);
            swap(_head, list._head);
            swap(_tail, list._tail);
        }
        return *this;
    }

    T& back()
    {
        if (empty())
        {
            throw std::underflow_error("list underflow !");
        }
        return _tail->_data;
    }

    const T& back()const
    {
        return const_cast<List*>(this)->back();
    }

    void push_back(const T& data)
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

    void pop_back()
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

    T& front()
    {
        if (empty())
        {
            throw std::underflow_error("list underflow !");
        }

        return _head->_data;
    }

    const T& front()const
    {
        return const_cast<List*>(this)->front();
    }

    void push_front(const T& data)
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

    void pop_front()
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

    void remove(const T& data)
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

    void clear()
    {
        for (Node* next; _head; _head = next)
        {
            next = _head->_next;
            delete _head;
        }
        _tail = nullptr;
    }

    bool empty()const
    {
        return _head == nullptr && _tail == nullptr;
    }

    size_t size()const
    {
        size_t counter = 0;
        for (Node* node = _head; node; node = node->_next)
        {
            counter++;
        }
        return counter;
    }

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

    bool equal(const T& a, const T& b)const
    {
        return a == b;
    }

    Node* _head;
    Node* _tail;
};

#endif


