#include <iostream>
#include <stdexcept>
//#include "kth_cprog_vektor.cpp"     // inkludera din headerfil h‰r
#include <assert.h>
#include <vector>
#include "Matrix.h"

void vector() {
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
    
    
    assert(!v.exists(2.3));
    v.insert(0, 2.3);
    assert(v.exists(2.3));
    v.clear();
    
    v.push_back(2.0);
    v.push_back(3.0);
    v.push_back(4.3);
    v.erase(2);
    assert(v[0] == 2.0 &&
           v[1] == 3.0 && v.size() == 2);
    v.insert(1, 5.0);
    v.erase(1);
    assert(v[0] == 2.0 &&
           v[1] == 3.0 && v.size() == 2);
    
    Vector<int> b({4,1,2,3,5,7,6,0});
    b.sort();
    for(int i = 0; i < b.size(); i++){
        assert(b[i] == i);
    }
    
    b.sort(false);
    for(int i = 0; i < b.size(); i++){
        assert(b[b.size()-1-i] == i);
    }
    
    b.push_back(4);
    b.push_back(3);
    b.push_back(7);
    b.push_back(2);
    b.push_back(2);
    
    b.unique_sort();
    
    for(int i = 0; i < b.size(); i++){
        assert(b[i] == i);
    }
    
    b.push_back(4);
    b.push_back(3);
    b.push_back(7);
    b.push_back(2);
    b.push_back(2);
    
    b.unique_sort(false);
    for(int i = 0; i < b.size(); i++){
        assert(b[b.size()-1-i] == i);
    }
    
    assert(b.size() == 8);
    
    Vector<int> c = b;
    
    b.erase(3);
    
    for(int i = 0; i < b.size(); i++){
        assert(c[c.size()-1-i] == i);
    }
    
    assert(c.size() == 8);
    
    c.insert(8, 10);
    assert(c[8] == 10);
    c.insert(0, 11);
    assert(c[0] == 11);
    
    {
        Vector<std::string> a = Vector<std::string>({"hejsan"});
        auto b = Vector<std::string>({"tjena"});
        
        b = a;
        
        b[0].append("!");
        
        assert(b[0] == "hejsan!");
        assert(a[0] == "hejsan");
    }
    {
        auto a = Vector<std::string>({"test"});
        a[0].append("!");
        auto b = Vector<std::string>(std::move(a));
    }
    {
        auto a = Vector<std::string>();
        a.push_back("hej");
    }
    
    std::cout << "Success" << std::endl;
}

void matrix() {
    Matrix m(2, 2);
    m[0][0] = 1;
    m[0][1] = 2;
    m[1][0] = -3;
    m[1][1] = 4;
    
    std::cout << m << std::endl;
    
    std::cin >> m;
    
    std::cout << m << std::endl;
}

int main()
{
    //vector();
    
    matrix();
    return 0;
}

