#include <iostream>
#include <set>
#include <map>
#include <stack>
#include <vector>
#include <string>
#include <queue>
using namespace std;

#define EPSILON '@'
set<char> validAlphabetSet;
set<char> validOperatorSet({'+', '*', '(', ')'});
map<char, int> operatorPrecedence = {{'*', 3}, {'.', 2}, {'+', 1}};
map<int, int> stateOfNode;
int nodeIdentity = 0;

bool validateRegex(string s) {
    for (int i = 0; i < s.size(); i++) {
        if (validAlphabetSet.find(s[i]) == validAlphabetSet.end() && validOperatorSet.find(s[i]) == validOperatorSet.end()) {
            return false;
        }
    }
    return true;
}

string addConcatenationOperatorToRegex(string s) {
    // We need to add '.' operator between alphabets like ab -> a.b
    string regexWithConcatOp;
    regexWithConcatOp.push_back(s[0]);

    for(int i=1; i<s.size(); i++) {
        if((validAlphabetSet.find(s[i]) != validAlphabetSet.end() && validAlphabetSet.find(s[i-1]) != validAlphabetSet.end())
            || (s[i] == '(' && (validAlphabetSet.find(s[i-1]) != validAlphabetSet.end() || s[i-1] == ')'))) {
            regexWithConcatOp.push_back('.');
            regexWithConcatOp.push_back(s[i]);
        } else if(i != s.size()-1 && ((s[i] == ')' && validAlphabetSet.find(s[i+1]) != validAlphabetSet.end()) 
            || (s[i] == '*' && (validAlphabetSet.find(s[i+1]) != validAlphabetSet.end() || s[i+1] == '(')))) {
            regexWithConcatOp.push_back(s[i]);
            regexWithConcatOp.push_back('.');
        }
        else {
            regexWithConcatOp.push_back(s[i]);
        }
    }

    return regexWithConcatOp;
}

string convertRegextoPostfix(string s) {
    
    stack<char> st;

    string postfixRegex;
    for(int i=0; i<s.size(); i++) {
        if(validAlphabetSet.find(s[i]) != validAlphabetSet.end()) {
            postfixRegex.push_back(s[i]);
        } else if (s[i] == '(') {
            st.push('(');
        } else if(s[i] == ')') {
            while(st.top() != '(') {
                postfixRegex.push_back(st.top());
                st.pop();
            }
            st.pop();
        } else {
            while(!st.empty() && operatorPrecedence[s[i]] <= operatorPrecedence[st.top()]) {
                postfixRegex.push_back(st.top());
                st.pop();
            }
            st.push(s[i]); 
        }
    }

    while (!st.empty()) {
        postfixRegex.push_back(st.top());
        st.pop();
    }

    return postfixRegex;
}

map<int, vector<vector<int>>> concatOperation(map<int, vector<vector<int>>> nfa1, map<int, vector<vector<int>>> nfa2) {
    
    map<int, vector<vector<int>>> finalNFA;
    for(auto i: nfa1) {
        finalNFA[i.first] = i.second;
    }
    for(auto i: nfa2) {
        finalNFA[i.first] = i.second;
    }

    int startNode;
    vector<int> finalNodes;

    for(auto i : nfa2) {
        if(stateOfNode[i.first] == 0) {
            startNode = i.first;
            stateOfNode[i.first] = 1; // Becomes an intermediate node
        }
    }

    for(auto i : nfa1) {
        if(stateOfNode[i.first] == 2) {
            finalNodes.push_back(i.first);
            stateOfNode[i.first] = 1;
        }
    }
    
    int epsilonColumn = validAlphabetSet.size();
    for(auto i : finalNodes) {
        vector<vector<int>> adjList = finalNFA[i];

        if(adjList[epsilonColumn].size() == 1 && adjList[epsilonColumn][0] == -1) {
            adjList[epsilonColumn].clear();
        }

        adjList[epsilonColumn].push_back(startNode);
        finalNFA[i] = adjList;
    }

    return finalNFA;
}

