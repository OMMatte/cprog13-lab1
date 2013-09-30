#include <iostream>

class A {
public:
    A() {
        std::cout << "The default contructor" << std::endl;
    }
    
    A(const A & ref) {
        std::cout << "The copy contructor" << std::endl;
    }
    
    ~A() {
        std::cout << "The destructor" << std::endl;
    }
    
    A(char * s) {
        std::cout << "Some other constructor " << s << std::endl;
    }
    
    A & operator=(const A & s) {
        std::cout << "The assignment operator" << std::endl;
        return *this;
    }
};

void no_ref(A a) {}
void with_ref(const A & a) {}


