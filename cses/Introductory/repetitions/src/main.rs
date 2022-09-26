/*
You are given a DNA sequence: a string consisting of characters A, C, G, and T.
Your task is to find the longest repetition in the sequence.
This is a maximum-length substring containing only one type of character.
 
INPUT:

The only input line contains a string of n characters.

OUTPUT:

Print one integer: the length of the longest repetition.
 
CONSTRAINTS:

1 <= n <= 10^6

EXAMPLE:

Input:

ATTCGGGA

Output:

3

TEST HERE:

https://cses.fi/problemset/task/1069

*/

use std::io;
use std::cmp;

fn read_input() -> String {
	let mut user_input = String::new();
	let stdin = io::stdin();
	stdin.read_line(&mut user_input).expect("Failed");
	
	user_input
}

fn solve() -> u64 {
	let dna_string: Vec<char> = read_input().chars().collect();

	let mut counter = 1;
	let mut max_counter = 0;

	let c = dna_string[0];
	for i in 1..(dna_string.len() - 1) {
		if dna_string[i] == dna_string[i-1] {
			counter += 1;
		} else {
			max_counter = cmp::max(counter, max_counter);
			counter = 1;
		}
	}

	cmp::max(counter, max_counter)
}

fn main() {
    println!("{}", solve());
}