map<int, vector<vector<int>>> unionOperation(map<int, vector<vector<int>>> nfa1, map<int, vector<vector<int>>> nfa2) {

    map<int, vector<vector<int>>> finalNFA;
    for(auto i: nfa1) {
        finalNFA[i.first] = i.second;
    }
    for(auto i: nfa2) {
        finalNFA[i.first] = i.second;
    }

    vector<int> startNodes;
    vector<int> finalNodes;

    for(auto i : nfa1) {
        if(stateOfNode[i.first] == 0) {
            startNodes.push_back(i.first);
            stateOfNode[i.first] = 1;
        } else if(stateOfNode[i.first] == 2) {
            finalNodes.push_back(i.first);
            stateOfNode[i.first] = 1;
        }
    }

    for(auto i : nfa2) {
        if(stateOfNode[i.first] == 0) {
            startNodes.push_back(i.first);
            stateOfNode[i.first] = 1;
        } else if(stateOfNode[i.first] == 2) {
            finalNodes.push_back(i.first);
            stateOfNode[i.first] = 1;
        }
    }

    int newStartNode = nodeIdentity++;
    int newFinalNode = nodeIdentity++;

    vector<vector<int>> startAdj(validAlphabetSet.size() + 1, vector<int>(1, -1));
    auto finalAdj = startAdj;

    int epsilonColumn = validAlphabetSet.size();
    startAdj[epsilonColumn] = startNodes;
    
    for(auto i : finalNodes) {
        vector<vector<int>> adjList = finalNFA[i];

        if(adjList[epsilonColumn].size() == 1 && adjList[epsilonColumn][0] == -1) {
            adjList[epsilonColumn].clear();
        }

        adjList[epsilonColumn].push_back(newFinalNode);
        finalNFA[i] = adjList;
    }


    finalNFA[newStartNode] = startAdj;
    finalNFA[newFinalNode] = finalAdj;
    stateOfNode[newStartNode] = 0;
    stateOfNode[newFinalNode] = 2;

    return finalNFA;

}

map<int, vector<vector<int>>> kleenStarOperation(map<int, vector<vector<int>>>& nfa1) {
    
    map<int, vector<vector<int>>> finalNFA;
    for(auto i: nfa1) {
        finalNFA[i.first] = i.second;
    }
    
    int startNode, finalNode;
    for(auto i : nfa1) {
        if(stateOfNode[i.first] == 0) {
            startNode = i.first;
            stateOfNode[i.first] = 1; // Becomes an intermediate node
        } else if(stateOfNode[i.first] == 2) {
            finalNode = i.first;
            stateOfNode[i.first] = 1;
        }
    }

    int newStartNode = nodeIdentity++;
    int newFinalNode = nodeIdentity++;

    vector<vector<int>> startAdj(validAlphabetSet.size() + 1, vector<int>(1, -1));
    auto finalAdj = startAdj;

    int epsilonColumn = validAlphabetSet.size();
    startAdj[epsilonColumn] = {startNode, newFinalNode};
    
    vector<vector<int>> adjList = finalNFA[finalNode];

    if(adjList[epsilonColumn].size() == 1 && adjList[epsilonColumn][0] == -1) {
        adjList[epsilonColumn].clear();
    }

    adjList[epsilonColumn].push_back(newFinalNode);
    adjList[epsilonColumn].push_back(startNode);
    finalNFA[finalNode] = adjList;


    finalNFA[newStartNode] = startAdj;
    finalNFA[newFinalNode] = finalAdj;
    stateOfNode[newStartNode] = 0;
    stateOfNode[newFinalNode] = 2;

    return finalNFA;

}

map<int, vector<vector<int>>> thomsonOperation(map<int, vector<vector<int>>>& nfa1, map<int, vector<vector<int>>> nfa2, char ch) {
    if(ch == '.') {
        /* Iterate over nfa2. Get the start node. 
        Iterate over nodes of nfa1. Find the final nodes. 
        Attach final nodes of nfa1 to start nodes of nfa2 using epsilon. */
        
        return concatOperation(nfa1, nfa2);

    } else if(ch == '+') {

        return unionOperation(nfa1, nfa2);

    } else if(ch == '*') {

        return kleenStarOperation(nfa1);
    }
}

