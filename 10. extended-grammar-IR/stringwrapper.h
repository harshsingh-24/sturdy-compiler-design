#include <iostream>
using namespace std;
class Wrapper {
public: 
    string label;
    int x = 0;

    Wrapper(string l) {
        label = l;
    }
};