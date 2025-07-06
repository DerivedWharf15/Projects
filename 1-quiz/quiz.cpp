#include <iostream>
#include <string>

using namespace std;

int main()
{
    string response;

    cout << "Math questions" << '\n';
    cout << "DerivedWharf15's first program" << '\n';

    cout << ">>";
    cin >> response;
    cout << endl;

    while (response == 'yes')
    {
        cout << "What is 538 + 846" << endl;
        cout << "Do you want to continue?" << endl;
        cin >> response;
        cout << endl;
    }

    cout << "Program ended. Goodbye!" << endl;

    return 0;
}