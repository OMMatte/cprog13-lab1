#include <stdexcept>
#include <memory>
#include <initializer_list>
#include <iterator>
#include <algorithm>

#define FACTOR     1.5

template <class T>
class Vector {
    std::size_t mSize;
    std::size_t mRealSize;
    std::unique_ptr<T[]> mValues;
    
    void init(const size_t size);
    void upsize();
    
public:
    /* Default constructor */
    Vector();
    
    /* Size constructor, set to explicit to prevent implicit conversions. If a function foo takes a vector parameter, the function cannot be called as foo(1). The user might think a vector with element 1 is constructed, when it is instead an empty vector of size 1 is constructed. */
    explicit Vector(const size_t size);
    
    /* Size value constructor */
    Vector(const size_t size, const T & value);
    
    /* Copy constructor */
    Vector(const Vector & v);
    
    /* Move constructor */
    Vector(Vector && v);
    
    /* Intializer list Constructor = */
    Vector(const std::initializer_list<T> data); //TODO: why not reference?
    
    ~Vector();
    
    /* Copy operator = */
    Vector & operator= (const Vector & v);
    
    /* Move operator = */
    Vector& operator= (Vector && v);
    
    /* Access operator [] */
    T & operator[] (const size_t index);
    T operator[] (const size_t index) const;
    
    void insert(const size_t index, const T & value);
    void push_back(const T & value);
    void erase(const size_t index);
    void clear();
    size_t size() const;
    void sort(bool ascending = true);
    void unique_sort(bool ascending = true);
    bool exists(const T & value) const;
};

//
// Constructors / Destructors
//

/* Default constructor */
template <class T>
Vector<T>::Vector() {
    mSize = 0;
    mRealSize = 0;
    mValues = nullptr;
}

/* Size constructor */
template <class T>
Vector<T>::Vector(const size_t size) {
    init(size);
}

/* Size value constructor */
template <class T>
Vector<T>::Vector(const size_t size, const T & value) {
    init(size);
    
    for(int i = 0; i < size; i++) {
        mValues.get()[i] = value;
    }
}

/* Copy constructor */
template <class T>
Vector<T>::Vector(const Vector & v) {
    init(v.mSize);
    
    for(int i = 0; i < mSize; i++) {
        mValues.get()[i] = v[i];
    }
}

/* Move constructor */
template <class T>
Vector<T>::Vector(Vector && v) {
    mSize = v.mSize();
    v.mSsize = 0;
    
    mValues = std::move(v.mValues);
    v.mValues = nullptr;
}

template <class T>
Vector<T>::~Vector() {
    mSize = 0;
    mValues = nullptr;
}

//
// Operators
//

/* Assign operator = */
template <class T>
Vector<T>::Vector(const std::initializer_list<T> data) {
    init(data.size());
    
    int i = 0;
    for(typename std::initializer_list<T>::iterator it = data.begin(); it != data.end(); ++it) {
        mValues.get()[i++] = *it;
    }
}

/* Copy operator = */
template <class T>
Vector<T> & Vector<T>::operator= (const Vector<T> & v) {
    if(this == &v) {
        return *this;
    }
    
    init(v.size());
    
    for(int i = 0; i < mSize; i++) {
        mValues.get()[i] = v[i];
    }
    
    return *this;
}

/* Move operator = */
template <class T>
Vector<T>& Vector<T>::operator= (Vector<T> && v) {
    if(this == &v) {
        return *this;
    }
    
    mSize = v.mSize;
    mValues = std::move(v.mValues); //TODO: releasas värdena i values?
    return *this;
}

/* Access operator [] */
template <class T>
T & Vector<T>::operator[] (const size_t index) {
    if(index >=  mSize) {
        throw std::out_of_range("Index too big.");
    }
    
    return mValues.get()[index];
}

/* Access operator [] */
template <class T>
T Vector<T>::operator[] (const size_t index) const {
    if(index >=  mSize) {
        throw std::out_of_range("Index too big.");
    }
    
    return mValues.get()[index];
}

//
// Private functions
//

template <class T>
void Vector<T>::init(const size_t size) {
    mSize = size;
    mRealSize = size;
    mValues = std::unique_ptr<T[]>(new T[size]());
}

template <class T>
void Vector<T>::upsize() {
    T *current = mValues.release();
    
    size_t newSize = mSize*FACTOR + 1;
    
    T *bigger = new T[(size_t)(mSize*FACTOR + 1)]();
    std::copy(current, current + mSize, bigger);
    
    delete[] current;
    
    mRealSize = newSize;
    
    mValues = std::unique_ptr<T[]>(bigger);
}

//
// Public functions
//

template <class T>
void Vector<T>::insert(const size_t index, const T & value) {
    if(index > mSize) {
        throw std::out_of_range("Index too high.");
    }
    
    if(mSize == mRealSize) {
        upsize();
    }
    
    if(index < mSize) {
        std::copy_backward(mValues.get() + index, mValues.get() + mSize, mValues.get() + mSize + 1);
    }
    
    mValues.get()[index] = value;
    
    mSize++;
}

template <class T>
void Vector<T>::push_back(const T & value) {
    insert(mSize, value);
}

template <class T>
void Vector<T>::erase(const size_t index) {
    if(index >= mSize) {
        throw std::out_of_range("Index too high.");
    }
    
    T *start = mValues.get();
    
    std::copy(start + index + 1, start + mSize, start + index);
    
    mSize--;
}

template <class T>
void Vector<T>::clear() {
    mSize = 0;
}

template <class T>
size_t Vector<T>::size() const {
    return mSize;
}

template <class T>
bool sortCompareDesc(const T & a, const T & b) {
    return (b < a);
}

template <class T>
void Vector<T>::sort(bool ascending) {
    if(!ascending) {
        std::sort(mValues.get(), mValues.get() + mSize, sortCompareDesc<T>);
    } else {
        std::sort(mValues.get(), mValues.get() + mSize);
    }
}

template <class T>
void Vector<T>::unique_sort(bool ascending) {
    sort(ascending);
    
    auto it = std::unique(mValues.get(), mValues.get() + mSize);
    mSize = std::distance(mValues.get(), it);
}

template <class T>
bool Vector<T>::exists(const T & value) const {
    auto res = std::find(mValues.get(), mValues.get() + mSize, value);
    return (res != (mValues.get() + mSize));
}