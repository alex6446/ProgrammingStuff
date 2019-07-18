body = [[300, 125], [300, 115], [300, 105], [300, 95], [300, 85], [300, 75], [300, 65], [300, 55], [300, 45], [300, 35], [300, 25]]

def reDraw():
	global body
	for i in range(len(body) - 1, 0, -1):
		body[i] = list(body[i - 1])

print("body before:", body)

reDraw()
body[0][1] += 10
print("body after:", body)

cords = [300, 105]
if cords in body:
	print("cords are in body")

for i in range(0, 591, 10):
	print(i)
