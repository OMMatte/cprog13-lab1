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

template <class T>
class Vector {
    std::size_t size;
    std::unique_ptr<T[]> values;
    
    void init(const size_t size);
    
public:
    /* Default constructor */
    Vector();
    
    /* Size constructor */
    explicit Vector(const size_t size);
    
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
    
    size_t getSize(void) const;
};

/* Default constructor */
template <class T>
Vector<T>::Vector() {
    size = 0;
    values = nullptr;
}

/* Size constructor */
template <class T>
Vector<T>::Vector(const size_t size) {
    init(size);
}

/* Copy constructor */
template <class T>
Vector<T>::Vector(const Vector & v) {
    init(v.getSize());
    
    for(int i = 0; i < size; i++) {
        values.get()[i] = v[i];
    }
}

/* Move constructor */
template <class T>
Vector<T>::Vector(Vector && v) {
    size = v.size;
    v.size = 0;
    
    values = std::move(v.values);
    v.values = nullptr; //KOLLA!
}

/* Assign operator = */
template <class T>
Vector<T>::Vector(const std::initializer_list<T> data) {
    init(data.size());
    
    int i = 0;
    for(typename std::initializer_list<T>::iterator it = data.begin(); it != data.end(); ++it) {
        values.get()[i++] = *it;
    }
}

template <class T>
Vector<T>::~Vector() {
    size = 0;
    values = nullptr;
}

template <class T>
void Vector<T>::init(const size_t size) {
    this->size = size;
    this->values = std::unique_ptr<T[]>(new T[size]());
}

/* Copy operator = */
template <class T>
Vector<T> & Vector<T>::operator= (const Vector<T> & v) {
    if(this == &v) {
        return *this;
    }
    
    size = v.getSize();
    
    values = std::unique_ptr<T[]>(new T[size]);
    
    for(int i = 0; i < size; i++) {
        values.get()[i] = v[i];
    }
    
    return *this;
}

/* Move operator = */
template <class T>
Vector<T>& Vector<T>::operator= (Vector<T> && v) {
    if(this == &v) {
        return *this;
    }
    
    size = v.size;
    values = std::move(v.values); //TODO: releasas värdena i values?
    return *this;
}

/* Access operator [] */
template <class T>
T & Vector<T>::operator[] (const size_t index) const {
    if(index >= size) {
        throw std::out_of_range("Index too big.");
    }
    
    return values.get()[index];
}

template <class T>
size_t Vector<T>::getSize(void) const {
    return size;
}