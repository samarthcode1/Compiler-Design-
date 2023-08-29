#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int identifier(string str)
{
    if (str.size() == 0)
    {
        return 0;
    }
    for (int i = 0; i < str.size(); i++)
    {
        if (str[i] != 'a' && str[i] != 'b')
        {
            return 0;
        }
    }
    
    int i;
    if (str[0] == 'a')
    {
        if (str.size() == 1)
        {
            return 1;
        }
        for (i = 1; i < str.size(); i++)
        {
            if (str[i] != 'a')
            {
                break;
            }
        }
        if (i == str.size())
        {
            return 0;
        }
        for (int j = i; j < str.size(); j++)
        {
            if (str[j] == 'a')
            {
                return 0;
            }
        }
        return 1;
    }
    else
    {
        for (int i = 0; i < str.size(); i++)
        {
            if (str[i] == 'a')
            {
                return 0;
            }
        }
        return 1;
    }
    return 1;
}
int main()
{
    ifstream fin;
    string str;
    fin.open("21bct0157_q3.txt");
    int i;
    if (!fin.is_open())
    {
        cout << "Error in opening the file\n"; 
        exit(0);
    }
    while (fin >> str)
    {
        i = identifier(str);
        if (i == 1)
        {
            cout << "The String " << str << " is accpeted.\n";
        }
        else
        {
            cout << "The String " << str << " is not accpeted.\n";
        }
    }
    fin.close();
    return 0;
}