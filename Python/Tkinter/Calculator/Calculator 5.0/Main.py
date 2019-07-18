import Functions as fn
import tkinter as tk
import math

class Main(tk.Frame):

	#colors
	White = "#dddddd"
	CapeCod = "#333333"

	ButtonFont=("TkDefaultFont", 14)

	input_box = None
	CurrentText = "0"
	CurrentNumber = "empty"
	CurrentOperation = "empty"
	OperatingNumber = "empty"
	Result = "empty"
	FloatNumber = False
	ZeroNum = False
	RootNum = False
	OperationOn = False
	NegativeNum = False
	FirstNegativeNum = False

	PreviousOperation = "empty"
	PreviousNumber = "empty"
	PreviousResult = "empty"
	Priority = False
	TemporarySwitch = False
	SignCount = 0


	def __init__(self, root):
		super().__init__(root)
		self.init_main()


	def init_main(self):
		self.InputBox = tk.Toplevel()
		self.OutputBox = tk.Toplevel()
		self.WindowSetup()

		self.InputBox.geometry("336x418+407+241")
		self.InputBox.overrideredirect(True)
		self.InputBox.configure(background = self.CapeCod)
		#self.InputBox.attributes("-topmost", False)

		self.OutputBox.geometry("688x500+500+200")
		self.OutputBox.overrideredirect(True)
		self.OutputBox.configure(background = self.White)
		#self.OutputBox.attributes("-topmost", False)

		self.input_box = tk.Label(self.OutputBox, anchor=tk.E, 
			padx=10, font=("TkDefaultFont", 18), 
			bg=self.White, fg=self.CapeCod, 
			text=self.CurrentText)
		self.input_box.place(x=400, y=300, width=246, height=120)


		btnAC = tk.Button(self.InputBox, text="AC", bg=self.CapeCod, fg=self.White, bd=0)
		btnScrt = tk.Button(self.InputBox, text="√", bg=self.CapeCod, fg=self.White, bd=0)
		btnPercent = tk.Button(self.InputBox, text="%", bg=self.CapeCod, fg=self.White, bd=0)
		btnDivide = tk.Button(self.InputBox, text="/", bg=self.CapeCod, fg=self.White, bd=0)
		btnMultiply = tk.Button(self.InputBox, text="x", bg=self.CapeCod, fg=self.White, bd=0)
		btnSubstract = tk.Button(self.InputBox, text="-", bg=self.CapeCod, fg=self.White, bd=0)
		btnAdd = tk.Button(self.InputBox, text="+", bg=self.CapeCod, fg=self.White, bd=0)
		btnEqual = tk.Button(self.InputBox, text="=", bg=self.CapeCod, fg=self.White, bd=0)
		btnDot = tk.Button(self.InputBox, text=".", bg=self.CapeCod, fg=self.White, bd=0)

		btn0 = tk.Button(self.InputBox, text="0", bg=self.CapeCod, fg=self.White, bd=0)
		btn1 = tk.Button(self.InputBox, text="1", bg=self.CapeCod, fg=self.White, bd=0)
		btn2 = tk.Button(self.InputBox, text="2", bg=self.CapeCod, fg=self.White, bd=0)
		btn3 = tk.Button(self.InputBox, text="3", bg=self.CapeCod, fg=self.White, bd=0)
		btn4 = tk.Button(self.InputBox, text="4", bg=self.CapeCod, fg=self.White, bd=0)
		btn5 = tk.Button(self.InputBox, text="5", bg=self.CapeCod, fg=self.White, bd=0)
		btn6 = tk.Button(self.InputBox, text="6", bg=self.CapeCod, fg=self.White, bd=0)
		btn7 = tk.Button(self.InputBox, text="7", bg=self.CapeCod, fg=self.White, bd=0)
		btn8 = tk.Button(self.InputBox, text="8", bg=self.CapeCod, fg=self.White, bd=0)
		btn9 = tk.Button(self.InputBox, text="9", bg=self.CapeCod, fg=self.White, bd=0)



		btnAC.config(highlightthickness=0, font=self.ButtonFont, command=lambda: fn.Clear(self))
		btnScrt.config(highlightthickness=0, font=self.ButtonFont, command=lambda: fn.Number(self, "√"))
		btnPercent.config(highlightthickness=0, font=self.ButtonFont, command=lambda: fn.Operation(self, "%"))
		btnDivide.config(highlightthickness=0, font=self.ButtonFont, command=lambda: fn.Operation(self, "/"))
		btnMultiply.config(highlightthickness=0, font=self.ButtonFont, command=lambda: fn.Operation(self, "x"))
		btnSubstract.config(highlightthickness=0, font=self.ButtonFont, command=lambda: fn.Operation(self, "-"))
		btnAdd.config(highlightthickness=0, font=self.ButtonFont, command=lambda: fn.Operation(self, "+"))
		btnEqual.config(highlightthickness=0, font=self.ButtonFont, command=lambda: fn.PrintResult(self))
		btnDot.config(highlightthickness=0, font=self.ButtonFont, command=lambda: fn.Number(self, "."))

		btn0.config(highlightthickness=0, font=self.ButtonFont, command=lambda: fn.Number(self, "0"))
		btn1.config(highlightthickness=0, font=self.ButtonFont, command=lambda: fn.Number(self, "1"))
		btn2.config(highlightthickness=0, font=self.ButtonFont, command=lambda: fn.Number(self, "2"))
		btn3.config(highlightthickness=0, font=self.ButtonFont, command=lambda: fn.Number(self, "3"))
		btn4.config(highlightthickness=0, font=self.ButtonFont, command=lambda: fn.Number(self, "4"))
		btn5.config(highlightthickness=0, font=self.ButtonFont, command=lambda: fn.Number(self, "5"))
		btn6.config(highlightthickness=0, font=self.ButtonFont, command=lambda: fn.Number(self, "6"))
		btn7.config(highlightthickness=0, font=self.ButtonFont, command=lambda: fn.Number(self, "7"))
		btn8.config(highlightthickness=0, font=self.ButtonFont, command=lambda: fn.Number(self, "8"))
		btn9.config(highlightthickness=0, font=self.ButtonFont, command=lambda: fn.Number(self, "9"))



		btnAC.place(x=10, y=11, width=79, height=79)
		btnScrt.place(x=89, y=11, width=79, height=79)
		btnPercent.place(x=168, y=11, width=79, height=79)
		btnDivide.place(x=247, y=11, width=79, height=79)
		btnMultiply.place(x=247, y=90, width=79, height=79)
		btnSubstract.place(x=247, y=169, width=79, height=79)
		btnAdd.place(x=247, y=248, width=79, height=79)
		btnEqual.place(x=247, y=327, width=79, height=79)
		btnDot.place(x=168, y=327, width=79, height=79)

		btn0.place(x=89, y=327, width=79, height=79)
		btn1.place(x=10, y=248, width=79, height=79)
		btn2.place(x=89, y=248, width=79, height=79)
		btn3.place(x=168, y=248, width=79, height=79)
		btn4.place(x=10, y=169, width=79, height=79)
		btn5.place(x=89, y=169, width=79, height=79)
		btn6.place(x=168, y=169, width=79, height=79)
		btn7.place(x=10, y=90, width=79, height=79)
		btn8.place(x=89, y=90, width=79, height=79)
		btn9.place(x=168, y=90, width=79, height=79)


		#OutputBox = tk.Frame(bg=self.White)
		#InputBox = tk.Frame(bg=self.CapeCod)

		#OutputBox.place(x=75, y=30, width=550, height=420)
		#InputBox.place(x=0, y=40, width=250, height=370)

		#testO = tk.Button(self.OutputBox, bg=self.CapeCod, text="OutputBox", command=root.destroy)
		#testO.place(x=65, y=64, height=120, width=150)

		#testI = tk.Button(self.InputBox, bg=self.CapeCod, text="InputBox", command=root.destroy)
		#testI.place(x=65, y=64, height=120, width=150)


	def WindowSetup(self):

		def hidewin():
			self.OutputBox.overrideredirect(False)
			self.OutputBox.iconify()


		Header = tk.Label(self.OutputBox, bg=self.White)
		MinimizeButton = tk.Button(self.OutputBox, text="_", font=12, bg=self.White, bd=0, 
			highlightthickness=0, command=hidewin)
		CloseButton = tk.Button(self.OutputBox, text="x", font=12, bg=self.White, bd=0, 
			highlightthickness=0, command=root.destroy)
		
		Header.place(x=0, y=0, width=490, height=30)
		#MinimizeButton.place(x=490, y=0, width=30, height=30)
		CloseButton.place(x=658, y=0, width=30, height=30)

		

		self._offsetx = 0
		self._offsety = 0
		Header.bind('<Button-1>', lambda x: fn.clickwin(self, x))
		Header.bind('<B1-Motion>', lambda x: fn.dragwin(self, x, self.OutputBox, self.InputBox))





root = tk.Tk()

app = Main(root)
app.pack()
#root.overrideredirect(True)
root.geometry("625x450+500+300")
root.resizable(False, False)
root.wait_visibility(root)
#root.wm_attributes("-alpha", 0.9)
root.withdraw()

root.mainloop()