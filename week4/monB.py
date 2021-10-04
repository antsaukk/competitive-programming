import math

def previousFibonacci(n):
    a = n/((1 + math.sqrt(5))/2.0)
    return round(a)

def nextFibonacci(n):
    a = n*(1 + math.sqrt(5))/2.0
    return round(a)

def isPerfectSquare(x):
    s = int(math.sqrt(x))
    return s*s == x

def isFibonacci(n):
    return isPerfectSquare(5*n*n + 4) or isPerfectSquare(5*n*n - 4)

def solve():
	ab = list(map(int, input().split()))
	phi_l = 2.078087 * math.log(ab[0]) + 1.672276
	phi_u = 2.078087 * math.log(ab[1]) + 1.672276

	if ab[0] == 1 and isFibonacci(ab[1]):
		print(round(phi_u) - round(phi_l) + 2)
	elif ab[0] == 1 and not isFibonacci(ab[1]): 
		print(round(2.078087 * math.log(nextFibonacci(ab[1])) + 1.672276) - round(phi_l) + 1)
	elif not isFibonacci(ab[0]) and isFibonacci(ab[1]): 
		print(round(phi_u) - round(2.078087 * math.log(ab[0]) + 1.672276) + 1)
	elif not isFibonacci(ab[0]) and not isFibonacci(ab[1]): 
		print(0)
	else:
		print(round(phi_u) - round(phi_l) + 1)


def main():
	solve()

if __name__ == "__main__":
	main()