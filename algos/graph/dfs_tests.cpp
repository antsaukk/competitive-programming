void TestDFSSmall1(){
 Graph<size_t, 4> G1(4);
 G1.AddEdge(0u, 1);
 G1.AddEdge(0u, 2); 
 G1.AddEdge(1u, 2); 
 G1.AddEdge(2u, 0); 
 G1.AddEdge(2u, 3); 
 G1.AddEdge(3u, 3);

 G1.DFS(2);
 
 ASSERT_EQUAL(G1.TraversalOrder(), "2 0 1 3 ");
}

void TestDFSSmall2(){
 Graph<size_t, 7> G(7);
 G.AddEdge(0u, 2);
 G.AddEdge(0u, 3); 
 G.AddEdge(0u, 5);

 G.AddEdge(1u, 2);

 G.AddEdge(2u, 0);
 G.AddEdge(2u, 1);
 G.AddEdge(2u, 4); 
 G.AddEdge(2u, 6);

 G.AddEdge(3u, 0);
 G.AddEdge(3u, 4);
 G.AddEdge(3u, 5);

 G.AddEdge(4u, 2);
 G.AddEdge(4u, 3);
 G.AddEdge(4u, 6);

 G.AddEdge(5u, 0);
 G.AddEdge(5u, 3);
 G.AddEdge(5u, 6);

 G.AddEdge(6u, 2);
 G.AddEdge(6u, 4);
 G.AddEdge(6u, 5);


 G.DFS(0);
 
 ASSERT_EQUAL(G.TraversalOrder(), "0 2 1 4 3 5 6 ");
}

void TestDFSSmall3(){
 Graph<size_t, 7> G(7);
 G.AddEdge(0u, 3);
 G.AddEdge(0u, 4); 
 G.AddEdge(0u, 6);

 G.AddEdge(1u, 3);

 G.AddEdge(2u, 5);
 G.AddEdge(2u, 4);

 G.AddEdge(3u, 0);
 G.AddEdge(3u, 1);
 G.AddEdge(3u, 4);
 G.AddEdge(3u, 5);

 G.AddEdge(4u, 0);
 G.AddEdge(4u, 2);
 G.AddEdge(4u, 3);
 G.AddEdge(4u, 5);

 G.AddEdge(5u, 2);
 G.AddEdge(5u, 4);
 G.AddEdge(5u, 3);
 G.AddEdge(5u, 6);

 G.AddEdge(6u, 0);
 G.AddEdge(6u, 5);

 G.DFS(0);

 ASSERT_EQUAL(G.TraversalOrder(), "0 3 1 4 2 5 6 ");
}

void TestDFSSmall4(){
 Graph<size_t, 5> G(5);
 G.AddEdge(0u, 1);
 G.AddEdge(0u, 2); 

 G.AddEdge(1u, 0);
 G.AddEdge(1u, 3);

 G.AddEdge(2u, 0);
 G.AddEdge(2u, 4);

 G.AddEdge(3u, 1);
 
 G.AddEdge(4u, 2);

 G.DFS(0);

 ASSERT_EQUAL(G.TraversalOrder(), "0 1 3 2 4 ");
}

void TestDFSSmall5(){
 Graph<size_t, 4> G(4);
 G.AddEdge(0u, 1);
 G.AddEdge(0u, 2); 

 G.AddEdge(1u, 0);
 G.AddEdge(1u, 3);

 G.AddEdge(2u, 0);
 G.AddEdge(2u, 3);
 
 G.AddEdge(3u, 1);
 G.AddEdge(3u, 2);

 G.DFS(0);

 ASSERT_EQUAL(G.TraversalOrder(), "0 1 3 2 ");
}

void TestDFSSmall6() {
 Graph<size_t, 11> G(11);
 G.AddEdge(0u, 1);
 G.AddEdge(1u, 0);

 G.AddEdge(1u, 2);
 G.AddEdge(2u, 1);

 G.AddEdge(2u, 3);
 G.AddEdge(3u, 2);

 G.AddEdge(3u, 4);
 G.AddEdge(4u, 3);

 G.AddEdge(4u, 5); 
 G.AddEdge(5u, 4);

 G.AddEdge(5u, 6);
 G.AddEdge(6u, 5);

 G.AddEdge(6u, 7);
 G.AddEdge(7u, 6);

 G.AddEdge(7u, 8);
 G.AddEdge(8u, 7);

 G.AddEdge(0u, 9);
 G.AddEdge(9u, 0);

 G.AddEdge(9u, 10);
 G.AddEdge(10u, 9);


 G.DFS(0);
 
 ASSERT_EQUAL(G.TraversalOrder(), "0 1 2 3 4 5 6 7 8 9 10 ");
}

void TestDFSSmallDisconnected() {
 Graph<size_t, 11> G(11);
 G.AddEdge(0u, 1);
 G.AddEdge(1u, 0);

 G.AddEdge(1u, 2);
 G.AddEdge(2u, 1);

 G.AddEdge(1u, 3);
 G.AddEdge(3u, 1);

 G.AddEdge(2u, 3);
 G.AddEdge(3u, 2);

 G.AddEdge(3u, 4);
 G.AddEdge(4u, 3);

 G.AddEdge(6u, 7);
 G.AddEdge(7u, 6);

 G.AddEdge(6u, 8);
 G.AddEdge(8u, 6);

 G.AddEdge(9u, 10);
 G.AddEdge(10u, 9);


 G.DFS(0);
 
 ASSERT_EQUAL(G.TraversalOrder(), "0 1 2 3 4 ");
}