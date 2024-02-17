#include "clock.h"

int main()
{
    // demonstrates constructors 
    Clock c1; 
    cout << endl << c1 << endl; 
    Clock c2(5); 
    cout << c2 << endl;
    Clock c3(1,2,3,4);
    cout << c3 << endl << endl; 

    // getters and setters 
    c1.setHours(6);
    cout << c1 << endl; 
    cout << c3.getSeconds() << endl;
    c3.Reset();
    cout << c3 << endl << endl; 
    

    // operator overloading 
    Clock a(2,4,6,8);
    Clock b(1,3,5,7);
    Clock c = a + b; 
    cout << c << endl;
    c = a - b;  
    cout << c << endl;
    if (a == b)
        cout << "true" << endl; 
    else 
        cout << "false" << endl; 
    if (a > b)
        cout << "true" << endl; 
    else 
        cout << "false" << endl; 
    if (a < b)
        cout << "true" << endl; 
    else 
        cout << "false" << endl; 
    cout << -a << endl << endl;  
}
