#include <iostream>
#include <string>
#include <fstream>
using namespace std;
class RecursiveDescentParser {
public:
    RecursiveDescentParser() {
        pointer = 0;
        errorFlag = 0;
    }
    bool startTopDownParser(string s) {
        input = s;
        E();
        if (pointer == s.size() && errorFlag == 0) {
            return true;
        }
        else {
            return false;
        }
    }
private:
    string input;
    int pointer;
    int errorFlag;

    void print(string a, string b) {
        if(pointer < input.length())
            cout << "( " << input[pointer];
        else
            cout << "( @" ;

        cout << ", " << a << " -> " << b  << " )" << endl;
    }
    void E() {
        print("E", "T");
        T();
        print("E", "EPrime");
        EPrime();
    }
    void EPrime() {
        if (input[pointer] == '+') {
            pointer++;
            print("EPrime", "T");
            T();
            print("Eprime", "Eprime");
            EPrime();
        }
    }
    void T() {
        print("T", "F");
        F();
        print("T", "TPrime");
        TPrime();
    }
    void TPrime() {
        if (input[pointer] == '*') {
            pointer++;
            print("TPrime", "F");
            F();
            print("TPrime", "TPrime");
            TPrime();
        }
    }
    void F() {
        if (isalnum(input[pointer])) //identifier
            pointer++;
        else if (input[pointer] == '(') {
            pointer++;
            print("F", "E");
            E();
            if (input[pointer] == ')')
                pointer++;
            else
                errorFlag = 1;
        }
        else
            errorFlag = 1;
    }
};
int main() {
    ifstream inputFile("input.txt");
    string inputStatement;
    getline(inputFile, inputStatement);
    cout << "Input string: " << inputStatement << endl;
    RecursiveDescentParser topDownParser = RecursiveDescentParser();
    bool check = topDownParser.startTopDownParser(inputStatement);
    if (check)
        cout << "Accepted\n";
    else
        cout << "Rejected\n";

    return 0;
}