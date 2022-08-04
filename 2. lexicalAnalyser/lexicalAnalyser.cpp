#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;
typedef int (*ExecuteMachinesDataType) (string s, int index);

vector<pair<string, string>> sequenceOfTokens; // Final Output

set<string> digitSet({"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"});
set<string> mathematicalSymbolSet({"E", ".", "+", "-"});
set<string> whitespaceSet({" ", "\t", "\n"});
set<string> letterSet;

map<int, string> machinesWithPriority = {{1, "relop"}, {2, "if"}, {3, "then"}, {4, "else"}, {5, "identifier"}, {6, "number"}, {7, "whitespace"}};

// "who's is it"<int> -> every node: <0,'a'> -> 1 : <start, label> -> <final node>
map<int, map<pair<int, string>, int>> transitionDiagram = {
    {
        1, { // {0-8} - relop
            {{0, "<"}, 1},
            {{1, "="}, 2},
            {{1, ">"}, 3},
            {{1, "other"}, 4}, // o - other
            {{0, "="}, 5},
            {{0, ">"}, 6},
            {{6, "="}, 7},
            {{6, "other"}, 8}
        }
    }, // transition diagram of relational operators
    {   
        2, { // {9-12} - if
            {{9, "i"}, 10},
            {{10, "f"}, 11},
            {{11, "nld"}, 12}, // nld is non-letter or non-digit
        }
    },
    {   
        3, { // {13-18} - then
            {{13, "t"}, 14},
            {{14, "h"}, 15},
            {{15, "e"}, 16},
            {{16, "n"}, 17},
            {{17, "nld"}, 18},
        }
    },
    {   
        4, { // {19-24} - else
            {{19, "e"}, 20},
            {{20, "l"}, 21},
            {{21, "s"}, 22},
            {{22, "e"}, 23},
            {{23, "nld"}, 24},
        }
    },
    {   
        5, { // {25-27} - identifier
            {{25, "letter"}, 26},
            {{26, "ld"}, 26}, // ld is letter or digit
            {{26, "other"}, 27},
        }
    },
    {   
        6, { // {28-37} - number
            {{28, "digit"}, 29},
            {{29, "digit"}, 29},
            {{29, "E"}, 32},
            {{29, "."}, 30},
            {{29, "other"}, 36},
            {{30, "digit"}, 31},
            {{31, "digit"}, 31},
            {{31, "other"}, 37},
            {{31, "E"}, 32},
            {{32, "+"}, 33},
            {{32, "-"}, 33},
            {{32, "digit"}, 34},
            {{33, "digit"}, 34},
            {{34, "digit"}, 34},
            {{34, "other"}, 35},
        }
    },
    {
        7, { // {38 - 40} - whitespace
            {{38, "delim"}, 39},
            {{39, "delim"}, 39},
            {{39, "other"}, 40}
        }
    }
};

// 0 - start, 1 - intermediate, 2 - final, 3- retracting
map<int, int> stateOfNode = {
    {0, 0}, {1, 1}, {2, 2}, {3, 2}, {4, 3}, {5, 2}, {6, 1}, {7, 2}, {8, 3},
    {9, 0}, {10, 1}, {11, 1}, {12, 3},
    {13, 0}, {14, 1}, {15, 1}, {16, 1}, {17, 1}, {18, 3},
    {19, 0}, {20, 1}, {21, 1}, {22, 1}, {23, 1}, {24, 3},
    {25, 0}, {26, 1}, {27, 3},
    {28, 0}, {29, 1}, {30, 1}, {31, 1}, {32, 1}, {33, 1}, {34, 1}, {35, 3}, {36, 3}, {37, 3},
    {38, 0}, {39, 1}, {40, 3}
};

map<int, set<string>> allowableTransitions = {
    {1, {">", "=", "<"}},
    {2, {"i", "f"}},
    {3, {"t", "h", "e", "n"}},
    {4, {"e", "l", "s", "e"}},
    {7, {" ", "\t", "\n"}}
};

map<int, int> startNode = {{1, 0}, {2, 9}, {3, 13}, {4, 19}, {5, 25}, {6, 28}, {7, 38}};

int relopMachine(string s, int index) {
    
    int i = index, currentNode = startNode[1];
    while(i < s.size() && stateOfNode[currentNode] != 2 && stateOfNode[currentNode] != 3 ) {
        if(transitionDiagram[1].find({currentNode, {s[i]}}) != transitionDiagram[1].end()) {
            // This means that transtion exists for the node
            currentNode = transitionDiagram[1][{currentNode, {s[i]}}];
            i++;
        } else if(transitionDiagram[1].find({currentNode, "other"}) != transitionDiagram[1].end()) {
            // This means that transtion exists for the node
            currentNode = transitionDiagram[1][{currentNode, "other"}];
            i++;
        } else {
            return index;
        }
    }

    if(stateOfNode[currentNode] != 2 && stateOfNode[currentNode] != 3) {
        return index;
    }
    
    // Retract Node
    if(stateOfNode[currentNode] == 3) {
        i--;
    } 
    string symbol = s.substr(index, i - index);
    sequenceOfTokens.push_back({"relop", symbol});

    return i;
}

