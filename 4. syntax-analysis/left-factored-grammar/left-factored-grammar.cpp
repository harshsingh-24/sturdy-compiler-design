#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <algorithm>
#include <set>
using namespace std;

set<char> nonTerminals;
vector<pair<string, vector<vector<string>>>> contextFreeGrammar;

string nonTerminalGenerator() {
    string s = {*nonTerminals.begin()};
    s += "'";
    nonTerminals.erase(nonTerminals.begin());
    return s;
}

void parseProduction(string s) {
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
    
    contextFreeGrammar.push_back({{s[0]}, rules});
}

void printCFG() {
    for(auto i : contextFreeGrammar) {
        cout << i.first << " -> " ;
        for(int j = 0; j < i.second.size(); j++) {
            for(auto k: i.second[j]) {
                cout << k;
            }
            if(j != i.second.size() - 1)
                cout << "|";
        }
        cout << endl;
    }
}

void equivalentLeftFactoredGrammar() {

    for(int z = 0; z < contextFreeGrammar.size(); z++) {
        vector<vector<string>> rhs = contextFreeGrammar[z].second;
        sort(rhs.begin(), rhs.end());

        vector<vector<string>> modifiedRules;
        vector<vector<int>> groups; // 0 - low, start, prefixlength

        int startOfGroup = 0, sizeOfGroup = 1, prefixLength = 1;
        for(int j=1; j<rhs.size(); j++) {
            if(rhs[j][0] == rhs[j-1][0]) {
                // Matched group
                sizeOfGroup++;
            } else {
                groups.push_back({startOfGroup, sizeOfGroup, prefixLength});
                startOfGroup = j;
                sizeOfGroup = 1;
            }
        }
        groups.push_back({startOfGroup, sizeOfGroup, prefixLength});

        for(int j=0; j<groups.size(); j++) {

            int start = groups[j][0];
            int size = groups[j][1];
            int prefix = groups[j][2];

            vector<string> prefixString = {rhs[start][0]};

            if(size == 1) {
                modifiedRules.push_back(rhs[start]);
            } else {
                while(1) {
                    bool flag = true;
                    for(int k=start+1; k<=start+size-1; k++) {
                        if(prefix >= rhs[k].size() || prefix >= rhs[k-1].size()) {
                            flag = false;
                            break;
                        }
                        if(rhs[k][prefix] != rhs[k-1][prefix]) {
                            flag = false;
                            break;
                        }
                    }
                    if(!flag)
                        break;
                    
                    prefixString.push_back(rhs[start][prefix]);
                    prefix++;
                }

                groups[j][2] = prefix;
                string nonTerminal = nonTerminalGenerator();
                prefixString.push_back(nonTerminal);
                modifiedRules.push_back(prefixString);
                

                // New Rules(Z being created here) A->aZ; Z->b1|b2|b3
                vector<vector<string>> newRules;
                for(int k=start; k<=start+size-1; k++) {
                    vector<string> temp;
                    for(int l=prefix; l<rhs[k].size(); l++) {
                        temp.push_back(rhs[k][l]);
                    }
                    newRules.push_back(temp);
                }
                contextFreeGrammar.push_back({nonTerminal, newRules});     
     
            }
        }   
        contextFreeGrammar[z].second = modifiedRules;
    }
}

int main() {
    for(char ch='A'; ch<='Z'; ch++) {
        nonTerminals.insert(ch);
    }
    ifstream inputFile("input.txt");
    string number;
    getline(inputFile, number);
    int n = stoi(number);
    fflush(stdin);
    string s;
    while(n--) {
        getline(inputFile, s);
        parseProduction(s);
    }  
    cout << "Input CFG - " << endl;
    printCFG();
    equivalentLeftFactoredGrammar();
    cout << "Left Factored Grammar -  " << endl;
    printCFG();
}