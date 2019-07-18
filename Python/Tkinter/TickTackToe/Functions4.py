import tkinter as tk
import random

playerFirst = False
N = 3

def CheckForWin(Buttons, N):
	count1 = 0
	count2 = 0
	count3 = 0
	count4 = 0

	for i in range(N):
		for j in range(N):
			if Buttons[i][j].cget("text") == '×':
				count1 += 1
			if Buttons[i][j].cget("text") == '○':
				count2 += 1
			if Buttons[j][i].cget("text") == '×':
				count3 += 1
			if Buttons[j][i].cget("text") == '○':
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
		if Buttons[i][i].cget("text") == '×':
			count1 += 1
		elif Buttons[i][i].cget("text") == '○':
			count2 += 1
		if Buttons[i][N-i-1].cget("text") == '×':
			count3 += 1
		elif Buttons[i][N-i-1].cget("text") == '○':
			count4 += 1

	if count1 == N or count3 == N:
		return 1
	if count2 == N or count4 == N:
		return -1

	return 0


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


def Is_emtpy(field):
	for i in range(N):
		for j in range(N):
			if field[i][j] == 'X' or field[i][j] == 'O':
				return False
	return True

def AnotherFuckingException(prev_field, ActualPlayer):
	index = 0
	if ActualPlayer == "X":
		opTurn = "O"
	else:
		opTurn = "X"
	field = list(prev_field)
	for i in range(N):
		for j in range(N):
			if field[i][j] == 'X' or field[i][j] == 'O':
				index += 1
	if index == 1:
		print("OOOKKK")
		if field[0][1] == opTurn or field[1][0] == opTurn or field[2][1] == opTurn or field[1][2] == opTurn:
			if field[i][j] != 'X' and field[i][j] != 'O':
				return True
	return False

def Emergency(prev_field, turn):
	field = list(prev_field)
	lose = -1
	win = -1
	for i in range(N):
		for j in range(N):
			if field[i][j] != 'X' and field[i][j] != 'O':
				tval = field[i][j]
				if turn == 'X':
					field[i][j] = 'O'
					temp = CheckWin(field)
					field[i][j] = 'X'
					temp2 = CheckWin(field)
					if temp2 == 1:
						win = [i, j]
					elif temp == -1:
						lose = [i, j]
				elif turn == 'O':
					field[i][j] = 'X'
					temp = CheckWin(field)
					field[i][j] = 'O'
					temp2 = CheckWin(field)
					if temp2 == -1:
						 win = [i, j]
					if temp == 1:
						lose = [i, j]
				field[i][j] = tval

	if not win == -1:
		return win
	elif not lose == -1:
		return lose
	else:
		return -1


def Jarvis(prev_field, player):
	n = CheckWin(prev_field)
	if Is_full(prev_field):
		if playerFirst and n == 1:
			print("1111")
			return [1, 0, 1]
		elif not playerFirst and n == -1:
			return [1, 0, 1]
		elif playerFirst and n == -1: 
			return [0, 1, 1]
		elif not playerFirst and n == 1: 
			return [0, 1, 1]
		else:
			return [1, 0, 1]
	if n:
		if playerFirst and n == 1:
			return [1, 0, 1]
		elif not playerFirst and n == -1:
			return [1, 0, 1]
		else: 
			return [0, 0, 1]

	if player == 1:
		turn = 'X'
	else:
		turn = 'O'

	field = list(prev_field)


	Weight = []
	Weight.append(0) 	#Weight[0] - wins
	Weight.append(0) 	#Weight[1] - lose
	Weight.append(0) 	#Weight[2] - amount of iterations

	for i in range(N):
		for j in range(N):
			if field[i][j] != 'X' and field[i][j] != 'O':
				temp = field[i][j]
				field[i][j] = turn
				tempV = Jarvis(field, player * -1)
				field[i][j] = temp
				Weight[0] += tempV[0]
				Weight[1] += tempV[1]
				Weight[2] += tempV[2]

	return Weight


def JarvisManager(prev_field, ActualPlayer):

	if Is_emtpy(prev_field):
		x = random.randint(0, (N-1))
		y = random.randint(0, (N-1))
		return [x, y]

	#if AnotherFuckingException(prev_field, ActualPlayer):
	#	return [1, 1]


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
	Opt = []
	Opt.append([x, y])


	for i in range(N):
		print(field[i])

	check = Emergency(field, ActualPlayer)
	if not check == -1:
		x = check[0]
		y = check[1]
		return [x, y]

	
	for i in range(N):
		for j in range(N):
			if field[i][j] != 'X' and field[i][j] != 'O':
				temp = field[i][j]
				field[i][j] = turn
				n = Jarvis(field, player * -1)
				print(i, Weight, n, end = " ")
				try:
					value = (n[0]/(n[0] + n[1])*100)/ n[2]
				except:
					value = 0
				print(value)
				if value > Weight:
					Weight = value
					#x = i
					#y = j
					Opt = []
					Opt.append([i, j])
				elif value == Weight:
					Opt.append([i, j])
				field[i][j] = temp

	index = random.randint(0, (len(Opt)-1))

	print("INDEXX ", Opt)

	print(turn)
	return Opt[index]