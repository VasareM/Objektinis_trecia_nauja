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