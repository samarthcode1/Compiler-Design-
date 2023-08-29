#include <iostream>
using namespace std;

/*
Productions:
Q->AbQ'
Q'->ABQ'|ε
A>BA'
A'->bA'|ε
B->a|b
String w=abbab
*/

bool Q();
bool Q_Dash();
bool A();
bool A_Dash();
bool B();

string str;
int cursor = 0;

bool Q()
{
    cout << "Q->AbQ'\n";
    if (A() == true)
    {
        cursor++;
        if (Q_Dash() == true)
        {
            return true;
        }
    }
}

bool Q_Dash()
{
    cout << "Q'->ABQ'\n";
    if (A() && B() && Q_Dash())
    {
        return true;
    }
    cout << "Q'->eps\n";
    return true;
}

bool A()
{
    cout << "A->BA'\n";
    if (B() && A_Dash())
    {
        return true;
    }
    return false;
}

bool A_Dash()
{
    cout << "A'->bA'\n";
    if (str[cursor] == 'b')
    {
        cursor++;
        if (A_Dash())
        {
            return true;
        }
    }
    cout << "A'->eps\n";
    return true;
}

bool B()
{
    cout << "B->a|b\n";
    if (str[cursor] == 'a')
    {
        cursor++;
        return true;
    }
    else if (str[cursor] == 'b')
    {
        cursor++;
        return true;
    }
    return false;
}

int main()
{
    cout << "Enter the string: ";
    cin >> str;
    Q();
    if (str.size() == cursor)
    {
        cout << "Accepted\n";
    }
    else
    {
        cout << "Rejected\n";
    }
    return 0;
}