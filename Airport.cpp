/*****************************************
** File:    Route.cpp
** Description: This file implements the basic getter/setter functions for the Airplane class
***********************************************/

#include "Airport.h"
using namespace std;

// Name: Airport() - Default Constructor
// Desc: Used to build a new empty airport
// Preconditions: None
// Postconditions: Creates a new Airport for use in a Route
Airport::Airport()
{
  m_code = "";      // Airport code (three letters)
  m_name = "";      // Name of airport
  m_city = "";      // City of airport
  m_country = "";   // Country of airport
  m_north = 0.0;    // North of airport
  m_west = 0.0;     // West of airport
  m_next = nullptr; // Airport pointer to next airport
}
// Name: Airport(string, string, string, string, double, double)
// Overloaded Constructor
// Desc: Used to build a new Airport passing it a
//   airport code, name, city, country, north, and west
// Preconditions: None
// Postconditions: Creates a new airport for use in a Route
Airport::Airport(string code, string name, string city, string country, double north, double west)
    : m_code(code), m_name(name), m_city(city), m_country(country), m_north(north), m_west(west)
{
}

// Name: ~Airport() - Destructor
// Desc: Used to destruct a airport
//**This function should be empty but must be implemented
// Preconditions: There is an existing airport
// Postconditions: Airport is deallocated and has no memory leaks!
Airport::~Airport()
{
}

// Name: GetCode()
// Desc: Returns the three letter code of the airport
// Preconditions: None
// Postconditions: Returns the three letter code of the airport
string Airport::GetCode()
{
  return m_code;
}

// Name: GetName()
// Desc: Returns the name of the airport
// Preconditions: None
// Postconditions: Returns the name of the airport
string Airport::GetName()
{
  return m_name;
}

// Name: GetNext()
// Desc: Returns the pointer to the next airport
// Preconditions: None (may return either airport or nullptr)
// Postconditions: Returns m_next;
Airport *Airport::GetNext()
{
  return m_next;
}

// Name: GetNorth()
// Desc: Returns the northern coordinates of the airport
// Preconditions: None
// Postconditions: Returns the N coordinates of the port
double Airport::GetNorth()
{
  return m_north;
}

// Name: GetWest()
// Desc: Returns the western coordinates of the airport
// Preconditions: None
// Postconditions: Returns the W coordinates of the airport
double Airport::GetWest()
{
  return m_west;
}

// Name: GetCity()
// Desc: Returns the city of where the airport is located
// Preconditions: None
// Postconditions: Returns the city of where the airport is located
string Airport::GetCity()
{
  return m_city;
}

// Name: GetCountry()
// Desc: Returns the country of where the airport is located
// Preconditions: None
// Postconditions: Returns the country of where the airport is located
string Airport::GetCountry()
{
  return m_country;
}

// Name: SetNext()
// Desc: Updates the pointer to a new target (either a airport or nullptr)
// Preconditions: None
// Postconditions: Sets the next airport
void Airport::SetNext(Airport *next)
{
  m_next = next;
}
