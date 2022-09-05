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

ifstream grammar("../text-files/grammarLL.txt");
ifstream parseTable("../text-files/predictive-parse-table.txt");
ifstream input("../text-files/tokenised-input.txt");
ifstream nameMap("../text-files/token-to-name-map.txt");
ofstream output("../text-files/output.txt");

int startSymbol;
map<pair<int, int>, pair<int, int>> predictiveParsingTable;
vector<pair<int, vector<vector<int>>>> contextFreeGrammar;
vector<int> tokenisedInput;
map<int, string> tokenName;

bool isTerminal(int token) {
    return (token >= 20 && token <= 50);
}

void tokenToNameMapping(string s) {
    string name;
    int token;
    stringstream ss(s);

    ss >> name >> token;
    tokenName[token] = name;
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

string getName(int token) {
    if(tokenName.find(token) != tokenName.end())
        return tokenName[token];
    
    string ans = "Q";
    ans = ans + to_string(token);
    return ans;
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
                output << "Match " << getName(token) << endl;
            } else {
                output << "ERROR. TOKEN MISMATCH. REJECTED!!" << "Expected: " << getName(inputToken) << ", Found: " << getName(token) << endl;
                return;
            }
        } else {

            if(predictiveParsingTable.find({token, inputToken}) == predictiveParsingTable.end()) {
                output << "ERROR. REJECTED. No Entry for in Parse Table for " << getName(token) << " " << getName(inputToken) << endl;
                return;
            }

            pair<int, int> productionIndexInGrammar = predictiveParsingTable[{token, inputToken}];
            int lhs = contextFreeGrammar[productionIndexInGrammar.first].first;
            vector<int> production = contextFreeGrammar[productionIndexInGrammar.first].second[productionIndexInGrammar.second];

            for (auto it = production.rbegin(); it != production.rend(); ++it) {
                st.push(*it);
            }

            output << "output " << getName(lhs) << " -> ";
            for(auto token: production) {
                output << getName(token) << " ";
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
    ifstream findStart("../text-files/tokenised-grammar.txt");
    findStart >> startSymbol;

    string s;
    while(getline(nameMap, s))
        tokenToNameMapping(s);

    while(getline(parseTable, s))
        parsePredictiveParsingTable(s);
    
    while(getline(grammar, s))
        parseProduction(s);

    getline(input, s);
    parseInput(s);

    predictiveParser();
}