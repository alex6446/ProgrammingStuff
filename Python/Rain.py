N = int(input())
odd = 0

matrix = []

for i in range(N):
	matrix.append(input().split())

buff = input()

colors = input().split()

for i in range(N):
	for j in range(N):
		if int(matrix[i][j]) == 1 and colors[i] != colors[j]:
			odd += 1

print(int(odd/2))
