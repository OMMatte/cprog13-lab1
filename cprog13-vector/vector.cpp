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
    std::unique_ptr<unsigned int[]> values;
    
public:
    /* Default constructor */
    Vector() {
        size = 0;
        values = nullptr;
    }
    
    /* Size constructor */
    explicit Vector(const size_t size) {
        this->size = size;
        this->values = std::unique_ptr<unsigned int[]>(new unsigned int[size]());
    }
    
    /* Copy constructor */
    Vector(const Vector & v) : Vector(v.getSize()) {
        for(int i = 0; i < size; i++) {
            values.get()[i] = v[i];
        }
    }
    
    /* Move constructor */
    Vector(Vector && v) {
        size = v.size;
        v.size = 0;
        
        values = std::move(v.values);
        v.values = nullptr; //KOLLA!
    }
    
    /* Assign operator = */
    Vector(const std::initializer_list<unsigned int> data) : Vector(data.size()) {
        int i = 0;
        for(std::initializer_list<unsigned int>::iterator it = data.begin(); it != data.end(); ++it) {
            values.get()[i++] = *it;
        }
    }
    
    ~Vector() {
        size = 0;
        values = nullptr;
    }
    
    /* Copy operator = */
    Vector & operator= (const Vector & v) {
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
    Vector& operator= (Vector && v) {
        if(this == &v) {
            return *this;
        }
        
        size = v.size;
        values = std::move(v.values); //TODO: releasas värdena i values?
        return *this;
    }
    
    /* Access operator [] */
    unsigned int & operator[] (const size_t index) const {
        if(index >= size) {
            throw std::out_of_range("Index too big.");
        }
        
        return values.get()[index];
    }
    
    size_t getSize(void) const {
        return size;
    }
};

int main() {
    Vector a = Vector(2);
    Vector b(std::move(a));
    Vector vektor(10);
    
    a = b;
    
    int x = 2;
    int i = vektor[7];
    vektor[3] = x; // OBS, ska fungera!
    Vector v2;
    v2 = {1, 2, 5};
    v2 = std::move(v2);
    v2[0] = 9;
    
    for(int i = 0; i < vektor.getSize(); i++) {
        std::cout << vektor[i];
    }
}

