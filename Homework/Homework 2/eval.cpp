// eval.cpp

#include "Map.h"
#include <iostream>
#include <string>
#include <stack>
#include <cctype>
#include <cassert>
using namespace std;

int evaluate(string infix, const Map& values, string& postfix, int& result);
// Evaluates an integer arithmetic expression

//   If infix is a syntactically valid infix integer expression whose
//   only operands are single lower case letters (whether or not they
//   appear in the values map), then postfix is set to the postfix
//   form of the expression; otherwise postfix may or may not be
//   changed, result is unchanged, and the function returns 1.  

//   If infix is syntactically valid but contains at least one lower
//   case letter operand that does not appear in the values map, then
//   result is unchanged and the function returns 2.  

//   If infix is syntactically valid and all its lower case operand letters
//   appear in the values map, then if evaluating the expression
//   (using for each letter in the expression the value in the map
//   that corresponds to it) attempts to divide by zero, then result
//   is unchanged and the function returns 3; otherwise, result is
//   set to the value of the expression and the function returns 0.


bool infix_valid(string infix)
{
    if (infix.empty())
    {
        return false;
    }

    int left = 0; //number of left parentheses
    int right = 0; //number of right parentheses
    bool prev_operator = false; //if the previous char was an operator
    bool prev_letter = false; //if the previous char was a letter
    bool prev_left = false; //if the previous char was a left parentheses
    bool prev_right = false; //if the previous char was a right parentheses


    //Let's remove the spaces in infix to make it easier
    string new_infix;
    for (int i = 0; i < infix.size(); i++)
    {
        if (infix[i] != ' ')
        {
            new_infix += infix[i];
        }
    }

    for (int i = 0; i < new_infix.size(); i++) //LOOP THROUGH THE NEW INFIX WITHOUT SPACES
    {
        char ch = new_infix[i];
        
        //Character must be a lowercase letter, an operator, or a parentheses
        if ((!islower(ch)) && !((ch == '+') || (ch == '*') || (ch == '-') 
            || (ch == '/') || (ch == '(') || (ch == ')')))
        {
            return false;
        }

        if ((i == 0) && (!islower(ch)) && (ch != '('))
        {
            return false; //if the first char in a string isn't a letter or a '('
        }

        if ((i == new_infix.size()-1) && (!islower(ch)) && (ch != ')'))
        {
            return false; //if the last char in a string isn't a letter or a ')'
        }

        bool prev_operator_temp = false;
        bool prev_letter_temp = false;
        bool prev_left_temp = false;
        bool prev_right_temp = false;

        if (islower(ch))
        {
            if ((prev_letter) || (prev_right))
            {
                return false; //if there's a letter or right parentheses before a letter
            }
            prev_letter_temp = true;
        }
        else if (ch == '(')
        {
            if ((prev_letter) || (prev_right))
            {
                return false; //if there's a letter or right parentheses before the left parentheses
            }
            prev_left_temp = true;
            left++;
        }
        else if (ch == ')')
        {
            if ((prev_left) || (prev_operator))
            {
                return false; //if there's a left parentheses or operator before a right parentheses
            }
            prev_right_temp = true;
            right++;
        }
        else if ((ch == '+') || (ch == '*') || (ch == '-') || (ch == '/')) //if it's an operator
        {
            if ((prev_operator) || (prev_left))
            {
                return false; //false if consecutive operators or a left parentheses before an operator
            }
            prev_operator_temp = true;
        }

        prev_operator = prev_operator_temp;
        prev_letter = prev_letter_temp;
        prev_left = prev_left_temp;
        prev_right = prev_right_temp;
    }

    if (left != right)
    {
        return false; //if there are an uneven number of left and right parentheses
    }

    return true; //if all the tests pass, return true
}

bool precedence(char ch, char p) //return true if the precedence of ch <= p
{
    if (((ch == '+') || (ch == '-')) && ((p == '+') || (p == '*') || (p == '-') || (p == '/')))
    {
        return true;
    }
    else if (((ch == '*') || (ch == '/')) && ((p == '*') || (p == '/')))
    {
        return true;
    }
    else
    {
        return false;
    }
}

