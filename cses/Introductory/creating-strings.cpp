/*
Given a string, your task is to generate all different strings that can be created using its characters.

INPUT:
The only input line has a string of length n. Each character is between a–z.

OUTPUT:
First print an integer k: the number of strings.
Then print k lines: the strings in alphabetical order.

CONSTRAINTS:
1 <= n <= 8
RESULT:
https://cses.fi/alon/result/3643356/
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

#define ui64 uint64_t

using namespace std;

template<typename T>
void display(T val){
        cout << val << "\n";
}

size_t solve(string& word, vector<string>& v){
        do {
                v.push_back(word);
        } while(next_permutation(word.begin(), word.end()));
        return v.size();
}


void show_output(vector<string>& v) {
        for(auto word : v)
                cout << word << "\n";
}

// untie std in/out to speed up computation
void desyncio() {
        ios_base::sync_with_stdio(false);
        cin.tie(nullptr);
}

int main() {
        desyncio();

        string word;
        cin >> word;
        sort(word.begin(), word.end());

        vector<string> v;

        display(solve(word, v));
        show_output(v);
        return 0;
}