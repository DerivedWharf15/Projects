// This program is still in its prototype stage

#include <iostream>

using namespace std;

int main()
{
    char response;
    int answer1;
    int answer2;

    cout << "Math questions\n";
    cout << "DerivedWharf15's first C++ program\n\n";

    cout << "Do you want to start? (y or n)\n";
    cout << ">> ";
    cin >> response;

    if (response == 'y' || response == 'Y') // First question
    {
        cout << "\nQuestion 1:";
        cout << "\nWhat is 512 + 64?\n";
        cout << ">> ";
        cin >> answer1;
    }
    else
    {
        cout << "\nClosing program\n";
    }

    if (answer1 == 576) // Second question
    {
        cout << "\nCorrect\n";
        cout << "Question 2:\n";
        cout << "What is 1024 / 4?\n";
        cout << ">> ";
        cin >> answer2;
    }
    else
    {
        cout << "\nIncorrect\n";
        cout << "Question 2:\n";
        cout << "What is 1024 / 4?\n";
        cout << ">> ";
        cin >> answer2;
    }
    return 0;
}