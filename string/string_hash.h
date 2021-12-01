#pragma once

#include <vector>
#include <string>
#include <assert.h>
#include <cmath>

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
	static const int64_t A = 3;//911382323; 
	static const int64_t B = 97;//972663749;
};