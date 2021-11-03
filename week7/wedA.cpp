#include <iostream>
//#include <vector>
#include <set>

using namespace std;


int main() {
	size_t n;
	cin >> n; 
	set<int> v;
	for(size_t i = 0; i < n; i++) {
		int num;
		cin >> num;
		v.insert(num);
	}
	cout << v.size();
	return 0; 
}