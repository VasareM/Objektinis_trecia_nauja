#include <iostream>
#include <initializer_list>

class Vector {
public:
 // constructors
    Vector();                                // default constructor
    Vector(std::size_t);                     // default fill constructor
    Vector(std::size_t, double);             // fill constructor
    Vector(std::initializer_list<double>);   // initializer list constructor
    ~Vector();

 // accessors
    double& at(std::size_t);
    double& operator[](std::size_t);
    double& front();
    double& back();

 // storage
    double* data();
    std::size_t size() const;
    std::size_t capacity() const; 
    bool empty() const;

 // modifiers
    void clear();


    // Capacity
// ...
    void shrink_to_fit();
    void reserve(size_t);

// Modifiers
    void push_back(double);
    void pop_back();
    void resize(size_t);
    void resize(size_t, double);
// ...
    void reserve( size_t new_cap );

    // Member types
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

    // Member functions
    // copy assignment operator
    Vector& operator=(const Vector& other) {
        if (this != &other) {
            delete[] _data;
            _size = other._size;
            _capacity = other._capacity;
            _data = new double[_capacity];
            std::copy(other._data, other._data + _size, _data);
        }
        return *this;
    }
    void assign(std::size_t count, double value) {
        delete[] _data;
        _data = new double[count];
        _size = _capacity = count;
        std::fill(_data, _data + count, value);
    }
    allocator_type get_allocator() const {
        return allocator_type();
    }
    iterator begin() { return _data; }
    const_iterator begin() const { return _data; }
    const_iterator cbegin() const { return _data; }

    iterator end() { return _data + _size; }
    const_iterator end() const { return _data + _size; }
    const_iterator cend() const { return _data + _size; }

    reverse_iterator rbegin() { return reverse_iterator(end()); }
    const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
    const_reverse_iterator crbegin() const { return const_reverse_iterator(end()); }

    reverse_iterator rend() { return reverse_iterator(begin()); }
    const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }
    const_reverse_iterator crend() const { return const_reverse_iterator(begin()); }

    std::size_t max_size() const {
        return std::numeric_limits<std::size_t>::max() / sizeof(double);
    }
    iterator insert(iterator pos, const double& value) {
        std::size_t index = pos - _data;

        if (_size == _capacity)
            reserve(_capacity == 0 ? 1 : 2 * _capacity);

        for (std::size_t i = _size; i > index; --i) {
            _data[i] = _data[i - 1];
        }

        _data[index] = value;
        ++_size;

        return _data + index;
    }
    // nebus emplace
    iterator erase(iterator pos) {
        if (pos >= _data + _size)
            return end();

        std::size_t index = pos - _data;

        for (std::size_t i = index; i < _size - 1; ++i) {
            _data[i] = _data[i + 1];
        }

        --_size;
        return _data + index;
    }
    void swap(Vector& other) noexcept {
        std::swap(_data, other._data);
        std::swap(_size, other._size);
        std::swap(_capacity, other._capacity);
    }



    // non member functions
    // non member swap
    inline void swap(Vector& a, Vector& b) noexcept {
        a.swap(b);
    }

private:
    double* _data;
    std::size_t _size;
    std::size_t _capacity;
};

//Constructors:
// Default
// Allocates memory for _data pointer
// Initialize _size, _capacity to zero
Vector::Vector()
    : _data{nullptr}, _size{0}, _capacity{0}
{}

// Default fill
// Allocates memory for _data pointer
// Initialize _size, _capacity to size
// The constructor fills the array with the default value of a double
// which is zero
Vector::Vector(std::size_t size)
    : _data{new double[size]}, _size{size}, _capacity{size}
{
    for (int i = 0; i < size; ++i) {
        _data[i] = {};
    }
}

// Fill
// Allocates memory for _data pointer
// Initialize _size, _capacity to size
// The constructor fills the array with val value
Vector::Vector(std::size_t size, double val)
    : _data{new double[size]}, _size{size}, _capacity{size}
{
    for (int i = 0; i < size; ++i) {
        _data[i] = val;
    }
}

// List Initializer
// Allocates memory for _data pointer
// Initialize _size, _capacity to size of the list
// Copy values from the list to the array
Vector::Vector(std::initializer_list<double> ilist)
    : _data{new double[ilist.size()]}, _size{ilist.size()}, _capacity{ilist.size()}
{
    int i = 0;
    for (auto& e : ilist)
    {
        *(_data + i) = e;
        ++i;
    }
}

//destructor
Vector::~Vector() {
 delete[] _data;
}

//accessors - allow us to access elements in the vector
// accepts an index `idx` of an element in the array
// throws an error if: idx > size() or idx < 0
// returns a reference to the value stored at idx.
double& Vector::at(std::size_t idx) {
    if (idx >= _size)
    throw std::out_of_range("index out of range");

    return *(_data + idx);
}

// accepts an index `idx` of an element in the array
// Doesn't perform any bound checking
// returns a reference to the value stored at idx.
double& Vector::operator[](std::size_t idx) {
    return *(_data + idx);
}

// returns a reference to the first element of the vector
double& Vector::front() {
    return *_data;                  // or, _data[0]
}

// returns a reference the last element
double& Vector::back() {
    return *(_data + (_size - 1));  // or, _data[_size - 1]
}

// returned the pointer data
double* Vector::data() {
    return _data;
}

// storage:
std::size_t Vector::size() const {
    return _size;
}

std::size_t Vector::capacity() const {
    return _capacity;
}

bool Vector::empty() const {
    return _size == 0;
}

// ištrina visus elementus
void Vector::clear() {
    _size = 0;  // _capacity remains unchanged, memory remains allocated
}
void Vector::reserve(size_t new_cap) {
    if (new_cap == 0 || new_cap <= capacity())
        return;

    double* temp = new double[new_cap];
    std::copy(_data, _data + capacity(), temp);
    delete[] _data;
    _data = temp;
    _capacity = new_cap;
}
void Vector::shrink_to_fit() {
    if (_capacity == _size)
        return;

    double* temp = new double[_size];
    std::copy(_data, _data + _size, temp);
    delete[] _data;
    _data = temp;
    _capacity = _size;
}


void Vector::resize(size_t new_size) {
    if (_size == new_size)
        return;

    if (new_size < _size) {
        // If shrinking, only update the size
        _size = new_size;
    } else {
        // If expanding
        if (new_size > _capacity)
            reserve(new_size);  // Only allocate new memory if needed

        // Fill new elements with default values
        for (size_t i = _size; i < new_size; ++i) {
            _data[i] = {};
        }

        _size = new_size;
    }
}
void Vector::push_back(double val) {
    if (_size == _capacity)
    reserve(_capacity == 0 ? 1 : 2 * _capacity);

    *(_data+_size) = val;
    ++_size;
}
void Vector::pop_back() {
    if (_size > 0)
    --_size;
}


///papildymai, member functions:
