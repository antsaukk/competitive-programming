#pragma once

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

