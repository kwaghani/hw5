#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void buildWords(string current, string floating, const set<string>& dict,
                set<string>& results, int index);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    set<string> results;
    buildWords(in, floating, dict, results, 0);
    return results;
}

// Define any helper functions here
void buildWords(string current, string floating, const set<string>& dict,
                set<string>& results, int index)
{
    if (index == current.size()) {
        if (floating.empty() && dict.find(current) != dict.end()) {
            results.insert(current);
        }
        return;
    }

    if (current[index] != '-') {
        buildWords(current, floating, dict, results, index + 1);
    }
    else {
        for (char c = 'a'; c <= 'z'; ++c) {
            current[index] = c;

            string newFloating = floating;

            auto pos = newFloating.find(c);
            if (pos != string::npos) {
                newFloating.erase(pos, 1);
                buildWords(current, newFloating, dict, results, index + 1);
            }
            else {
                if (newFloating.size() <= count(current.begin(), current.end(), '-')) {
                    buildWords(current, newFloating, dict, results, index + 1);
                }
            }
        }
    }
}
