import tkinter as tk
#import Functions as fn

class Main(tk.Frame):

	N = 3
	Player = "x"
	Indent = 3
	Header = None
	PCFirst = True
	GameOver = False
	GameField = []
	Buttons = []
	Active = False

	BackgroundColor = "#3c3b3d"
	SeparatorColor = "#252526"

	X = "×"
	O = "○"

	def __init__(self, root):
		super().__init__(root)
		self.menu()


	def computer_turn(self):
		if self.PCFirst:
			playerFirst = False
		else:
			playerFirst = True
		xy = self.JarvisManager(self.GameField)
		print(xy, self.Player)
		i = xy[0]
		j = xy[1]
		if self.Player == "x":
			self.Buttons[i][j].configure(text=self.X)
			self.GameField[i][j] = "X"
		else:
			self.Buttons[i][j].configure(text=self.O, anchor=tk.S)
			self.GameField[i][j] = "O"
		self.Header.configure(text="Player")




	def def_win(self, Buttons):
		if not self.GameOver:
			winner = self.CheckForWin(Buttons, self.N)
			if winner == 1:
				if self.PCFirst:
					self.Header.configure(text="PC Wins!")
				else:
					self.Header.configure(text="You Win!")
				GameOver = True
			elif winner == -1:
				if self.PCFirst:
					self.Header.configure(text="You Win!")
				else:
					self.Header.configure(text="PC Wins!")
				GameOver = True


	def set_letter(self, Buttons, i, j):
		if Buttons[i][j].cget("text") == " " and self.Active:
			if self.Player == "x":
				Buttons[i][j].configure(text=self.X)
				self.GameField[i][j] = "X"
				self.def_win(Buttons)
				self.Header.configure(text="Computer")
				self.Player = "o"
				self.Active = False
				self.computer_turn()
				self.Active = True
				self.Player = "x"
				
			elif self.Player == "o":
				Buttons[i][j].configure(text=self.O, anchor=tk.S)
				self.GameField[i][j] = "O"
				self.def_win(Buttons)
				self.Header.configure(text="Computer")
				self.Player = "x"
				self.Active = False
				self.computer_turn()
				self.Active = True
				self.Player = "o"
				
		self.def_win(Buttons)

	def menu(self):
		self.Header = tk.Label(root, bg=self.BackgroundColor, fg=self.SeparatorColor, font=("TkDefaultFont", 30), text="Who is first?")
		self.Header.place(x=0, y=0, width=350, height=120)
		CompF = tk.Label(root, fg="#464547", bg=self.SeparatorColor, font=("TkDefaultFont", 20), text="Computer")
		UsrF = tk.Label(root, fg="#464547", bg=self.SeparatorColor, font=("TkDefaultFont", 20), text="Player")
		CompF.place(x=75, y=180, width=200, height=50)
		UsrF.place(x=75, y=270, width=200, height=50)
		def setC(event):
			self.PCFirst = True
			self.Active = False
			self.init_main()
		def setU(event):
			self.PCFirst = False
			self.Active = True
			self.init_main()
		CompF.bind("<Button-1>", setC)
		UsrF.bind("<Button-1>", setU)


	def init_main(self):
		N = self.N
		Indent = self.Indent
		ButtonSize = int((330-Indent*(N-1))/N)
		self.Header.configure(font=("TkDefaultFont", 45), text="Player")

		field = tk.Frame(bg=self.SeparatorColor)
		field.place(x=10, y=110, width=330, height=330)

		for i in range(N):
			self.Buttons.append([])
			self.GameField.append([])
		for i in range(N):
			for j in range(N):
				self.GameField[i].append(j)
				temp = tk.Label(field, bg=self.BackgroundColor, fg=self.SeparatorColor, font=("TkDefaultFont", 76), text=" ")
				self.Buttons[i].append(temp)
				X = ButtonSize*i + Indent*i
				Y = ButtonSize*j + Indent*j
				self.Buttons[i][j].place(x=X, y=Y, width=ButtonSize, height=ButtonSize)
				#Buttons[i].bind("<Button-1>", lambda x: self.set_letter(Buttons, i))

		self.Buttons[0][0].bind("<Button-1>", lambda x: self.set_letter(self.Buttons, 0, 0))
		self.Buttons[0][1].bind("<Button-1>", lambda x: self.set_letter(self.Buttons, 0, 1))
		self.Buttons[0][2].bind("<Button-1>", lambda x: self.set_letter(self.Buttons, 0, 2))
		self.Buttons[1][0].bind("<Button-1>", lambda x: self.set_letter(self.Buttons, 1, 0))
		self.Buttons[1][1].bind("<Button-1>", lambda x: self.set_letter(self.Buttons, 1, 1))
		self.Buttons[1][2].bind("<Button-1>", lambda x: self.set_letter(self.Buttons, 1, 2))
		self.Buttons[2][0].bind("<Button-1>", lambda x: self.set_letter(self.Buttons, 2, 0))
		self.Buttons[2][1].bind("<Button-1>", lambda x: self.set_letter(self.Buttons, 2, 1))
		self.Buttons[2][2].bind("<Button-1>", lambda x: self.set_letter(self.Buttons, 2, 2))

		if self.PCFirst:
			self.computer_turn()
			self.Active = True
			self.Player = "o"


	playerFirst = True
	N = 3

	def CheckForWin(self, Buttons, N):
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

	def CheckWin(self, field):
		N = self.N
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


	def Is_full(self, field):
		N = self.N
		for i in range(N):
			for j in range(N):
				if field[i][j] != 'X' and field[i][j] != 'O':
					return False
		return True


	def Emergency(self, prev_field, turn):
		N = self.N
		field = list(prev_field)
		lose = -1
		win = -1
		for i in range(N):
			for j in range(N):
				if field[i][j] != 'X' and field[i][j] != 'O':
					tval = field[i][j]
					if turn == 'X':
						field[i][j] = 'O'
						temp = self.CheckWin(field)
						field[i][j] = 'X'
						temp2 = self.CheckWin(field)
						if temp2 == 1:
							win = [i, j]
						elif temp == -1:
							lose = [i, j]
					elif turn == 'O':
						field[i][j] = 'X'
						temp = self.CheckWin(field)
						field[i][j] = 'O'
						temp2 = self.CheckWin(field)
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


	def Jarvis(self, prev_field, player):
		N = self.N
		n = self.CheckWin(prev_field)
		if self.Is_full(prev_field):
			if self.playerFirst and n == 1:
				return [1, 0, 1]
			elif not self.playerFirst and n == -1:
				return [1, 0, 1]
			elif self.playerFirst and n == -1: 
				return [0, 1, 1]
			elif not self.playerFirst and n == 1: 
				return [0, 1, 1]
			else:
				return [1, 0, 1]
		if n:
			if self.playerFirst and n == 1:
				return [1, 0, 1]
			elif not self.playerFirst and n == -1:
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
					tempV = self.Jarvis(field, player * -1)
					field[i][j] = temp
					Weight[0] += tempV[0]
					Weight[1] += tempV[1]
					Weight[2] += tempV[2]

		return Weight


	def JarvisManager(self, prev_field):
		N = self.N
		if self.PCFirst == True:
			self.playerFirst = False
		else:
			self.playerFirst = True

		if self.playerFirst:
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

		check = self.Emergency(field, turn)
		if not check == -1:
			x = check[0]
			y = check[1]
			return [x, y]

		for i in range(N):
			for j in range(N):
				if field[i][j] != 'X' and field[i][j] != 'O':
					temp = field[i][j]
					field[i][j] = turn
					n = self.Jarvis(field, player * -1)
					print(i, Weight, n, end = " ")
					try:
						value = (n[0]/(n[0] + n[1])*100)/ n[2]
					except:
						value = 0
					print(value)
					if value > Weight:
						Weight = value
						x = i
						y = j
					field[i][j] = temp

		return [x, y]


		




		


root = tk.Tk()
app = Main(root)
app.pack()
root.title("Крестики нолики")
root.geometry("350x450+500+500")
root.configure(background=app.BackgroundColor)



root.mainloop()