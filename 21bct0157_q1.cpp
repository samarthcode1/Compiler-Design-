//21BCT0157
#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
using namespace std;
void First(vector<pair<char, string>> newGrammer, map<char, set<char>> &first, char nonTerminal);

void Follow(vector<pair<char, string>> newGrammer, map<char, set<char>> &follow, map<char, set<char>> first, char nonTerminal)
{
    for (auto iterator = newGrammer.begin(); iterator != newGrammer.end(); ++iterator)
    {
        bool completed = true;
        auto c = iterator->second.begin();
        for (; c != iterator->second.end(); c++)
        {
            if (*c == nonTerminal)
            {
                completed = false;
                break;
            }
        }
        ++c;

        for (; c != iterator->second.end() && completed == false; c++)
        {
            if (!isupper(*c))
            {
                follow[nonTerminal].insert(*c);
                completed = true;
                break;
            }

            set<char> first1(first[*c]);
            if (first1.find('e') == first1.end())
            {
                follow[nonTerminal].insert(first1.begin(), first1.end());
                completed = true;
                break;
            }
            first1.erase('e');
            follow[nonTerminal].insert(first1.begin(), first1.end());
        }

        if (c == iterator->second.end() && completed == false)
        {
            if (follow[iterator->first].empty())
            {
                Follow(newGrammer, follow, first, iterator->first);
            }
            follow[nonTerminal].insert(follow[iterator->first].begin(), follow[iterator->first].end());
        }
    }
}

void First(vector<pair<char, string>> newGrammer, map<char, set<char>> &first, char nonTerminal)
{
    for (auto iterator = newGrammer.begin(); iterator != newGrammer.end(); iterator++)
    {
        if (iterator->first != nonTerminal)
            continue;

        string right = iterator->second;
        for (auto c = right.begin(); c != right.end(); c++)
        {
            if (!isupper(*c))
            {
                first[nonTerminal].insert(*c);
                break;
            }
            else
            {
                if (first[*c].empty())
                {
                    First(newGrammer, first, *c);
                }

                if (first[*c].find('e') == first[*c].end())
                {
                    first[nonTerminal].insert(first[*c].begin(), first[*c].end());
                    break;
                }

                set<char> first1(first[*c].begin(), first[*c].end());

                if (c + 1 != right.end())
                {
                    first1.erase('e');
                }
                first[nonTerminal].insert(first1.begin(), first1.end());
            }
        }
    }
}

void showStackContent(stack<char> stk)
{
    if (stk.empty())
    {
        return;
    }
    char n = stk.top();
    stk.pop();
    cout << n << "";
    showStackContent(stk);
    stk.push(n);
}

