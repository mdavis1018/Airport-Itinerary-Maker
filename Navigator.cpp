/*****************************************
** File:    Route.cpp
** Description: This file implements the navigator class functions and displays the main menu to the user
***********************************************/

#include "Navigator.h"
using namespace std;
#include <fstream>
#include <iostream>
#include <sstream>

// Name: Navigator (string) - Overloaded Constructor
// Desc: Creates a navigator object to manage routes
// Preconditions:  Provided with a filename of airports to load
// Postconditions: m_filename is populated with fileName
Navigator::Navigator(string fileName) : m_fileName(fileName)
{
}

// Name: Navigator (destructor)
// Desc: Deallocates all dynamic aspects of a Navigator
// Preconditions: There is an existing Navigator
// Postconditions: All airports and routes are cleared
Navigator::~Navigator()
{
  // Delete all dynamically allocated Airport objects
  for (size_t i = 0; i < m_airports.size(); i++)
  {
    delete m_airports[i]; // Delete the dynamically allocated Airport object
  }
  m_airports.clear(); // Clear the vector after deleting all Airport objects
  cout << "Deleting Airports" << endl;
  // Delete all dynamically allocated Route objects
  for (size_t i = 0; i < m_routes.size(); i++)
  {
    delete m_routes[i]; // Delete the dynamically allocated Route object
  }
  m_routes.clear(); // Clear the vector after deleting all Route objects
  cout << "Deleting Routes" << endl;
}

// Name: ReadFile
// Desc: Reads in a file that has data about each airport
//   including code, name, city, country, degrees north and degrees west.
//   Dynamically allocates airports and stores them in m_airports
//   The vector can hold many airports.
// Preconditions: Valid file name of airports
// Postconditions: Dynamically allocates each airport
//   and enters it into m_airports
void Navigator::ReadFile()
{
  ifstream file(m_fileName);
  if (!file.is_open()) // file failed to open
  {
    cerr << "Unable to open file: " << m_fileName << endl;
    return; // Return if the file cannot be opened
  }

  cout << "Opened File" << endl;
  string line; // used to store each line read from the file
  while (getline(file, line))
  {
    if (line.empty())
    {
      cout << "Encountered an empty line, stopping file reading." << endl;
      return; // exit function
    }

    // Parse the line to extract airport details using ',' as the delimiter.
    size_t pos = 0;                            // position in string to start searching for the next comma
    size_t end = line.find(',', pos);          // find the first comma in the line
    string code = line.substr(pos, end - pos); // extract airport code

    pos = end + 1;
    end = line.find(',', pos);
    string name = line.substr(pos, end - pos);

    pos = end + 1;
    end = line.find(',', pos);
    string city = line.substr(pos, end - pos);

    pos = end + 1;
    end = line.find(',', pos);
    string country = line.substr(pos, end - pos);

    pos = end + 1;
    end = line.find(',', pos);
    string tempNorth = line.substr(pos, end - pos);
    double north = stod(tempNorth); // Direct conversion, handles negative

    pos = end + 1;
    string tempWest = line.substr(pos); // No need to find next comma, it's the rest of the string
    double west = stod(tempWest);       // Direct conversion, handles negative

    // Create a new Airport object with the parsed data.
    Airport *newAirport = new Airport(code, name, city, country, north, west);
    m_airports.push_back(newAirport); // add newly created Airport object to the vector of airports
  }

  file.close();                                             // Close the file after reading its contents
  cout << "Airports loaded: " << m_airports.size() << endl; // report the number of airports loaded
}

// Name: DisplayAirports
// Desc: Displays each airport in m_airports
// Preconditions: At least one airport is in m_airports
// Postconditions: Displays all airports.
//  Uses overloaded << provided in Airport.h
void Navigator::DisplayAirports()
{
  for (size_t i = 0; i < m_airports.size(); i++)
  {
    cout << i + 1 << "." << *(m_airports[i]) << endl;
  }
}

