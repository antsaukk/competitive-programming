#include <iostream>
#include <string>
#include <vector>
#include <assert.h>
#include <cmath>
#include <utility>

// https://cses.fi/381/task/D - palindrome matching

class Hash {
public:
	Hash() {}

	void build_hash(const std::string& s) {
		size_t n = s.size(); 
		h.resize(n); 
		p.resize(n);
		hfy(s); 
		pfy(n);
	}

	void hfy(const std::string& s) {
		h[0] = s[0]; 
		for(size_t k = 1; k < s.size(); k++) {
			h[k] = (h[k-1] * A + s[k]) % B;
		}
	}

	void pfy(size_t n) {
		p[0] = 1; 
		for(size_t k = 1; k < n; k++) {
			p[k] = (p[k-1] * A) % B;
		}
	}

	int get_hash(size_t a, size_t b) {
		assert(b > a);
		if (a > 0){
			return (h[b] - h[a-1] * p[b-a+1]) % B;
		} else return h[b];
	}

	void z_algorithm(std::string& s) {
		int n = s.size();
		z.resize(n); 
		int x = 0;
		int y = 0;
		for (int i = 1; i < n; i++) {
			z[i] = std::max(0, std::min(z[i-x], y-i+1));
			while(i + z[i] < n && s[z[i]] == s[i + z[i]]){
				x = i; 
				y = i + z[i]; 
				z[i]++;
			}
		}
	}

	std::vector<int>& z_array() {
		return z;
	}

private:
	std::vector<int> h;
	std::vector<int> p;
	std::vector<int> z;
	static const int64_t A = 911382323; //3
	static const int64_t B = 972663749; //97
};


void solve(string& str, size_t n, size_t m) {
	Hash sol; 
	sol.build_hash(str);
	for(size_t i = 0; i < m; i++) {
		int a, b, c; 
		cin >> a >> b >> c; 
		if(a==1) {
			Hash hsh;
			str[b] = "x";
			hsh.build_hash(str);
		} else {
			if(sol.get_hash(a, (a+b)/2) == sol.get_hash(a, (a+b)/2));
			//not finished
		}
	}
	
}

int main() {
	//std::ios_base::sync_with_stdio(false);
	//std::cin.tie(nullptr);

	size_t n, m; 
	cin >> n >> m;
	string s; 
	cin >> s;

	solve(s, n, m);

	return 0;
}