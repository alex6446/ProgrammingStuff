import tkinter as tk
import math

class Main(tk.Frame):

	Width = 800
	Height = 800
	Scale = 25

	def __init__(self, root):
		super().__init__(root)
		root.update()
		self.Width = root.winfo_width()
		self.Height = root.winfo_height()
		self.init_main()

	def Draw(self, space):

		W = self.Width
		H = self.Height
		S = self.Scale
		x = -1 * W/2
		y = -1 * W/2

		space.delete(tk.ALL)


		space.create_line(0, H/2, W, H/2, width=2, fill="grey", arrow="last")
		space.create_line(W/2, H, W/2, 0, width=2, fill="grey", arrow="last")

		while x <= W/2:
			try:
				y1 = math.tan(x);
				space.create_oval(int(S*x+W/2), int(H-(S*y1+H/2)), 
					int(S*x+W/2), int(H-(S*y1+H/2)), width=5, outline="red")
				x1 = math.atan(y)
				space.create_oval(int(S*x1+W/2), int(H-(S*y+H/2)), 
					int(S*x1+W/2), int(H-(S*y+H/2)), width=5, outline="red")
			except:
				pass
			x += 0.5
			y += 0.5

		

	def ReScale(self, event, space):
		if event.num == 5:
			self.Scale += 10
		else:
			self.Scale -= 10
		print("Done", self.Scale)

		self.Draw(space)

	def init_main(self):
		W = self.Width
		H = self.Height
		S = self.Scale

		space = tk.Canvas(root, width=W, height=H)
		space.pack()

		space.bind("<Button-4>", lambda x: self.ReScale(x, space))
		space.bind("<Button-5>", lambda x: self.ReScale(x, space))

		self.Draw(space)






#start modification






root = tk.Tk()
root.geometry("800x800+200+200")
app = Main(root)
app.pack()
root.mainloop()