#include <iostream>
using namespace std;
struct Symbol
{
    int value;
    char type;
};
int index = 0;
Symbol currentValue;
string expression;
Symbol nextSymbol();
void checkSymbol(char expT)
{
    if (currentValue.type = expT)
    {
        currentValue = nextSymbol();
    }
    else
    {
        cout << "Syntax Error: \n";
        cout << "Symbol " << currentValue.type << " Found at Invalid Position\n";
        exit(0);
    }
}

Symbol nextSymbol()
{
    Symbol symbol;
    if (index < expression.length())
    {
        if (isdigit(expression[index]))
        {
            symbol.type = 'D';
            symbol.value = expression[index] - '0';
            index++;
        }
        else
        {
            symbol.type = expression[index];
            symbol.value = 0;
            index++;
        }
    }
    else
    {
        symbol.type = '$';
        symbol.value = 0;
    }
    return symbol;
}

int characterSymbol()
{
    int ans = 0;
    if (currentValue.type == 'D')
    {
        ans = currentValue.value;
        checkSymbol('D');
        cout << "Execution " << ans << endl;
    }
    else
    {
        cout << "Syntax Error: \n";
        cout << "Symbol " << currentValue.type << " Found at Invalid Position\n";
        exit(0);
    }
    return ans;
}
int multiply()
{
    int ans = characterSymbol();
    while (currentValue.type == '*')
    {
        checkSymbol('*');
        int factorValue = characterSymbol();
        ans *= factorValue;
        cout << "Result: " << ans << endl;
    }
    return ans;
}
int sum()
{
    int ans = multiply();
    while (currentValue.type == '+')
    {
        checkSymbol('+');
        int termValue = multiply();
        ans += termValue;
        cout << "Result: " << ans << endl;
    }
    return ans;
}
void calculate()
{
    currentValue = nextSymbol();
    int ans = sum();
    cout << "The Final Result is " << ans << endl;
    ;
}
int main()
{
    cout << "Enter the expression\n";
    cin >> expression;
    calculate();
    return 0;
}