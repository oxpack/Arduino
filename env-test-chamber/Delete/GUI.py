#!/usr/bin/python3

import tkinter
class App(tkinter.Tk):
    def __init__(self):
        tkinter.Tk.__init__(self)
        self.grid()
        self.T=21.0
        self.create_widgets()
        self.label = tkinter.Label()
        self.label.grid(row=1, column=0)
        self.label2=tkinter.Label()
        self.label2.grid(row=2, column=0)
        self.label3=tkinter.Label()
        self.label3.grid(row=3, column=0)
        self.UpdateImage(1000)
        self.attributes('-fullscreen',False)
        self.title('Temperature Control')
    def increase(self):
        if self.T<40:
            self.T+=0.1
            self.mlabel2["text"]=str(round(self.T,1))
    def decrease(self):
        if self.T>10:
            self.T-=0.1
            self.mlabel2["text"]=str(round(self.T,1))
    def create_widgets(self):
        self.mlabel1=tkinter.Label(self, text='Temperature:', font=("Helvetica", 16))
        self.mlabel1.grid(row=0, column=0)
        self.mbutton1=tkinter.Button(self, text='<', repeatinterval = 50, repeatdelay = 100, font=("Helvetica", 16),command=self.decrease)
        self.mbutton1.grid(row=0, column=1)
        self.mlabel2=tkinter.Label(self, text=self.T, font=("Helvetica", 16))
        self.mlabel2.grid(row=0, column=2)
        self.mlabel3=tkinter.Label(self, text='C', font=("Helvetica", 16))
        self.mlabel3.grid(row=0, column=3)
        self.mbutton2=tkinter.Button(self, text='>', repeatinterval = 50, repeatdelay = 100, font=("Helvetica", 16),command=self.increase)
        self.mbutton2.grid(row=0, column=4)
        self.mbutton3=tkinter.Button(self, text='SET', font=("Helvetica", 16), command=self.set)
        self.mbutton3.grid(row=0, column=5)
    def UpdateImage(self, delay, event=None):
        self.image = self.get_image()
        self.label.configure(image=self.image)
        self.image2 = self.get_image2()
        self.label2.configure(image=self.image2)
        self.image3 = self.get_image3()
        self.label3.configure(image=self.image3)
        self.after(delay, self.UpdateImage, 1000)

    def get_image(self):
        image = tkinter.PhotoImage(file ='etc-1h.png')
        return image
    def get_image2(self):
        image2 = tkinter.PhotoImage(file ='etc-1d.png')
        return image2
    def get_image3(self):
        image3 = tkinter.PhotoImage(file ='etc-1w.png')
        return image3
    def set(self):
        x=x

if __name__ == "__main__":
    app=App()
    app.mainloop()

