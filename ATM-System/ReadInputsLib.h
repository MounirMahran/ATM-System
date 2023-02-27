#pragma once

#include <vector>
#include <iostream>
#include <string>
using namespace std;

namespace ReadInput {

    float ReadPositiveFloatNumber(string Message) {
        float Num;
        do {
            cout << Message << endl;
            cin >> Num;
        } while (Num <= 0);

        return Num;
    }

    int ReadPositiveIntNumber(string Message) {
        int Num;
        do {
            cout << Message << endl;
            cin >> Num;
        } while (Num <= 0);

        return Num;
    }

    string ReadString(string Message) {
        string Str;

        cout << Message << endl;
        getline(cin >> ws , Str);

        return Str;
    }

    char ReadCharacter(string Message) {
        char Ch;
        cout << Message << endl;
        cin >> Ch;
        return Ch;
    }

    int ReadNumInRange(int From, int To, string Message) {
        int Num;

        do {
            cout << Message << endl;
            cin >> Num;
        } while (Num < From || Num > To);
        return Num;
    }

    int ReadNumber(string Message) {
        int Num;
        cout << Message << endl;
        cin >> Num;

        while (cin.fail()) {

            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            cout << "Invalid number, please enter a valid one" << endl;
            cin >> Num;
        }
        return Num;
    }

    void ReadVector(vector <int>& vNumbers) {
        int Num = 0;
        char ReadMore;
        do {
            Num = ReadInput::ReadNumber("Please enter an integer number");
            vNumbers.push_back(Num);
            ReadMore = ReadInput::ReadCharacter("If you want to continue enter Y and if not enter N");

        } while (ReadMore == 'y' || ReadMore == 'Y');
    }

}


