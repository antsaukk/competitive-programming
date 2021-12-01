#include <iostream>
#include <string>
#include <vector>
#include <assert.h>
#include <cmath>

//https://cses.fi/380/result/3098579/ - string matching

using namespace std; 

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



void solve(string& str, string& sub) {
	string s = sub + "#" + str;
	Hash sol;
	sol.z_algorithm(s); 
	auto v = sol.z_array(); int n = sub.size();
	size_t count = 0; 
	for(size_t i = 0; i < v.size(); i++) {
		if (v[i] == n) count++;
	}
	cout << count;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);

	string str;
	string sub; 
	cin >> str >> sub; 

	solve(str, sub);  

	return 0;
}