#include "profile.h"
#include "test_runner.h"
#include "graph.h"

#include "DFSTests.cpp"
#include "BFSTests.cpp"

int main() {
 TestRunner tr;
 {
	LOG_DURATION("DFS TESTS TOTAL");
	RUN_TEST(tr, TestDFSSmall1);
	RUN_TEST(tr, TestDFSSmall2);
	RUN_TEST(tr, TestDFSSmall3);
	RUN_TEST(tr, TestDFSSmall4);
	RUN_TEST(tr, TestDFSSmall5);
	RUN_TEST(tr, TestDFSSmall6);
	RUN_TEST(tr, TestDFSSmallDisconnected);
 }
 {
 	LOG_DURATION("BFS TESTS TOTAL");
	RUN_TEST(tr, TestSmallBFS1);
	RUN_TEST(tr, TestSmallBFS2);
	RUN_TEST(tr, TestSmallBFSDisconnected);
	RUN_TEST(tr, TestSmallBFS4);
 }
 return 0;
}