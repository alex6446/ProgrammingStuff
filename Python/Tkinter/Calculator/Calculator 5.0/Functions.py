#import tkinter as tk
import math

def clickwin(self ,event):
	self._offsetx = event.x
	self._offsety = event.y

def dragwin(self, event, OutputBox, InputBox):
	x = self.winfo_pointerx() - self._offsetx
	y = self.winfo_pointery() - self._offsety
	OutputBox.geometry('+{x}+{y}'.format(x=x,y=y))
	x = x - 93
	y = y + 41
	InputBox.geometry('+{x}+{y}'.format(x=x,y=y))



def Number(self, x):

	self.OperationOn = False
	if self.CurrentText == "0" and not self.ZeroNum:
		self.CurrentText = str(x)
		self.input_box.config(text=self.CurrentText)
	else:
		self.CurrentText += str(x)
		self.input_box.config(text=self.CurrentText)
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
	self.SignCount += 1
	#if x == "+" or x == "-":
	#	if Priority:
	if self.TemporarySwitch:
		self.Priority = False
		self.TemporarySwitch = False
	if x == "+" or x == "-":
		self.PreviousResult = self.Result
	#self.FirstNegativeNum = False
	if not self.OperationOn:
		self.RootNum = False
		if (x == "/" or x == "x"):
			if self.CurrentOperation == "+" or self.CurrentOperation == "-":
				#if not self.NegativeNum:
				self.PreviousOperation = self.CurrentOperation
				self.Priority = True
				print("OK")
				#elif not self.SignCount == 2 and not self.CurrentText[0] == "-":
				if self.SignCount == 2 and self.CurrentText[0] == "-":
					self.Priority = False
		if not self.CurrentOperation == "empty" and self.NegativeNum == True:
			if not self.OperatingNumber == "empty":
				self.CurrentText += ")"
				self.input_box.config(text=self.CurrentText)
			if not self.Priority:
				self.NegativeNum = False
			print(self.Result)
		if not self.CurrentText == "0":
			self.CurrentText += x
			self.input_box.config(text=self.CurrentText)
		elif x == "-":
			self.CurrentText = x
			self.input_box.config(text=self.CurrentText)
			self.NegativeNum = True
		print(x)
		
		#self.CurrentOperation = x
		if self.OperatingNumber == "empty":
			if not self.CurrentNumber == "empty":
				if not self.FloatNumber:
						self.OperatingNumber = int(self.CurrentNumber)
				else:
						self.OperatingNumber = float(self.CurrentNumber)
		#elif :	
		print("OperatingNumber: ", self.OperatingNumber)
		if not self.Result == "empty":
			if (x == "/" or x == "x") and self.Priority:
				if self.CurrentOperation == "+" or self.CurrentOperation == "-":
					self.PreviousNumber = self.PreviousResult
					#if self.Result < 0: due to float tto string error
					if self.NegativeNum:
						self.OperatingNumber = -1*float(self.CurrentNumber)
						self.NegativeNum = False
					else:
						self.OperatingNumber = self.CurrentNumber
				else:
					self.OperatingNumber = self.Result
			else:
				self.OperatingNumber = self.Result

		self.CurrentNumber = "empty"
		self.OperationOn = True		
		self.CurrentOperation = x		
		Count(self)
		self.FirstNegativeNum = False

	elif x == "-" and self.NegativeNum == False:
		self.NegativeNum = True
		self.CurrentText = self.CurrentText + "(" + x
		self.input_box.config(text=self.CurrentText)



	print(self.CurrentText)
	print("OperatingNumber: ", self.OperatingNumber)
	print("CurrentNumber:", self.CurrentNumber)
	print("CurrentOperation:", self.CurrentOperation)
	print("PreviousOperation: ", self.PreviousOperation)
	print("PreviousNumber:", self.PreviousNumber)
	print("PreviousResult:", self.PreviousResult)
	print("Result:", self.Result)
	print("Priority: ", self.Priority)
	print("NegativeNum: ", self.NegativeNum)
	print("FirstNegativeNum: ", self.FirstNegativeNum)
	print()





