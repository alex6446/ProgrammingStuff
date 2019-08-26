N = int(input())
matrix = []

for i in range(N):
	matrix.append(input().split())

trio = [5, 6, 7]
trio[1] = 8

minlen = 3001

for i in range(N):
	for j in range(N):
		for k in range(N):
			if i != j and j != k and i != k:
				if int(matrix[i][j]) + int(matrix[j][k]) + int(matrix[i][k]) < minlen:
	 				trio[0] = i
					trio[1] = j
					trio[2] = k
					minlen = int(matrix[i][j]) + int(matrix[j][k]) + int(matrix[i][k])

print(trio[0]+1, trio[1]+1, trio[2]+1)
