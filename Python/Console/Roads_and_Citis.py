n = int(input())
result = 0
matrix = []

for i in range(n):
	matrix.append(input().split())

for i in range(n):
	for j in range(n):
		if (int(matrix[i][j]) == 1) and (int(matrix[j][i]) == 1):
			result += 1
			matrix[i][j] = 0
			matrix[j][i] = 0

print(result)




