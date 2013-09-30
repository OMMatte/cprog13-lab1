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

/*
int main()
{
    std::cout << "test 1" << std::endl;
    A a("my name is a");
    
    std::cout << "test 2" << std::endl;
    A b = a;         // vad Šr skillnaden
    
    std::cout << "test 3" << std::endl;
    A c(a);          // mellan dessa
    
    std::cout << "test 4" << std::endl;
    A d;             // tre tekniker?
    
    std::cout << "test 5" << std::endl;
    d = a;
    
    std::cout << "test 6" << std::endl;
    no_ref(a);       // Bildas temporŠra objekt?
    
    std::cout << "test 7" << std::endl;
    with_ref(a);     // Bildas temporŠra objekt?
    
    std::cout << "test 8" << std::endl;
    A *aa = new A[5];
    
    std::cout << "test 9" << std::endl;
    delete aa;       // Vad kommer att hŠnda?
    
    return 0;
}*/
