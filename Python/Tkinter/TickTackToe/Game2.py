import tkinter as tk
import Functions as fn

class Main(tk.Frame):

	N = 3
	Buttons = []
	Field = []
	MainFrame = None
	Player = "x"
	Indent = 3

	BackgroundColor = "#3c3b3d"
	SeparatorColor = "#252526"

	#X = "×"
	#O = "○"

	def __init__(self, root):
		super().__init__(root)
		self.init_main()


	def def_win(self):
		winner = fn.CheckWin(self.Field, self.N)
		print(winner)


	def set_letter(self, i, j):
		self.Buttons[i][j].focus_set()
		print("in", i, j, self.Field[i][j])
		if self.Field[i][j] == "none":
			print("in")
			if self.Player == "x":
				x1 = 4 #self.Buttons[0][0].cget("x") + 2
				y1 = 4 #self.Buttons[0][0].cget("y") + 2
				x2 = x1 + int(self.Buttons[0][0].cget("width")) - 6
				y2 = y1 + int(self.Buttons[0][0].cget("height")) - 6
				self.Buttons[i][j].create_line(x1, y1, x2, y2, width=5, fill=self.SeparatorColor)
				print(x1, y1, x2, y2)
				self.Player = "o"
			elif self.Player == "o":
				self.Player = "x"
		self.def_win()


	def init_main(self):
		N = self.N
		Indent = self.Indent
		ButtonSize = int((330-Indent*(N-1))/N)

		field = tk.Frame(bg=self.SeparatorColor)
		field.place(x=10, y=110, width=330, height=330)

		self.MainFrame = field

		for i in range(N):
			self.Buttons.append([])
			self.Field.append([])
		for i in range(N):
			for j in range(N):
				self.Field[i].append("none")
				temp = tk.Canvas(field, bg=self.BackgroundColor, width=ButtonSize, height=ButtonSize)
				self.Buttons[i].append(temp)
				X = ButtonSize*i + Indent*i
				Y = ButtonSize*j + Indent*j
				self.Buttons[i][j].place(x=X, y=Y)
				#Buttons[i].bind("<Button-1>", lambda x: self.set_letter(Buttons, i))
			
		field.focus_set()
		#self.Buttons[0][0].focus_set()	
		self.Buttons[0][0].bind("<Button-1>", lambda x: self.set_letter(0, 0))
		#self.Buttons[0][1].focus_set()
		self.Buttons[0][1].bind("<Button-1>", lambda x: self.set_letter(0, 1))
		self.Buttons[0][2].bind("<Button-1>", lambda x: self.set_letter(0, 2))
		self.Buttons[1][0].bind("<Button-1>", lambda x: self.set_letter(1, 0))
		self.Buttons[1][1].bind("<Button-1>", lambda x: self.set_letter(1, 1))
		self.Buttons[1][2].bind("<Button-1>", lambda x: self.set_letter(1, 2))
		self.Buttons[2][0].bind("<Button-1>", lambda x: self.set_letter(2, 0))
		self.Buttons[2][1].bind("<Button-1>", lambda x: self.set_letter(2, 1))
		self.Buttons[2][2].bind("<Button-1>", lambda x: self.set_letter(2, 2))

		
		




		


root = tk.Tk()
app = Main(root)
app.pack()
root.title("Крестики нолики")
root.geometry("350x450+500+500")
root.configure(background=app.BackgroundColor)



root.mainloop()