#include <iostream>
using namespace std;
class Node {
public: 
    bool op; // true - operation, false - operand
    int type; // 1 - +, 2 - '-', 3 - '*', 4 - '/'
    Node* left;
    Node* right;
    float val;
    string mermaid;

    Node(bool o, float v) { // This is for integer node/ leaf nodes
        op = o; 
        type = -1;
        val  = v;
        left = NULL;
        right = NULL;
        mermaid = to_string(v);
    }

    Node(bool o, int t, Node* l, Node* r, float v) { // This is for non-integer node/non-leaf nodes
        op = o;
        type = t;
        val = v;
        left = l;
        right = r;

        if(t == 1) {
            mermaid = "+";
        } else if(t == 2) {
            mermaid = "-";
        } else if(t == 3) {
            mermaid = "*";
        } else if (t == 4) {
            mermaid = "/";
        }  else {
            mermaid = "NULL";
        }
    }
};