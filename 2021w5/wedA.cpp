#include <vector>
#include <iostream>

using namespace std;

int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a%b);
}

int listGCD(vector<int>& vect, int a, int b) {
    int res = vect[a];
    for (int i = a+1; i <= b; i++) {
        res = gcd(vect[i], res);
 
        if(res == 1) {
           return 1;
        }
    }
    return res;
}

int main() {

	int n, q; 
	cin >> n >> q; 

	vector<int> temp(n);

	for(int i = 0; i < n; i++) {
		cin >>  temp[i];
	}

	char c; 
	for(int i = 0; i < q; i++) {
		cin >> c; 
		if (c=='q') {
			int a, b; 
			cin >> a >> b;
			cout << listGCD(temp, a, b) << "\n";
		} else {
			int j, v; 
			cin >> j >> v;
			temp[j] = v;
		}
	}
	return 0;
}