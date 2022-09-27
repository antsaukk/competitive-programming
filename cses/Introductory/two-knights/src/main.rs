/*
Your task is to count for k=1,2,…,n the number of ways two knights can be placed on a k×k chessboard so that they do not attack each other.
 
INPUT:
 
The only input line contains an integer n.
 
OUTPUT:
 
Print n integers: the results.
 
CONSTRAINTS:
 
1 <= n <= 10000
 
EXAMPLE:
 
Input:
 
8
 
Output:
 
0
6
28
96
252
550
1056
1848
 
TEST HERE:
 
*/
 
extern crate num;
 
use std::io;
 
use num::bigint::BigInt;
use num::bigint::ToBigInt;
use num::traits::One;
 
fn read_input() -> String {
	let mut user_input = String::new();
	let stdin = io::stdin();
	stdin.read_line(&mut user_input).expect("Failed");
	
	user_input
}
 
fn n_choose_k(n: u64, k: u64) -> BigInt {
    let mut res = BigInt::one();
 
    for i in 0..k {
        res = (res * (n - i).to_bigint().unwrap()) /
              (i + 1).to_bigint().unwrap();
    }
    res
}
 
fn count_combinations(n: u64) {
 
	println!("{}", 0);
	if n==1 { return; }
 
	let answ = n_choose_k(4, 2);
	println!("{}", answ); // 4 choose 2
	if n==2 { return; }
 
	let mut counter = 1;
	let mut recursor = 2;
 
	for i in 3..n+1 {
		let answ = n_choose_k(i*i, 2);
 
		println!("{}", answ - 8*counter); // (n choose 2) - 8*counter
 
		counter += recursor;
		recursor += 1;
	}
}	
 
fn main() {
	let n = read_input().trim().parse::<u64>().unwrap();
	
    count_combinations(n);
}