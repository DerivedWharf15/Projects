#include <iostream>
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()
#include <limits>  // For numeric_limits<>

using namespace std;

int main()
{
    srand(time(0)); // Step 1 of generating a random number

    int min = 1;
    int max = 99;
    int guess = 0;
    bool continueGuessing = true;
    int randomNumberInRange = min + (rand() % (max - min + 1)); // Step 2 of generating a random number and assigns it to a named variable

    cout << "Number guesser\n";
    cout << "A C++ program made by DerivedWharf15\n\n";
    cout << "Guess a number between 1 to 99\n";
    cout << "Remember to enter 0 to exit anytime\n";

    do
    {
        cout << ">> ";
        cin >> guess;

        if (guess == 0) // If the user wants to exit
        {
            cout << "\nThe number was "<< randomNumberInRange;
            cout << "\nExiting game. Thanks for playing!\n\n";
            continueGuessing = false;
        }
        else if (guess == randomNumberInRange) // If the user guessed correctly
        {
            cout << "\nYou guessed the number!\n\n";
            cout << "Thank you for playing this game\n\n";
            continueGuessing = false;
        }
        else if (cin.fail()) // If the user entered something else other than a number
        {
            cout << "\nYou have entered a non-number\n";
            cout << "Please enter a number between 1 to 99 in digits\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else if (guess > 99) // If they entered a number higher than 99
        {
            cout << "\nYour number is higher than 99\n";
            cout << "Enter a number between 1 to 99\n";
            cout << "And enter 0 to exit\n";
        }
        else if (guess < 0) // If they entered a number lower than 0
        {
            cout << "\nYour number is lower than 0\n";
            cout << "Enter a number between 1 to 99\n";
            cout << "And enter 0 to exit\n";
        }
        else if (guess > randomNumberInRange) // If the user guessed too high
        {
            cout << "\nToo high, guess lower\n";
        }
        else if (guess < randomNumberInRange) // If the user guessed too low
        {
            cout << "\nToo low, guess higher\n";
        }
    }
    while (continueGuessing);


    return 0;
}