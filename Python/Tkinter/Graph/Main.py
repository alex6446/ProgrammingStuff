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

	def Draw(self, space, graph):

		W = self.Width
		H = self.Height
		S = self.Scale
		x = -1 * W/2

		space.delete(tk.ALL)


		while x <= W/2:
			try:
				y = math.sqrt(x+2);
				graph.put("red", (int(S*x+W/2), int(H-(S*y+H/2))))
			except:
				pass

			x += 0.001

		space.create_line(0, H/2, W, H/2, width=2, fill="grey", arrow="last")
		space.create_line(W/2, H, W/2, 0, width=2, fill="grey", arrow="last")
		space.create_image((W//2,H//2), image=graph, state="normal")

	def ReScale(self, event, space, graph):
		if event.num == 5:
			self.Scale += 10
		else:
			self.Scale -= 10
		print("Done", self.Scale)

		self.Draw(space, graph)

	def init_main(self):
		W = self.Width
		H = self.Height
		S = self.Scale

		space = tk.Canvas(root, width=W, height=H)
		space.pack()

		graph = tk.PhotoImage(width=W, height=H)

		space.bind("<Button-4>", lambda x: self.ReScale(x, space, graph))
		space.bind("<Button-5>", lambda x: self.ReScale(x, space, graph))

		self.Draw(space, graph)






#start modification






root = tk.Tk()
root.geometry("800x800+200+200")
app = Main(root)
app.pack()
root.mainloop()