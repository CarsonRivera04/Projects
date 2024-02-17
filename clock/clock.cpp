#include "clock.h"

Clock::Clock()
// default constructor setting all time values to 0 
{
    this->days = 0; 
    this->hours = 0; 
    this->minutes = 0;
    this->seconds = 0;
}

Clock::Clock(int days)
// conversion constructor setting days to given value 
{
    this->days = days;  // sets days to given value  
    this->hours = 0; 
    this->minutes = 0;
    this->seconds = 0;
}

Clock::Clock(int minutes, int seconds)
// 2-parameter constructor settings days and minutes  
{
    this->days = 0; 
    this->hours = 0; 
    this->minutes = 0;
    this->seconds = 0;
   
    // converts time to seconds 
    seconds += (minutes * 60);  
    
    if (abs(seconds) >= 86400)
    // checks if there is more than a day of time 
    {
        this->days = seconds / 86400;   // adds amount of days 
        seconds %=86400;    // adds remainder to seconds 
    } 
    if (abs(seconds) >= 3600)
    // checks if there is more than one hour
    {
        this->hours = seconds / 3600;   // adds amount of hours 
        seconds %= 3600;    // adds remainder to seconds 
    }
    
    if (abs(seconds) >= 60)
    // checks if there is more than a minute of time 
    {   
        this->minutes = seconds / 60;   // adds amount of minutes
        seconds %= 60;  // adds remainder to seconds 
    }
    this->seconds = seconds;    // sets seconds
}

Clock::Clock(int days, int hours, int minutes, int seconds)
// 4-parameter constructor setting all data members 
{
    this->days = 0; 
    this->hours = 0; 
    this->minutes = 0;
    this->seconds = 0;

    // converts time to seconds 
    seconds += (minutes * 60) + (hours * 3600) + (days * 86400);
    
    if (abs(seconds) >= 86400)
    // checks if there is more than a day of time 
    {
        this->days = seconds / 86400;   // adds amount of days 
        seconds %=86400;    // adds remainder to seconds 
    } 
    if (abs(seconds) >= 3600)
    // checks if there is more than one hour
    {
        this->hours = seconds / 3600;   // adds amount of hours 
        seconds %= 3600;    // adds remainder to seconds 
    }
    if (abs(seconds) >= 60)
    // checks if there is more than one minute 
    {   
        this->minutes = seconds / 60;   // adds amount of minutes 
        seconds %= 60;  // adds remainder to seconds 
    }
    this->seconds = seconds;    // sets seconds 
}

void Clock::setDays(int days)
// setter for days 
{
    *this = Clock(days, hours, minutes, seconds); 
}

void Clock::setHours(int hours)
// setter for hours
{
    *this = Clock(days, hours, minutes, seconds); 
}

void Clock::setMinutes(int minutes)
// setter for minutes
{
    *this = Clock(days, hours, minutes, seconds); 
}
void Clock::setSeconds(int seconds)
// setter for seconds 
{
    *this = Clock(days, hours, minutes, seconds); 
}

int Clock::getDays() const 
// getter for days 
{
    return days; 
}

int Clock::getHours() const 
// getter for hours 
{
    return hours; 
}

int Clock::getMinutes() const 
// getter for minutes
{
    return minutes; 
}

int Clock::getSeconds() const 
// getter for seconds 
{
    return seconds; 
}

void Clock::Reset()
// sets all data members to 0 (reset clock)
{
    days = 0;
    hours = 0;
    minutes = 0;
    seconds = 0;
}

Clock operator+(const Clock& c1, const Clock& c2) 
// addition operator overload - returns addition of each time value in 4-parameter constructor
{ 
    return Clock(c1.days+c2.days, c1.hours+c2.hours, c1.minutes+c2.minutes, c1.seconds+c2.seconds);
}

Clock operator-(const Clock& c1, const Clock& c2)
// subtraction operator overload - returns subtraction of each time value in 4-parameter constructor
{
    return Clock(c1.days-c2.days, c1.hours-c2.hours, c1.minutes-c2.minutes, c1.seconds-c2.seconds);
}

bool operator==(const Clock& c1, const Clock& c2)
// comparision operator overload returning true if both clocks are equal 
{
    if ((c1.days == c2.days) && (c1.hours == c2.hours) && 
       (c1.minutes == c2.minutes) && (c1.seconds == c2.seconds))
        return true; 
    else 
        return false; 
}

bool operator<(const Clock& c1, const Clock& c2)
// comparison operator overload returning true if first clock is < than second 
{
    int seconds1 = c1.seconds + (c1.minutes * 60) + (c1.hours * 3600) + (c1.days * 86400);
    int seconds2 = c2.seconds + (c2.minutes * 60) + (c2.hours * 3600) + (c2.days * 86400);
    if (seconds1 < seconds2)
        return true; 
    else 
        return false; 
}

bool operator>(const Clock& c1, const Clock& c2)
// comparison operator overload returning true if first clock is > than second 
{
    int seconds1 = c1.seconds + (c1.minutes * 60) + (c1.hours * 3600) + (c1.days * 86400);
    int seconds2 = c2.seconds + (c2.minutes * 60) + (c2.hours * 3600) + (c2.days * 86400);
    if (seconds1 > seconds2)
        return true; 
    else 
        return false; 
}

ostream& operator<<(ostream& o, const Clock& c)
// operator overload allowing user to print clock w/ insertion operator
{
    o.fill('0');
    o.setf(ios::right);
    o << setw(2) << c.days << ':';
    o << setw(2) << c.hours << ':';
    o << setw(2) << c.minutes << ':';
    o << setw(2) << c.seconds;  
    return o; 
}

Clock Clock::operator-()
// negation operator overload returning constructor with negative parameters
{
    return Clock(-1*days, -1*hours, -1*minutes, -1*seconds);
}


