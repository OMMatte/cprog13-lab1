#include <iostream>
#include <stdexcept>
#include "vector.cpp"     // inkludera din headerfil h‰r
#include <assert.h>

int main()
{
    Vector<double> v;           // ok: defaultkonstruktor ger vektor med flyttal
    Vector<char> *a = new Vector<char>[3];  // dynamiskt allokerade ser ut så här
    delete [] a;
    
    assert(v.size() == 0);      // tom från början
    v.push_back(3.14);          // lägg till ett element sist
    assert(v.size() == 1);      // nu ligger ett element i vektorn
    v.insert(0, 2.10);          // lägg till före element 0, dvs först
    assert(v[0] == 2.10 &&      // hamnade de rätt?
           v[1] == 3.14);
    assert(v.size() == 2);      // nu ligger två element i vektorn
    v.sort(false);              // sortera i fallande ordning
    assert(v[0] == 3.14 &&      // hamnade de rätt?
           v[1] == 2.10);
    assert(v.size() == 2);      // ingenting ändrat?
    v[1] = 2.11;                // tilldelning av enstaka element;
    
    const Vector<double> &vc = v;  // skapa konstant referens
    assert(vc.size() == 2);     // ok: ändrar ej vektorn som är konstant
    assert(vc[0] == 3.14 &&     // ok: ändrar ej vektorn som är konstant
           vc[1] == 2.11);
    
    v.erase(0);                 // ta bort första elementet
    assert(v.size() == 1);      // rätt antal elelment
    v.clear();                  // töm hela vektorn
    assert(v.size() == 0);      // tom när alla element är borttagna
    
 
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
