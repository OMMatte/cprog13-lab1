//
//  main.cpp
//  cprog13-vector
//
//  Created by Lucas Wiener on 9/30/13.
//  Copyright (c) 2013 cprog. All rights reserved.
//

//http://blog.smartbear.com/c-plus-plus/c11-tutorial-introducing-the-move-constructor-and-the-move-assignment-operator/

#include <iostream>

class Vector {
    size_t size;
    std::unique_ptr<unsigned int> values;
    
public:
    Vector(const size_t & size) {        
        this->size = size;
        this->values = std::unique_ptr<unsigned int>(new unsigned int[size]());
    }
    
    Vector(const Vector & v) {
        Vector(v.getSize());
        
        for(int i = 0; i < size; i++) {
            values.get()[i] = v[i];
        }
    }
    
    Vector(const Vector && v) {
        
    }
    
    size_t getSize(void) const {
        return size;
    }
    
    Vector operator= (const Vector & v) const {
        return Vector(v);
    }
    
    unsigned int operator[] (const size_t & index) const {
        if(index >= size) {
            throw std::out_of_range("Index too big.");
        }
        
        return values.get()[index];
    }
};