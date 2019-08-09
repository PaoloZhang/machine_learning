import matplotlib
matplotlib.use('tkAgg')
import numpy as np
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
from matplotlib.backends.backend_tkagg import NavigationToolbar2TkAgg
from matplotlib.figure import Figure
import matplotlib.image as mpimg
import tkinter as tk
from tkinter import filedialog
from PIL import Image, ImageDraw 
import svd_image

class Application(tk.Tk):
    def __init__(self):
        super().__init__()
        self.file = ''
        self.wm_title("Embed matplotlib in tkinter")
        self.createWidgets()

    def createWidgets(self):
        fig = Figure(figsize=(5,2),dpi = 100)
        
        self.ax1 = fig.add_subplot(1,2,1)
        self.ax2 = fig.add_subplot(1,2,2)

        self.canvas = FigureCanvasTkAgg(fig,master=self)
        self.canvas.get_tk_widget().pack(side = tk.TOP,fill = tk.BOTH,expand =1)
        self.canvas._tkcanvas.pack(side = tk.TOP,fill = tk.BOTH,expand =1)
        toolbar = NavigationToolbar2TkAgg(self.canvas,self)
        toolbar.update()
        footframe = tk.Frame(master = self).pack(side=tk.BOTTOM)
        tk.Button(master=footframe,text='convert',command=self.convert).pack(side = tk.BOTTOM)
        self.entry = tk.Entry(master=footframe, show=None, font=('Arial', 14))
        self.entry.pack(side = tk.BOTTOM)

        main_menu = tk.Menu(self)

        file_menu = tk.Menu(main_menu,tearoff = 0)

        file_menu.add_command(label = 'Open',command = self.open_file)
        file_menu.add_command(label = 'Exit', command = self._quit)
        main_menu.add_cascade(label = 'File',menu = file_menu)
        self.config(menu = main_menu)

    def _quit(self):
        self.quit()
        self.destroy()

    def open_file(self):
        file = tk.filedialog.askopenfilename() 
        if (file != ''):
            self.file = file
            img_eg = mpimg.imread(file)
            self.ax1.imshow(img_eg)
            #.join(img_eg.shape)
            self.ax1.set(title = ("src:"+str(tuple(img_eg.shape))))
            self.canvas.draw()
    
    def convert(self):
        if (self.file != ''):
            sval = int(self.entry.get())
            if (sval > 0):
                data = mpimg.imread(self.file)
                real_sval, transformed_data = svd_image.svd_compress(data, sval)
                self.ax2.imshow(transformed_data.astype(np.uint8))
                shape = transformed_data.shape
                if len(shape) == 2:
                    shape[1] = shape[1] * shape[2]
                    shape[2] = 1
                ratio = (shape[0] + shape[1]+1) * real_sval/ float(shape[0] * shape[1])
                self.ax2.set(title = ("compress ratio:{:.4f}".format(ratio)))
                self.canvas.draw()

if  __name__ == '__main__':
    app = Application()
    app.mainloop()