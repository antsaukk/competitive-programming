#include <iostream>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <assert.h>
#include <random>

#include "profile.h"
#include "test_runner.h"

using namespace std;

template <typename T>
size_t BinarySearch(const vector<T>& data, size_t start, size_t end, T element) {
 if (end >= start) {
 	size_t middle = start + (end - start) / 2;
 	if (data[middle] == element)
 		return middle;
 	if (data[middle] > element)
 		return BinarySearch(data, start, middle-1, element);
 	return BinarySearch(data, middle+1, end, element);
 }
 return data.size() + 1;
}

void TestDistinctSimple(){
 const vector<int> t1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}; 
 for (size_t i = 0; i < 10; i++){
 	ASSERT_EQUAL(BinarySearch(t1, 0u, t1.size()-1, t1[i]), i);
 }
}

void TestUniformRandomIndex(){
 vector<int> t1(1000000);
 for (size_t i = 0; i < t1.size(); i++){
 	t1[i] = i % 10; 
 }
 int val = rand() % 23456789;
 size_t ix = rand() % 1000000;
 assert(0<=ix&&ix<=t1.size()-1);
 t1[ix] = val;
 sort(t1.begin(), t1.end());
 size_t index = distance(t1.begin(), find(t1.begin(), t1.end(), val));

 LOG_DURATION("Benchmark on uniform data with random value (1 000 000 elements)");
 ASSERT_EQUAL(BinarySearch(t1, 0u, t1.size()-1, val), index);
}

void TestNonExistent() {
 vector<int> t1(1'000'000, 1);
 ASSERT_EQUAL(BinarySearch(t1, 0u, t1.size()-1, static_cast<int>(t1.size() + 1)), t1.size() + 1);
}

void TestNonExistentLarge() {
 vector<int> t1(99'000'000, 1);
 ASSERT_EQUAL(BinarySearch(t1, 0u, t1.size()-1, static_cast<int>(t1.size() + 1)), t1.size() + 1);
}

void TestNonExistentEXLarge() {
 vector<int> t1(1'000'000'000, 1);
 size_t result = 0;
 {
    LOG_DURATION("Benchmark nonexistent on 1 000 000 000 elements");
    result = BinarySearch(t1, 0u, t1.size()-1, static_cast<int>(t1.size() + 1));
 }
 ASSERT_EQUAL(result, t1.size() + 1);
}

void TestRandomLarge() {
 int n = 1'000'000'000;
 constexpr int ub = 1'234'567'899;
 vector<int> t1(n);
 for (size_t i = 0; i < 10u; i++) { t1[i] = i % 10'000; }

 random_device rd; 
 mt19937 gen(rd());
 uniform_int_distribution<> uniform_dist(n, ub);

 for (size_t j = 0; j < 10u; j++) {
    int rval = uniform_dist(gen);
    size_t ix = rand() % 1'000'000'000;
    assert(0<=ix&&ix<=t1.size()-1);
    t1[ix] = rval;
    sort(t1.begin(), t1.end());
    size_t index = distance(t1.begin(), find(t1.begin(), t1.end(), rval));
    size_t result = 0;
    {
        LOG_DURATION("Benchmark on uniform data with random value (1 000 000 000 elements)");
        result = BinarySearch(t1, 0u, t1.size()-1, rval);
    }
    ASSERT_EQUAL(result, index);
 }
}

int main(){
 TestRunner tr;

 RUN_TEST(tr, TestDistinctSimple); //short input no need for benchmark
 {
    RUN_TEST(tr, TestUniformRandomIndex);
 }
 {
    LOG_DURATION("Benchmark nonexistent on 1 000 000 elements");
    RUN_TEST(tr, TestNonExistent);
 }
 {
    LOG_DURATION("Benchmark nonexistent on 99 000 000 elements");
    RUN_TEST(tr, TestNonExistentLarge);
 }
 RUN_TEST(tr, TestNonExistentEXLarge);
 RUN_TEST(tr, TestRandomLarge);
 return 0;
}