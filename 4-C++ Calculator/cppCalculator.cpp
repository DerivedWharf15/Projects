#include <iostream>
#include <string> 
#include <vector>    // Required for dynamic arrays (vectors)
#include <sstream>   // Required for string stream operations (though not directly used in final version, good for parsing)
#include <limits>    // Required for numeric_limits (for input validation)
#include <algorithm> // Required for std::transform (to convert to lowercase)
#include <cctype>    // Required for ::isspace, ::isdigit (character classification)
#include <stdexcept> // Required for runtime_error, out_of_range

using namespace std;

// Function to check if a character is one of the basic arithmetic operators (+, -, *, /)
bool isOperator(char c)
{
    return c == '+' || c == '-' || c == '*' || c == '/';
}

// Helper function to check if a character is an opening parenthesis
bool isOpeningParenthesis(char c)
{
    return c == '(' || c == '[' || c == '{';
}

// Helper function to check if a character is a closing parenthesis
bool isClosingParenthesis(char c)
{
    return c == ')' || c == ']' || c == '}';
}

// Helper function to get the matching opening parenthesis for a given closing parenthesis
char getMatchingOpeningParenthesis(char closingParen)
{
    if (closingParen == ')') return '(';
    if (closingParen == ']') return '[';
    if (closingParen == '}') return '{';
    return '\0'; // Should not happen if called with a valid closing parenthesis
}

// Function to determine the precedence of an operator
// Higher numbers mean higher precedence (e.g., * and / have higher precedence than + and -)
int getPrecedence(char op)
{
    if (op == '+' || op == '-') return 1; // Addition and Subtraction have lower precedence
    if (op == '*' || op == '/') return 2; // Multiplication and Division have higher precedence
    return 0; // For any character that is not a recognized operator
}

// Function to perform a single arithmetic operation
double performOperation(double a, double b, char op)
{
    switch (op)
    {
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '*':
            return a * b;
        case '/':
            // Check for division by zero to prevent errors
            if (b == 0)
            {
                throw runtime_error("Division by zero!"); // Throw an error if dividing by zero
            }
            return a / b;
        default:
            // This case should ideally not be reached if only valid operators are passed
            throw runtime_error("Unknown operator encountered during calculation.");
    }
}

