#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <set>

#define EPSILON 55
#define DOLLAR 56

using namespace std;

int startSymbol;
vector<int> nonTerminals;
map<int, vector<vector<int>>> contextFreeGrammar;
ifstream inputFile("grammarLL.txt");
ofstream outputFile1("first-set.txt");
map<int, set<int>> firstSet;

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
}