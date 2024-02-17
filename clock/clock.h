#include <iostream>
#include <stdlib.h>
#include <iomanip>
using namespace std; 

class Clock 
{
    // operator overloads 
    friend Clock operator+(const Clock& c1, const Clock& c2);   // addition
    friend Clock operator-(const Clock& c1, const Clock& c2);   // subtraction
    friend bool operator==(const Clock& c1, const Clock& c2);   // comparison ==  
    friend bool operator<(const Clock& c1, const Clock& c2);    // comparison <
    friend bool operator>(const Clock& c1, const Clock& c2);    // comparison >
    friend ostream& operator<<(ostream& o, const Clock& c);     // insertion operator 
    
    public:
        Clock();                            // default constructor 
        Clock(int days);                    // conversion constructor     
        Clock(int minutes, int seconds);    // 2-parameterized constructor 
        Clock(int days, int hours, int minutes, int seconds);   // 4-parameterized constructor  

        // getters and setters
        void setDays(int days);  
        void setHours(int hours);  
        void setMinutes(int minutes);  
        void setSeconds(int secondss);  
        int getDays() const; 
        int getHours() const; 
        int getMinutes() const; 
        int getSeconds() const; 
        
        void Reset();
    
        Clock operator-();  // operator overload for negation of time parameters
    private: 
        int days; 
        int hours; 
        int minutes; 
        int seconds; 
};
