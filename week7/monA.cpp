#include <iostream>
#include <string>
#include <vector>

using namespace std;

size_t index(size_t ind) {
	return ind-1;
}

void solve(string a, string b) {
	if((a.at(0) == '-' || b.at(0) == '-') && (a.at(0) != '-' || b.at(0) != '-' )) {
		cout<<"-";
	}

	if(a.at(0) == '-') {
		a = a.substr(1);
	}
   
    if(b.at(0) == '-') {
    	b = b.substr(1);
    }
 	cout << "here";
 	int n1 = a.size();
    int n2 = b.size();

    cout << "this" << n1 << " " << n2;
    if (n1 == 0 || n2 == 0){
    	cout << "0";
    	return;
    }
 
    vector<int> result(n1 + n2);
 
    size_t p1 = 0;
    size_t p2 = 0;
     
    for (size_t i = index(n1); i >= 0; i--) {
    	
        int carry = 0;
        size_t n1 = a[i] - '0';
 
        p2 = 0;
                  
        for (size_t j = index(n2); j >= 0; j--) {
            size_t n2 = b[j] - '0';
 
            int sum = n1*n2 + result[p1 + p2] + carry;
 
            carry = sum/10;

            result[p1 + p2] = sum % 10;
 
            p2++;
        }
 
        if (carry > 0){
            result[p1 + p2] += carry;
        }

        p1++;
    }
 
    int i = result.size() - 1;
    while (i >= 0 && result[i] == 0) i--;

    if (i == -1) {
    	cout << "0";
    }
     
    while (i >= 0) {
        cout << to_string(result[i--]);
    }
}

int main() {
	string a; 
	string b;
	cin >> a >> b;
	cout << a << " " << b;
	solve(a, b);

	return 0; 
}