int ifMachine(string s, int index) {

    int i = index, currentNode = startNode[2];
    while(i < s.size() && stateOfNode[currentNode] != 2 && stateOfNode[currentNode] != 3 ) {
        if(transitionDiagram[2].find({currentNode, {s[i]}}) != transitionDiagram[2].end()) {
            // This means that transtion exists for the node
            currentNode = transitionDiagram[2][{currentNode, {s[i]}}];
            i++;
        } else if(transitionDiagram[2].find({currentNode, "nld"}) != transitionDiagram[2].end()) {
            // This means that transtion exists for the node
            if(digitSet.find({s[i]}) ==  digitSet.end() && letterSet.find({s[i]}) == letterSet.end()) {
                currentNode = transitionDiagram[2][{currentNode, "nld"}];
                i++;
            }
            else {
                return index;
            }
        } else {
            return index;
        }
    }

    if(stateOfNode[currentNode] != 2 && stateOfNode[currentNode] != 3) {
        return index;
    }

    // Retract Node
    if(stateOfNode[currentNode] == 3) {
        i--;
    } 
    sequenceOfTokens.push_back({"if", ""});
    return i;
}

int thenMachine(string s, int index) {
    int i = index, currentNode = startNode[3];
    while(i < s.size() && stateOfNode[currentNode] != 2 && stateOfNode[currentNode] != 3 ) {
        if(transitionDiagram[3].find({currentNode, {s[i]}}) != transitionDiagram[3].end()) {
            // This means that transtion exists for the node
            currentNode = transitionDiagram[3][{currentNode, {s[i]}}];
            i++;
        } else if(transitionDiagram[3].find({currentNode, "nld"}) != transitionDiagram[3].end()) {
            // This means that transtion exists for the node
            if(digitSet.find({s[i]}) ==  digitSet.end() && letterSet.find({s[i]}) == letterSet.end()) {
                currentNode = transitionDiagram[3][{currentNode, "nld"}];
                i++;
            }
            else {
                return index;
            }
        } else {
            return index;
        }
    }

    if(stateOfNode[currentNode] != 2 && stateOfNode[currentNode] != 3) {
        return index;
    }

    // Retract Node
    if(stateOfNode[currentNode] == 3) {
        i--;
    } 
    sequenceOfTokens.push_back({"then", ""});
    return i;
}

int elseMachine(string s, int index) {
    int i = index, currentNode = startNode[4];
    while(i < s.size() && stateOfNode[currentNode] != 2 && stateOfNode[currentNode] != 3 ) {
        if(transitionDiagram[4].find({currentNode, {s[i]}}) != transitionDiagram[4].end()) {
            // This means that transtion exists for the node
            currentNode = transitionDiagram[4][{currentNode, {s[i]}}];
            i++;
        } else if(transitionDiagram[4].find({currentNode, "nld"}) != transitionDiagram[4].end()) {
            // This means that transtion exists for the node
            if(digitSet.find({s[i]}) ==  digitSet.end() && letterSet.find({s[i]}) == letterSet.end()) {
                currentNode = transitionDiagram[4][{currentNode, "nld"}];
                i++;
            }
            else {
                return index;
            }
        } else {
            return index;
        }
    }

    if(stateOfNode[currentNode] != 2 && stateOfNode[currentNode] != 3) {
        return index;
    }

    // Retract Node
    if(stateOfNode[currentNode] == 3) {
        i--;
    } 
    sequenceOfTokens.push_back({"else", ""});
    return i;
}

int identifierMachine(string s, int index) {
    int i = index, currentNode = startNode[5];
    while(i < s.size() && stateOfNode[currentNode] != 2 && stateOfNode[currentNode] != 3 ) {
        if(transitionDiagram[5].find({currentNode, "letter"}) != transitionDiagram[5].end() && letterSet.find({s[i]}) != letterSet.end()) {
            // This means that transtion exists for the node
            currentNode = transitionDiagram[5][{currentNode, "letter"}];
            i++;
        } else if(transitionDiagram[5].find({currentNode, "ld"}) != transitionDiagram[5].end() && (digitSet.find({s[i]}) !=  digitSet.end() || letterSet.find({s[i]}) != letterSet.end())) {
            // This means that transtion exists for the node
            currentNode = transitionDiagram[5][{currentNode, "ld"}];
            i++;
        } else if(transitionDiagram[5].find({currentNode, "other"}) != transitionDiagram[5].end()) {
            // This means that transtion exists for the node
            currentNode = transitionDiagram[5][{currentNode, "other"}];
            i++;
        } else {
            return index;
        }
    }

    if(stateOfNode[currentNode] != 2 && stateOfNode[currentNode] != 3) {
        return index;
    }

    // Retract Node
    if(stateOfNode[currentNode] == 3) {
        i--;
    } 
    string symbol = s.substr(index, i - index);
    sequenceOfTokens.push_back({"identifier", symbol});
    return i;
}

