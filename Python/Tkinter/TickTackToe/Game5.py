import tkinter as tk
import Functions5 as fn

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
	InMenu = True

	BackgroundColor = "#3c3b3d"
	SeparatorColor = "#252526"

	X = "×"
	O = "○"

	def __init__(self, root):
		super().__init__(root)
		self.menu()


	def computer_turn(self):
		root.update()
		if not self.GameOver:
			self.Header.configure(text="Thinking...")
			if self.PCFirst:
				playerFirst = False
			else:
				playerFirst = True
			if self.Player == "x":
				ActualPlayer = "X"
			else:
				ActualPlayer = "O"
			xy = fn.JarvisManager(self.GameField, ActualPlayer)
			print(xy, self.Player)
			i = xy[0]
			j = xy[1]
			if self.Player == "x":
				self.Buttons[i][j].configure(text=self.X)
				self.GameField[i][j] = "X"
			else:
				self.Buttons[i][j].configure(text=self.O, anchor=tk.S)
				self.GameField[i][j] = "O"
			self.Header.configure(text="Your Turn")




	def def_win(self, Buttons):
		if not self.GameOver:
			winner = fn.CheckForWin(Buttons, self.N)
			if winner == 1:
				if self.PCFirst:
					self.Header.configure(text="PC Wins!")
					self.restart_game()
				else:
					self.Header.configure(text="You Win!")
					self.restart_game()
				self.GameOver = True
			elif winner == -1:
				if self.PCFirst:
					self.Header.configure(text="You Win!")
					self.restart_game()
				else:
					self.Header.configure(text="PC Wins!")
					self.restart_game()
				self.GameOver = True
		if fn.Is_full(self.GameField) and not self.GameOver:
			self.GameOver = True
			self.Header.configure(text="Dead Heat(")
			self.restart_game()
			return



	def set_letter(self, Buttons, i, j):
		if not self.GameOver:
			if Buttons[i][j].cget("text") == " " and self.Active:
				if self.Player == "x":
					Buttons[i][j].configure(text=self.X)
					self.GameField[i][j] = "X"
					self.def_win(Buttons)
					
					self.Player = "o"
					self.Active = False
					self.computer_turn()
					self.Active = True
					self.Player = "x"
				elif self.Player == "o":
					Buttons[i][j].configure(text=self.O, anchor=tk.S)
					self.GameField[i][j] = "O"
					self.def_win(Buttons)
					self.Player = "x"
					self.Active = False
					self.computer_turn()
					self.Active = True
					self.Player = "o"
					
			self.def_win(Buttons)


	def restart_game(self):
		self.Active = False
		RestartButton = tk.Label(root, fg="#464547", bg=self.SeparatorColor, font=("TkDefaultFont", 20), text="Restart")
		RestartButton.place(x=75, y=250, width=200, height=50)
		def Clear(event):
			if not self.InMenu:
				N = self.N
				t = 1
				for i in range(N):
					for j in range(N):
						self.GameField[i][j] = t
						self.Buttons[i][j].destroy()
				self.Player = "x"
				self.Header = None
				self.PCFirst = True
				self.GameOver = False
				self.GameField = []
				self.Buttons = []
				self.Active = False
				self.MainField.destroy()
				RestartButton.configure(bg=self.BackgroundColor, fg=self.BackgroundColor)
				self.InMenu = True
				self.menu()
			
		RestartButton.bind("<Button-1>", Clear)


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
		self.InMenu = False
		N = self.N
		Indent = self.Indent
		ButtonSize = int((330-Indent*(N-1))/N)
		self.Header.configure(font=("TkDefaultFont", 40), text="Your Turn")

		self.MainField = tk.Frame(bg=self.SeparatorColor)
		self.MainField.place(x=10, y=110, width=330, height=330)

		for i in range(N):
			self.Buttons.append([])
			self.GameField.append([])
		t = 1
		for i in range(N):
			for j in range(N):
				self.GameField[i].append(t)
				temp = tk.Label(self.MainField, bg=self.BackgroundColor, fg=self.SeparatorColor, font=("TkDefaultFont", 76), text=" ")
				self.Buttons[i].append(temp)
				X = ButtonSize*i + Indent*i
				Y = ButtonSize*j + Indent*j
				self.Buttons[i][j].place(x=X, y=Y, width=ButtonSize, height=ButtonSize)
				#Buttons[i].bind("<Button-1>", lambda x: self.set_letter(Buttons, i))
				t += 1

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
			#self.Player = "o"
			self.Header.configure(text="Thinking...")
			self.computer_turn()
			self.Active = True
			self.Player = "o"


	
		




		


root = tk.Tk()
app = Main(root)
app.pack()
root.title("Крестики нолики")
root.geometry("350x450+500+500")
root.configure(background=app.BackgroundColor)



root.mainloop()