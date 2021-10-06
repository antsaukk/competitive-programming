from itertools import permutations
from collections import Counter
import math
import string

def solve1(x):
	print(len(set(permutations(x))))


def solve(x):
	L = len(x)
	freq = [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
	#print(len(freq))
	
	for i in range(0, L) :
		if (x[i] >= 'a') :
			freq[(ord)(x[i]) - 97] = freq[(ord)(x[i]) - 97] + 1;
   
	repetition = 1
	for i in range(26) :
		repetition = repetition * math.factorial(freq[i])
   
	print(int(math.factorial(L)/repetition))
	

def main():
	x = input()
	#solve1(x)
	solve(x)

if __name__ == "__main__":
	main()