#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>

#define EPSILON 55

using namespace std;

vector<int> nonTerminals;
map<int, vector<vector<int>>> contextFreeGrammar;
int maxToken;
ifstream inputFile("tokenised-grammar.txt");
ofstream outputFile("tg-non-left-recursive.txt");

class Generator {
    int nextToken;

public: 

    Generator() {
        nextToken = max(100, maxToken + 1);
    } 

    int nextTokenGenerator() {
        return nextToken++;
    }

    void retract() {
        nextToken--;
    }

};

void parseProduction(string s) {

    stringstream ss(s);
    int leftHandSide;
    ss >> leftHandSide;
    maxToken = max(maxToken, leftHandSide);

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
            maxToken = max(maxToken, a);
            temp.push_back(a);
        }
    }
    if(!temp.empty())
        rules.push_back(temp);

    contextFreeGrammar[leftHandSide] = rules;
}

void printCFG() {
    int check = 0;
    for(auto i : contextFreeGrammar) {
        outputFile << i.first << " - " ;
        for(int j = 0; j < i.second.size(); j++) {
            for(auto k: contextFreeGrammar[i.first][j]) {
                outputFile << k << " ";
            }
            if(j != i.second.size() - 1)
                outputFile << "| ";
        }
        if(check != contextFreeGrammar.size() - 1)
            outputFile << endl;
        check++;
    }
}

void removeImmediateLeftRecursion(int s, Generator& generator) {
    vector<vector<int>> currentGrammar = contextFreeGrammar[s]; // We got production rule of s
    // Now take vector<string> out of it
    vector<vector<int>> existingRule;
    vector<vector<int>> newRule;

    int sPrime = generator.nextTokenGenerator();

    for(auto v: currentGrammar) {
        if(v[0] == s) {
            // I got the vector to be modified
            v.erase(v.begin());
            v.push_back(sPrime);
            newRule.push_back(v);
        } else {
            v.push_back(sPrime);
            existingRule.push_back(v);
        }
    }

    if(!newRule.empty()) {
        newRule.push_back({EPSILON});
        contextFreeGrammar[s] = existingRule;
        contextFreeGrammar[sPrime] = newRule;
    } else {
        generator.retract();
    }

    return;
}

void replaceProduction(int a, int b) {
    vector<vector<int>> aGrammar = contextFreeGrammar[a]; 
    vector<vector<int>> modifiedRule;
    for(auto v: aGrammar) {
        if(v[0] == b) {
            vector<vector<int>> bGrammar = contextFreeGrammar[b];
            v.erase(v.begin());
            vector<int> ruleSuffix = v;

            for(auto rulePrefix: bGrammar) { 
                vector<int> prefixSuffix(rulePrefix.size() + ruleSuffix.size());
                prefixSuffix.insert(prefixSuffix.end(), rulePrefix.begin(), rulePrefix.end());
                prefixSuffix.insert(prefixSuffix.end(), ruleSuffix.begin(), ruleSuffix.end());
                modifiedRule.push_back(prefixSuffix);
            }
        } else {
            modifiedRule.push_back(v);
        }
    }
    contextFreeGrammar[a] = modifiedRule;
}

void removeLeftRecursion() {
    Generator generator = Generator();
    int n = nonTerminals.size();
    for(int i=0; i<n; i++) {
        for(int j=0; j<i; j++) {
            for(auto k: contextFreeGrammar[nonTerminals[i]]) {
                if(k[0] == nonTerminals[j])
                    replaceProduction(nonTerminals[i], nonTerminals[j]);
                else 
                    continue;
            } 
        }
        removeImmediateLeftRecursion(nonTerminals[i], generator);
    }
}

int main() {
    string s;
    maxToken = 0;
    while(getline(inputFile, s))
        parseProduction(s);
    removeLeftRecursion();
    printCFG();
}