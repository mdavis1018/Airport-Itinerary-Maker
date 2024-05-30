/*****************************************
** File:    Route.cpp
** Description: This file implements the route functions in Route.h that allow us to maniupulate airplane routes
***********************************************/

#include "Route.h"
using namespace std;

// Name: Route() - Default Constructor
// Desc: Used to build a new Route (linked list) make up of airports
// Preconditions: None
// Postconditions: Creates a new Route where m_head and m_tail
//   point to nullptr and size = 0
Route::Route() : m_head(nullptr), m_tail(nullptr), m_size(0) {}

// Name: SetName(string)
// Desc: Sets the name of the route (usually first
//   airport to last airport)
// Preconditions: None
// Postconditions: Sets name of route
void Route::SetName(string name)
{
  m_name = name;
}

// Name: ~Route() - Destructor
// Desc: Used to destruct a strand of Route
// Preconditions: There is an existing Route strand with at least
//   one airport
// Postconditions: Route is deallocated (including all
//   dynamically allocated airports) to have no memory leaks!
Route::~Route()
{
  Airport *current = m_head; // head of the linked list
  while (current != nullptr)
  {
    Airport *next = current->GetNext(); // getting next node
    delete current;                     // delete current node
    current = next;
  }
  m_head = nullptr;
  m_tail = nullptr;
  m_size = 0;
}

// Name: InsertEnd (string, string, double double)
// Desc: Creates a new airport using the data passed to it.
//   Inserts the new airport at the end of the route
// Preconditions: Takes in a Airport
// Requires a Route
// Postconditions: Adds the new airport to the end of a route
void Route::InsertEnd(string code, string name, string city, string country, double north, double west)
{
  Airport *newAirport = new Airport(code, name, city, country, north, west);
  newAirport->SetNext(nullptr);

  if (m_head == nullptr) // check if the list is empty
  {
    m_head = m_tail = newAirport; // list is empty, newAirport is both the head and tail
  }
  else
  {
    // If the list is not empty, attach the newAirport to the end of the list and update the tail.
    m_tail->SetNext(newAirport);
    m_tail = newAirport;
  }
  m_size++;
}

// Name: RemoveAirport(int index)
// Desc: Removes a airport from the route at the index provided
//   Hint: Special cases (first airport, last airport, middle airport)
// Preconditions: Index must be less than the size of the route
//   Cannot make route less than two airports. If the route has
//   two or fewer airports, fails.
// Postconditions: Name may be updated. Size is reduced.
//   Route has one less airport.
void Route::RemoveAirport(int index)
{
  // checking for invalid input
  if (index < 0 || index >= m_size)
  {
    cout << "Invalid index." << endl;
    return;
  }

  Airport *current = m_head;
  Airport *prev = nullptr; // initialize previous pointer to null
  for (int i = 0; i < index; ++i)
  {
    prev = current; // keep track of the previous node
    current = current->GetNext();
  }
  // case where node to be removed is the first node
  if (prev == nullptr)
  {
    m_head = current->GetNext();
  }
  else
  {
    // For nodes in the middle or the end, bypass the current node by linking prev to current's next
    prev->SetNext(current->GetNext());
  }
  // case where node to be removed is the last node
  if (current == m_tail)
  {
    m_tail = prev;
  }
  delete current; // Free the memory occupied by the node being removed

  m_size--;
}

// Name: GetName()
// Desc: Returns the name of the route (Usually starting airport to last airport For example: Baltimore to Boston
// Preconditions: Requires a Route
// Postconditions: Returns m_name;
string Route::GetName()
{
  return m_name;
}

// Name: UpdateName()
// Desc: Updates m_name based on the name of the first airport in the route and the last airport in the route For example: Baltimore to Boston
// Preconditions: Requires a Route with at least two airports
// Postconditions: Returns m_name;
string Route::UpdateName()
{
  if (m_head != nullptr && m_tail != nullptr)
  {
    // route's name is first airport to last airport
    m_name = m_head->GetName() + " to " + m_tail->GetName();
  }
  return m_name;
}

// Name: GetSize()
// Desc: Returns the number of airports in a route
// Preconditions: Requires a Route
// Postconditions: Returns m_size;
int Route::GetSize()
{
  return m_size;
}

// Name: ReverseRoute
// Desc: Reverses a route
// Preconditions: Reverses the Route
// Postconditions: Route is reversed in place; nothing returned
void Route::ReverseRoute()
{
  Airport *prev = nullptr;
  Airport *current = m_head;
  Airport *next = nullptr;
  m_tail = m_head; // After reversal, head becomes tail

  while (current != nullptr)
  {
    next = current->GetNext(); // Store next node
    current->SetNext(prev);    // Reverse current node's pointer
    prev = current;            // Move pointers one position ahead
    current = next;
  }
  m_head = prev; // After reversal, prev will be new head
}

// Name: GetData (int)
// Desc: Returns an airport at a specific index
// Preconditions: Requires a Route
// Postconditions: Returns the airport from specific item
Airport *Route::GetData(int index)
{
  if (index < 0 || index >= m_size)
  {
    return nullptr; // If the index is out of bounds, return nullptr to indicate an invalid request.
  }

  Airport *temp = m_head; // Start from the head of the list.

  for (int i = 0; i < index; i++)
  {
    temp = temp->GetNext();
  }
  return temp;
}

// Name: DisplayRoute
// Desc: Displays all of the airports in a route
// Preconditions: Requires a Route
// Postconditions: Displays all of the airports in a route
// Formatted: Baltimore, Maryland (N39.209 W76.517)
void Route::DisplayRoute()
{
  int counter = 1; // Initialize a counter to number each Airport in the output.

  Airport *current = m_head;

  while (current != nullptr)
  {
    // Basic null check to ensure current points to a valid Airport object
    if (current != nullptr)
    {
      cout << counter << ". " << current->GetCode() << ", " << current->GetName()
           << ", " << current->GetCity() << ", " << current->GetCountry()
           << " ("
           << "N:" << current->GetNorth() << " "
           << "W:" << current->GetWest() << ")" << endl;
    }
    else
    {
      cout << "Encountered a nullptr in the route." << endl;
    }

    current = current->GetNext(); // Move to the next Airport in the list.
    counter++;
  }
}