string infix2postfix(string infix)
{
    string postfix = "";  // Initialize postfix to empty
    stack<char> opstack;  // Initialize the operator stack to empty

    for (int i = 0; i < infix.size(); i++) // For each character ch in the infix string
    {
        switch (char ch = infix[i]) //Switch (ch)
        {
        case ' ':
            break;

        //case operand
        case 'a':
        case 'b':
        case 'c':
        case 'd':
        case 'e':
        case 'f':
        case 'g':
        case 'h':
        case 'i':
        case 'j':
        case 'k':
        case 'l':
        case 'm':
        case 'n':
        case 'o':
        case 'p':
        case 'q':
        case 'r':
        case 's':
        case 't':
        case 'u':
        case 'v':
        case 'w':
        case 'x':
        case 'y':
        case 'z':
            postfix += ch;    // append ch to end of postfix
            break;            // break

        case '(':           //case '('
            opstack.push(ch); // push ch onto the operator stack
            break;            // break

        case ')':           //case ')'
                            // pop stack until matching '('
            while (opstack.top() != '(') // While stack top is not '('
            {
                postfix += opstack.top(); // append the stack top to postfix
                opstack.pop();            // pop the stack
            }
            opstack.pop(); //pop the stack, remove the '('
            break;         //break

        //case operator:
        case '+':
        case '*':
        case '-':
        case '/':
            while ((!opstack.empty()) && (opstack.top() != '(') && (precedence(ch, opstack.top())))
            {
                postfix += opstack.top(); //append the stack top to postfix
                opstack.pop(); //pop the stack
            }
            opstack.push(ch); //push ch onto the stack
            break; //break
        }
    }

    while (!opstack.empty()) //while the stack is not empty
    {
        postfix += opstack.top(); //append the stack top to postfix
        opstack.pop(); //pop the stack
    }
    return postfix;
}

int evaluate(string infix, const Map& values, string& postfix, int& result)
{
    if (!infix_valid(infix))
    {
        return 1;
    }

    postfix = infix2postfix(infix);


    for (int i = 0; i < infix.size(); i++) //if contains one lower case letter that
                                           //isn't in the values map, return 2
    {
        char temp = infix[i];
        if ((islower(temp)) && (!values.contains(temp)))
        {
            return 2;
        }
    }

    // Now we know infix is syntactically valid and all its lower case operand letters
    // appear in the values map

    //EVALUATION OF POSTFIX EXPRESSION

    stack<int> opStack; //initialize operand stack to empty

    for (int i = 0; i < postfix.size(); i++) //For each character ch in the postfix string
    {
        char ch = postfix[i];

        //if ch is an operand, push the value that ch represents onto the operand stack
        if (isalpha(ch))
        {
            int val;
            values.get(ch, val);
            opStack.push(val);
        }
        else // ch is a binary operator
        {
            int operand2 = opStack.top(); //set operand2 to the top of the operand stack
            opStack.pop(); //pop the stack
            int operand1 = opStack.top(); //set operand1 to the top of the operand stack
            opStack.pop(); //pop the stack

            //Now apply the operation that ch represents to operand1 and operand2, and
            //push the result onto the stack

            if (ch == '+')
            {
                opStack.push(operand1 + operand2);
            }
            else if (ch == '*')
            {
                opStack.push(operand1 * operand2);
            }
            else if (ch == '-')
            {
                opStack.push(operand1 - operand2);
            }
            else if (ch == '/')
            {
                //check if it divides by 0
                if (operand2 == 0)
                {
                    return 3;
                }
                opStack.push(operand1 / operand2);
                break;
            }
        }
    }
    // Now we are done looping through the postfix string
    // When the loop is finished, the operand stack will contain one item,
    // the result of evaluating the expression
    result = opStack.top();
    return 0;
}

int main()
{
    char vars[] = { 'a', 'e', 'i', 'o', 'u', 'y', '#' };
    int  vals[] = { 3,  -9,   6,   2,   4,   1 };
    Map m;
    for (int k = 0; vars[k] != '#'; k++)
        m.insert(vars[k], vals[k]);
    string pf;
    int answer;
    assert(evaluate("a+ e", m, pf, answer) == 0 &&
        pf == "ae+" && answer == -6);
    answer = 999;
    assert(evaluate("", m, pf, answer) == 1 && answer == 999);
    assert(evaluate("a+", m, pf, answer) == 1 && answer == 999);
    assert(evaluate("a i", m, pf, answer) == 1 && answer == 999);
    assert(evaluate("ai", m, pf, answer) == 1 && answer == 999);
    assert(evaluate("()", m, pf, answer) == 1 && answer == 999);
    assert(evaluate("()o", m, pf, answer) == 1 && answer == 999);
    assert(evaluate("y(o+u)", m, pf, answer) == 1 && answer == 999);
    assert(evaluate("y(*o)", m, pf, answer) == 1 && answer == 999);
    assert(evaluate("a+E", m, pf, answer) == 1 && answer == 999);
    assert(evaluate("(a+(i-o)", m, pf, answer) == 1 && answer == 999);
    // unary operators not allowed:
    assert(evaluate("-a", m, pf, answer) == 1 && answer == 999);
    assert(evaluate("a*b", m, pf, answer) == 2 &&
        pf == "ab*" && answer == 999);
    assert(evaluate("y +o *(   a-u)  ", m, pf, answer) == 0 &&
        pf == "yoau-*+" && answer == -1);
    answer = 999;
    assert(evaluate("o/(y-y)", m, pf, answer) == 3 &&
        pf == "oyy-/" && answer == 999);
    assert(evaluate(" a  ", m, pf, answer) == 0 &&
        pf == "a" && answer == 3);
    assert(evaluate("((a))", m, pf, answer) == 0 &&
        pf == "a" && answer == 3);
    cout << "Passed all tests" << endl;
}