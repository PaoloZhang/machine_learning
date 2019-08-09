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

        main_menu = tk.Menu(self)

        file_menu = tk.Menu(main_menu,tearoff = 0)

        file_menu.add_command(label = 'Open',command = self._open_file)
        file_menu.add_command(label = 'Exit', command = self._quit)
        main_menu.add_cascade(label = 'File',menu = file_menu)
        self.config(menu = main_menu)

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

    def _open_file(self):
        file = tk.filedialog.askopenfilename() 
        image = Image.open(file) 
        image.show()

if  __name__ == '__main__':
    app = Application()
    app.mainloop()