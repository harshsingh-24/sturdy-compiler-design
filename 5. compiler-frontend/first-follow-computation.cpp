#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <set>
#include <stack>

#define EPSILON 55
#define DOLLAR 56

using namespace std;

int startSymbol;
vector<int> nonTerminals;
map<int, vector<vector<int>>> contextFreeGrammar;
// ifstream inputFile("grammarLL.txt");
ifstream inputFile("grammarLL.txt");
ofstream outputFile1("first-set.txt");
ofstream outputFile2("follow-set.txt");
map<int, set<int>> firstSet;
map<int, set<int>> followSet;

bool isTerminal(int token) {
    return (token >= 20 && token <= 50);
}

void parseProduction(string s) {

    stringstream ss(s);
    int leftHandSide;
    ss >> leftHandSide;

    nonTerminals.push_back(leftHandSide);

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

    contextFreeGrammar[leftHandSide] = rules;
}

set<int> firstSetComputation(int nonTerminal) {
    if(firstSet[nonTerminal].size() != 0) {
        return firstSet[nonTerminal];
    }
    vector<vector<int>> rhs = contextFreeGrammar[nonTerminal];
    
    set<int> currentFirstSet;
    for(auto production: rhs) {
        if(production.size() == 1 && production[0] == EPSILON) {
            currentFirstSet.insert(EPSILON);
            continue;
        }
        
        for(int i=0; i<production.size(); i++) {
            int token = production[i];
            if(isTerminal(token)) {
                currentFirstSet.insert(token);
                break;
            } else {
                set<int> temp = firstSetComputation(token);
                if(temp.find(EPSILON) == temp.end()) {
                    currentFirstSet.insert(temp.begin(), temp.end());
                    break;
                }

                if(i != production.size() - 1) {
                    temp.erase(EPSILON);
                }
                if(nonTerminal == startSymbol) {
                    temp.insert(DOLLAR);
                }
                currentFirstSet.insert(temp.begin(), temp.end());
            }
        }
    }

    firstSet[nonTerminal] = currentFirstSet;
    return currentFirstSet;
}

void printFirstSet() {
    int index = 0;
    for(auto i: firstSet) {
        outputFile1 << i.first << " - "; 
        for(auto j: i.second) {
            outputFile1 << j << " ";
        }
        if(index != firstSet.size() - 1)
            outputFile1 << endl;
        index++;
    }
}

void printFollowSet() {
    int index = 0;
    for(auto i: followSet) {
        outputFile2 << i.first << " - "; 
        for(auto j: i.second) {
            outputFile2 << j << " ";
        }
        if(index != followSet.size() - 1)
            outputFile2 << endl;
        index++;
    }
}

set<int> computeFirstOfExpression(stack<int> s) {

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

void followSetComputation() {

    for(auto k: nonTerminals) {
        if(k == startSymbol)
            followSet[k] = {DOLLAR};
        else
            followSet[k] = {};
    }

    for(auto k: contextFreeGrammar) {
        int lhs = k.first;
        vector<vector<int>> rhs = k.second;

        for(auto production : rhs) {
            stack<int> betaSuffix;
            for(int i=production.size() - 1; i>= 0; i--) {
                int token = production[i];

                if(isTerminal(token) || token == EPSILON) {
                    betaSuffix.push(token);
                    continue;
                }

                set<int> firstOfBetaSuffix = computeFirstOfExpression(betaSuffix);

                if(firstOfBetaSuffix.find(EPSILON) != firstOfBetaSuffix.end()) {
                    followSet[token].insert(lhs);
                    firstOfBetaSuffix.erase(EPSILON);
                }

                followSet[token].insert(firstOfBetaSuffix.begin(), firstOfBetaSuffix.end());
                // Some code

                betaSuffix.push(token);
            }
        }
    }

    // Expand the table
    bool flag = true;
    while(flag) {
        flag = false;

        for(auto i: followSet) { // Iterate over table until it grows

            set<int> temp;
            for(auto token: i.second) {
                if(token == DOLLAR || isTerminal(token)) 
                    continue;

                temp.insert(followSet[token].begin(), followSet[token].end()); // Substitute Non-Terminal with its set
            }
            int oldSize = i.second.size();
            followSet[i.first].insert(temp.begin(), temp.end());
            int newSize = followSet[i.first].size();

            if(newSize > oldSize)
                flag = true;
        }
    }

    // Delete Non-Terminals from table

    for(auto i: followSet) {
        set<int> onlyTerminalsSet;
        for(auto token: i.second) {
            if(isTerminal(token) || token == DOLLAR) {
                onlyTerminalsSet.insert(token);
            }
        }
        followSet[i.first] = onlyTerminalsSet;
    }
}

int main() {
    
    ifstream findStart("tokenised-grammar.txt");
    findStart >> startSymbol;

    string s;
    while(getline(inputFile, s))
        parseProduction(s);

    for(int i=0; i<nonTerminals.size(); i++) {
        firstSetComputation(nonTerminals[i]);
    }

    printFirstSet();

    followSetComputation();

    printFollowSet();
}