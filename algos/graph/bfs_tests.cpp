void TestSmallBFS1() {
 Graph<size_t, 7> G(7);
 G.AddEdge(0u, 2);
 G.AddEdge(0u, 3);
 G.AddEdge(0u, 4);
 G.AddEdge(0u, 5);

 G.AddEdge(1u, 2);
 G.AddEdge(1u, 5);

 G.AddEdge(2u, 0);
 G.AddEdge(2u, 1);
 G.AddEdge(2u, 3); 

 G.AddEdge(3u, 0);
 G.AddEdge(3u, 2);
 G.AddEdge(3u, 4);
 G.AddEdge(3u, 6);

 G.AddEdge(4u, 0);
 G.AddEdge(4u, 3);

 G.AddEdge(5u, 0);
 G.AddEdge(5u, 1);
 G.AddEdge(5u, 6);

 G.AddEdge(6u, 3);
 G.AddEdge(6u, 5);


 G.BFS(0);
 
 ASSERT_EQUAL(G.TraversalOrder(), "0 2 3 4 5 1 6 ");
}

void TestSmallBFS2() {
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


 G.BFS(0);
 
 ASSERT_EQUAL(G.TraversalOrder(), "0 1 9 2 10 3 4 5 6 7 8 ");
}

void TestSmallBFSDisconnected() {
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


 G.BFS(0);
 
 ASSERT_EQUAL(G.TraversalOrder(), "0 1 2 3 4 ");
}

void TestSmallBFS4() {
 Graph<size_t, 7> G(7);
 G.AddEdge(0u, 1);
 G.AddEdge(1u, 0);

 G.AddEdge(0u, 2);
 G.AddEdge(2u, 0);

 G.AddEdge(0u, 3);
 G.AddEdge(3u, 0);

 G.AddEdge(0u, 5);
 G.AddEdge(5u, 0);

 G.AddEdge(0u, 6);
 G.AddEdge(6u, 0);

 G.AddEdge(1u, 2);
 G.AddEdge(2u, 1);

 G.AddEdge(1u, 4);
 G.AddEdge(4u, 1);

 G.AddEdge(1u, 6);
 G.AddEdge(6u, 1);

 G.AddEdge(2u, 3);
 G.AddEdge(3u, 2);

 G.AddEdge(2u, 6);
 G.AddEdge(6u, 2);

 G.BFS(0);
 
 ASSERT_EQUAL(G.TraversalOrder(), "0 1 2 3 5 6 4 ");
}