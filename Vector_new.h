#include <iostream>
#include <initializer_list>
#include <algorithm>
#include <limits>
#include <memory>
#include <iterator>

class Vector {
public:
    using value_type = double;
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

Vector::Vector() : _data(nullptr), _size(0), _capacity(0) {}

Vector::Vector(size_type n) : _data(new value_type[n]()), _size(n), _capacity(n) {}

Vector::Vector(size_type n, value_type val) : _data(new value_type[n]), _size(n), _capacity(n) {
    std::fill(_data, _data + n, val);
}

Vector::Vector(std::initializer_list<value_type> ilist)
    : _data(new value_type[ilist.size()]), _size(ilist.size()), _capacity(ilist.size()) {
    std::copy(ilist.begin(), ilist.end(), _data);
}

Vector::~Vector() {
    delete[] _data;
}

Vector& Vector::operator=(const Vector& other) {
    if (this == &other) return *this;
    delete[] _data;
    _data = new value_type[other._capacity];
    _size = other._size;
    _capacity = other._capacity;
    std::copy(other._data, other._data + _size, _data);
    return *this;
}

Vector::reference Vector::at(size_type pos) {
    if (pos >= _size) throw std::out_of_range("Index out of range");
    return _data[pos];
}

Vector::reference Vector::operator[](size_type pos) {
    return _data[pos];
}

Vector::reference Vector::front() {
    return _data[0];
}

Vector::reference Vector::back() {
    return _data[_size - 1];
}

Vector::size_type Vector::size() const { return _size; }
Vector::size_type Vector::capacity() const { return _capacity; }
bool Vector::empty() const { return _size == 0; }
Vector::size_type Vector::max_size() const { return std::numeric_limits<size_type>::max() / sizeof(value_type); }

void Vector::reserve(size_type new_cap) {
    if (new_cap <= _capacity) return;
    pointer new_data = new value_type[new_cap];
    std::copy(_data, _data + _size, new_data);
    delete[] _data;
    _data = new_data;
    _capacity = new_cap;
}

void Vector::shrink_to_fit() {
    if (_capacity == _size) return;
    pointer new_data = new value_type[_size];
    std::copy(_data, _data + _size, new_data);
    delete[] _data;
    _data = new_data;
    _capacity = _size;
}

void Vector::resize(size_type new_size) {
    resize(new_size, value_type());
}

void Vector::resize(size_type new_size, value_type val) {
    if (new_size < _size) {
        _size = new_size;
    } else {
        if (new_size > _capacity) reserve(new_size);
        std::fill(_data + _size, _data + new_size, val);
        _size = new_size;
    }
}

void Vector::clear() {
    _size = 0;
}

void Vector::push_back(value_type val) {
    if (_size == _capacity) reserve(_capacity == 0 ? 1 : 2 * _capacity);
    _data[_size++] = val;
}

void Vector::pop_back() {
    if (_size > 0) --_size;
}

Vector::iterator Vector::insert(iterator pos, const value_type& val) {
    size_type index = pos - _data;
    if (_size == _capacity) reserve(_capacity == 0 ? 1 : 2 * _capacity);
    std::move_backward(_data + index, _data + _size, _data + _size + 1);
    _data[index] = val;
    ++_size;
    return _data + index;
}

Vector::iterator Vector::erase(iterator pos) {
    size_type index = pos - _data;
    std::move(_data + index + 1, _data + _size, _data + index);
    --_size;
    return _data + index;
}

void Vector::assign(size_type count, value_type val) {
    if (count > _capacity) {
        delete[] _data;
        _data = new value_type[count];
        _capacity = count;
    }
    std::fill(_data, _data + count, val);
    _size = count;
}

void Vector::swap(Vector& other) noexcept {
    std::swap(_data, other._data);
    std::swap(_size, other._size);
    std::swap(_capacity, other._capacity);
}

Vector::iterator Vector::begin() { return _data; }
Vector::const_iterator Vector::begin() const { return _data; }
Vector::const_iterator Vector::cbegin() const { return _data; }

Vector::iterator Vector::end() { return _data + _size; }
Vector::const_iterator Vector::end() const { return _data + _size; }
Vector::const_iterator Vector::cend() const { return _data + _size; }

Vector::reverse_iterator Vector::rbegin() { return reverse_iterator(end()); }
Vector::const_reverse_iterator Vector::rbegin() const { return const_reverse_iterator(end()); }
Vector::const_reverse_iterator Vector::crbegin() const { return const_reverse_iterator(end()); }

Vector::reverse_iterator Vector::rend() { return reverse_iterator(begin()); }
Vector::const_reverse_iterator Vector::rend() const { return const_reverse_iterator(begin()); }
Vector::const_reverse_iterator Vector::crend() const { return const_reverse_iterator(begin()); }

Vector::allocator_type Vector::get_allocator() const {
    return allocator_type();
}

Vector::pointer Vector::data() {
    return _data;
}
