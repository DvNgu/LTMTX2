import  tkinter as tk
from tkinter import ttk
import socket
import time



def task():
	s.sendall(b"s")
	temp = int(s.recv(128))
	label6.configure(text=int(temp), foreground = 'blue')
	humi = int(s.recv(128))
	label7.configure(text=int(humi), foreground = 'blue')
	win.after(2000, task)
def connect():
	try:
		ip = ipval.get()
		port = portval.get()
		s.connect((str(ip), int(port)))
		label3.configure(text="connected", foreground="green")
		win.after(0, task)
		ipval.set("")
		portval.set("")
		label4.grid(column=0, row=4)
		label5.grid(column=1, row=4)
		label6.grid(column=0, row=5)
		label7.grid(column=1, row=5)
	except:
		label3.configure(text="ERROR", foreground="red")

win = tk.Tk()
win.title("py connect")

win.resizable(False, False)
cone = False
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

ipval=tk.StringVar()
portval=tk.StringVar()

label1 = ttk.Label(win,text='IP', font=("Arial", 16))
label1.grid(column=0, row=0)
label2 = ttk.Label(win,text='PORT', font=("Arial", 16))
label2.grid(column=1, row=0)

ipval_entered = ttk.Entry(win, textvariable=ipval, font = ('Arial', 16))
ipval_entered.grid(column=0, row=1)
portval_entered = ttk.Combobox(win, textvariable=portval, font = ('Arial', 16))
portval_entered.grid(column=1, row=1)
portval_entered['values'] = (0, 10, 80, 128)
portval_entered.current(0)

action1 = ttk.Button(win, text='CONNECT NOW',command=connect)
action1.grid(row=3)
label3 = ttk.Label(win,text='Disconect', font=("Arial", 16))
label3.grid(column=1, row=3)
label3.configure(foreground='red')
label4 = ttk.Label(win,text='TEMPERATURE', font=("Arial", 16))
label5 = ttk.Label(win,text='HUMIDITY', font=("Arial", 16))


label6 = ttk.Label(win,text='--', font=("Arial", 48), borderwidth=2, relief="solid")
label6.configure(foreground='red')
label7 = ttk.Label(win,text='--', font=("Arial", 48), borderwidth=2, relief="solid")
label7.configure(foreground='red')

win.mainloop()



