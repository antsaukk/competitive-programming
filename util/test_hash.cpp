#include <iostream> 

#include "string_hash.h"
#include "test_runner.h"

using namespace std;

void TestHash1() {
	string s = "ALLEY";
	Hash th;
	th.build_hash(s);
	ASSERT_EQUAL(th.get_hash(0, s.size() - 1), 52);
}

void TestZ() {
	string s = "ATT#HATTIVATTI";
	Hash th;
	th.z_algorithm(s);
	ASSERT_EQUAL(th.z_array(), vector<int>({0,0,0,0,0,3,0,0,0,0,3,0,0,0}));
}

int main() {
	TestRunner t; 
	RUN_TEST(t, TestHash1);
	RUN_TEST(t, TestZ);
	return 0;
}