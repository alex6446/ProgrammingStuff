import tkinter as tk

class Main(tk.Frame):
	def __init__(self, root):
		super().__init__(root)
		self.init_main()

	def init_main(self):

		Label1 = tk.Label(root, bg="#222222", font=("TkDefaultFont", 14), text="Press Button1 to start")
		Label1.place(x=190, y=50, width=220, height=50)

		Entry1 = tk.Entry(root, width=3, bd=0, bg="#151515", fg="#484848",
			highlightcolor="black", highlightbackground="black")
		Entry1.place(x=250, y=100, width=100, height=30)

		def MakeText():
			if Entry1.get() == "":
				Entry1.insert(0, "Hello World!")
			print(Entry1.get())

		Button1 = tk.Button(root, text="Button1", bg="#151515", fg="#484848", bd=0,
			font=("TkDefaultFont", 11), highlightthickness=0, 
			highlightcolor="black", highlightbackground="grey", 
			activebackground="#2f2f2f", command=lambda: MakeText())
		Button1.place(x=250, y=150, width=100, height=30)



root = tk.Tk()

app = Main(root)
app.pack()

root.title("Empty Project")
root.geometry("600x400+500+500")
root.configure(background="#222222")

root.mainloop()
