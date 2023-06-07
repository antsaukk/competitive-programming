/*
You are given a list consisting of n integers. 
Your task is to remove elements from the list at given positions, and report the removed elements.
 
INPUT:

The first input line has an integer n: the initial size of the list. During the process, the elements are numbered 1,2,…,k
where k is the current size of the list.

The second line has n integers x1,x2,…,xn : the contents of the list.

OUTPUT:

Print the elements in the order they are removed.
 
CONSTRAINTS:

1 <= n <= 2*10^5
1 <= xi <=10^9
1 <= pi <= n−i+1

EXAMPLE:
5
2 6 1 4 2
3 1 3 1 1

Input:
5
2 6 1 4 2
3 1 3 1 1

Output:
1 2 2 6 4

SOLUTION:

VERIFY HERE:
https://cses.fi/problemset/task/1749

*/

#[warn(unused_variables)]

use std::io;
use std::str::FromStr;
use std::fmt::Debug;

pub struct SegmentTree {
    seg_tree_: Vec<usize>,
    sn_: usize,
    n_: usize
}

pub trait SegTreeQueries {
    fn update(&mut self, k: usize);
    fn preprocess(&mut self);
}

impl SegTreeQueries for SegmentTree {

    fn update(&mut self, mut k: usize) {
        k += self.sn_;
        self.seg_tree_[k] = 0;

        while k > 1 {
            k /= 2; 

            self.seg_tree_[k] = self.seg_tree_[2*k] + self.seg_tree_[2*k+1];
        }
    }

    fn preprocess(&mut self) {
        self.seg_tree_[0] -= 1;

        for k in ((self.sn_ + self.n_)..(2*self.sn_)).rev() {
            self.seg_tree_[k] -= 1;
        }

        for k in (1..self.sn_).rev() {
            self.seg_tree_[k] = self.seg_tree_[2*k] + self.seg_tree_[2*k+1];
        }
    }
}

fn find_position(segtree: &mut SegmentTree, mut index_to_remove: usize) -> usize {
    let mut k: usize = 1; 

    while k < segtree.sn_ {
        let left = segtree.seg_tree_[2*k];
        let right = segtree.seg_tree_[2*k + 1];

        let ldiff: i32 = left as i32 - index_to_remove as i32;

        if ldiff >= 0 || right == 0 {
            k = 2*k;
        } else {
            k = 2*k + 1;
            index_to_remove -= left;
        }
    }

    k - segtree.sn_
}

fn solve(numbers: Vec<u64>, removals: Vec<usize>) {
    let mut segtree = SegmentTree {
        seg_tree_: vec![1; 2*numbers.len().next_power_of_two()],
        sn_: numbers.len().next_power_of_two(),
        n_: numbers.len()
    };

    segtree.preprocess();

    for i in &removals {
        let index_to_remove = find_position(&mut segtree, *i);
        print!("{:?} ", numbers[index_to_remove]);
        segtree.update(index_to_remove);
    }
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

fn main() {
    let _n = read_input().trim().parse::<u64>().unwrap();
    let numbers: Vec<u64> = read_vector();
    let removals: Vec<usize> = read_vector();

    solve(numbers, removals);
}