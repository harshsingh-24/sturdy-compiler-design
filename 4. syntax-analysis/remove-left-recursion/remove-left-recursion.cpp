#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
using namespace std;

vector<string> nonTerminals;
map<string, vector<vector<string>>> contextFreeGrammar;

void parseProduction(string s) {
    nonTerminals.push_back({s[0]});
    vector<vector<string>> rules;
    vector<string> temp;

    for(int i=3; i<s.size(); i++) {
        if(s[i] == '|' ) {
            rules.push_back(temp);
            temp.clear();
        } else 
            temp.push_back({s[i]});
    }
    if(!temp.empty())
        rules.push_back(temp);
    
    contextFreeGrammar[{s[0]}] = rules;
}

void printCFG() {
    for(auto i : contextFreeGrammar) {
        cout << i.first << " -> " ;
        for(int j = 0; j < i.second.size(); j++) {
            for(auto k: contextFreeGrammar[i.first][j]) {
                cout << k;
            }
            if(j != i.second.size() - 1)
                cout << "|";
        }
        cout << endl;
    }
}

void removeImmediateLeftRecursion(string s) {
    vector<vector<string>> currentGrammar = contextFreeGrammar[s]; // We got production rule of s
    // Now take vector<string> out of it
    vector<vector<string>> existingRule;
    vector<vector<string>> newRule;

    for(auto v: currentGrammar) {
        if(v[0] == s) {
            // I got the vector to be modified
            v.erase(v.begin());
            v.push_back(s + "'");
            newRule.push_back(v);
        } else {
            v.push_back(s + "'");
            existingRule.push_back(v);
        }
    }

    if(!newRule.empty()) {
        newRule.push_back({"@"});
        contextFreeGrammar[s] = existingRule;
        contextFreeGrammar[s + "'"] = newRule;
    }
    return;
}

void replaceProduction(string a, string b) {
    vector<vector<string>> aGrammar = contextFreeGrammar[a]; 
    vector<vector<string>> modifiedRule;
    for(auto v: aGrammar) {
        if(v[0] == b) {
            vector<vector<string>> bGrammar = contextFreeGrammar[b];
            v.erase(v.begin());
            vector<string> ruleSuffix = v;

            for(auto rulePrefix: bGrammar) { 
                vector<string> prefixSuffix(rulePrefix.size() + ruleSuffix.size());
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
        removeImmediateLeftRecursion(nonTerminals[i]);
    }
}

int main() {
    ifstream inputFile("input.txt");
    string number;
    getline(inputFile, number);
    int n = stoi(number);
    fflush(stdin);
    string s;
    while(getline(inputFile, s))
        parseProduction(s);
    cout << "Input CFG - " << endl;
    printCFG();
    removeLeftRecursion();
    cout << "Modified CFG - " << endl;
    printCFG();
}