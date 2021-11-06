#include <iostream>
#include <set>

using namespace std;


int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);

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