// Core function to evaluate a mathematical expression string
// This function implements a simplified version of the Shunting-Yard algorithm
// to handle operator precedence and parentheses.
double evaluateExpression(const string& expression)
{
    vector<double> numbers;   // Stack to store numbers (operands)
    vector<char> operators;   // Stack to store operators and parentheses

    string currentToken;      // Temporary string to build numbers from characters

    // First, create a cleaned version of the expression by removing all spaces
    string cleanedExpression;
    for (char c : expression)
    {
        if (!isspace(c)) // If the character is not a space
        {
            cleanedExpression += c; // Add it to the cleaned expression
        }
    }

    // Iterate through each character of the cleaned expression
    for (int i = 0; i < cleanedExpression.length(); ++i)
    {
        char c = cleanedExpression[i];

        // If the character is a digit or a decimal point, it's part of a number
        if (isdigit(c) || c == '.')
        {
            currentToken += c; // Append the character to the current number string
        }
        // If the character is an opening parenthesis
        else if (isOpeningParenthesis(c))
        {
            // If we have accumulated a number before an opening parenthesis (e.g., "5(2+3)"),
            // this implies multiplication. For simplicity, we will require explicit multiplication.
            // If currentToken is not empty, it means a number was just parsed.
            // If an opening parenthesis follows, it's an error unless an operator is between them.
            if (!currentToken.empty()) {
                throw runtime_error("Malformed expression: Missing operator before opening parenthesis.");
            }
            operators.push_back(c); // Push the opening parenthesis onto the operators stack
        }
        // If the character is a closing parenthesis
        else if (isClosingParenthesis(c))
        {
            // If we have accumulated a number, push it to the numbers stack
            if (!currentToken.empty())
            {
                numbers.push_back(stod(currentToken));
                currentToken = "";
            }

            // Pop operators from the stack and perform operations until the matching opening parenthesis is found
            char matchingOpeningParen = getMatchingOpeningParenthesis(c);
            bool foundMatchingParen = false;
            while (!operators.empty() && operators.back() != matchingOpeningParen)
            {
                // Ensure there are enough numbers for the operation
                if (numbers.size() < 2)
                {
                    throw runtime_error("Malformed expression: Not enough numbers for an operation inside parentheses.");
                }
                // Pop the last two numbers and the last operator
                double b = numbers.back(); numbers.pop_back();
                double a = numbers.back(); numbers.pop_back();
                char op = operators.back(); operators.pop_back();
                // Perform the operation and push the result back onto the numbers stack
                numbers.push_back(performOperation(a, b, op));
            }

            // After the loop, if the stack is empty or the top is not the matching opening parenthesis, it's an error
            if (operators.empty() || operators.back() != matchingOpeningParen)
            {
                throw runtime_error("Mismatched parentheses or invalid expression.");
            }
            operators.pop_back(); // Pop the matching opening parenthesis from the stack
        }
        // If the character is an arithmetic operator (+, -, *, /)
        else if (isOperator(c))
        {
            // If we have accumulated a number, push it to the numbers stack
            if (!currentToken.empty())
            {
                numbers.push_back(stod(currentToken));
                currentToken = "";
            }

            // Special handling for unary minus (e.g., "-5" or "4*-5")
            // If '-' is at the beginning of the expression, or immediately after another operator or opening parenthesis,
            // it's considered part of the next number (making it negative).
            if (c == '-' && (i == 0 || isOperator(cleanedExpression[i-1]) || isOpeningParenthesis(cleanedExpression[i-1])))
            {
                currentToken += c; // Start building a negative number string
                continue; // Continue to the next character to get the digits of the negative number
            }

            // Process operators on the stack based on precedence
            // While there are operators on the stack AND the top operator is NOT an opening parenthesis AND
            // the top operator has higher or equal precedence to the current operator, perform the operation.
            while (!operators.empty() && !isOpeningParenthesis(operators.back()) && getPrecedence(operators.back()) >= getPrecedence(c))
            {
                // Ensure there are enough numbers for the operation
                if (numbers.size() < 2)
                {
                    throw runtime_error("Malformed expression: Not enough numbers for an operation.");
                }
                // Pop the last two numbers and the last operator
                double b = numbers.back(); numbers.pop_back();
                double a = numbers.back(); numbers.pop_back();
                char op = operators.back(); operators.pop_back();
                // Perform the operation and push the result back onto the numbers stack
                numbers.push_back(performOperation(a, b, op));
            }
            // Push the current operator onto the operators stack
            operators.push_back(c);
        }
        else
        {
            // If an unrecognized character is found, throw an error
            throw runtime_error("Invalid character in expression: '" + string(1, c) + "'");
        }
    }

    // After parsing all characters, if there's a number left in currentToken, push it
    if (!currentToken.empty())
    {
        numbers.push_back(stod(currentToken));
    }

    // Evaluate any remaining operators in the stack
    // (These will be lower precedence operators like + or - that were waiting, or operators inside parentheses)
    while (!operators.empty())
    {
        // If an opening parenthesis remains on the stack, it means it was never closed
        if (isOpeningParenthesis(operators.back()))
        {
            throw runtime_error("Mismatched parentheses: An opening parenthesis was not closed.");
        }
        if (numbers.size() < 2)
        {
            throw runtime_error("Malformed expression: Not enough numbers for remaining operations.");
        }
        double b = numbers.back(); numbers.pop_back();
        double a = numbers.back(); numbers.pop_back();
        char op = operators.back(); operators.pop_back();
        numbers.push_back(performOperation(a, b, op));
    }

    // At the end, the numbers stack should contain exactly one result
    if (numbers.size() != 1)
    {
        throw runtime_error("Malformed expression: Result is ambiguous or too many numbers remain.");
    }

    return numbers.back(); // Return the final result
}

int main()
{
    string expression; // Variable to store the user's input expression

    // Finally started including "\n" within the first operator
    cout << "C++ Calculator\n";
    cout << "A C++ program made by DerivedWharf15\n\n";
    cout << "Enter expressions (e.g., 5 + 3 * 2 or (10 / 2) - 1)\n";
    cout << "Different types of parentheses like (), [], and {} are also supported\n";
    cout << "Type 'exit' close the program\n";

    while (true)
    {
        cout << "\n>> ";
        // Read the entire line of input from the user, including spaces
        getline(cin, expression);

        // If the input is empty, just prompt again
        if (expression.empty())
        {
            continue;
        }

        // Create a lowercase version of the input to check for the 'exit' command
        string lowerCaseExpression = expression;
        transform(lowerCaseExpression.begin(), lowerCaseExpression.end(), lowerCaseExpression.begin(), ::tolower);

        // Check if the user wants to exit
        if (lowerCaseExpression == "exit")
        {
            cout << "\nClosing Calculator\nThank you for using this program\n\n";
            break; // Exit the loop and end the program
        }

        // Try to evaluate the expression and catch any errors that might occur
        try
        {
            double result = evaluateExpression(expression); // Call the evaluation function
            cout << "Result: " << result << '\n' << "type 'exit' to close the programn\n"; // Print the calculated result
        }
        catch (const runtime_error& e)
        {
            // Catch specific runtime errors (like division by zero or invalid characters)
            cout << "Error: " << e.what() << '\n';
        }
        catch (const out_of_range& e)
        {
            // Catch errors if numbers in the expression are too large or too small
            cout << "Error: A number in the expression is too large or small. " << e.what() << '\n';
        }
        catch (...)
        {
            // Catch any other unexpected errors
            cout << "An unknown error occurred during calculation. Please check your expression.\n";
        }
    }

    return 0;
}
