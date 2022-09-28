#include <iostream>

#define READ(x) (cin >> (x))

using namespace std;

inline void desyncio() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}

template <typename T>
void PrintOut(T value, string const& delimeter = "") {
	cout << value << delimeter;
}

void run(size_t t) {
	for (size_t i = 0; i < t; i++) {

		size_t a, b; 
		READ(a);
		READ(b);

		while (a > 0 && b > 0) {
			if (a > b) {
				a -= 2;
				b--;
			} else {
				a--; 
				b -= 2;
			}
		}

		if (a == 0 && b == 0) {
			PrintOut("YES\n");
		} else {
			PrintOut("NO\n");
		}
	}
}

int main() {
	desyncio();

	size_t t; 
	READ(t);

    run(t);
    
    return 0;
}