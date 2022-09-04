#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <set>
#include <stack>
#include <algorithm>

#define EPSILON 55
#define DOLLAR 56

using namespace std;

ifstream grammar("grammarLL.txt");
ifstream parseTable("predictive-parse-table.txt");
ifstream input("tokenised-input.txt");
ofstream output("output.txt");

int startSymbol;
map<pair<int, int>, pair<int, int>> predictiveParsingTable;
vector<pair<int, vector<vector<int>>>> contextFreeGrammar;
vector<int> tokenisedInput;

bool isTerminal(int token) {
    return (token >= 20 && token <= 50);
}

void parseProduction(string s) {

    stringstream ss(s);
    int leftHandSide;
    ss >> leftHandSide;

    vector<vector<int>> rules;
    vector<int> temp;
    string token;

    while(ss >> token) {
        if(token == "-") {
            continue;
        } else if(token == "|") {
            rules.push_back(temp);
            temp.clear();
        } else {
            int a = stoi(token);
            temp.push_back(a);
        }
    }
    if(!temp.empty())
        rules.push_back(temp);

    contextFreeGrammar.push_back({leftHandSide, rules});
}

void parsePredictiveParsingTable(string s) {
    stringstream ss(s);
    int nonTerminal, terminal, i, j;
    string removeMinus;
    
    ss >> nonTerminal >> terminal >> removeMinus >> i >> j;

    predictiveParsingTable[{nonTerminal, terminal}] = {i, j};
}

void parseInput(string s) {
    stringstream ss(s);
    int token;
    while(ss >> token) {
        tokenisedInput.push_back(token);    
    }
    tokenisedInput.push_back(DOLLAR); // End of Input
}

void predictiveParser() {
    int index = 0;
    stack<int> st;
    st.push(DOLLAR);
    st.push(startSymbol);

    while(st.top() != DOLLAR && tokenisedInput[index] != DOLLAR) {
        int token = st.top();
        st.pop();
        if(token == EPSILON)
            continue;

        int inputToken = tokenisedInput[index];

        if(isTerminal(token)) {
            if(token == tokenisedInput[index]) {
                index++;
                output << "Match " << token << endl;
            } else {
                output << "ERROR. TOKEN MISMATCH. REJECTED!!" << "Expected " << inputToken << " Found " << token << endl;
                return;
            }
        } else {

            if(predictiveParsingTable.find({token, inputToken}) == predictiveParsingTable.end()) {
                output << "ERROR. REJECTED. No Entry for in Parse Table for " << token << " " << inputToken << endl;
                return;
            }

            pair<int, int> productionIndexInGrammar = predictiveParsingTable[{token, inputToken}];
            int lhs = contextFreeGrammar[productionIndexInGrammar.first].first;
            vector<int> production = contextFreeGrammar[productionIndexInGrammar.first].second[productionIndexInGrammar.second];

            for (auto it = production.rbegin(); it != production.rend(); ++it) {
                st.push(*it);
            }

            output << "output " << lhs << " - ";
            for(auto token: production) {
                output << token << " ";
            }
            output << endl;
        }
    }

    if(st.top() == DOLLAR && tokenisedInput[index] == DOLLAR) {
        output << endl << endl << "ACCEPTED" << endl;
        return;
    }

    output << endl << endl << "INPUT MISMATCH. REJECTED!!" << endl;
}

int main() {
    ifstream findStart("tokenised-grammar.txt");
    findStart >> startSymbol;

    string s;
    while(getline(parseTable, s))
        parsePredictiveParsingTable(s);
    
    while(getline(grammar, s))
        parseProduction(s);

    getline(input, s);
    parseInput(s);

    predictiveParser();
}