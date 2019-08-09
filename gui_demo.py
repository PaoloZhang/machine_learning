import matplotlib
matplotlib.use('tkAgg')
import numpy as np
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
from matplotlib.backends.backend_tkagg import NavigationToolbar2TkAgg
from matplotlib.figure import Figure
import tkinter as tk
from tkinter import filedialog
from PIL import Image, ImageDraw 

class Application(tk.Tk):
    def __init__(self):
        super().__init__()
        self.wm_title("Embed matplotlib in tkinter")
        self.createWidgets()

    def createWidgets(self):
        fig = Figure(figsize=(5,4),dpi = 100)
        self.ax = fig.add_subplot(111)
        self.canvas = FigureCanvasTkAgg(fig,master=self)
        self.canvas.get_tk_widget().pack(side = tk.TOP,fill = tk.BOTH,expand =1)
        self.canvas._tkcanvas.pack(side = tk.TOP,fill = tk.BOTH,expand =1)
        toolbar = NavigationToolbar2TkAgg(self.canvas,self)
        toolbar.update()
        footframe = tk.Frame(master = self).pack(side=tk.BOTTOM)
        tk.Button(master  = footframe,text = 'redraw',command = self.draw).pack(side = tk.BOTTOM)
        tk.Button(master=footframe,text='exit',command=self._quit).pack(side = tk.BOTTOM)
        self.draw()

    def draw(self):
        x = np.random.randint(0,50,size = 100)
        y = np.random.randint(0,50,size = 100)
        self.ax.clear()
        self.ax.scatter(x,y,s = 3)
        self.canvas.show()
    def _quit(self):
        self.quit()
        self.destroy()




def init_window():
    window = tk.Tk()

    window.title('demo')

    window.geometry('1024x768')
    
    label = tk.Label(window,text ='This is tkinter',bg = 'green',font=('Arial',12),width = 30,height = 2)

    label.pack()
    
    canvas = tk.Canvas(window,width = 500,height =768 )
    canvas.pack()
    
    main_menu = tk.Menu(window)

    file_menu = tk.Menu(main_menu,tearoff = 0)

    file_menu.add_command(label = 'Open',command = open_file)
    file_menu.add_command(label = 'Exit', command = window.quit)
    main_menu.add_cascade(label = 'File',menu = file_menu)
    
    window.config(menu = main_menu)

    window.mainloop()

def open_file():
    file = tk.filedialog.askopenfilename() 
    image = Image.open(file) 
    image.show()

if  __name__ == '__main__':
    #init_window()
    app = Application()
    app.mainloop()