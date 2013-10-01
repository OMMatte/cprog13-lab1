//
//  main.cpp
//  cprog13-vector
//
//  Created by Lucas Wiener on 9/30/13.
//  Copyright (c) 2013 cprog. All rights reserved.
//

#include "vector.h"
#include <stdexcept>

/* Default constructor */
Vector::Vector() {
    size = 0;
    values = nullptr;
}

/* Size constructor */
Vector::Vector(const size_t size) {
    this->size = size;
    this->values = std::unique_ptr<unsigned int[]>(new unsigned int[size]());
}

/* Copy constructor */
Vector::Vector(const Vector & v) : Vector(v.getSize()) {
    for(int i = 0; i < size; i++) {
        values.get()[i] = v[i];
    }
}

/* Move constructor */
Vector::Vector(Vector && v) {
    size = v.size;
    v.size = 0;
    
    values = std::move(v.values);
    v.values = nullptr; //KOLLA!
}

/* Assign operator = */
Vector::Vector(const std::initializer_list<unsigned int> data) : Vector(data.size()) {
    int i = 0;
    for(std::initializer_list<unsigned int>::iterator it = data.begin(); it != data.end(); ++it) {
        values.get()[i++] = *it;
    }
}

Vector::~Vector() {
    size = 0;
    values = nullptr;
}

/* Copy operator = */
Vector & Vector::operator= (const Vector & v) {
    if(this == &v) {
        return *this;
    }
    
    size = v.getSize();
    
    values = std::unique_ptr<unsigned int[]>(new unsigned int[size]);
    
    for(int i = 0; i < size; i++) {
        values.get()[i] = v[i];
    }
    
    return *this;
}

/* Move operator = */
Vector& Vector::operator= (Vector && v) {
    if(this == &v) {
        return *this;
    }
    
    size = v.size;
    values = std::move(v.values); //TODO: releasas värdena i values?
    return *this;
}

/* Access operator [] */
unsigned int & Vector::operator[] (const size_t index) const {
    if(index >= size) {
        throw std::out_of_range("Index too big.");
    }
    
    return values.get()[index];
}

size_t Vector::getSize(void) const {
    return size;
}