from tkinter import *




def OnMW(event):
	move = 0
	if event.num == 5:
		move = 3
	if event.num == 4:
		move = -3
	canvas.yview_scroll(move, "units")





parent = Tk()

canvas = Canvas(parent, height=400)
frame = Frame(canvas)

scrollbar = Scrollbar(parent, orient="vertical", command=canvas.yview)
canvas.configure(yscrollcommand=scrollbar.set)
#scrollbar.pack(side="right", fill="y")
canvas.pack(side="left", fill="both", expand=True)
canvas.create_window((4,4), window=frame, anchor="nw", tags="frame")

frame.bind("<Configure>", lambda x: canvas.configure(scrollregion=canvas.bbox("all")))
parent.bind("<Down>", lambda x: canvas.yview_scroll(3, 'units'))
parent.bind("<Up>", lambda x: canvas.yview_scroll(-3, 'units'))

canvas.bind("<Button-4>", OnMW)
canvas.bind("<Button-5>", OnMW)

labels = [Label(frame, text=str(i)) for i in range(100)]
for l in labels: l.pack()

BigText = "Hello"
big_text = Label(frame, font=("TkDefaultFont", 18), text=BigText)

smallText = "World"
small_text = Label(frame, font=("TkDefaultFont", 10), text=smallText)

emptyText = ""
empty_text = Label(frame, font=("TkDefaultFont", 10), text=emptyText)

big_text.pack()
small_text.pack()
empty_text.pack()

parent.mainloop() 