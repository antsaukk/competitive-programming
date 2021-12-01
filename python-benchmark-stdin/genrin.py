import tempfile, random
import sys

def generateRandomIntegers(filename, separator):
	N = 1000000
	with open(filename, "w") as nf:
		if separator == ' ':
			nf.write(' '.join(str(random.randint(0, N)) for j in range(N)))
		else:
			nf.write('\n'.join(str(random.randint(0, N)) for j in range(N)))

def main():
	try: 
		generateRandomIntegers(sys.argv[1], sys.argv[2])
	except getopt.GetoptError as error:
		print(error)

if __name__ == "__main__":
	main()