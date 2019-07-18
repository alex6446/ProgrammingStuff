import tkinter as tk
import math

class Main(tk.Frame):
	def __init__(self, root):
		super().__init__(root)
		self.init_main()

		root.overrideredirect(True)
		#root.wait_visibility(True)
		#root.wm_attributes("-topmost", True)
		#root.wm_attributes("-disabled", True)
		#root.wm_attributes("-alpha", 0.0)
		#root.geometry("600x500+500+300")
		self._offsetx = 0
		self._offsety = 0
		header = tk.Frame()
		header.pack(side=tk.TOP, fill=tk.X)

		name = tk.Label(header, text="THIS is HEADER", bg="green")
		name.pack() 

		name.bind('<ButtonPress-1>',self.clickwin)
		name.bind('<B1-Motion>',self.dragwin)
		header.bind('<Button-1>',self.clickwin)
		header.bind('<B1-Motion>',self.dragwin)

		CloseButton = tk.Button(header, text="X", bd=0, highlightthickness=0, command=root.destroy)
		CloseButton.pack(side=tk.RIGHT)

		inbox = tk.Frame()
		txtSpace = tk.Label(inbox, anchor=tk.E, padx=10, font=("TkDefaultFont",1), width=440, 
			height=110, bg='white')
		
		butons = tk.Frame()
		panel = tk.Label(butons, bg="black",font=("TkDefaultFont",1), width=120, height=80,)

		butons.lift(inbox)
		inbox.pack(side=tk.RIGHT)
		butons.pack(side=tk.LEFT)
		txtSpace.pack(side=tk.RIGHT)
		panel.pack(side=tk.LEFT)

		

	def dragwin(self,event):
		x = self.winfo_pointerx() - self._offsetx
		y = self.winfo_pointery() - self._offsety
		root.geometry('+{x}+{y}'.format(x=x,y=y))

	def clickwin(self,event):
		self._offsetx = event.x
		self._offsety = event.y


	def init_main(self):
		pass
		





root = tk.Tk()

app = Main(root)
app.pack()
root.title("Calculator 5.0")
root.geometry("500x400+500+300")
#root.geometry("550x832+500+300")
root.resizable(False, False)
#root.configure(background = "#161a2d")
#root.configure(background = "white")

root.mainloop()