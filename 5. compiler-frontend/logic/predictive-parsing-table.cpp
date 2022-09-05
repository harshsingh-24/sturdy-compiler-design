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
ifstream first("../text-files/first-set.txt");
ifstream follow("../text-files/follow-set.txt");
ofstream parseTable("../text-files/predictive-parse-table.txt");

map<int, set<int>> firstSet;
map<int, set<int>> followSet;
vector<pair<int, vector<vector<int>>>> contextFreeGrammar;
map<pair<int, int>, pair<int, int>> predictiveParsingTable; // <Non-Terminal, Terminal>  -> <Which Production Rule in Grammar>

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

void parseFirstSet(string s) {
    stringstream ss(s);
    int leftHandSide;
    ss >> leftHandSide;

    set<int> temp;
    string token;

    while(ss >> token) {
        if(token == "-") {
            continue;
        } else {
            int a = stoi(token);
            temp.insert(a);
        }
    }

    firstSet[leftHandSide] = temp;
}

void parseFollowSet(string s) {
    stringstream ss(s);
    int leftHandSide;
    ss >> leftHandSide;

    set<int> temp;
    string token;

    while(ss >> token) {
        if(token == "-") {
            continue;
        } else {
            int a = stoi(token);
            temp.insert(a);
        }
    }

    followSet[leftHandSide] = temp;
}

bool isTerminal(int token) {
    return (token >= 20 && token <= 50);
}

set<int> computeFirstOfExpression(stack<int, vector<int>> s) {

    if(s.empty() || (s.size() == 1 && s.top() == EPSILON))
        return {EPSILON};

    set<int> ans;

    while(!s.empty()) {
        int token = s.top();
        if(isTerminal(token)) {
            ans.insert(token);
            return ans;
        }

        set<int> firstSetToken = firstSet[token];
        if(firstSetToken.find(EPSILON) != firstSetToken.end()) {
            firstSetToken.erase(EPSILON);
            ans.insert(firstSetToken.begin(), firstSetToken.end());
        } else {
            ans.insert(firstSetToken.begin(), firstSetToken.end());
            return ans;
        }
        s.pop();
    }

    ans.insert(EPSILON);
    return ans;
}

void constructPredictiveParsingTable() {
    for(int i=0; i<contextFreeGrammar.size(); i++) {
        int lhs = contextFreeGrammar[i].first;
        vector<vector<int>> productions = contextFreeGrammar[i].second;

        for(int j=0; j<productions.size(); j++) {
            vector<int> production = productions[j];
            reverse(production.begin(), production.end());
            stack<int, vector<int>> alpha(production);

            set<int> firstOfAlpha = computeFirstOfExpression(alpha);

            bool epsilonCheck = false;
            for(auto token: firstOfAlpha) {
                if(token == EPSILON) {
                    epsilonCheck = true;
                } else if(token == DOLLAR) {
                    continue;
                } else {
                    predictiveParsingTable[{lhs, token}] = {i, j}; // Mapped production to pair
                }
            }

            if(epsilonCheck) {
                set<int> followOfLHS = followSet[lhs];
                for(auto token: followOfLHS) {
                    predictiveParsingTable[{lhs, token}] = {i, j};
                }
            }
        }
    }
}

void printPredictiveParsingTable() {
    int index = 0;
    for(auto i: predictiveParsingTable) {
        parseTable << i.first.first << " " << i.first.second << " - " << i.second.first << " " << i.second.second;
        if(index != predictiveParsingTable.size() - 1)
            parseTable << endl;
        index++;
    }
}

int main() {
    string s;
    while(getline(grammar, s))
        parseProduction(s);

    while(getline(first, s))
        parseFirstSet(s); 

    while(getline(follow, s))
        parseFollowSet(s); 

    constructPredictiveParsingTable();

    printPredictiveParsingTable();
}