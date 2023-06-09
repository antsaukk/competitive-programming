/*

INPUT:

OUTPUT:
 
CONSTRAINTS:

1 <= n <= 2*10^5
1 <= xi <=10^9
1 <= pi <= n−i+1

EXAMPLE:


Input:


Output:

SOLUTION:

VERIFY HERE:

*/

#[warn(unused_variables)]

use std::io;
use std::str::FromStr;
use std::fmt::Debug;
use std::cmp;

#[derive(Clone)]
pub struct Edge {
    a_: isize,
    b_: isize,
    e_: isize
}

pub struct Graph {
    edges_: Vec<Edge>
}

fn read_input() -> String {
    let mut user_input = String::new();
    let stdin = io::stdin();
    stdin.read_line(&mut user_input).expect("Failed");

    user_input
}

fn read_vector<T: std::str::FromStr>() -> Vec<T> where <T as FromStr>::Err: Debug {
    let vector = read_input()
        .split_whitespace()
        .map(|x| x.parse::<T>())
        .collect::<Result<Vec<T>, _>>()
        .unwrap();

    vector
}

fn build_graph(num_edges: usize) -> Graph {
    let mut g = Graph {
        edges_: vec![
        Edge{a_: 0, b_: 0, e_: 0}; num_edges]
    };

    for i in 0..num_edges {
        let edge: Vec<isize> = read_vector();
        g.edges_[i as usize] = Edge{
            a_: edge[0] - 1,
            b_: edge[1] - 1,
            e_: edge[2]
        };
    }

    g
}

fn solve(vertices: usize, graph: &Graph) -> u64 {
    let mut distance = vec![u64::MAX/2; vertices];
    distance[0] = 0;

    for _ in 1..vertices {
        for edge in &graph.edges_ {
            println!("{:?} ", distance);
            distance[edge.b_ as usize] = cmp::min(distance[edge.b_ as usize], distance[edge.a_ as usize] + edge.e_ as u64);
        }
    }

    println!("{:?} ", distance);

    distance[vertices-1]/2
}

fn main() {
    let parameters: Vec<usize> = read_vector();
    let g = build_graph(parameters[1]);
    println!("{:?}", solve(parameters[0], &g));
}
