#include <iostream>
#include <stdexcept>
#include "vector.cpp"     // inkludera din headerfil h�r
#include <assert.h>

int main()
{
    Vector<double> v;           // ok: defaultkonstruktor ger vektor med flyttal
    Vector<char> *a = new Vector<char>[3];  // dynamiskt allokerade ser ut s� h�r
    delete [] a;
    
    assert(v.size() == 0);      // tom fr�n b�rjan
    v.push_back(3.14);          // l�gg till ett element sist
    assert(v.size() == 1);      // nu ligger ett element i vektorn
    v.insert(0, 2.10);          // l�gg till f�re element 0, dvs f�rst
    assert(v[0] == 2.10 &&      // hamnade de r�tt?
           v[1] == 3.14);
    assert(v.size() == 2);      // nu ligger tv� element i vektorn
    v.sort(false);              // sortera i fallande ordning
    assert(v[0] == 3.14 &&      // hamnade de r�tt?
           v[1] == 2.10);
    assert(v.size() == 2);      // ingenting �ndrat?
    v[1] = 2.11;                // tilldelning av enstaka element;
    
    const Vector<double> &vc = v;  // skapa konstant referens
    assert(vc.size() == 2);     // ok: �ndrar ej vektorn som �r konstant
    assert(vc[0] == 3.14 &&     // ok: �ndrar ej vektorn som �r konstant
           vc[1] == 2.11);
    
    v.erase(0);                 // ta bort f�rsta elementet
    assert(v.size() == 1);      // r�tt antal elelment
    v.clear();                  // t�m hela vektorn
    assert(v.size() == 0);      // tom n�r alla element �r borttagna
    
 
    Vector<int> lol({0,1,2,3,4,5,6,7});
    
    lol.erase(2);
    lol.erase(4-1);
    lol.insert(3, 4);
    lol.insert(0, 0);
    lol.erase(7);
    lol.insert(0, 7);
    lol.insert(8, 0);
    lol.push_back(9);
    lol.erase(9);
    lol.erase(0);
    lol.erase(0);
    
    lol.clear();
    
    lol.push_back(1);
    lol.erase(0);
    lol.insert(1, 10310311);
    
    for(int i = 0; i < lol.size(); i++) {
        std::cout << lol[i];
    }
    
    return 0;
}
