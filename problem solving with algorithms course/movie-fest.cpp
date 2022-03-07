/*
In a movie festival n movies will be shown. You know the starting and ending time of each movie.
What is the maximum number of movies you can watch entirely?

INPUT:
The first input line has an integer n: the number of movies.

After this, there are n lines that describe the movies.
Each line has two integers a and b: the starting and ending times of a movie.

OUTPUT:
Print one integer: the maximum number of movies.

CONSTRAINTS:
1 <= n <= 2*10^5
1 <= a <= b <= 10^9
RESULT:
not finished
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

#define ui64 uint64_t

using namespace std;

typedef pair<ui64, ui64> P;

template<typename T>
void display(T val){
        cout << val;
}

void read(vector<P>& v) {
        ui64 a, b;
        for(size_t i = 0; i < v.size(); i++) {
                cin >> a >> b; 
                v[i] = make_pair(a, b);
        }
}

// look at chap6 competitives programmer handbook
ui64 solve(vector<P>& v){
        ui64 count = 1;
        ui64 last_selected = 0;
        for(size_t current = 1; current < v.size(); current++) {
                if (v[current].first >= v[last_selected].second) {
                        count++;
                        last_selected++;
                }
        }
        return count;
}


// untie std in/out to speed up computation
void desyncio() {
        ios_base::sync_with_stdio(false);
        cin.tie(nullptr);
}

int main() {
        desyncio();

        ui64 n; 
        cin >> n;

        vector<P> v(n);
        read(v);

        auto cmp = [](const P& p1, 
                      const P& p2) {
                if(p1.second < p2.second) return true;
                if(p1.second == p2.second) 
                        return p1.first < p2.first;
                return false;
        };
        sort(v.begin(), v.end(), cmp);

        display(solve(v));
        return 0;
}