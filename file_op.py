import os
import os.path

BRANCH = '├─'
LAST_BRANCH = '└─'
TAB = '│  '
EMPTY_TAB = '   '
NEW_LINE = '\n'

def tree(path = '.',placeholder = ''):
    if (os.access(path,os.R_OK)==False):
        return
    folder_list = [folder for folder in os.listdir(path) if os.path.isdir(os.path.join(path,folder))]
    file_list = [file for file in os.listdir(path) if os.path.isfile(os.path.join(path,file))]
    '''
    for file in os.listdir(path):
        if os.path.isfile(os.path.join(path,file)):
            if (extention == ''):
                file_list.append(file)
            else:
                 (_,ext) = os.path.splitext(file)
                 if extention == ext:
                     file_list.append(file)
    '''
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

if __name__ == "__main__":
    print(tree())