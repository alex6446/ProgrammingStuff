import tkinter as tk
import tkinter.filedialog

class App(tk.Tk):
	def __init__(self):
		tk.Tk.__init__(self)
		self.floater = FloatingWindow(self)
		self.overrideredirect(True)
		self.geometry("+500+300")


class FloatingWindow(tk.Toplevel):
	def __init__(self, *args, **kwargs):
		tk.Toplevel.__init__(self, *args, **kwargs)

		
		self.label = tk.Label(self, text="Click on the grip to move")
		self.grip = tk.Label(self, bitmap="gray25")
		self.grip.pack(side="left", fill="y")
		self.label.pack(side="right", fill="both", expand=True)

		self.grip.bind("<Button-1>", self.StartMove)
		self.grip.bind("<ButtonRelease-1>", self.StopMove)
		self.grip.bind("<B1-Motion>", self.OnMotion)

	def StartMove(self, event):
		self.x = event.x
		self.y = event.y
		print(self.x,self.y)

	def StopMove(self, event):
		self.x = None
		self.y = None
		print(self.x,self.y)

	def OnMotion(self, event):
		deltax = event.x - self.x
		deltay = event.y - self.y
		x = self.winfo_x() + deltax
		y = self.winfo_y() + deltay
		self.geometry("+%s+%s" % (x, y))
		print(self.x,self.y)


#root = tk.Tk()
app = App()
app.mainloop()