int numberMachine(string s, int index) {
    int i = index, currentNode = startNode[6];
    while(i < s.size() && stateOfNode[currentNode] != 2 && stateOfNode[currentNode] != 3 ) {
        if(transitionDiagram[6].find({currentNode, "digit"}) != transitionDiagram[6].end() && digitSet.find({s[i]}) != digitSet.end()) {
            // This means that transtion exists for the node
            currentNode = transitionDiagram[6][{currentNode, "digit"}];
            i++;
        } else if(transitionDiagram[6].find({currentNode, {s[i]}}) != transitionDiagram[6].end() && (mathematicalSymbolSet.find({s[i]}) !=  mathematicalSymbolSet.end())) {
            // This means that transtion exists for the node
            currentNode = transitionDiagram[6][{currentNode, {s[i]}}];
            i++;
        } else if(transitionDiagram[6].find({currentNode, "other"}) != transitionDiagram[6].end()) {
            // This means that transtion exists for the node
            currentNode = transitionDiagram[6][{currentNode, "other"}];
            i++;
        } else {
            return index;
        }
    }

    if(stateOfNode[currentNode] != 2 && stateOfNode[currentNode] != 3) {
        return index;
    }

    // Retract Node
    if(stateOfNode[currentNode] == 3) {
        i--;
    } 
    string symbol = s.substr(index, i - index);
    sequenceOfTokens.push_back({"number", symbol});
    return i;
}

int whitespaceMachine(string s, int index) {

    int i = index, currentNode = startNode[7];
    while(i < s.size() && stateOfNode[currentNode] != 2 && stateOfNode[currentNode] != 3 ) {
        if(transitionDiagram[7].find({currentNode, "delim"}) != transitionDiagram[7].end() && whitespaceSet.find({s[i]}) != whitespaceSet.end()) {
            // This means that transtion exists for the node
            currentNode = transitionDiagram[7][{currentNode, "delim"}];
            i++;
        } else if(transitionDiagram[7].find({currentNode, "other"}) != transitionDiagram[7].end()) {
            // This means that transtion exists for the node
            currentNode = transitionDiagram[7][{currentNode, "other"}];
            i++;
        } else {
            return index;
        }
    }

    if(stateOfNode[currentNode] != 2 && stateOfNode[currentNode] != 3) {
        return index;
    }

    // Retract Node
    if(stateOfNode[currentNode] == 3) {
        i--;
    } 
    return i;
}

ExecuteMachinesDataType ExecuteMachines[] = 
{
    relopMachine, 
    ifMachine, 
    thenMachine,
    elseMachine,
    identifierMachine,
    numberMachine,
    whitespaceMachine
};

void print(vector<pair<string, string>> sequenceOfTokens) {
    for(auto i: sequenceOfTokens) {
        cout << "(" << i.first << ", " << i.second << ")" << endl;
    }
}

void lexicalAnalyser(string s) {
    // We will recursively iterate over machines serially until fully accepted

    int length = s.size(), track = 0;
    
    while(track <= length && s[track] != '#') {
        for(int machineNumber = 1; machineNumber <= 7; machineNumber++) {
            int breakCall = ExecuteMachines[machineNumber - 1](s,track);
            if(breakCall > track) {
                track = breakCall;
                break; // accepted state
            }
        }
    }

    print(sequenceOfTokens);
}

int main() {

    // Letter Set Initialisation
    for(char c='a', d='A'; c<='z', d<='Z';c++, d++) {
        string s1 = "", s2="";
        s1 += c; s2 += d;
        letterSet.insert(s1);
        letterSet.insert(s2);
    }

    // allowableTransitions addition of entries
    set<string> temp1, temp2;
    set_union(letterSet.begin(), letterSet.end(), digitSet.begin(), digitSet.end(), inserter(temp1,temp1.begin()));
    set_union(mathematicalSymbolSet.begin(), mathematicalSymbolSet.end(), digitSet.begin(), digitSet.end(), inserter(temp2,temp2.begin()));
    allowableTransitions[5] = temp1;
    allowableTransitions[6] = temp2;


    string inputStatement;
    cout << "Enter statement: ";
    getline(cin, inputStatement);
    inputStatement.push_back('#');

    // Feeding the input to lexical analyser
    lexicalAnalyser(inputStatement);

    return 0;
}