// Name: InsertNewRoute
// Desc: Dynamically allocates a new route with the user selecting each airport in the route. Each route can have a minimum of two
//   airports. Will not allow a one airport route.
//   Checks for min of two valid airports (1-40)
//   Route named using Route's UpdateName.
//   For example, Baltimore to Boston
//   Once route is created, inserted into m_routes.
// Preconditions: Populated m_routes
// Postconditions: Inserts a new route into m_routes
void Navigator::InsertNewRoute()
{
  // Display all available airports for selection
  DisplayAirports();

  // Dynamically allocate a new Route object on the heap
  Route *newRoute = new Route();

  string startCityName, endCityName; // Strings to hold the names of the first and last cities added to the route

  int airportIndex; // Variable to hold the user's choice of airport index

  int airportsAdded = 0;
  bool addingAirports = true;

  while (addingAirports)
  {
    cout << "Enter the number of the airport to add to your Route: (-1 to end)" << endl;
    cin >> airportIndex;

    // Check if the user wants to end the airport addition process
    if (airportIndex == -1)
    {
      // Ensure that at least two airports have been added to form a valid route
      if (airportsAdded < 2)
      {
        cout << "You must add at least two airports to the route. Please continue adding airports." << endl;
      }
      else
      {
        // Valid route created, stop the loop by setting the flag to false
        addingAirports = false;
      }
    }
    else if (airportIndex > 0 && airportIndex <= static_cast<int>(m_airports.size()))
    {
      // The user has entered a valid airport index; proceed to add the selected airport to the route
      Airport *selectedAirport = m_airports[airportIndex - 1];
      newRoute->InsertEnd(selectedAirport->GetCode(), selectedAirport->GetName(), selectedAirport->GetCity(), selectedAirport->GetCountry(), selectedAirport->GetNorth(), selectedAirport->GetWest());
      airportsAdded++; // Increment the counter for added airports

      if (airportsAdded == 1)
      {
        startCityName = selectedAirport->GetCity(); // Set the start city name
      }
      endCityName = selectedAirport->GetCity(); // Always update the end city name to the last one added
    }
    else
    {
      // The user has entered an invalid index, prompt them to try again
      cout << "Invalid airport number, " << airportIndex << " is out of range, try again." << endl;
    }
  }

  if (airportsAdded >= 2)
  {
    // Set the route's name based on the first and last cities added
    newRoute->SetName(startCityName + " to " + endCityName);
    // Add the newly created route to the vector of routes in the Navigator
    m_routes.push_back(newRoute);
    cout << "Done Building a New Route named: " << newRoute->GetName() << endl;
  }
  else
  {
    // If the route does not have enough airports, delete the dynamically allocated route and inform the user
    delete newRoute;
    cout << "Route creation cancelled. Not enough airports added." << endl;
  }
}

// Name: DisplayRoute
// Desc: Using ChooseRoute, displays a numbered list of all routes.
//    If no routes, indicates that there are no routes to display
//    User selects a route from list to display
//    Displays numbered list of each airport in route
//    Displays total miles of a route using RouteDistance
// Preconditions: Routes has more than one airport
// Postconditions: Displays all airports in a route and
//    the total miles of the route
void Navigator::DisplayRoute()
{
  // Check if there are routes to display
  if (m_routes.empty())
  {
    cout << "There are no routes to display." << endl;
    return;
  }
  int index = ChooseRoute();
  // Validate the chosen index
  if (index >= 0 && index < static_cast<int>(m_routes.size()))
  {
    // Display the chosen route
    cout << "Displaying Route: " << m_routes[index]->GetName() << endl;
    m_routes[index]->DisplayRoute(); // Call DisplayRoute on the Route object

    // Calculate and display the total distance of the route using the RouteDistance method.
    cout << "The total miles of this route is " << RouteDistance(m_routes[index]) << " miles" << endl;
  }
  else
  {
    cout << "No route selected or invalid choice." << endl;
  }
}