void printNFA(map<int, vector<vector<int>>> NFA) {
    
    cout << "epsilon-NFA is: " << endl;
    cout  << "State/Symbol -->" << endl << " |" << endl << " v" << endl << endl << "                        "; 
    for(auto i: validAlphabetSet) {
        cout << i << "      ";
    }
    cout << EPSILON << endl;

    for(auto j: NFA) {
        if(stateOfNode[j.first] == 0) 
            cout << "(s) ";
        else if(stateOfNode[j.first] == 1)
            cout << "    ";
        else
            cout << "(f) ";

        cout << j.first << "->" << "               ";
        for(auto k: j.second) {
            cout << "{ " ;
            for(int l=0; l < k.size(); l++) {
                if(l != k.size() - 1)
                    cout << k[l] << ",";
                else
                    cout << k[l] << " ";
            }
            cout << "} ";
        }
        cout << endl << endl;
    }
}

map<int, vector<vector<int>>> generateNFAForAlphabet(char i) {
    // NFA is a graph. Graph is represented as adjacency matrix. 
        map<int, vector<vector<int>>> adjacenyMatrix;
        stateOfNode[nodeIdentity] = 0;
        stateOfNode[nodeIdentity + 1] = 2;
        
        vector<vector<int>> v1;
        vector<vector<int>> v2;

        for(auto j: validAlphabetSet) {
            if(i == j) {
                v1.push_back({nodeIdentity + 1});
                v2.push_back({-1});
            } else {
                v1.push_back({-1});
                v2.push_back({-1});
            }
        }

        // For EPSILON
        v1.push_back({-1});
        v2.push_back({-1});

        adjacenyMatrix[nodeIdentity] = v1;
        adjacenyMatrix[nodeIdentity + 1] = v2;
        nodeIdentity += 2; // We made two new nodes

        return adjacenyMatrix;
}

int main()
{
    string alphabetSetAsString;
    cout << "Enter Alphabet Set(as space-seperated string): ";
    getline(cin, alphabetSetAsString);

    for(auto ch: alphabetSetAsString) {
        if(ch == ' ')
            continue;
        else
            validAlphabetSet.insert(ch);
    }

    string regex;
    cout << "Enter Regex: ";
    cin >> regex;
    // Validate Regular Expression for valid Alphabet Set and Operator Set
    if (validateRegex(regex)) {
        cout << "Regex validation SUCCESS" << endl;
    } else {
        cout << "Regex validation FAILED. Invalid Regex" << endl;
        return 0;
    }
    
    // For easy NFA creation, we need to add Concat(.) Operator
    string modRegex = addConcatenationOperatorToRegex(regex);
    cout << "Modified Expression is: " << modRegex << endl;

    // For easy parsing, we need to convert Infix Regex to Postfix Expression
    string postfixRegex = convertRegextoPostfix(modRegex);
    cout << "Postfix Expression is: " << postfixRegex << endl;

    int alphabetSetSize = validAlphabetSet.size();

    // Let us evaluate the Postfix Expression
    stack<map<int, vector<vector<int>>>> s;
    for(int i=0; i<postfixRegex.size(); i++) {
        map<int, vector<vector<int>>> firstNFA;
        map<int, vector<vector<int>>> secondNFA;
        if(validAlphabetSet.find(postfixRegex[i]) != validAlphabetSet.end()) { // Operand

            s.push(generateNFAForAlphabet(postfixRegex[i]));

        } else if (postfixRegex[i] == '*') {
            // Unary Op: Pop Once
            firstNFA = s.top();
            s.pop();
            s.push(thomsonOperation(firstNFA, firstNFA, postfixRegex[i]));
        }
        else {
            // It is an operator
            secondNFA = s.top();
            s.pop();
            firstNFA = s.top();
            s.pop();
            s.push(thomsonOperation(firstNFA, secondNFA, postfixRegex[i]));
        }
    }

    map<int, vector<vector<int>>> finalNFA = s.top();
    printNFA(finalNFA);

    return 0;
}