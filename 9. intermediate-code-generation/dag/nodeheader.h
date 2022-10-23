#include <iostream>
#include <string>
using namespace std;
class Node {
public: 
    int type; // 1 - +, 2 - '-', 3 - '*', 4 - '/'
    Node* left;
    Node* right;
    float val;
    string mermaid;
    string extra;

    Node(string alpha, float v) { // This is for integer node/ leaf nodes
        type = -1;
        val  = v;
        left = NULL;
        right = NULL;
        extra = alpha;
        mermaid = to_string(v);
    }

    Node(int t, Node* l, Node* r, float v, string alpha) { // This is for non-integer node/non-leaf nodes
        type = t;
        val = v;
        left = l;
        right = r;
        extra = alpha;

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