def Count(self):
	if not self.CurrentNumber == "empty":
		if self.FloatNumber:
			Operand = float(self.CurrentNumber)
		else:
			Operand = int(self.CurrentNumber)
		if self.RootNum:
			Operand = math.sqrt(Operand)
		if self.NegativeNum:
			Operand *= -1

		print(self.CurrentText)
		print("OperatingNumber: ", self.OperatingNumber)
		print("CurrentNumber:", self.CurrentNumber)
		print("CurrentOperation:", self.CurrentOperation)
		print("PreviousOperation: ", self.PreviousOperation)
		print("PreviousNumber:", self.PreviousNumber)
		print("PreviousResult:", self.PreviousResult)
		print("Result:", self.Result)
		print("Priority: ", self.Priority)
		print("NegativeNum: ", self.NegativeNum)
		print("FirstNegativeNum: ", self.FirstNegativeNum)
		print()
		if not self.CurrentOperation == "empty" and not self.OperatingNumber == "empty":
			try:
				if float(self.OperatingNumber) == float(int(self.OperatingNumber)):
					Subject = int(self.OperatingNumber)
				else: 
					Subject = float(self.OperatingNumber)
			except ValueError:
				Subject = float(self.OperatingNumber)

			if self.Result == "empty" and self.CurrentText[0] == "-":
				Subject *= -1
				self.FirstNegativeNum = True
				print("Done", Subject)
			elif self.FirstNegativeNum == True and self.CurrentText[0] == "-":
				Subject *= -1

			if self.CurrentOperation == "+":
				if self.Priority:
					if self.PreviousOperation == "+":
						Subject = self.PreviousNumber + self.OperatingNumber
					else:
						Subject = self.PreviousNumber - self.OperatingNumber
					self.TemporarySwitch = True

				self.Result = Subject + Operand
			elif self.CurrentOperation == "-":
				if self.Priority:
					if self.PreviousOperation == "+":
						Subject = self.PreviousNumber + self.OperatingNumber
					else:
						Subject = self.PreviousNumber - self.OperatingNumber
					self.TemporarySwitch = True
				self.Result = Subject - Operand
			elif self.CurrentOperation == "x":
				print(Subject*Operand)
				self.Result = Subject * Operand
			elif self.CurrentOperation == "/":
				self.Result = Subject / Operand

			#elif self.CurrentOperation == "empty" and self.OperatingNumber == "empty":
		elif self.OperatingNumber == "empty":
			self.Result = Operand

	elif self.Priority and not self.TemporarySwitch:
		if self.CurrentOperation == "+" or self.CurrentOperation == "-":
			if self.PreviousOperation == "+":
				self.PreviousResult = self.PreviousNumber + self.Result
			else:
				self.PreviousResult = self.PreviousNumber - self.Result
	if self.Result == "empty" and self.CurrentText[0] == "-":
		self.FirstNegativeNum = True
		print("FNN = TRUE")




	print(self.CurrentText)
	print("OperatingNumber: ", self.OperatingNumber)
	print("CurrentNumber:", self.CurrentNumber)
	print("CurrentOperation:", self.CurrentOperation)
	print("PreviousOperation: ", self.PreviousOperation)
	print("PreviousNumber:", self.PreviousNumber)
	print("PreviousResult:", self.PreviousResult)
	print("Result:", self.Result)
	print("Priority: ", self.Priority)
	print("NegativeNum: ", self.NegativeNum)
	print("FirstNegativeNum: ", self.FirstNegativeNum)
	print()
	###############################



def PrintResult(self):
	if not self.Result == "empty":
		if float(int(self.Result)) == float(self.Result) and self.FloatNumber == True:
			self.FloatNumber = False
			self.Result = int(self.Result)
		if self.Priority:
			if not self.TemporarySwitch:
				if self.PreviousOperation == "+":
					self.Result = self.PreviousNumber + self.Result
				else:
					self.Result = self.PreviousNumber - self.Result
		self.CurrentText = str(self.Result)
		self.input_box.config(text=self.CurrentText)
		self.CurrentOperation = "empty"
		self.OperatingNumber = "empty"
		#self.FloatNumber = False
		self.ZeroNum = False
		self.RootNum = False
		self.OperationOn = False
		self.NegativeNum = False
		self.FirstNegativeNum = False
		self.PreviousOperation = "empty"
		self.PreviousNumber = "empty"
		self.PreviousResult = "empty"
		self.Priority = False
		self.TemporarySwitch = False
		if self.CurrentText[0] == "-":
			self.SignCount = 1
		else:
			self.SignCount = 0


def Clear(self):

	self.CurrentText = "0"
	self.input_box.config(text=self.CurrentText)
	self.CurrentNumber = "empty"
	self.CurrentOperation = "empty"
	self.OperatingNumber = "empty"
	self.Result = "empty"
	self.FloatNumber = False
	self.ZeroNum = False
	self.RootNum = False
	self.OperationOn = False
	self.NegativeNum = False
	self.FirstNegativeNum = False

	self.PreviousOperation = "empty"
	self.PreviousNumber = "empty"
	self.PreviousResult = "empty"
	self.Priority = False
	self.TemporarySwitch = False
	self.SignCount = 0



#def hidewin(OutputBox, InputBox):
#	OutputBox.overrideredirect(False)
#	OutputBox.iconify()