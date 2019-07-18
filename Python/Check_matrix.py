import sys

n = int(input())

matrix = []
for i in range(n):
	matrix.append(input().split())

for i in range(n):
	for j in range(n):
		if matrix[i][j] != matrix[j][i]:
			print("NO")
			sys.exit()
		if i == j and int(matrix[i][j]) != 0:
			print("NO")
			sys.exit()

print("YES")