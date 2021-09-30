import sys

def readMultipleLinesTwo():
	N = 1000000
	print(sum([int(input()) for i in range(N)]))

def readMultipleLinesOne(): 
	N = 1000000
	S = 0
	for i in range(N): #xrange
		S += int(input())
	print(S)

def readOneLine(): 
	S = sum(list(map(int, input().split())))
	print(S)

def main():
	try:
		X = int(sys.argv[1])
		if X == 1: 
			readOneLine()
		elif X == 2:
			readMultipleLinesOne()
		elif X == 3: 
			readMultipleLinesTwo()
	except getopt.GetoptError as error:
		print(error)

if __name__ == "__main__":
	main()