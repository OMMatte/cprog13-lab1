//
//  vector.h
//  cprog13-vector
//
//  Created by Lucas Wiener on 10/1/13.
//  Copyright (c) 2013 cprog. All rights reserved.
//

#ifndef cprog13_vector_vector_h
#define cprog13_vector_vector_h

#include <memory>
#include <initializer_list>

class Vector {
    std::size_t size;
    std::unique_ptr<unsigned int[]> values;
    
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
    Vector(const std::initializer_list<unsigned int> data);
    
    ~Vector();
    
    /* Copy operator = */
    Vector & operator= (const Vector & v);
    
    /* Move operator = */
    Vector& operator= (Vector && v);
    
    /* Access operator [] */
    unsigned int & operator[] (const size_t index) const;
    
    size_t getSize(void) const;
};

#endif
