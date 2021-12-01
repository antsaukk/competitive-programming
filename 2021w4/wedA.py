MAX_CHAR = 26
 
# Utility function to find factorial of n.
def factorial(n) :
     
    fact = 1;
    for i in range(2, n + 1) :
        fact = fact * i;
    return fact


def solve(x):
	length = len(x)
	freq = [0] * MAX_CHAR

	for i in range(0, length) :
		if (x[i] >= 'a') :
			freq[(ord)(x[i]) - 97] = freq[(ord)(x[i]) - 97] + 1;
   
	fact = 1
	for i in range(0, MAX_CHAR) :
		fact = fact * factorial(freq[i])
   
	print(int(factorial(length)/fact))


def main():
	x = input()
	solve(x)

if __name__ == "__main__":
	main()



	