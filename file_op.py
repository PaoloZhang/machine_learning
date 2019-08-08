import os
import os.path

BRANCH = '├─'
LAST_BRANCH = '└─'
TAB = '│  '
EMPTY_TAB = '   '
NEW_LINE = '\n'

'''
return the bitwise little endian: XWRF
F: Exists
R: Read
W: Write
X: Excutable
'''
def check(path = '.'):
    privilege = 0
    if os.access(path, os.F_OK):
        privilege |= 0x1
        if os.access(path,os.R_OK):
            privilege |= (0x1 << 1)
        if os.access(path,os.W_OK):
            privilege |= (0x1 << 2)
        if os.access(path,os.X_OK):
            privilege |= (0x1 << 3)
    return privilege

def is_readable(path = '.'):
    return check(path) & (0x1<<1) 

def tree(path = '.',placeholder = ''):
    if (False == is_readable(path)):
        return
    folder_list = [folder for folder in os.listdir(path) if os.path.isdir(os.path.join(path,folder))]
    file_list = [file for file in os.listdir(path) if os.path.isfile(os.path.join(path,file))]

    result = ''
    for folder in folder_list[:-1]:
        result += placeholder + BRANCH + folder + NEW_LINE
        result += tree(os.path.join(path,folder),placeholder + TAB)
    if folder_list:
        result += placeholder + (BRANCH if file_list else LAST_BRANCH) + folder_list[-1] + NEW_LINE
        result += tree(os.path.join(path,folder_list[-1]),placeholder+(TAB if file_list else EMPTY_TAB))
    for file in file_list[:-1]:
        result += placeholder + BRANCH + file + NEW_LINE
    if file_list:
        result += placeholder + LAST_BRANCH + file_list[-1]+ NEW_LINE
    return result

def search(file_list,path = '.',extention = ''):
    #file_list = []
    if (False == is_readable(path)):
        return file_list
    folder_list = [os.path.join(path,folder) for folder in os.listdir(path) if os.path.isdir(os.path.join(path,folder))]
    
    for file in os.listdir(path):
        if os.path.isfile(os.path.join(path,file)):
            if (extention == ''):
                file_list.append(os.path.join(path,file))
            else:
                 (_,ext) = os.path.splitext(file)
                 if extention == ext:
                     file_list.append(os.path.join(path,file))
    
    for folder in folder_list:
        search(file_list,folder,extention)
    
def test_search():
    file_list = []
    search(file_list,path='/Users',extention='.py')
    print(file_list)

if __name__ == "__main__":
    test_search()