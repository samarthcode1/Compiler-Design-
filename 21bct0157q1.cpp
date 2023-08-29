#include <iostream>
#include <string.h>
#include <stack>
#include <unordered_map>
using namespace std;
char lookahead;
int error = 0;
int main()  
{
    unordered_map<int, string> mp;
    mp.insert({0, "E'->E"});
    mp.insert({1, "E->E*T"});
    mp.insert({2, "E->T"});
    mp.insert({3, "T->T+F"});
    mp.insert({4, "T->F"});
    mp.insert({5, "F->(E)"});
    mp.insert({6, "F->id"});
    cout << "So the Grammar used for Parsing:\n";
    for (int i = 0; i < 7; i++)
    {
        cout << mp[i] << "\n";
    }
    cout << "Enter the Length of String including '$':";
    int n;
    cin >> n;
    char arr[n + 1];
    cout << "Enter the String after Appending '$':";
    cin >> arr;
    stack<int>states;
    stack<char>st;
    stack<char>buffer;
    st.push('$');
    states.push(0);
    for (int i = n; i >= 0; i--)
    {
        buffer.push(arr[i]);
    }
    lookahead = buffer.top();
    cout << "\n";
    cout << "The parsing productions used are:\n";
    while (error == 0)
    {
        if (states.top() == 0)
        {
            if (lookahead == 'i')
            {
                states.push(5);
                st.push('i');
                buffer.pop();
                lookahead = buffer.top();
            }
            else if (lookahead == '(')
            {
                states.push(4);
                st.push('(');
                buffer.pop();
                lookahead = buffer.top();
            }
            else if (lookahead == 'E')
            {
                states.push(1);
                st.push('E');
                buffer.pop();
                lookahead = buffer.top();
            }
            else if (lookahead == 'T')
            {
                states.push(2);
                st.push('T');
                buffer.pop();
                lookahead = buffer.top();
            }
            else if (lookahead == 'F')
            {

                states.push(3);
                st.push('F');
                buffer.pop();
                lookahead = buffer.top();
            }
            else
            {
                error = 1;
            }
        }
        else if (states.top() == 1)
        {
            if (lookahead == '*')
            {
                states.push(6);
                st.push('*');
                buffer.pop();
                lookahead = buffer.top();
            }
            else if (lookahead == '$')
            {
                st.push('$');
                buffer.pop();
                break;
            }
            else
            {
                error = 1;
            }
        }
        else if (states.top() == 2)
        {
            if (lookahead == '*' || lookahead == '$')
            {
                states.push(0);
                st.pop();
                st.push('E');
                while (st.top() != '$')
                {
                    buffer.push(st.top());
                    st.pop();
                }
                cout << mp[2] << "\n";
                lookahead = buffer.top();
            }
            else if (lookahead == '+')
            {
                states.push(7);

                st.push('+');
                buffer.pop();
                lookahead = buffer.top();
            }
            else
            {
                error = 1;
            }
        }
        else if (states.top() == 3)
        {
            if (lookahead == '+' || lookahead == '$' || lookahead == '*')
            {
                states.push(0);
                st.pop();
                st.push('T');
                while (st.top() != '$')
                {
                    buffer.push(st.top());
                    st.pop();
                }
                cout << mp[4] << "\n";
                lookahead = buffer.top();
            }
            else
            {
                error = 1;
            }
        }
        else if (states.top() == 4)
        {
            if (lookahead == 'i')
            {
                states.push(11);
                st.push('i');
                buffer.pop();
                lookahead = buffer.top();
            }
            else if (lookahead == '(')
            {
                states.push(12);
                st.push('(');
                buffer.pop();
                lookahead = buffer.top();
            }
            else if (lookahead == 'E')
            {
                states.push(8);

                st.push('E');
                buffer.pop();
                lookahead = buffer.top();
            }
            else if (lookahead == 'T')
            {
                states.push(9);
                st.push('T');
                buffer.pop();
                lookahead = buffer.top();
            }
            else if (lookahead == 'F')
            {
                states.push(10);
                st.push('F');
                buffer.pop();
                lookahead = buffer.top();
            }
            else
            {
                error = 1;
            }
        }
        else if (states.top() == 5)
        {
            if (lookahead == '+' || lookahead == '$' || lookahead == '*')
            {
                states.push(0);
                st.pop();
                st.push('F');
                while (st.top() != '$')
                {
                    buffer.push(st.top());
                    st.pop();
                }
                cout << mp[6] << "\n";
                lookahead = buffer.top();
            }
            else
            {
                error = 1;
            }
        }
        else if (states.top() == 6)
        {
            if (lookahead == 'i')
            {
                states.push(5);

                st.push('i');
                buffer.pop();
                lookahead = buffer.top();
            }
            else if (lookahead == '(')
            {
                states.push(4);
                st.push('(');
                buffer.pop();
                lookahead = buffer.top();
            }
            else if (lookahead == 'T')
            {
                states.push(13);
                st.push('T');
                buffer.pop();
                lookahead = buffer.top();
            }
            else if (lookahead == 'F')
            {
                states.push(14);
                st.push('F');
                buffer.pop();
                lookahead = buffer.top();
            }
            else
            {
                error = 1;
            }
        }
        else if (states.top() == 7)
        {
            if (lookahead == 'i')
            {
                states.push(5);
                st.push('i');
                buffer.pop();
                lookahead = buffer.top();
            }
            else if (lookahead == '(')
            {
                states.push(4);
                st.push('(');
                buffer.pop();
                lookahead = buffer.top();
            }
            else if (lookahead == 'F')
            {

                states.push(15);
                st.push('F');
                buffer.pop();
                lookahead = buffer.top();
            }
            else
            {
                error = 1;
            }
        }
        else if (states.top() == 8)
        {
            if (lookahead == '*')
            {
                states.push(17);
                st.push('*');
                buffer.pop();
                lookahead = buffer.top();
            }
            else if (lookahead == ')')
            {
                states.push(16);
                st.push(')');
                buffer.pop();
                lookahead = buffer.top();
            }
            else
            {
                error = 1;
            }
        }
        else if (states.top() == 9)
        {
            if (lookahead == '*' || lookahead == ')')
            {
                states.push(0);
                st.pop();
                st.push('E');
                while (st.top() != '$')
                {
                    buffer.push(st.top());
                    st.pop();
                }
                cout << mp[2] << "\n";
                lookahead = buffer.top();
            }
            else if (lookahead == '+')
            {

                states.push(18);
                st.push('+');
                buffer.pop();
                lookahead = buffer.top();
            }
            else
            {
                error = 1;
            }
        }
        else if (states.top() == 10)
        {
            if (lookahead == '*' || lookahead == ')' || lookahead == '+')
            {
                states.push(0);
                st.pop();
                st.push('T');
                while (st.top() != '$')
                {
                    buffer.push(st.top());
                    st.pop();
                }
                cout << mp[4] << "\n";
                lookahead = buffer.top();
            }
            else
            {
                error = 1;
            }
        }
        else if (states.top() == 11)
        {
            if (lookahead == '*' || lookahead == ')' || lookahead == '+')
            {
                states.push(0);
                st.pop();
                st.push('F');
                while (st.top() != '$')
                {
                    buffer.push(st.top());
                    st.pop();
                }
                cout << mp[6] << "\n";
                lookahead = buffer.top();
            }
            else
            {
                error = 1;
            }
        }
        else if (states.top() == 12)
        {
            if (lookahead == 'i')
            {
                states.push(11);
                st.push('i');
                buffer.pop();
                lookahead = buffer.top();
            }
            else if (lookahead == '(')
            {
                states.push(12);
                st.push('(');
                buffer.pop();
                lookahead = buffer.top();
            }
            else if (lookahead == 'E')
            {
                states.push(19);
                st.push('E');
                buffer.pop();
                lookahead = buffer.top();
            }
            else if (lookahead == 'T')
            {
                states.push(9);
                st.push('T');
                buffer.pop();
                lookahead = buffer.top();
            }
            else if (lookahead == 'F')
            {
                states.push(10);
                st.push('F');
                buffer.pop();
                lookahead = buffer.top();
            }
            else
            {
                error = 1;
            }
        }
        else if (states.top() == 13)
        {
            if (lookahead == '*' || lookahead == '$')
            {

                states.push(0);
                st.pop();
                st.pop();
                st.pop();
                st.push('E');
                while (st.top() != '$')
                {
                    buffer.push(st.top());
                    st.pop();
                }
                cout << mp[1] << "\n";
                lookahead = buffer.top();
            }
            else if (lookahead == '+')
            {
                states.push(7);
                st.push('+');
                buffer.pop();
                lookahead = buffer.top();
            }
            else
            {
                error = 1;
            }
        }
        else if (states.top() == 14)
        {
            if (lookahead == '*' || lookahead == '$' || lookahead == '+')
            {
                states.push(0);
                st.pop();
                st.push('T');
                while (st.top() != '$')
                {
                    buffer.push(st.top());
                    st.pop();
                }
                cout << mp[4] << "\n";
                lookahead = buffer.top();
            }
            else
            {
                error = 1;
            }
        }
        else if (states.top() == 15)
        {
            if (lookahead == '*' || lookahead == '$' || lookahead == '+')

            {
                states.push(0);
                st.pop();
                st.pop();
                st.pop();
                st.push('T');
                while (st.top() != '$')
                {
                    buffer.push(st.top());
                    st.pop();
                }
                cout << mp[3] << "\n";
                lookahead = buffer.top();
            }
            else
            {
                error = 1;
            }
        }
        else if (states.top() == 16)
        {
            if (lookahead == '*' || lookahead == '$' || lookahead == '+')
            {
                states.push(0);
                st.pop();
                st.pop();
                st.pop();
                st.push('F');
                while (st.top() != '$')
                {
                    buffer.push(st.top());
                    st.pop();
                }
                cout << mp[5] << "\n";
                lookahead = buffer.top();
            }
            else
            {
                error = 1;
            }
        }
        else if (states.top() == 17)
        {
            if (lookahead == 'i')
            {
                states.push(11);
                st.push('i');
                buffer.pop();

                lookahead = buffer.top();
            }
            else if (lookahead == '(')
            {
                states.push(12);
                st.push('(');
                buffer.pop();
                lookahead = buffer.top();
            }
            else if (lookahead == 'T')
            {
                states.push(20);
                st.push('T');
                buffer.pop();
                lookahead = buffer.top();
            }
            else if (lookahead == 'F')
            {
                states.push(10);
                st.push('F');
                buffer.pop();
                lookahead = buffer.top();
            }
            else
            {
                error = 1;
            }
        }
        else if (states.top() == 18)
        {
            if (lookahead == 'i')
            {
                states.push(11);
                st.push('i');
                buffer.pop();
                lookahead = buffer.top();
            }
            else if (lookahead == '(')
            {
                states.push(12);
                st.push('(');
                buffer.pop();
                lookahead = buffer.top();
            }
            else if (lookahead == 'F')
            {
                states.push(21);
                st.push('F');

                buffer.pop();
                lookahead = buffer.top();
            }
            else
            {
                error = 1;
            }
        }
        else if (states.top() == 19)
        {
            if (lookahead == '*')
            {
                states.push(17);
                st.push('*');
                buffer.pop();
                lookahead = buffer.top();
            }
            else if (lookahead == ')')
            {
                states.push(22);
                st.push(')');
                buffer.pop();
                lookahead = buffer.top();
            }
            else
            {
                error = 1;
            }
        }
        else if (states.top() == 20)
        {
            if (lookahead == '*' || lookahead == ')')
            {
                states.push(0);
                st.pop();
                st.pop();
                st.pop();
                st.push('E');
                while (st.top() != '$')
                {
                    buffer.push(st.top());
                    st.pop();
                }
                cout << mp[1] << "\n";
                lookahead = buffer.top();
            }
            else if (lookahead == '+')
            {

                states.push(18);
                st.push('+');
                buffer.pop();
                lookahead = buffer.top();
            }
            else
            {
                error = 1;
            }
        }
        else if (states.top() == 21)
        {
            if (lookahead == '*' || lookahead == ')' || lookahead == '+')
            {
                states.push(0);
                st.pop();
                st.pop();
                st.pop();
                st.push('T');
                while (st.top() != '$')
                {
                    buffer.push(st.top());
                    st.pop();
                }
                cout << mp[3] << "\n";
                lookahead = buffer.top();
            }
            else
            {
                error = 1;
            }
        }
        else if (states.top() == 22)
        {
            if (lookahead == '*' || lookahead == ')' || lookahead == '+')
            {
                states.push(0);
                st.pop();
                st.pop();
                st.pop();
                st.push('F');
                while (st.top() != '$')
                {
                    buffer.push(st.top());
                    st.pop();
                }
                cout << mp[5] << "\n";
                lookahead = buffer.top();
            }
            else
            {
                error = 1;
            }
        }
    }
    if (error == 0)
    {
        cout << "Successfully Parsed the String\n";
    }
    else
    {
        cout << "Parsing failed\n";
    }
    cout << "Samarth Nag (21BCT0157)";
    return 0;
}