#include <iostream>
#include <cmath>
#include <limits>    // For numeric limits
#include <string>    // For std::string
#include <algorithm> // For std::transform
#include <cctype>    // For std::tolower

using namespace std;

int main()
{
    double point1X;
    double point1Y;
    double point1Z;
    double point2X;
    double point2Y;
    double point2Z;
    double distance;
    bool continueCalculating = true;
    string userInput;

    point1X = 0;
    point1Y = 0;
    point1Z = 0;
    point2X = 0;
    point2Y = 0;

        cout << '\n' << "3D Coordinate Distance Calculator" << '\n';
        cout << "A C++ program made by DerivedWharf15" << '\n' << '\n';

    do // Loop to allow the program to be used multiple times
    {
        cout << "Enter the coordinates of two points, on X Y plane (numbers only)" << '\n';
        cout << "Example : 7 9 1 -4 3 2" << '\n';
        cout << ">> ";

        // Checks for valid user input
        while (!(cin >> point1X >> point1Y >> point1Z >> point2X >> point2Y >> point2Z))
        {
            cout << '\n' << "Invalid input. Please enter numbers only." << '\n';
            cout << "Example : 7 9 1 -4 3 2" << '\n';
            cin.clear(); // Clear the error flags
            // Discard invalid input from the buffer
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << ">> ";
        }
        cout << '\n';

        // Calculate the distance
        distance = sqrt(pow(point2X - point1X, 2) + pow(point2Y - point1Y, 2) + pow(point2Z - point1Z, 2));

        cout << "The distance between the coordinates " << point1X << " " << point1Y << point1Z << " and " << point2X << " " << point2Y << point2Z << " is " << distance << '\n' << '\n';
        cout << "Do you want to calculate another distance? (yes/no) >> ";
        cin >> userInput;
        cout << '\n';

        // Converts user input to lowercase
        transform(userInput.begin(), userInput.end(), userInput.begin(), ::tolower);

        // Checks user's input to loop
        if (userInput == "yes" || userInput == "y")
        {
            continueCalculating = true;
        }
        else
        {
            continueCalculating = false;
        }
    }
    while (continueCalculating);

    cout << "Thank you for using this program" << '\n' << '\n';
}