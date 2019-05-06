#include <iostream>
#include <exception>
using namespace std;

template <class T>
class List
{
public:
    // 构造、析构、拷贝构造、拷贝赋值
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

    //获取尾元素
    T& back()
    {
        if (empty())
        {
            throw UnderFlow();
        }
        return _tail->_data;
    }

    const T& back()const
    {
        return const_cast<List*>(this)->back();
    }

    //在尾部压入和弹出元素
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
            return UnderFlow();
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

    //获取头元素
    T& front()
    {
        if (empty())
        {
            return UnderFlow();
        }

        return _head->_data;
    }

    const T& front()const
    {
        return const_cast<List*>(this)->front();
    }

    //在首部压入和弹出元素
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
            return UnderFlow();
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

    //移除所有匹配元素
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

    //清空
    void clear()
    {
        for (Node* next; _head; _head = next)
        {
            next = _head->_next;
            delete _head;
        }
        _tail = nullptr;
    }

    //判空
    bool empty()const
    {
        return _head == nullptr && _tail == nullptr;
    }

    //获取元素个数
    size_t size()const
    {
        size_t counter = 0;
        for (Node* node = _head; node; node = node->_next)
        {
            counter++;
        }
        return counter;
    }

    //输出
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

    class OverFlow : public exception
    {
        const char* what (void) const throw()
        {
            return "链表上溢";
        }
    };

    class UnderFlow : public exception
    {
        const char* what (void) const throw()
        {
            return "链表下溢";
        }
    };

    bool equal(const T& a, const T& b)const
    {
        return a == b;
    }

    Node* _head;
    Node* _tail;
};

int main()
{
    List<int> l;
    l.push_back(1);
    l.push_back(2);
    l.push_back(2);
    l.push_front(3);
    l.remove(2);

    cout << l << endl;
    return 0;
}
