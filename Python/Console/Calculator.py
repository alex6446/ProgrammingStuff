import tkinter as tk

class Main(tk.Frame):

	CurrentText = "0"

	def __init__(self, root):
		super().__init__(root)
		self.init_main()

	def init_main(self):
		inputbox = tk.Frame(bg='#161a2d', bd=1)
		inputbox.pack(side=tk.TOP, fill=tk.X)

		#CurrentText = "0"

		input_label = tk.Label(inputbox, anchor=tk.E, padx=10, font=("TkDefaultFont",14), width=30, height=4, bg='#1d2035', fg="#cbd1d9", text=self.CurrentText)
		input_label.pack(side=tk.LEFT, fill=tk.X)

		l0 = tk.Frame(bg='#161a2d', bd=0)
		l1 = tk.Frame(bg='#161a2d', bd=0)
		l2 = tk.Frame(bg='#161a2d', bd=0)
		l3 = tk.Frame(bg='#161a2d', bd=0)
		l4 = tk.Frame(bg='#161a2d', bd=0)

		l0.pack(side=tk.BOTTOM, fill=tk.X)
		l1.pack(side=tk.BOTTOM, fill=tk.X)
		l2.pack(side=tk.BOTTOM, fill=tk.X)
		l3.pack(side=tk.BOTTOM, fill=tk.X)
		l4.pack(side=tk.BOTTOM, fill=tk.X)


		def Add(self, x):
			if self.CurrentText == "0":
				self.CurrentText = str(x)
				input_label.config(text=self.CurrentText)
			else:
				self.CurrentText += str(x)
				input_label.config(text=self.CurrentText)

		def Clear(self):
			self.CurrentText = "0"
			input_label.config(text=self.CurrentText)


		btn0f = tk.Button(l0, text="", width=4, height=3, bg="#161a2d", fg="#cbd1d9", bd=0)
		btn0 = tk.Button(l0, text="0", width=4, height=3, bg="#161a2d", fg="#cbd1d9", bd=0)
		btn1 = tk.Button(l1, text="1", width=4, height=3, bg="#161a2d", fg="#cbd1d9", bd=0)
		btn2 = tk.Button(l1, text="2", width=4, height=3, bg="#161a2d", fg="#cbd1d9", bd=0)
		btn3 = tk.Button(l1, text="3", width=4, height=3, bg="#161a2d", fg="#cbd1d9", bd=0)
		btn4 = tk.Button(l2, text="4", width=4, height=3, bg="#161a2d", fg="#cbd1d9", bd=0)
		btn5 = tk.Button(l2, text="5", width=4, height=3, bg="#161a2d", fg="#cbd1d9", bd=0)
		btn6 = tk.Button(l2, text="6", width=4, height=3, bg="#161a2d", fg="#cbd1d9", bd=0)
		btn7 = tk.Button(l3, text="7", width=4, height=3, bg="#161a2d", fg="#cbd1d9", bd=0)
		btn8 = tk.Button(l3, text="8", width=4, height=3, bg="#161a2d", fg="#cbd1d9", bd=0)
		btn9 = tk.Button(l3, text="9", width=4, height=3, bg="#161a2d", fg="#cbd1d9", bd=0)
		btnAC = tk.Button(l4, text="AC", width=4, height=3, bg="#7c388c", fg="#cbd1d9", bd=0)
		btnSr = tk.Button(l4, text="√", width=4, height=3, bg="#1d2035", fg="#cbd1d9", bd=0)
		btnPrc = tk.Button(l4, text="%", width=4, height=3, bg="#1d2035", fg="#cbd1d9", bd=0)
		btnDiv = tk.Button(l4, text="/", width=4, height=3, bg="#1d2035", fg="#cbd1d9", bd=0)
		btnMult = tk.Button(l3, text="X", width=4, height=3, bg="#1d2035", fg="#cbd1d9", bd=0)
		btnMin = tk.Button(l2, text="-", width=4, height=3, bg="#1d2035", fg="#cbd1d9", bd=0)
		btnAdd = tk.Button(l1, text="+", width=4, height=3, bg="#1d2035", fg="#cbd1d9", bd=0)
		btnDot = tk.Button(l0, text=".", width=4, height=3, bg="#161a2d", fg="#cbd1d9", bd=0)
		btnEqw = tk.Button(l0, text="=", width=4, height=3, bg="#1d2035", fg="#cbd1d9", bd=0)


		btn0f.pack(side=tk.LEFT)
		btn0.pack(side=tk.LEFT)
		btn1.pack(side=tk.LEFT)
		btn2.pack(side=tk.LEFT)
		btn3.pack(side=tk.LEFT)
		btn4.pack(side=tk.LEFT)
		btn5.pack(side=tk.LEFT)
		btn6.pack(side=tk.LEFT)
		btn7.pack(side=tk.LEFT)
		btn8.pack(side=tk.LEFT)
		btn9.pack(side=tk.LEFT)
		btnAC.pack(side=tk.LEFT)
		btnSr.pack(side=tk.LEFT)
		btnPrc.pack(side=tk.LEFT)
		btnDiv.pack(side=tk.LEFT)
		btnMult.pack(side=tk.LEFT)
		btnMin.pack(side=tk.LEFT)
		btnAdd.pack(side=tk.LEFT)
		btnDot.pack(side=tk.LEFT)
		btnEqw.pack(side=tk.LEFT)


		btn0f.config(highlightthickness=1, highlightbackground="#161a2d")
		btn0.config(highlightthickness=1, highlightbackground="#161a2d", command=lambda: Add(self, 0))
		btn1.config(highlightthickness=1, highlightbackground="#161a2d", command=lambda: Add(self, 1))
		btn2.config(highlightthickness=1, highlightbackground="#161a2d", command=lambda: Add(self, 2))
		btn3.config(highlightthickness=1, highlightbackground="#161a2d", command=lambda: Add(self, 3))
		btn4.config(highlightthickness=1, highlightbackground="#161a2d", command=lambda: Add(self, 4))
		btn5.config(highlightthickness=1, highlightbackground="#161a2d", command=lambda: Add(self, 5))
		btn6.config(highlightthickness=1, highlightbackground="#161a2d", command=lambda: Add(self, 6))
		btn7.config(highlightthickness=1, highlightbackground="#161a2d", command=lambda: Add(self, 7))
		btn8.config(highlightthickness=1, highlightbackground="#161a2d", command=lambda: Add(self, 8))
		btn9.config(highlightthickness=1, highlightbackground="#161a2d", command=lambda: Add(self, 9))
		btnAC.config(highlightthickness=1, highlightbackground="#161a2d", command=lambda: Clear(self))
		btnSr.config(highlightthickness=1, highlightbackground="#161a2d", command=lambda: Add(self, "√"))
		btnPrc.config(highlightthickness=1, highlightbackground="#161a2d", command=lambda: Add(self, "%"))
		btnDiv.config(highlightthickness=1, highlightbackground="#161a2d", command=lambda: Add(self, "/"))
		btnMult.config(highlightthickness=1, highlightbackground="#161a2d", command=lambda: Add(self, "x"))
		btnMin.config(highlightthickness=1, highlightbackground="#161a2d", command=lambda: Add(self, "-"))
		btnAdd.config(highlightthickness=1, highlightbackground="#161a2d", command=lambda: Add(self, "+"))
		btnDot.config(highlightthickness=1, highlightbackground="#161a2d", command=lambda: Add(self, "."))
		btnEqw.config(highlightthickness=1, highlightbackground="#161a2d", command=lambda: Add(self, "="))





root = tk.Tk()
app = Main(root)
app.pack()
root.title("Calculator")
root.geometry("234x413+500+300")
root.resizable(False, False)
root.mainloop()
		