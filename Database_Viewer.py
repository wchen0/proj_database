from tkinter import *



# read data from file and return a list
def read_file(filename):
	_list = []
	try:
		f = open(filename,"r")
		line = f.readline()
		while line:
			_list.append(line.strip().split())
			line = f.readline()
		f.close()
		return _list
	except:
		return None



# print table from a list
def Display():
	filename = Entry.get().strip()
	_list = read_file(filename)
	if _list == None:
		Label(root, anchor=W, text="Cannot Open File " + filename).grid(row=1, column=0)
		return
	if int(_list[0][0]) >= 0:
		if len(_list[0]) <= int(_list[0][0])+2:
			Label(root, anchor=W, text="Invalid Primary Key").grid(row=1, column=0)
		else:
			Label(root, anchor=W, text="   Primary Key: " + _list[0][int(_list[0][0])+2]).grid(row=1, column=0)
	else:
		Label(root, anchor=W, text="   No Primary Key").grid(row=1, column=0)

	# print column
	for col in range(2, len(_list[0])):
		Label(root, text=_list[0][col], relief=SUNKEN).grid(row=2, column=col-2)

	# print content
	for row in range(1, len(_list)):
		for col in range(0, len(_list[row])):
			Label(root, text=_list[row][col]).grid(row=row+2, column=col)





root = Tk()

root.title("Database Viewer")

Enter_Label = Label(root, text="Please Enter Name of the File: ", anchor=W)
Enter_Label.grid(row=0, column=0)

Display_Button = Button(root, text='Display', padx=20, pady=5, command=Display)
Display_Button.grid(row=0,column=4)

Entry = Entry(root, width=50, borderwidth=7)
Entry.grid(row=0, column=1, columnspan=3)
Entry.insert(0, "C:\\Users\\WEITIAN\\Desktop\\Database_x86\\")


root.mainloop()