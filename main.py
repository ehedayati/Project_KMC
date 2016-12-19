from Tkinter import *
from subprocess import call
import tkMessageBox

#

top = Tk()
top.wm_title("KMC")

L1 = Label(top, text="number of Rows/column:\t", borderwidth=1).grid(row=1, column=1)
E1var = StringVar()
E1var.set("10")
E1 = Entry(top, bd=5, textvariable=E1var, borderwidth=1).grid(row=1, column=3)

L2 = Label(top, text="Bond Energy:\t\t", borderwidth=1).grid(row=2, column=1)
E2var = StringVar()
E2var.set("-10")
E2 = Entry(top, bd=5, textvariable=E2var, borderwidth=1).grid(row=2, column=3)

L3 = Label(top, text="Chemical potential difference:\t", borderwidth=1).grid(row=3, column=1)
E3var = StringVar()
E3var.set("9")
E3 = Entry(top, bd=5, textvariable=E3var, borderwidth=1).grid(row=3, column=3)

L4 = Label(top, text="Number of KMC sweeps:\t", borderwidth=1).grid(row=4, column=1)
E4var = StringVar()
E4var.set("100")
E4 = Entry(top, bd=5, textvariable=E4var, borderwidth=1).grid(row=4, column=3)


def run_kmc():
    call(["./SC_porject_crystal_growth_KMC"])
def gen_movie():
    call(["bash","visualization/vmd/runme.sh"])
def gen_plot():
    call(["bash","visualization/gnuplot/runme.sh"])
    

_simulation = Button(top, text="Start Simulation", borderwidth=1, command=run_kmc).grid(row=5, column=2)
_video = Button(top, text="Video generation", borderwidth=1, command=gen_movie).grid(row=6, column=1)
_plot = Button(top, text="Plot generation", borderwidth=1, command=gen_plot).grid(row=6, column=3)

top.mainloop()
