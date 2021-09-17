#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

int main() {
 size_t n; 
 cin >> n;

 string word;

 vector<string> words(n);
 vector<int> mapp(n, 1); 
 for(size_t i = 0; i < n; i++) {
    cin >> word; 
    words.push_back(word);
 }
 
 map<string, vector<string>> results;
 for (size_t i = 0; i < n; i++) {
    set<char> container;
    for (auto w : words[i]) 
        container.insert(w);
    for (size_t j = i; j < n; j++) {
        if (i!=j && words[j].size() == words[i].size() && mapp[j]!=-1) {
            bool l = true;
            for (auto l : words[j]) {
                l &= (container.count(l) == 1);
            }
            if (l) {
             results[words[i]].push_back(words[j]);
             mapp[j] = -1;
            }      
        } 
    }
    mapp[i] = -1;
 }

 cout << results.size() << endl; 

 for (auto& group : results) {
    cout << 1 + group.second.size() << endl;
    cout << group.first << endl;
    for (auto& s : group.second) {
        cout << s << endl;
    }
 }

 return 0;
}