// Name: RouteDistance
// Desc: Calculates the total distance of a route
// Goes from airport 1 to airport 2 then airport 2 to airport 3
//  and repeats for length of route.
//  Calculates the distance using CalcDistance (provided)
//  Aggregates the total and returns the total in miles
// Preconditions: Populated route with more than one airport
// Postconditions: Returns the total miles between all airports in a route
double Navigator::RouteDistance(Route *route)
{
  double totalDistance = 0.0; // Initialize total distance to zero.

  // Check if the route pointer is null or if the route has fewer than 2 airports.
  // A valid route for distance calculation requires at least two airports.
  if (route == nullptr || route->GetSize() < 2)
  {
    return totalDistance; // Return 0.0 if the route is invalid for distance calculation.
  }

  // Iterate over each pair of consecutive airports in the route to calculate the total distance.
  for (int i = 0; i < route->GetSize() - 1; i++)
  {
    // Retrieve the current airport and the next airport in the route for distance calculation.
    Airport *currentAirport = route->GetData(i);
    Airport *nextAirport = route->GetData(i + 1);

    // Calculate the distance between the current airport and the next airport using their geographic coordinates.
    // The CalcDistance method is assumed to calculate the distance based on latitude (north) and longitude (west).
    double distance = CalcDistance(currentAirport->GetNorth(), currentAirport->GetWest(),
                                   nextAirport->GetNorth(), nextAirport->GetWest());

    // Add the calculated distance to the total distance of the route.
    totalDistance += distance;
  }

  // After iterating through all pairs of airports, return the total distance of the route.
  return totalDistance;
}

// Name: ChooseRoute
// Desc: Allows user to choose a specific route to work with
//   by displaying numbered list
// Preconditions: Populated m_routes
// Postconditions: Returns the index of the selected route minus 1
int Navigator::ChooseRoute()
{
  if (m_routes.empty())
  {
    cout << "No routes available." << endl;
    return -1; // Return an invalid index if no routes are available
  }

  int choice = -1;
  bool validChoice = false; // Bool flag to control the loop

  while (!validChoice)
  {
    cout << "Choose a route:" << endl;
    for (size_t i = 0; i < m_routes.size(); i++)
    {
      // Display each route's name.
      cout << i + 1 << ": " << m_routes[i]->GetName() << endl;
    }
    cout << "Which route would you like to use?" << endl;
    cin >> choice;

    // Validate the choice is within the range of available routes.
    if (choice < 1 || choice > static_cast<int>(m_routes.size()))
    {
      cout << "Invalid choice, please enter a number between 1 and " << m_routes.size() << ". Try again." << endl;
      // validChoice remains false, so the loop continues
    }
    else
    {
      validChoice = true; // A valid choice was made, so update the flag to exit the loop
    }
  }
  return choice - 1; // Adjust for 0-based indexing before returning
}

// Name: RemoveAirportFromRoute()
// Desc: Using ChooseRoute, displays a numbered list of all routes. User selects one of the routes to remove an airport from. Displays a numbered list of all airports in selected route. User selects airport to remove from list. Each route has a minimum of two airports (will not allow). Removes airport from route if more than two. If first or last airport removed, updates name of route using UpdateName
// Preconditions: Route has more than one airport
// Postconditions: Displays updated route with removed airport and new name
// Removes an airport from a user-selected route.
void Navigator::RemoveAirportFromRoute()
{
  // Check if there are any routes to remove airports from
  if (m_routes.empty())
  {
    cout << "No routes to remove airports" << endl;
    return; // Early return if there are no routes
  }

  // user chooses a route from the list
  int routeIndex = ChooseRoute();
  // Validate the chosen route index
  if (routeIndex < 0 || routeIndex >= static_cast<int>(m_routes.size()))
  {
    cout << "Invalid route selection." << endl;
    return; // Return early if the selection is invalid
  }

  Route *selectedRoute = m_routes[routeIndex]; // Access the selected route

  // Prevent removal if the route has two or fewer airports (minimum required for a valid route)
  if (selectedRoute->GetSize() <= 2)
  {
    cout << "Cannot remove an airport if there are two or fewer airports in the route." << endl;
    return;
  }

  // Display the selected route's name to confirm to the user their selection
  cout << selectedRoute->GetName() << endl;

  // Display airports in the selected route as a numbered list for the user to choose from
  selectedRoute->DisplayRoute();

  int airportIndex = -1;    // Variable to store the user's choice of airport index
  bool validChoice = false; // Bool flag to determine if a valid choice has been made

  // Loop until a valid airport index is chosen by the user
  while (!validChoice)
  {
    cout << "Which airport would you like to remove? (Enter number): ";
    cin >> airportIndex;
    airportIndex -= 1; // Adjust the user's input for 0-based indexing

    // Validate the chosen airport index
    if (airportIndex >= 0 && airportIndex < selectedRoute->GetSize())
    {
      selectedRoute->RemoveAirport(airportIndex); // Remove the chosen airport from the route

      // Update the route's name based on the first and last airports remaining in the route
      Airport *firstAirport = selectedRoute->GetData(0);                           // Get the first airport
      Airport *lastAirport = selectedRoute->GetData(selectedRoute->GetSize() - 1); // Get the last airport
      if (firstAirport && lastAirport)                                             // Check if both airports exist
      {
        // Create a new name based on the cities of the first and last airports
        string newRouteName = firstAirport->GetCity() + " to " + lastAirport->GetCity();
        selectedRoute->SetName(newRouteName); // Update the route's name
      }

      selectedRoute->DisplayRoute(); // Display the updated route
      cout << "Route named " << selectedRoute->GetName() << " updated" << endl;
      validChoice = true; // Mark that a valid choice has been made, breaking the loop
    }
    else
    {
      cout << "Invalid airport selection. Please try again." << endl;
    }
  }
}

