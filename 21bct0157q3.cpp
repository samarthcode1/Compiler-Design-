#include <iostream>
#include <stack>
#include <vector>
#include <unordered_map>
using namespace std;

unordered_map<char, vector<string>> Follow = {
    {'E', {")", "$"}},
    {'X', {")", "$"}},
    {'T', {"+", ")", "$"}},
    {'Y', {"+", ")", "$"}},
    {'F', {"*", "+", ")", "$"}}};

unordered_map<char, vector<string>> First = {
    {'E', {"(", "i"}},
    {'X', {"+", "e"}},
    {'T', {"(", "i"}},
    {'Y', {"*", "e"}},
    {'F', {"(", "i"}}};

struct Grammer
{
    char Left;
    string right;
};

vector<Grammer> cfg = {
    {'E', "TX"},
    {'X', "+TX|e"},
    {'T', "FY"},
    {'Y', "*FY|e"},
    {'F', "(E)|i"}};

unordered_map<char, unordered_map<string, int>> Parsing_Table;
void GenerateParsingTable()
{
    for (const auto &rule_equation : cfg)
    {
        char Variables = rule_equation.Left;
        string productions = rule_equation.right;
        int productionIndex = 0;
        size_t index = productions.find("|");
        while (index != string::npos)
        {
            string production = productions.substr(0, index);
            Parsing_Table[Variables][production] = productionIndex++;
            productions.erase(0, index + 1);
            index = productions.find("|");
        }

        Parsing_Table[Variables][productions] = productionIndex;
    }
}

int parseString(const string &str)
{
    stack<char> symbol;
    stack<int> state;
    symbol.push('$');
    state.push(0);
    size_t inputIndex = 0;

    while (!symbol.empty())
    {
        char stackTopSymbol = symbol.top();
        int stackTopState = state.top();

        if (stackTopSymbol == str[inputIndex])
        {
            symbol.pop();
            state.pop();
            inputIndex++;
        }
        else if (stackTopSymbol == '$')
        {
            return 1;
        }
        else if (isupper(stackTopSymbol))
        {
            string Lookahead = str.substr(inputIndex, 1);

            if (Parsing_Table[stackTopSymbol].find(Lookahead) == Parsing_Table[stackTopSymbol].end())
            {
                return 0;
            }

            int productionIndex = Parsing_Table[stackTopSymbol][Lookahead];

            if (productionIndex == -1)
            {
                return 0;
            }

            symbol.pop();
            state.pop();

            string productionRHS = cfg[productionIndex].right;
            for (int i = productionRHS.length() - 1; i >= 0; i--)
            {
                if (productionRHS[i] != 'e')
                {
                    symbol.push(productionRHS[i]);
                    state.push(0);
                }
            }
        }
        else
        {
            return 0;
        }
    }
    return 0;
}

int main()
{
    GenerateParsingTable();
    string str = "w =(i*i)+(i*i)+i";
    bool output = parseString(str);
    cout << "The Given String is: " << str << "\n";
    if (output)
    {
        cout << "Hence the Given String is Parsed Successfully\n";
        cout << "String is Accepted\n";
        cout<<"21BCT0157\n";
    }
    else
    {
        cout << "Hence the Given String do not Parsed Successfully\n";
        cout << "String is Rejected\n";
    }
    return 0;
}