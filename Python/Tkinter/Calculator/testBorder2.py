import tkinter as tk

class Win(tk.Tk):

	def __init__(self,master=None):
		tk.Tk.__init__(self,master)
		self.overrideredirect(True)
		self.geometry("600x500+500+300")
		self._offsetx = 0
		self._offsety = 0
		header = tk.Frame(bg="#111111")
		header.pack(side=tk.TOP, fill=tk.X)

		name = tk.Label(header, text="THIS is HEADER")
		name.pack(side=tk.LEFT, fill=tk.X) 

		header.bind('<Button-1>',self.clickwin)
		header.bind('<B1-Motion>',self.dragwin)

	def dragwin(self,event):
		x = self.winfo_pointerx() - self._offsetx
		y = self.winfo_pointery() - self._offsety
		self.geometry('+{x}+{y}'.format(x=x,y=y))

	def clickwin(self,event):
		self._offsetx = event.x
		self._offsety = event.y


win = Win()
win.mainloop()