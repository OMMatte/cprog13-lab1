//
//  main.cpp
//  cprog13-vector
//
//  Created by Lucas Wiener on 9/30/13.
//  Copyright (c) 2013 cprog. All rights reserved.
//

#include <stdexcept>
#include <memory>
#include <initializer_list>
#include <iterator>
#include <algorithm>

template <class T>
class Vector {
    std::size_t mSize;
    std::unique_ptr<T[]> mValues;
    
    void init(const size_t size);
    
public:
    /* Default constructor */
    Vector();
    
    /* Size constructor */
    explicit Vector(const size_t size);
    
    /* Size value constructor */
    Vector(const size_t size, const T & value);
    
    /* Copy constructor */
    Vector(const Vector & v);
    
    /* Move constructor */
    Vector(Vector && v);
    
    /* Assign operator = */
    Vector(const std::initializer_list<T> data);
    
    ~Vector();
    
    /* Copy operator = */
    Vector & operator= (const Vector & v);
    
    /* Move operator = */
    Vector& operator= (Vector && v);
    
    /* Access operator [] */
    T & operator[] (const size_t index) const;
    
    void insert(const size_t index, const T & value);
    void push_back(const T & value);
    void erase(const size_t index);
    void clear();
    size_t size() const;
    void sort(bool ascending = true);
    void unique_sort(bool ascending = true);
    bool exists(const T & value) const;
};

/* Default constructor */
template <class T>
Vector<T>::Vector() {
    mSize = 0;
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
    init(v.size());
    
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

/* Assign operator = */
template <class T>
Vector<T>::Vector(const std::initializer_list<T> data) {
    init(data.size());
    
    int i = 0;
    for(typename std::initializer_list<T>::iterator it = data.begin(); it != data.end(); ++it) {
        mValues.get()[i++] = *it;
    }
}

template <class T>
Vector<T>::~Vector() {
    mSize = 0;
    mValues = nullptr;
}

template <class T>
void Vector<T>::init(const size_t size) {
    mSize = size;
    mValues = std::unique_ptr<T[]>(new T[size]());
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
    
    mSize = v.size;
    mValues = std::move(v.values); //TODO: releasas värdena i values?
    return *this;
}

/* Access operator [] */
template <class T>
T & Vector<T>::operator[] (const size_t index) const {
    if(index >=  mSize) {
        throw std::out_of_range("Index too big.");
    }
    
    return mValues.get()[index];
}

template <class T>
void Vector<T>::insert(const size_t index, const T & value) {
    if(index > mSize) {
        throw std::out_of_range("Index too high.");
    }
    
    T *array = mValues.release();
    
    T *array2 = new T[mSize+1];
    std::copy(array, array + index, array2);
    std::copy(array + index, array + mSize, array2 + index + 1);
    array2[index] = value;
    
    delete[] array;
    
    mValues = std::unique_ptr<T[]>(array2);
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

    std::copy(start, start + index, start);
    std::copy(start + index + 1, start + mSize, start + index);
    
    mSize--;
}

template <class T>
void Vector<T>::clear() {
    init(0);
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