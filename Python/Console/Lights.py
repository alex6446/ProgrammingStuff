buff = input().split()

N = int(buff[0])
M = int(buff[1])

crossroads = []
lights = []

for i in range(M):
	crossroads.append(input().split())

for i in range(N):
	lights.append(0)

for i in range(M):
	lights[int(crossroads[i][0])-1] += 1
	lights[int(crossroads[i][1])-1] += 1

for i in lights:
	print(i, end = ' ')
