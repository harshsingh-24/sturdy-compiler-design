#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <algorithm>
#include <set>
#include <sstream>

#define EPSILON 55

using namespace std;

vector<int> nonTerminals;
vector<pair<int, vector<vector<int>>>> contextFreeGrammar;
int maxToken;
ifstream inputFile("tg-non-left-recursive.txt");
ofstream outputFile("grammarLL.txt");

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

    contextFreeGrammar.push_back({leftHandSide, rules});
}

void printCFG() {
    int check = 0;
    for(auto i : contextFreeGrammar) {
        outputFile << i.first << " - " ;
        for(int j = 0; j < i.second.size(); j++) {
            for(auto k: i.second[j]) {
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

void equivalentLeftFactoredGrammar(Generator& generator) {

    for(int z = 0; z < contextFreeGrammar.size(); z++) {
        vector<vector<int>> rhs = contextFreeGrammar[z].second;
        sort(rhs.begin(), rhs.end());

        vector<vector<int>> modifiedRules;
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

            vector<int> prefixString = {rhs[start][0]};

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
                int nonTerminal = generator.nextTokenGenerator();
                prefixString.push_back(nonTerminal);
                modifiedRules.push_back(prefixString);
                

                // New Rules(Z being created here) A->aZ; Z->b1|b2|b3
                vector<vector<int>> newRules;
                for(int k=start; k<=start+size-1; k++) {
                    vector<int> temp;
                    for(int l=prefix; l<rhs[k].size(); l++) {
                        temp.push_back(rhs[k][l]);
                    }
                    if(temp.empty())
                        temp.push_back(EPSILON);

                    newRules.push_back(temp);
                }
                contextFreeGrammar.push_back({nonTerminal, newRules});     
            }
        }   
        contextFreeGrammar[z].second = modifiedRules;
    }
}

int main() {
    string s;
    maxToken = 0;
    while(getline(inputFile, s))
        parseProduction(s);  
    
    Generator generator = Generator();
    equivalentLeftFactoredGrammar(generator);
    printCFG();
}