int main()
{
    fstream input_file;
    input_file.open("q1.txt");
    if (input_file.fail())
    {
        cout << "Error while opening the File!"
             << "\n";
        return 2;
    }

    cout << "Grammer acc from File Input:"
         << "\n";
    vector<pair<char, string>> newGrammer;
    int number_count = 0;
    while (!input_file.eof())
    {
        char input_buffer[20];
        input_file.getline(input_buffer, 19);

        char left_side = input_buffer[0];
        string right = input_buffer + 3;
        pair<char, string> prod(left_side, right);
        newGrammer.push_back(prod);
        cout << ++number_count << ". " << newGrammer.back().first << " -> " << newGrammer.back().second << "\n";
    }
    cout << "\n";

    set<char> nonTermials;
    for (auto i = newGrammer.begin(); i != newGrammer.end(); ++i)
    {
        nonTermials.insert(i->first);
    }
    cout << "Hence the Variables for the given Grammer is:  ";
    for (auto i = nonTermials.begin(); i != nonTermials.end(); ++i)
    {
        cout << *i << " ";
    }
    cout << "\n";

    set<char> terms;
    for (auto i = newGrammer.begin(); i != newGrammer.end(); ++i)
    {
        for (auto c = i->second.begin(); c != i->second.end(); ++c)
        {
            if (!isupper(*c))
                terms.insert(*c);
        }
    }

    terms.erase('e');
    terms.insert('$');
    cout << "Hence the Terminals for the Grammer is: ";
    for (auto i = terms.begin(); i != terms.end(); ++i)
    {
        cout << *i << " ";
    }
    cout << "\n"
         << "\n";

    char start_sym = newGrammer.begin()->first;
    map<char, set<char>> first;
    for (auto nonTerminal = nonTermials.begin(); nonTerminal != nonTermials.end(); ++nonTerminal)
    {
        if (first[*nonTerminal].empty())
            First(newGrammer, first, *nonTerminal);
    }

    cout << "First :"
         << "\n";
    for (auto iterator = first.begin(); iterator != first.end(); ++iterator)
    {
        cout << iterator->first << " : ";
        for (auto firsts_it = iterator->second.begin(); firsts_it != iterator->second.end(); ++firsts_it)
        {
            cout << *firsts_it << " ";
        }
        cout << "\n";
    }
    cout << "\n";

    map<char, set<char>> follow;
    char start_var = newGrammer.begin()->first;
    follow[start_var].insert('$');
    Follow(newGrammer, follow, first, start_var);

    for (auto iterator = nonTermials.begin(); iterator != nonTermials.end(); ++iterator)
    {
        if (follow[*iterator].empty())
            Follow(newGrammer, follow, first, *iterator);
    }

    cout << "Follow: "
         << "\n";
    for (auto iterator = follow.begin(); iterator != follow.end(); iterator++)
    {
        cout << iterator->first << " : ";
        for (auto follow_iterator = iterator->second.begin(); follow_iterator != iterator->second.end(); ++follow_iterator)
        {
            cout << *follow_iterator << " ";
        }
        cout << "\n";
    }
    cout << "\n";
    cout << "So for the Parcing table the following represent the numbers and their corresponding production so accordingly the parce table is filled\n";
    cout << " 1 Represents == E -> TB \n 2 Represents == B -> *TB \n 3 Represents == B -> e \n 4 Represents == T -> FC \n 5 Represents == C -> +FC \n 6 Represents == C -> e \n 7 Represents == F -> (E) \n 8 Represents == F -> i"
         << "\n";

    int parseTable[nonTermials.size()][terms.size()];
    fill(&parseTable[0][0], &parseTable[0][0] + sizeof(parseTable) / sizeof(parseTable[0][0]), -1);
    for (auto prod = newGrammer.begin(); prod != newGrammer.end(); prod++)
    {
        string right = prod->second;
        set<char> next_list;
        bool completed = false;

        for (auto c = right.begin(); c != right.end(); ++c)
        {
            if (!isupper(*c))
            {
                if (*c != 'e')
                {
                    next_list.insert(*c);
                    completed = true;
                    break;
                }
                continue;
            }

            set<char> first1(first[*c].begin(), first[*c].end());
            if (first1.find('e') == first1.end())
            {
                next_list.insert(first1.begin(), first1.end());
                completed = true;
                break;
            }
            first1.erase('e');
            next_list.insert(first1.begin(), first1.end());
        }

        if (!completed)
            next_list.insert(follow[prod->first].begin(), follow[prod->first].end());

        for (auto c = next_list.begin(); c != next_list.end(); ++c)
        {
            int row = distance(nonTermials.begin(), nonTermials.find(prod->first));
            int column = distance(terms.begin(), terms.find(*c));
            int prod_num = distance(newGrammer.begin(), prod);
            if (parseTable[row][column] != -1)
            {
                cout << "Collision occring at [" << row << "][" << column << "] for the production " << prod_num << "\n";
                continue;
            }
            parseTable[row][column] = prod_num;
        }
    }

    cout << "Parse Table: "<< "\n";
    cout << " ";
    for (auto i = terms.begin(); i != terms.end(); ++i)
    {
        cout << *i << " ";
    }
    cout << "\n";

    for (auto row = nonTermials.begin(); row != nonTermials.end(); ++row)
    {
        cout << *row << " ";
        for (int column = 0; column < terms.size(); ++column)
        {
            int r = distance(nonTermials.begin(), row);
            if (parseTable[r][column] == -1)
            {
                cout << "- ";
                continue;
            }
            cout << parseTable[r][column] << " ";
        }
        cout << "\n";
    }
    cout << "\n";

    string input_string;
    cout << "Enter the Input String: ";
    cin >> input_string;
    input_string.push_back('$');
    cout << "\n";

    stack<char> st;
    st.push('$');
    st.push('E');
    for (auto c = input_string.begin(); c != input_string.end(); ++c)
    {
        if (terms.find(*c) == terms.end())
        {
            cout << "Opps the Input String is invalid!"<< "\n";
            return 2;
        }
    }

    cout << "showStackContent\t\t"<< "String"<< "\n";
    showStackContent(st);
    cout << "\t\t" << input_string << "\n";

    bool taken = true;
    while (!st.empty() && !input_string.empty())
    {
        if (input_string[0] == st.top())
        {
            st.pop();
            input_string.erase(0, 1);
            showStackContent(st);
            cout << "\t\t" << input_string << "\n";
        }
        else if (!isupper(st.top()))
        {
            cout << "\nUnmatched terminal found!!"
                 << "\n";
            taken = false;
            break;
        }
        else
        {
            char stack_top = st.top();
            int row = distance(nonTermials.begin(), nonTermials.find(stack_top));
            int column = distance(terms.begin(), terms.find(input_string[0]));
            int prod_num = parseTable[row][column];

            if (prod_num == -1)
            {
                cout << "Oops No production found in parse table"<< "\n";
                taken = false;
                break;
            }
            st.pop();

            string right = newGrammer[prod_num].second;
            if (right[0] == 'e')
                continue;
            for (auto c = right.rbegin(); c != right.rend(); c++)
            {
                st.push(*c);
            }
            showStackContent(st);
            cout << "\t\t" << input_string << "\n";
        }
    }

    if (taken){
        cout << "Hence the Input String is Accepted!"<< "\n";
        cout<<"21BCT0157\n";
    }
    else{
        cout << "Hence the Input String is not Accepted"<< "\n";
        cout<<"21BCT0157\n";
    }
    return 0;
}