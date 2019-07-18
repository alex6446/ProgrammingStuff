import tkinter as tk
import math

class Main(tk.Frame):

	Width = 500
	Height = 500
	Scale = 25
	sScale = 25
	Xmove = 0
	Ymove = 0

	a = 1
	b = 0
	c = 0

	def __init__(self, root):
		super().__init__(root)
		#root.update()
		#self.Width = root.winfo_width()
		#self.Height = root.winfo_height()
		self.init_main()

	def Draw(self, space):

		W = self.Width
		H = self.Height
		S = self.Scale
		x = -1 * W/2
		Ox = H/2 + self.Ymove
		Oy = W/2 + self.Xmove
		a = self.a
		b = self.b
		c = self.c

		space.delete(tk.ALL)


		space.create_line(0, Ox, W, Ox, width=2, fill="grey", arrow="last")
		space.create_line(Oy, H, Oy, 0, width=2, fill="grey", arrow="last")

		index = (W-Oy) / S
		for i in range(int(index)):
			space.create_line((Oy + S*i), Ox-4, (Oy + S*i), Ox+4, width=1, fill="grey")

		index = Oy / S
		for i in range(int(index)):
			space.create_line((Oy - S*i), Ox-4, (Oy - S*i), Ox+4, width=1, fill="grey")

		index = Ox / S
		for i in range(int(index)):
			space.create_line(Oy-4, (Ox - S*i), Oy+4, (Ox - S*i), width=1, fill="grey")

		index = (H-Ox) / S
		for i in range(int(index)):
			space.create_line(Oy-4, (Ox + S*i), Oy+4, (Ox + S*i), width=1, fill="grey")
		
		while x <= W/2:
			try:
				y = math.sqrt(1-(math.sqrt(x**2)-1)**2)
				x2 = x + .1
				y2 = math.sqrt(1-(math.sqrt(x2**2)-1)**2)
				space.create_line(int(S*x+Oy), int(H-(S*y+H/2) + self.Ymove), 
					int(S*x2+Oy), int(H-(S*y2+H/2)+ self.Ymove), width=2, fill="red")
				y = -2.5*(math.sqrt(1-math.sqrt(math.sqrt(x**2)/2)))
				y2 = -2.5*(math.sqrt(1-math.sqrt(math.sqrt(x2**2)/2)))
				space.create_line(int(S*x+Oy), int(H-(S*y+H/2) + self.Ymove), 
					int(S*x2+Oy), int(H-(S*y2+H/2)+ self.Ymove), width=2, fill="red")
			except:
				pass
			x += .001


		

	def ReScale(self, event, space):
		if event.num == 5:
			self.sScale += 10
		else:
			self.sScale -= 10
		if self.sScale < 0:
			self.Scale = -1/self.sScale
		else:
			self.Scale = self.sScale
		self.Draw(space)

	def Move(self, event, space, dir):
		if dir == "r":
			self.Xmove -= 50
		elif dir == "l":
			self.Xmove += 50
		elif dir == "u":
			self.Ymove += 50
		elif dir == "d":
			self.Ymove -= 50
		self.Draw(space)

	def SetParameters(self, inA, inB, inC, space):
			self.a = float(inA.get())
			self.b = float(inB.get())
			self.c = float(inC.get())
			self.Draw(space)

	def init_main(self):
		W = self.Width
		H = self.Height
		S = self.Scale


		root.update()
		#self.Width = root.winfo_width()
		#self.Height = root.winfo_height()

		spaceX = root.winfo_width() - W - 10
		spaceY = 10
		space = tk.Canvas(root, width=W, height=H)
		space.place(x=spaceX, y = spaceY)

		space.bind("<Button-4>", lambda x: self.ReScale(x, space))
		space.bind("<Button-5>", lambda x: self.ReScale(x, space))
		space.focus_set()
		space.bind("<Right>", lambda x: self.Move(x, space, "r"))
		space.bind("<Left>", lambda x: self.Move(x, space, "l"))
		space.bind("<Up>", lambda x: self.Move(x, space, "u"))
		space.bind("<Down>", lambda x: self.Move(x, space, "d"))
		space.bind("<Button-1>", lambda x: space.focus_set())
		self.Draw(space)

		txtY = tk.Label(root, bg="#b3b3b3", text="y  = ")
		inA = tk.Entry(root, width=3, bd=0, bg="#b3b3b3", 
			highlightcolor="black", highlightbackground="grey")
		txtX2 = tk.Label(root, bg="#b3b3b3", text="x²  + ")
		inB = tk.Entry(root, width=3, bd=0, bg="#b3b3b3", 
			highlightcolor="black", highlightbackground="grey")
		txtX = tk.Label(root, bg="#b3b3b3", text="x  + ")
		inC = tk.Entry(root, width=3, bd=0, bg="#b3b3b3", 
			highlightcolor="black", highlightbackground="grey")

		txtY.place(x=10, y=90)
		inA.place(x=50, y=90)
		txtX2.place(x=80, y=90)
		inB.place(x=125, y=90)
		txtX.place(x=155, y=90)
		inC.place(x=200, y=90)

		inA.insert(0, "1")
		inB.insert(0, "0")
		inC.insert(0, "0")

		def SetDefault():
			inA.delete(0, "end")
			inB.delete(0, "end")
			inC.delete(0, "end")
			inA.insert(0, "1")
			inB.insert(0, "0")
			inC.insert(0, "0")
			self.SetParameters(inA, inB, inC, space)

		Apply = tk.Button(root, text="Apply", bd=0, bg="#888888")
		Apply.place(x=180, y=140, width=70, height=30)
		Apply.config(highlightthickness=0, activebackground="#999999", 
			command=lambda: self.SetParameters(inA, inB, inC, space))
		Default = tk.Button(root, text="Default", bd=0, bg="#888888")
		Default.place(x=90, y=140, width=70, height=30)
		Default.config(highlightthickness=0, activebackground="#999999", 
			command=SetDefault)




root = tk.Tk()
root.geometry("800x520+200+200")
root.configure(background = "#b3b3b3")
root.resizable(False, False)
app = Main(root)
app.pack()
root.mainloop()
