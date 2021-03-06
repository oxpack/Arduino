#!/usr/bin/python2

import Tkinter
import sys
import time
import serial_functions

class App(Tkinter.Tk):
    def __init__(self):
        Tkinter.Tk.__init__(self)
        self.grid()
        self.T=21.0
        self.create_widgets()
        self.label = Tkinter.Label()
        self.label.grid(row=1, column=1, columnspan=6)
        self.label2=Tkinter.Label()
        self.label2.grid(row=2, column=1, columnspan=6)
        self.label3=Tkinter.Label()
        self.label3.grid(row=3, column=1, columnspan=6)
        self.UpdateImage(1000)
        self.attributes('-fullscreen',True)
        self.title('Temperature Control')
    def increase(self):
        if self.T<50:
            self.T+=0.1
            self.mlabel2["text"]=str(round(self.T,1))
    def decrease(self):
        if self.T>10:
            self.T-=0.1
            self.mlabel2["text"]=str(round(self.T,1))
    def create_widgets(self):
        self.mlabel1=Tkinter.Label(self, text='              ', font=("Helvetica", 16))
        self.mlabel1.grid(row=0, column=0)
        self.mlabel1=Tkinter.Label(self, text='Temperature:', font=("Helvetica", 16))
        self.mlabel1.grid(row=0, column=1)
        self.mbutton1=Tkinter.Button(self, text='<', repeatinterval = 50, repeatdelay = 100, font=("Helvetica", 16),command=self.decrease)
        self.mbutton1.grid(row=0, column=2)
        self.mlabel2=Tkinter.Label(self, text=self.T, font=("Helvetica", 16))
        self.mlabel2.grid(row=0, column=3)
        self.mlabel3=Tkinter.Label(self, text='C', font=("Helvetica", 16))
        self.mlabel3.grid(row=0, column=4)
        self.mbutton2=Tkinter.Button(self, text='>', repeatinterval = 50, repeatdelay = 100, font=("Helvetica", 16),command=self.increase)
        self.mbutton2.grid(row=0, column=5)
        
    def UpdateImage(self, delay, event=None):
	self.mbutton3=Tkinter.Button(self, text='SET', font=("Helvetica", 16), command=serial_functions.setpt_chg(self.T))
        self.mbutton3.grid(row=0, column=6)	
	print(self.T)
        self.image = self.get_image()
        self.label.configure(image=self.image)
        self.image2 = self.get_image2()
        self.label2.configure(image=self.image2)
        self.image3 = self.get_image3()
       	self.label3.configure(image=self.image3)
       	self.t_process = serial_functions.temp_read()
       	command=serial_functions.temp_rec(self.t_process)
       	command=serial_functions.make_gr()
       	self.after(delay, self.UpdateImage, 30000)

    def get_image(self):
        image = Tkinter.PhotoImage(file ='etc-1h.png')
        return image
    def get_image2(self):
        image2 = Tkinter.PhotoImage(file ='etc-1d.png')
        return image2
    def get_image3(self):
        image3 = Tkinter.PhotoImage(file ='etc-1w.png')
        return image3

if __name__ == "__main__":
    app=App()
    app.mainloop()

