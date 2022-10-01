import math

def solve(n: int):
	f = math.factorial(n)

	counter = 0
	while f%10 == 0:
		counter += 1;
		f //= 10;

	print(counter)

def main():
	n = int(input())
	solve(n)

if __name__ == "__main__":
	main()