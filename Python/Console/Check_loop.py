import sys

n = int(input())

matrix = []
for i in range(n):
	matrix.append(input().split())

for i in range(n):
	if int(matrix[i][i]) == 1:
		print("YES")
		sys.exit()

print("NO")