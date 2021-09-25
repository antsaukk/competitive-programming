#include "dp.cpp"
#include "test_runner.h"

void TestMIS() {
	auto res = mis_in_path(vector<int>({5, 6, 8, 9, 3}), 5);
	ASSERT_EQUAL(res.first, vector<int>({4, 2, 0}));
	ASSERT_EQUAL(res.second, 16);
}

void TestMIS1(){
	auto res1 = mis_in_path(vector<int>({5, 7, 1, 4, 1}), 5);
	ASSERT_EQUAL(res1.first, vector<int>({3, 1}));
	ASSERT_EQUAL(res1.second, 11);
}

void TestMIS2(){
	auto res2 = mis_in_path(vector<int>({5, 12, 1, 1, 1, 1}), 6);
	ASSERT_EQUAL(res2.first, vector<int>({5, 3, 1}));
	ASSERT_EQUAL(res2.second, 14);
}

void TestMIS3(){
	auto res3 = mis_in_path(vector<int>({100, 1000, 999, 2000, 3500}), 5);
	ASSERT_EQUAL(res3.first, vector<int>({4, 2, 0}));
	ASSERT_EQUAL(res3.second, 4599);
}

void TestMIS4(){
	auto res4 = mis_in_path(vector<int>({6, 5, 9, 8, 3, 1000, 11, 13, 100, 3}), 10);
	ASSERT_EQUAL(res4.first, vector<int>({8, 5, 2, 0}));
	ASSERT_EQUAL(res4.second, 1115);
}

void TestMIS5(){
	auto res5 = mis_in_path(vector<int>({6, 5, 9, 8, 3, 1000, 11, 13, 100, 3}), 10);
	ASSERT_EQUAL(res5.first, vector<int>({8, 5, 2, 0}));
	ASSERT_EQUAL(res5.second, 1115);
}

void TestMIS6(){
	auto res5 = mis_in_path(vector<int>({6, 5, 1, 8, 9, 1000, 1, 10}), 8);
	ASSERT_EQUAL(res5.first, vector<int>({7, 5, 3, 0}));
	ASSERT_EQUAL(res5.second, 1024);
}

void TestMIS7(){
	auto res5 = mis_in_path(vector<int>({1, 1, 1, 1, 1}), 5);
	ASSERT_EQUAL(res5.first, vector<int>({4, 2, 0}));
	ASSERT_EQUAL(res5.second, 3);
}

int main() {

	TestRunner tr;
	RUN_TEST(tr, TestMIS); 
	RUN_TEST(tr, TestMIS1); 
	RUN_TEST(tr, TestMIS2); 
	RUN_TEST(tr, TestMIS3); 
	RUN_TEST(tr, TestMIS4); 
	RUN_TEST(tr, TestMIS5);
	RUN_TEST(tr, TestMIS6);
	RUN_TEST(tr, TestMIS7); 

	int run; 
	cin >> run; 
	if (run) {
		size_t n;
		cin >> n;

		vector<int> w(n);
		for(size_t i = 0; i < n; i++){ cin >> w[i]; }

		mis_in_path(w, n);
	}
	
	return 0;
}