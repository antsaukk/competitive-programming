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
https://cses.fi/alon/task/1749/

*/

#[warn(unused_variables)]

use std::io;
use std::str::FromStr;
use std::fmt::Debug;
use std::convert::TryInto;

struct BitVector {
    bit_vector_: Vec<u64>,
    n_: usize
}

pub trait BitManipulations {
    fn unset_bit(&mut self, index: usize);
    fn get_bit(&self, index: usize) -> u8;
    fn compute_shift(&self, index: usize) -> usize;
    fn compute_removal(&mut self, index_to_remove: usize) -> usize;

    fn print_state(&self);
}

impl BitManipulations for BitVector {
    fn unset_bit(&mut self, index: usize) {
        let bitix: usize  = index / 64;
        let shift: usize  = self.compute_shift(index);
        self.bit_vector_[bitix] &= !(1 << shift);
    }

    fn get_bit(&self, index: usize) -> u8 {
        let bitix: usize = index / 64;
        let shift: usize = self.compute_shift(index);
        let bit: u8 = ((self.bit_vector_[bitix] & (1 << shift)) >> shift).try_into().unwrap();

        bit
    }

    fn compute_shift(&self, index: usize) -> usize {
        let shift: usize = 64 - index % 64 - 1;

        shift
    }

    fn compute_removal(&mut self, index_to_remove: usize) -> usize {
        let mut ind: usize = 0;
        let mut check_sum: u8 = 0;


        for _ in 0..self.n_ {
            check_sum += self.get_bit(ind);
            ind += 1;

            if usize::from(check_sum) == index_to_remove {
                break;
            }
        }

        ind -= 1;

        self.unset_bit(ind);

        ind
    }

    fn print_state(&self) {
        for i in 0..self.n_ {
            print!("{:?} ", self.get_bit(i));
        }
        println!("");
    }
}

fn compute_size(length: usize) -> usize {
    let size: usize = (length + 64 - 1) / 64;

    size
}

fn solve(numbers: Vec<u64>, removals: Vec<usize>) {
    let mut bitvec = BitVector {
        bit_vector_: vec![0xFFFFFFFFFFFFFFFF; compute_size(numbers.len())],
        n_: numbers.len() 
    };

    for i in 0..removals.len() {
        let index_to_remove: usize = bitvec.compute_removal(removals[i]);
        print!("{:?} ", numbers[index_to_remove]);
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
