#ifndef VECTOR_NEW_H
#define VECTOR_NEW_H

#include <iostream>
#include <initializer_list>
#include <algorithm>
#include <limits>
#include <memory>
#include <iterator>
//#include <vector>

template <typename T>
class Vector {
public:
    using value_type = T;
    using allocator_type = std::allocator<value_type>;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = value_type*;
    using const_pointer = const value_type*;
    using iterator = value_type*;
    using const_iterator = const value_type*;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    Vector();
    Vector(size_type);
    Vector(size_type, value_type);
    Vector(std::initializer_list<value_type>);
    Vector(const Vector<T>& other); // Only this copy constructor
    ~Vector();

    Vector& operator=(const Vector&);

    reference at(size_type);
    reference operator[](size_type);
    reference front();
    reference back();

    size_type size() const;
    size_type capacity() const;
    bool empty() const;
    size_type max_size() const;

    void reserve(size_type);
    void shrink_to_fit();
    void resize(size_type);
    void resize(size_type, value_type);

    void clear();
    void push_back(value_type);
    void pop_back();
    iterator insert(iterator, const value_type&);
    iterator erase(iterator);
    iterator erase(iterator first, iterator last); // Add this declaration
    void assign(size_type, value_type);
    void swap(Vector&) noexcept;

    iterator begin();
    const_iterator begin() const;
    const_iterator cbegin() const;

    iterator end();
    const_iterator end() const;
    const_iterator cend() const;

    reverse_iterator rbegin();
    const_reverse_iterator rbegin() const;
    const_reverse_iterator crbegin() const;

    reverse_iterator rend();
    const_reverse_iterator rend() const;
    const_reverse_iterator crend() const;

    allocator_type get_allocator() const;

    pointer data();

private:
    pointer _data = nullptr;
    size_type _size = 0;
    size_type _capacity = 0;
};

// Implementation

template <typename T>
Vector<T>::Vector() : _data(nullptr), _size(0), _capacity(0) {}

template <typename T>
Vector<T>::Vector(size_type n) : _data(new value_type[n]()), _size(n), _capacity(n) {}

template <typename T>
Vector<T>::Vector(size_type n, value_type val) : _data(new value_type[n]), _size(n), _capacity(n) {
    std::fill(_data, _data + n, val);
}

template <typename T>
Vector<T>::Vector(std::initializer_list<value_type> ilist)
    : _data(new value_type[ilist.size()]), _size(ilist.size()), _capacity(ilist.size()) {
    std::copy(ilist.begin(), ilist.end(), _data);
}

template <typename T>
Vector<T>::Vector(const Vector<T>& other)
    : _data(new T[other.size()]), _size(other.size()), _capacity(other.size()) {
    std::copy(other.begin(), other.end(), _data);
}

template <typename T>
Vector<T>::~Vector() {
    delete[] _data;
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector& other) {
    if (this == &other) return *this;
    delete[] _data;
    _data = new value_type[other._capacity];
    _size = other._size;
    _capacity = other._capacity;
    std::copy(other._data, other._data + _size, _data);
    return *this;
}

template <typename T>
typename Vector<T>::reference Vector<T>::at(size_type pos) {
    if (pos >= _size) throw std::out_of_range("Index out of range");
    return _data[pos];
}

template <typename T>
typename Vector<T>::reference Vector<T>::operator[](size_type pos) {
    return _data[pos];
}

template <typename T>
typename Vector<T>::reference Vector<T>::front() {
    return _data[0];
}

template <typename T>
typename Vector<T>::reference Vector<T>::back() {
    return _data[_size - 1];
}

template <typename T>
typename Vector<T>::size_type Vector<T>::size() const { return _size; }
template <typename T>
typename Vector<T>::size_type Vector<T>::capacity() const { return _capacity; }
template <typename T>
bool Vector<T>::empty() const { return _size == 0; }
template <typename T>
typename Vector<T>::size_type Vector<T>::max_size() const { return std::numeric_limits<size_type>::max() / sizeof(value_type); }

template <typename T>
void Vector<T>::reserve(size_type new_cap) {
    if (new_cap <= _capacity) return;
    pointer new_data = new value_type[new_cap];
    std::copy(_data, _data + _size, new_data);
    delete[] _data;
    _data = new_data;
    _capacity = new_cap;
}

