from tkinter import*
from tkinter.filedialog import askopenfilename
import matplotlib
matplotlib.use("TkAgg")
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg, NavigationToolbar2TkAgg
from matplotlib.figure import Figure

import wave
import numpy
from scipy.io import wavfile as wav
from scipy.fftpack import fft
import numpy as np

import matplotlib.pyplot as plt

def addLabel():
    fname = askopenfilename(filetypes=(("Template files", "*.tplate"),
                                           ("HTML files", "*.html;*.htm"),
                                           ("All files", "*.*") ))
    spf = wave.open(fname,'r')
    filename= fname.split("/")[-1]
    v.set(filename)
    
    #Extract Raw Audio from Wav File
    signal = spf.readframes(-1)
    signal = numpy.fromstring(signal, 'Int32')
    f = Figure(figsize=(5,5), dpi=54)
    a = f.add_subplot(111)
    a.set_ylabel('Amplitude',fontsize=14)
    a.plot(signal)
    canvas = FigureCanvasTkAgg(f, my_window)
    canvas.show()
    canvas.get_tk_widget().place(x=48,y=50)#pack(side=tk.BOTTOM, fill=tk.BOTH, expand=True)
  #00  v.set(duration)

def addFFT():
    #spf = wave.open(fname,'r')
    
    rate, data = wav.read(v.get(),'r')
    fft_out = fft(data)
    f = Figure(figsize=(5,5), dpi=54)
    a = f.add_subplot(111)
    
    a.set_ylabel('Imaginary',fontsize=14)
    a.set_xlabel('Amplitude',fontsize=14)
    a.plot(data,np.abs(fft_out))
    canvas = FigureCanvasTkAgg(f, my_window)
    canvas.show()
    canvas.get_tk_widget().place(x=405,y=50)#pack(side=tk.BOTTOM, fill=tk.BOTH, expand=True)
    
my_window=Tk()
my_window.title("HCI 164309")

#my_window.geometry("1000x900")
my_window.geometry("700x420")
my_window.configure(background='white')

lbl_grop1= Label(my_window,text="",relief="solid",width=39,height=20,background="white").place(x=45,y=35)
vg=StringVar(my_window);
v=StringVar(my_window);

uploadGroup= Label(my_window,text="",relief="solid",width=39,height=2,background="white").place(x=45,y=356)
lbl_duration= Label(my_window,text="Duration",foreground="black",background="white").place(x=210,y=367)
lbl_time= Label(my_window,text="",relief="solid",width=3,height=1,background="white",textvariable=vg).place(x=260,y=365)
btn_upload=Button(my_window, text="Upload",command=addLabel, height = 1, width = 13).place(x=60,y=361)


lbl_group2= Label(my_window,text="",relief="solid",width=39,height=20,background="white").place(x=397,y=35)
lbl_auSigna=Label(my_window, 
		 text="Audio Signal",
        background="white",
		 font = "Helvetica 14 bold ").place(x=100,y=0)

lbl_fftName=Label(my_window, 
		 text="Fast Fourier Transform",
        background="white",
		 font = "Helvetica 14 bold ").place(x=420,y=0)
label_4= Label(my_window,text="",relief="solid",width=39,height=2,background="white").place(x=397,y=356)
button_7=Button(my_window, text="Plot",command=addFFT, height = 1, width = 13).place(x=480,y=361)

lbl_fileName=Label(my_window,text="",background="white",foreground="white",textvariable=v)
   
#group = LabelFrame(my_window , text="aliii", padx=0, pady=300, background = "white").place(x=0,y=300)

#left = Button(group, text="Upload",command=addLabel, height = 1, width = 6).place(x=0,y=300)



my_window.mainloop()