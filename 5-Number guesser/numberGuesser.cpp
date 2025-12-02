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
    char response;
    int gameCount = 0;
    int guessCount = 0;
    bool correct = false;
    bool continueGuessing = true;
    int randomNumberInRange = min + (rand() % (max - min + 1)); // Step 2 of generating a random number and assigns it to a named variable

    cout << "Number guesser\n";
    cout << "A C++ program made by DerivedWharf15\n\n";
    cout << "Guess a number between 1 to 99\n";
    cout << "Remember to enter 0 to exit any time\n";

    do // Loop
    {
        cout << ">> ";
        cin >> guess;

        //-------------Every possible scenario-------------//

        if (cin.fail()) // If the user entered something else other than a number
        {
            cout << "\nYou have entered a non-number\n";
            cout << "Please enter a number between 1 to 99 in digits\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else if (guess == 0) // If the user wants to exit
        {
            cout << "\nThe number was "<< randomNumberInRange;
            cout << "\nThank you for playing this game\n\n";
            continueGuessing = false;
            guessCount++;
        }
        else if (guess == randomNumberInRange) // If the user guessed correctly
        {
            gameCount++;
            guessCount++;
            correct = true;
        }
        else if (guess > 99) // If they entered a number higher than 99
        {
            cout << "\nYour number is higher than 99\n";
            cout << "Enter a number between 1 to 99\n";
            cout << "And enter 0 to exit\n";
            guessCount++;
        }
        else if (guess < 0) // If they entered a number lower than 0
        {
            cout << "\nYour number is lower than 0\n";
            cout << "Enter a number between 1 to 99\n";
            cout << "And enter 0 to exit\n";
            guessCount++;
        }
        else if (guess > randomNumberInRange) // If the user guessed too high
        {
            cout << "\nToo high, guess lower\n";
            guessCount++;
        }
        else if (guess < randomNumberInRange) // If the user guessed too low
        {
            cout << "\nToo low, guess higher\n";
            guessCount++;
        }

        //-------------When the user wins-------------//

        if (guessCount == 1 && continueGuessing == true && correct == true) // If the user guessed the number on their first attempt
        {
            cout << "\nYou guessed it on your first try!\n";
            cout << "Congrats!\n\n";
        }
        else if (guessCount < 6 && continueGuessing == true && correct == true) // If the user guessed the number in under 6 attemtps
        {
            cout << "\nWhoah you only guessed " << guessCount << " times!";
            cout << "Congrats!\n\n";
        }
        else if (guessCount < 11 && continueGuessing == true && correct == true) // If the user guessed the number in under 11 attempts
        {
            cout << "\nYou guesssed the number!\n";
            cout << "You only guessed " << guessCount << " times\n\n";
        }
        else if (guessCount > 10 && continueGuessing == true && correct == true) // If the user guessed the number more than 10 attempts
        {
            cout << "\nYou guessed the number!\n";
            cout << "You guessed " << guessCount << " times\n\n";
        }

        if (continueGuessing == true && correct == true)
        {
            cout << "Would you like to guess another number? (y/n)\n"; // Promt the user if they want to guess again
            cout << "You played " << gameCount << " time(s)\n";
            cout << ">> ";
            cin >> response;
        }

        if (response == 'Y' || response == 'y' && continueGuessing == true && correct == true) // If the user wants to guess again
        {
            cout << "\nYou chose to guess again\n";
            cout << "Enter a number between 1 - 99\n";
            cout << "And enter 0 to exit any time\n";
            continueGuessing = true;
            guessCount = 0; // Set the guess counter back to 0
        }
        else if (response == 'N' || response == 'n' && continueGuessing == true && correct == true) // If the user wants to exit
        {
            cout << "\nThank you for playing this game\n\n";
            continueGuessing = false;
        }
        else if (continueGuessing == true && correct == true) // If the user enters neither y nor n
        {
            cout << "\nYou have entered neither y nor n, but closing program anyway\n";
            cout << "Thank you for playing this game\n\n";
            continueGuessing = false;
        }
        correct = false;
    }
    while (continueGuessing);

    return 0;
}
/* Latest additions:
    Guess count
    Games won count
    Win messages depending on number of attempts
    Replay option
*/
