import os

N = 3
field = [ ]
gameOver = False
playerFirst = True
aiON = False
FirstPlayer = "FirstPlayer"
SecondPlayer = "SecondPlayer"
Swap = False # Used only to tell the final result correctly

def Menu():
	global playerFirst
	global FirstPlayer
	global SecondPlayer
	global Swap
	global aiON

	print("Do you want to play with computer?")
	print("1 - Yes")
	print("2 - No")
	option = input()

	if option == '1' or option == "Yes":
		aiON = True
		FirstPlayer = input("Enter your name: ")
		print("Do you want to be first?")
		print("1 - Yes")
		print("2 - No")
		option = input()
		if option == '1' or option == "Yes":
			return
		else:
			playerFirst = False
			Swap = True
			return
	else:
		FirstPlayer = input("Enter first player name: ")
		SecondPlayer = input("Enter second player name: ")

def Print():
	os.system('clear')
	for i in range(N):
		for j in range(N):
			print(field[i][j], end = ' ')
		print()

def Input(field):
	if playerFirst:
		print(FirstPlayer, " turn (X):", end = ' ')
		opt = input()
	else:
		print(SecondPlayer, " turn (O):", end = ' ')
		opt = input()

	for i in range(N):
		for j in range(N):
			if field[i][j] == int(opt):
				if playerFirst:
					field[i][j] = 'X'
					return True
				else:
					field[i][j] = 'O'
					return True
	return False

def ChangePlayer():
	global playerFirst

	if playerFirst:
		playerFirst = False
	else:
		playerFirst = True

def CheckWin(field):
	count1 = 0
	count2 = 0
	count3 = 0
	count4 = 0

	for i in range(N):
		for j in range(N):
			if field[i][j] == 'X':
				count1 += 1
			if field[i][j] == 'O':
				count2 += 1
			if field[j][i] == 'X':
				count3 += 1
			if field[j][i] == 'O':
				count4 += 1

		if count1 == N or count3 == N:
			return 1
		if count2 == N or count4 == N:
			return -1
		count1 = 0
		count2 = 0
		count3 = 0
		count4 = 0

	for i in range(N):
		if field[i][i] == 'X':
			count1 += 1
		elif field[i][i] == 'O':
			count2 += 1
		if field[i][N-i-1] == 'X':
			count3 += 1
		elif field[i][N-i-1] == 'O':
			count4 += 1

	if count1 == N or count3 == N:
		return 1
	if count2 == N or count4 == N:
		return -1

	return 0

def Is_full(field):
	for i in range(N):
		for j in range(N):
			if field[i][j] != 'X' and field[i][j] != 'O':
				return False
	return True

def Result():
	if winner == 1:
		if not aiON:
			print(FirstPlayer, " win!")
		else:
			if Swap:
				print("Computer win!")
			else:
				print(FirstPlayer, " win!")
	elif winner == -1:
		if not aiON:
			print(SecondPlayer, " win!")
		else:
			if Swap:
				print(FirstPlayer, " win!")
			else:
				print("Computer win!")
	elif winner == 0:
		print("Nobody wins today(")



def Jarvis(prev_field, player):
	n = CheckWin(prev_field)
	if Is_full(prev_field):
		return [0, 1]
	if n:
		if playerFirst and n == 1:
			return [10, 1]
		elif not playerFirst and n == -1:
			return [10, 1]
		else: 
			return [-10, 1]

	if player == 1:
		turn = 'X'
	else:
		turn = 'O'

	field = list(prev_field)

	Weight = 0
	Depth = 1

	for i in range(N):
		for j in range(N):
			if field[i][j] != 'X' and field[i][j] != 'O':
				temp = field[i][j]
				field[i][j] = turn
				temp1 = Jarvis(field, player * -1)
				Weight += temp1[0]
				Depth += temp1[1]
				field[i][j] = temp
	return Weight, Depth

def JarvisManager(prev_field):
	global playerFirst
	if playerFirst:
		player = 1
		turn = 'X'
	else:
		player = -1
		turn = 'O'

	field = list(prev_field)

	for i in range(N):
		for j in range(N):
			if field[i][j] != 'X' and field[i][j] != 'O':
				x = i
				y = j

	Weight = -1



	for i in range(N):
		for j in range(N):
			if field[i][j] != 'X' and field[i][j] != 'O':
				temp = field[i][j]
				field[i][j] = turn
				n = Jarvis(field, player * -1)
				print(Weight, n[0]/n[1], "i: ", i, "j: ", j)
				if (n[0]/n[1]) > Weight:
					Weight = n[0]/n[1]
					x = i
					y = j
				field[i][j] = temp

	prev_field[x][y] = turn


for i in range(N):
	field.append([])

t = 1

for i in range(N):
	for j in range(N):
		field[i].append(t)
		t += 1

winner = 0

Menu()

while not gameOver:
	Print()
	if aiON:
		if playerFirst and Input(field):
			winner = CheckWin(field)
			if winner or Is_full(field):
				gameOver = True
			ChangePlayer()
		elif not playerFirst:
			JarvisManager(field)
			winner = CheckWin(field)
			if winner or Is_full(field):
				gameOver = True
			ChangePlayer()
	else:
		if Input(field):
			winner = CheckWin(field)
			if winner or Is_full(field):
				gameOver = True
			ChangePlayer()

Print()
Result()
