#ifndef STACK_H
#define STACK_H

#include <mutex>
#include <functional>
#include <thread>
#include <stdexcept>
#include <cstddef>
#include <iostream>

template <typename T>
class stack
{
public:
    stack();

    auto empty() const ->bool;
    auto size() const -> size_t;   /* unsigned int */

    auto push(T const & value)  -> void;
    auto pop()   -> T;

private:
    typedef struct Node
    {
        T     value;
        Node* next;
    };

    Node*         _top;  /*  */
    unsigned int  _size;

    mutable std::mutex mutexstack_;
    auto throw_is_empty() const -> void;

};

template <typename T>
stack<T>::stack() : _top(nullptr), _size(0)
{

}

template <typename T>
auto stack<T>::push(T const & value) -> void
{
    std::lock_guard<std::mutex> lock(mutexstack_);
    Node* old_top = _top;
    _top = new Node;
    _top->value = value;
    _top->next = old_top;
    _size ++;
}

template <typename T>
auto stack<T>::pop()   -> T
{
    std::lock_guard<std::mutex> lock(mutexstack_);
    Node* old_top = _top;
    if (_size > 0)
    {
        _top = _top->next;
        T value = old_top->value;
        delete old_top;
        _size --;
        return value;
    }

    throw_is_empty();
}

template <typename T>
auto stack<T>::throw_is_empty() const -> void
{
    throw std::logic_error("Error!!!");
}

template <typename T>
auto stack<T>::empty() const ->bool
{
    std::lock_guard<std::mutex> lock(mutexstack_);
    return (0 == _size);
}

template <typename T>
auto stack<T>::size() const -> size_t
{
    std::lock_guard<std::mutex> lock(mutexstack_);
    return _size;
}

#endif // STACK_H