template <typename T>
void Vector<T>::shrink_to_fit() {
    if (_capacity == _size) return;
    pointer new_data = new value_type[_size];
    std::copy(_data, _data + _size, new_data);
    delete[] _data;
    _data = new_data;
    _capacity = _size;
}

template <typename T>
void Vector<T>::resize(size_type new_size) {
    resize(new_size, value_type());
}

template <typename T>
void Vector<T>::resize(size_type new_size, value_type val) {
    if (new_size < _size) {
        _size = new_size;
    } else {
        if (new_size > _capacity) reserve(new_size);
        std::fill(_data + _size, _data + new_size, val);
        _size = new_size;
    }
}

template <typename T>
void Vector<T>::clear() {
    _size = 0;
}

template <typename T>
void Vector<T>::push_back(value_type val) {
    if (_size == _capacity) reserve(_capacity == 0 ? 1 : 2 * _capacity);
    _data[_size++] = val;
}

template <typename T>
void Vector<T>::pop_back() {
    if (_size > 0) --_size;
}

template <typename T>
typename Vector<T>::iterator Vector<T>::insert(iterator pos, const value_type& val) {
    size_type index = pos - _data;
    if (_size == _capacity) reserve(_capacity == 0 ? 1 : 2 * _capacity);
    std::move_backward(_data + index, _data + _size, _data + _size + 1);
    _data[index] = val;
    ++_size;
    return _data + index;
}

template <typename T>
typename Vector<T>::iterator Vector<T>::erase(iterator pos) {
    size_type index = pos - _data;
    std::move(_data + index + 1, _data + _size, _data + index);
    --_size;
    return _data + index;
}

// Add this implementation:
template <typename T>
typename Vector<T>::iterator Vector<T>::erase(iterator first, iterator last) {
    if (first == last) return first;
    size_type index_first = first - _data;
    size_type index_last = last - _data;
    size_type count = index_last - index_first;
    std::move(_data + index_last, _data + _size, _data + index_first);
    _size -= count;
    return _data + index_first;
}

template <typename T>
void Vector<T>::assign(size_type count, value_type val) {
    if (count > _capacity) {
        delete[] _data;
        _data = new value_type[count];
        _capacity = count;
    }
    std::fill(_data, _data + count, val);
    _size = count;
}

template <typename T>
void Vector<T>::swap(Vector& other) noexcept {
    std::swap(_data, other._data);
    std::swap(_size, other._size);
    std::swap(_capacity, other._capacity);
}

template <typename T>
typename Vector<T>::iterator Vector<T>::begin() { return _data; }
template <typename T>
typename Vector<T>::const_iterator Vector<T>::begin() const { return _data; }
template <typename T>
typename Vector<T>::const_iterator Vector<T>::cbegin() const { return _data; }

template <typename T>
typename Vector<T>::iterator Vector<T>::end() { return _data + _size; }
template <typename T>
typename Vector<T>::const_iterator Vector<T>::end() const { return _data + _size; }
template <typename T>
typename Vector<T>::const_iterator Vector<T>::cend() const { return _data + _size; }

template <typename T>
typename Vector<T>::reverse_iterator Vector<T>::rbegin() { return reverse_iterator(end()); }
template <typename T>
typename Vector<T>::const_reverse_iterator Vector<T>::rbegin() const { return const_reverse_iterator(end()); }
template <typename T>
typename Vector<T>::const_reverse_iterator Vector<T>::crbegin() const { return const_reverse_iterator(end()); }

template <typename T>
typename Vector<T>::reverse_iterator Vector<T>::rend() { return reverse_iterator(begin()); }
template <typename T>
typename Vector<T>::const_reverse_iterator Vector<T>::rend() const { return const_reverse_iterator(begin()); }
template <typename T>
typename Vector<T>::const_reverse_iterator Vector<T>::crend() const { return const_reverse_iterator(begin()); }

template <typename T>
typename Vector<T>::allocator_type Vector<T>::get_allocator() const {
    return allocator_type();
}

template <typename T>
typename Vector<T>::pointer Vector<T>::data() {
    return _data;
}

#endif // VECTOR_NEW_H
