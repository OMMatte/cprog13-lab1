#include <iostream>
#include <stdexcept>
#include "vector.cpp"     // inkludera din headerfil h�r

class A {
    int hej;
};

int main()
{
    // N�gra saker som ska fungera:
    Vector<int> a(7);           // initiering med 7 element
    Vector<int> b(a);           // kopieringskonstruktor
    Vector<int> c = a;          // kopieringskonstruktor

    a = b;                 // tilldelning genom kopiering
    a[5] = 7;              // tilldelning till element

    const Vector<int> e(10);    // konstant objekt med 10 element
    int i = e[5];          // const int oper[](int) const k�rs
    i = a[0];              // vektorn �r nollindexerad
    i = a[5];              // int oper[](int) k�rs
    
    a[5]++;                // �ka v�rdet till 8

    try {
        i = e[10];             // f�rs�ker h�mta element som ligger utanf�r e
    } catch (std::out_of_range e) {
        std::cout << e.what() << std::endl;
    }
    
#if 0
    // Diverse saker att testa
    e[5] = 3;              // fel: (kompilerar ej) tilldelning till const
    b = b;                 // hmm: se till att inte minnet som skall beh�llas frig�rs
#endif

    Vector<double> dvect;
    Vector<A *> apvect;
    Vector<int> ivect(10);
    
    return 0;
}
