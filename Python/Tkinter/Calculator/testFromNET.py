import tkinter as tk


root = tk.Tk()
root.overrideredirect(True)
root.geometry("450x300+300+300")
root.config(background="darkblue")
root.columnconfigure(0, weight=1)

def move_event(event):
    root.geometry('+{0}+{1}'.format(event.x_root, event.y_root))

title_frame = tk.Frame(root)
title_frame.grid(row=0, column=0, sticky="ew")
title_frame.columnconfigure(0, weight=1)
title_frame.bind('<B1-Motion>', move_event)

tk.Label(title_frame, text="Custom title bar").grid(row=0, column=0, sticky="w")
tk.Button(title_frame, text="-").grid(row=0, column=1, sticky="e")
tk.Button(title_frame, text="[]").grid(row=0, column=2, sticky="e")
tk.Button(title_frame, text="X", command=root.destroy).grid(row=0, column=3, sticky="e")

tk.Label(root, text="Test window!", fg="white", bg="darkblue").grid(row=1, column=0)

root.mainloop()