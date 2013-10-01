#include <iostream>
#include <stdexcept>
#include "vector.cpp"     // inkludera din headerfil här

class A {
    
public:
    
    int hej;
    A() {
        hej = 1337;
    }
    
    A(int a) {
        hej = a;
    }
    
    bool operator> (const A & a) const{
        return (hej > a.hej);
    }
};

int main()
{
    // Några saker som ska fungera:
    Vector<int> a(7);           // initiering med 7 element
    Vector<int> b(a);           // kopieringskonstruktor
    Vector<int> c = a;          // kopieringskonstruktor

    a = b;                 // tilldelning genom kopiering
    a[5] = 7;              // tilldelning till element

    const Vector<int> e(10);    // konstant objekt med 10 element
    int i = e[5];          // const int oper[](int) const körs
    i = a[0];              // vektorn är nollindexerad
    i = a[5];              // int oper[](int) körs
    
    a[5]++;                // öka värdet till 8

    try {
        i = e[10];             // försöker hämta element som ligger utanför e
    } catch (std::out_of_range e) {
        std::cout << e.what() << std::endl;
    }
    
#if 0
    // Diverse saker att testa
    e[5] = 3;              // fel: (kompilerar ej) tilldelning till const
    b = b;                 // hmm: se till att inte minnet som skall behållas frigörs
#endif

    Vector<double> dvect;
    Vector<A *> apvect;
    Vector<int> ivect(10);
    
    Vector<int> test({3,1,3,0,5,4,6});
    
    for(int i = 0; i < test.size(); i++) {
        std::cout << test[i];
    }
   
    test.erase(1);
    
    std::cout << std::endl;
    
    for(int i = 0; i < test.size(); i++) {
        std::cout << test[i];
    }
    
    std::cout << (test.exists(2) ? "ja" : "nej");
    
    return 0;
}