// Name: ReverseRoute
// Desc: Using ChooseRoute, users chooses route and the route is reversed
//   If no routes in m_routes, indicates no routes available to reverse
//   Updates route name using UpdateName
//   For example, Baltimore to Boston becomes Boston to Baltimore
// Preconditions: Populated m_routes
// Postconditions: Reverses a specific route by reversing the airports
//   in place. Must move airports, cannot just change data in airports.
// Reverses the order of airports in a user-selected route.
void Navigator::ReverseRoute()
{
  if (m_routes.empty())
  {
    cout << "No routes to reverse." << endl;
    return; // Exit the function if there are no routes.
  }

  // Prompt the user to select a route from the list of available routes.
  int index = ChooseRoute();
  // Validate the user's selection.
  if (index < 0 || index >= static_cast<int>(m_routes.size()))
  {
    cout << "Invalid route selection." << endl;
    return;
  }

  // Call the ReverseRoute method on the selected Route object to reverse its order.
  m_routes[index]->ReverseRoute();

  // After reversing, check if the route has at least one airport to safely update its name.
  if (m_routes[index]->GetSize() > 0)
  {
    // Retrieve the first and last airports in the reversed route.
    Airport *firstAirport = m_routes[index]->GetData(0);                             // The new first airport after reversal.
    Airport *lastAirport = m_routes[index]->GetData(m_routes[index]->GetSize() - 1); // The new last airport.

    // Ensure both airports are valid (not null) before proceeding.
    if (firstAirport && lastAirport)
    {
      // Construct a new route name using the cities of the first and last airports.
      string newRouteName = firstAirport->GetCity() + " to " + lastAirport->GetCity();
      m_routes[index]->SetName(newRouteName); // Update the route's name with the new name.
    }
  }

  // Retrieve and display the updated name of the reversed route.
  string newRouteName = m_routes[index]->GetName();
  cout << "Done reversing route: " << newRouteName << endl;

  // display the details of the reversed route to the user.
  m_routes[index]->DisplayRoute();
}

// Name: MainMenu
// Desc: Displays the main menu and manages exiting
// Preconditions: Populated m_airports
// Postconditions: Exits when someone chooses 5
void Navigator::MainMenu()
{
  int choice = 0; // sets user choice to invalid choice
  do
  {
    cout << "What would you like to do?:" << endl;
    cout << "1. Create new route" << endl;
    cout << "2. Display Route" << endl;
    cout << "3. Remove airport from route" << endl;
    cout << "4. Reverse Route" << endl;
    cout << "5. Exit" << endl;
    cin >> choice;

    switch (choice)
    {
    case 1:
      InsertNewRoute();
      break;
    case 2:
      DisplayRoute();
      break;
    case 3:
      RemoveAirportFromRoute();
      break;
    case 4:
      ReverseRoute();
      break;
    case 5:
      // Exit
      cout << "Exiting." << endl;
      break;
    default:
      cout << "Invalid choice, please enter a number between 1-5." << endl;
      break;
    }
  } while (choice != 5); // Repeat until the user chooses to exit
}

// Name: Start
// Desc: Loads the file and calls the main menu
// Preconditions: m_fileName is populated
// Postconditions: All ports are loaded and the main menu runs
void Navigator::Start()
{
  if (m_fileName.empty())
  {
    cout << "File name not found, exiting..." << endl;
  }
  // If m_fileName is populated, proceed with reading the file and displaying the main menu
  ReadFile();
  MainMenu();
}
