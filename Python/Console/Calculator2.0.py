import tkinter as tk
import math

class Main(tk.Frame):

	def __init__(self, root):
		super().__init__(root)
		self.init_main()

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

	def init_main(self):

		#input_box_color = "#1d2035"
		#ac_color = "#7c388c"
		#op_color = "#1d2035"
		#num_color = "#161a2d"
		#text_color = "#cbd1d9"

		input_box_color = "#1a1c1d"
		ac_color = "#3e6588"
		op_color = "#1a1c1d"
		num_color = "#070808"
		text_color = "#ffffff"

		fix_dot = tk.Label(root, bg=num_color,)
		fix_dot.place(x=0, y=0, width=432, height=10)

		input_box = tk.Label(root, anchor=tk.E, 
			padx=10, font=("TkDefaultFont", 14), 
			bg=input_box_color, fg=text_color, 
			text=self.CurrentText)
		input_box.place(x=2, y=2, width=246, height=120)

		extend_pannel = tk.Label(root, anchor=tk.E, 
			padx=10, font=("TkDefaultFont", 14), 
			bg=input_box_color, fg=text_color)
		extend_pannel.place(x=250, y=2, width=246, height=430)


		def Number(self, x):
			self.OperationOn = False
			if self.CurrentText == "0" and not self.ZeroNum:
				self.CurrentText = str(x)
				input_box.config(text=self.CurrentText)
			else:
				self.CurrentText += str(x)
				input_box.config(text=self.CurrentText)

			if not x == "√":
				if self.CurrentNumber == "empty":
					self.CurrentNumber = str(x)
				else:
					self.CurrentNumber += str(x)

			if x == ".":
				self.FloatNumber = True
			elif x == "0":
				self.ZeroNum = True
			elif x == "√":
				self.RootNum = True
			Count(self)


		def Operation(self, x):
			if not self.OperationOn:
				self.RootNum = False
				if not self.CurrentOperation == "empty" and self.NegativeNum == True:
					self.CurrentText += ")"
					input_box.config(text=self.CurrentText)
				self.NegativeNum = False

				if not self.CurrentText == "0":
					self.CurrentText += x
					input_box.config(text=self.CurrentText)
				elif x == "-":
					self.CurrentText = x
					input_box.config(text=self.CurrentText)
					NegativeNum = True


				self.CurrentOperation = x
				if self.OperatingNumber == "empty":
					if not self.CurrentNumber == "empty":
						if not self.FloatNumber:
							self.OperatingNumber = int(self.CurrentNumber)
						else:
							self.OperatingNumber = float(self.CurrentNumber)
				#elif :	

				if not self.Result == "empty":
					self.OperatingNumber = self.Result

				self.CurrentNumber = "empty"
				self.OperationOn = True

				Count(self)
			elif x == "-" and self.NegativeNum == False:
				self.NegativeNum = True
				self.CurrentText = self.CurrentText + "(" + x
				input_box.config(text=self.CurrentText)



		def Clear(self):
			self.CurrentText = "0"
			input_box.config(text=self.CurrentText)
			self.CurrentNumber = "empty"
			self.CurrentOperation = "empty"
			self.OperatingNumber = "empty"
			self.Result = "empty"
			self.FloatNumber = False
			self.ZeroNum = False
			self.RootNum = False
			self.OperationOn = False
			self.NegativeNum = False


		def Count(self):
				#start modification

			if not self.CurrentNumber == "empty":

				if self.FloatNumber:
					Operand = float(self.CurrentNumber)
				else:
					Operand = int(self.CurrentNumber)
				if self.RootNum:
					Operand = math.sqrt(Operand)
				if self.NegativeNum:
					Operand *= -1

				if not self.CurrentOperation == "empty" and not self.OperatingNumber == "empty":

					if float(self.OperatingNumber) == float(int(self.OperatingNumber)):
						Subject = int(self.OperatingNumber)
					else: 
						Subject = float(self.OperatingNumber)
					if self.Result == "empty" and self.CurrentText[0] == "-":
						Subject *= -1

					if self.CurrentOperation == "+":
						self.Result = Subject + Operand
					elif self.CurrentOperation == "-":
						self.Result = Subject - Operand
					elif self.CurrentOperation == "x":
						self.Result = Subject * Operand
					elif self.CurrentOperation == "/":
						self.Result = Subject / Operand

				elif self.CurrentOperation == "empty" and self.OperatingNumber == "empty":
					self.Result = Operand


		def PrintResult(self):
			if not self.Result == "empty":
				if float(int(self.Result)) == float(self.Result) and self.FloatNumber == True:
					self.FloatNumber = False
					self.Result = int(self.Result)

				self.CurrentText = str(self.Result)
				input_box.config(text=self.CurrentText)

				self.CurrentOperation = "empty"
				self.OperatingNumber = "empty"
				#self.FloatNumber = False
				self.ZeroNum = False
				self.RootNum = False
				self.OperationOn = False
				self.NegativeNum = False




		btnAC = tk.Button(root, text="AC", bg=ac_color, fg=text_color, bd=0)
		btnScrt = tk.Button(root, text="√", bg=op_color, fg=text_color, bd=0)
		btnPercent = tk.Button(root, text="%", bg=op_color, fg=text_color, bd=0)
		btnDivide = tk.Button(root, text="/", bg=op_color, fg=text_color, bd=0)
		btnMultiply = tk.Button(root, text="x", bg=op_color, fg=text_color, bd=0)
		btnSubstract = tk.Button(root, text="-", bg=op_color, fg=text_color, bd=0)
		btnAdd = tk.Button(root, text="+", bg=op_color, fg=text_color, bd=0)
		btnEqual = tk.Button(root, text="=", bg=op_color, fg=text_color, bd=0)
		btnDot = tk.Button(root, text=".", bg=num_color, fg=text_color, bd=0)

		btn0 = tk.Button(root, text="0", bg=num_color, fg=text_color, bd=0)
		btn1 = tk.Button(root, text="1", bg=num_color, fg=text_color, bd=0)
		btn2 = tk.Button(root, text="2", bg=num_color, fg=text_color, bd=0)
		btn3 = tk.Button(root, text="3", bg=num_color, fg=text_color, bd=0)
		btn4 = tk.Button(root, text="4", bg=num_color, fg=text_color, bd=0)
		btn5 = tk.Button(root, text="5", bg=num_color, fg=text_color, bd=0)
		btn6 = tk.Button(root, text="6", bg=num_color, fg=text_color, bd=0)
		btn7 = tk.Button(root, text="7", bg=num_color, fg=text_color, bd=0)
		btn8 = tk.Button(root, text="8", bg=num_color, fg=text_color, bd=0)
		btn9 = tk.Button(root, text="9", bg=num_color, fg=text_color, bd=0)



		btnAC.config(highlightthickness=0, command=lambda: Clear(self))
		btnScrt.config(highlightthickness=0, command=lambda: Number(self, "√"))
		btnPercent.config(highlightthickness=0, command=lambda: Operation(self, "%"))
		btnDivide.config(highlightthickness=0, command=lambda: Operation(self, "/"))
		btnMultiply.config(highlightthickness=0, command=lambda: Operation(self, "x"))
		btnSubstract.config(highlightthickness=0, command=lambda: Operation(self, "-"))
		btnAdd.config(highlightthickness=0, command=lambda: Operation(self, "+"))
		btnEqual.config(highlightthickness=0, command=lambda: PrintResult(self))
		btnDot.config(highlightthickness=0, command=lambda: Number(self, "."))

		btn0.config(highlightthickness=0, command=lambda: Number(self, "0"))
		btn1.config(highlightthickness=0, command=lambda: Number(self, "1"))
		btn2.config(highlightthickness=0, command=lambda: Number(self, "2"))
		btn3.config(highlightthickness=0, command=lambda: Number(self, "3"))
		btn4.config(highlightthickness=0, command=lambda: Number(self, "4"))
		btn5.config(highlightthickness=0, command=lambda: Number(self, "5"))
		btn6.config(highlightthickness=0, command=lambda: Number(self, "6"))
		btn7.config(highlightthickness=0, command=lambda: Number(self, "7"))
		btn8.config(highlightthickness=0, command=lambda: Number(self, "8"))
		btn9.config(highlightthickness=0, command=lambda: Number(self, "9"))
		


		btnAC.place(x=2, y=124, width=60, height=60)
		btnScrt.place(x=64, y=124, width=60, height=60)
		btnPercent.place(x=126, y=124, width=60, height=60)
		btnDivide.place(x=188, y=124, width=60, height=60)
		btnMultiply.place(x=188, y=186, width=60, height=60)
		btnSubstract.place(x=188, y=248, width=60, height=60)
		btnAdd.place(x=188, y=310, width=60, height=60)
		btnEqual.place(x=188, y=372, width=60, height=60)
		btnDot.place(x=126, y=372, width=60, height=60)

		btn0.place(x=64, y=372, width=60, height=60)
		btn1.place(x=2, y=310, width=60, height=60)
		btn2.place(x=64, y=310, width=60, height=60)
		btn3.place(x=126, y=310, width=60, height=60)
		btn4.place(x=2, y=248, width=60, height=60)
		btn5.place(x=64, y=248, width=60, height=60)
		btn6.place(x=126, y=248, width=60, height=60)
		btn7.place(x=2, y=186, width=60, height=60)
		btn8.place(x=64, y=186, width=60, height=60)
		btn9.place(x=126, y=186, width=60, height=60)





root = tk.Tk()

app = Main(root)
app.pack()
root.title("Calculator 2.0")
root.geometry("498x434+500+300")
#root.geometry("550x832+500+300")
root.resizable(False, False)
#root.configure(background = "#161a2d")
root.configure(background = "#070808")

root.mainloop()