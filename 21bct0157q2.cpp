#include <iostream>
#include <string>
#include <stack>
#include <unordered_map>
#include <vector>
using namespace std;

vector<string> Grammer = 
{
    "Q -> QAB",
    "Q -> Ab",
    "A -> Ab",
    "A -> B",
    "B -> a",
    "B -> b"
};

unordered_map<char, unordered_map<char, string>> Parsing_Table =
    {
        {'0', {{'a', "s3"}, {'b', "s4"}, {'Q', "1"}}},
        {'1', {{'A', "s5"}, {'B', "s6"}, {'$', "accept"}}},
        {'2', {{'$', "r2"}}},
        {'3', {{'a', "s3"}, {'b', "s4"}, {'Q', "7"}}},
        {'4', {{'a', "r4"}, {'b', "r4"}, {'$', "r4"}}},
        {'5', {{'a', "r1"}, {'b', "s6"}}},
        {'6', {{'a', "r3"}, {'b', "r3"}, {'$', "r3"}}},
        {'7', {{'A', "r6"}, {'B', "r6"}}}
    };

int Parsing(const string &str)
{
    stack<char> stk;
    stk.push('0');
    size_t index = 0;
    while (index < str.size())
    {
        char present_state = stk.top();
        char symbol = str[index];
        if (Parsing_Table.find(present_state) == Parsing_Table.end() ||
            Parsing_Table[present_state].find(symbol) ==
                Parsing_Table[present_state].end())
        {
            cout << "Hence the Given String is Parsed Successfully\n";
            cout << "So the String is Accepted\n";
            return 0;
        }
        string operation = Parsing_Table[present_state][symbol];
        if (operation == "accept")
        {
            return 1;
        }
        else if (operation[0] == 's')
        {
            char followingState = operation[1];
            stk.push(symbol);
            stk.push(followingState);
            index++;
        }
        else if (operation[0] == 'r')
        {
            int grammerIndex = stoi(operation.substr(1));
            int numPop = Grammer[grammerIndex - 1].size() - 4;
            for (int i = 0; i < 2 * numPop; i++)
            {
                stk.pop();
            }
            char prevState = stk.top();
            char nonTerminal = Grammer[grammerIndex - 1][0];
            stk.push(nonTerminal);
            stk.push(Parsing_Table[prevState][nonTerminal][0]);
        }
    }
    cout << "So the given String do not parse the grammer so Rejected\n";
    return 0;
}

int main()
{
    string str = "abbab";
    cout << "The given string is " << str << "\n";
    cout << "The given grammar is\n";
    for (int i = 0; i < Grammer.size(); i++)
    {
        cout << Grammer[i] << "\n";
    }
    cout<<"21BCT0157\n";
    Parsing(str);
    return 0;
}
