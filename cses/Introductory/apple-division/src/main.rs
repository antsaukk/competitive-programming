#[warn(unused_variables)]

use std::ops::Sub;
use std::ops::Add;

use std::io;

fn read_input() -> String {
	let mut user_input = String::new();
	let stdin = io::stdin();
	stdin.read_line(&mut user_input).expect("Failed");
	
	user_input
}

/*fn solve<T: 
			std::fmt::Debug + 
			std::cmp::Ord + 
			std::ops::Add + 
			std::ops::AddAssign + 
			std::ops::Sub + 
			Copy
			>
			(n: u64, container: &mut Vec<T>) -> T
where T: Add<Output = T>, T: Sub<Output = T>
{
	if n == 1 {
		return container[0];
	}
	container.sort_by(|a, b| b.cmp(a));

	let mut group1 = container[0 as usize];
	let mut group2 = container[1 as usize];

	for i in 2..n {
		let apple = container[i as usize];

		let diff1 = group1 + apple - group2;
		let diff2 = group2 + apple - group1;

		if diff1 < diff2 {
			group1 += apple;
		} else {
			group2 += apple;
		}
	}

	group1 - group2
}*/

trait Summable<T>
{
	fn sum(&self) -> T;
} 

impl Summable<i64> for Vec<i64>
{
	fn sum(&self) -> i64 {
		let mut res: i64 = 0;
		for element in self {
			res += *element;
		}
		res
	}
}

fn solve(n: u64, container: &mut Vec<i64>) -> i64 {
	let b = 1 << n;
	//println!("{:?}", b);

	let mut min_diff = i64::MAX;
	let set_sum = container.sum();

	for i in 0..b {
		let mut subset: Vec<i64> = Vec::new();
		for j in 0..n { 
			if i&(1<<j) != 0 { subset.push(j as i64); }
		}
		println!("{:?}", subset);
		let subset_sum1 = subset.sum();
		let subset_sum2 = set_sum - subset_sum1;
		let diff = subset_sum2 - subset_sum1;
		if diff.abs() < min_diff {
			min_diff = diff.abs();
		}

	}

	min_diff
}

fn main() {
	let n = read_input().trim().parse::<u64>().unwrap();

	let mut apples = read_input()
		.split_whitespace()
    	.map(|x| x.parse::<i64>())
        .collect::<Result<Vec<i64>, _>>()
        .unwrap();

 	println!("{}", solve(n, &mut apples));
}
