from nltk.corpus import wordnet as wn
import numpy as np
import random
import sys
import getopt

def get_prompt():
    print("Please input the prompt \n"+"1:learn_matrix_axis()")
    print('exit():exit')
    input_text = input(">>")
    return input_text

#learn the meaning of axis, can write a blog in future.
def learn_matrix_axis():
    axis0 = 3
    axis1 = 4
    axis2 = 5
    origin_matrix = np.random.random(axis0 * axis1 * axis2  )
    origin_matrix = origin_matrix.reshape(axis0,axis1,axis2)
    print('matrix is:\n'+repr(origin_matrix))
    print('matrix[0] is:\n'+repr(origin_matrix[0]))
    print('matrix[0][0] is:\n'+repr(origin_matrix[0][0]))
    print('matrix[0][0][0] is:\n'+repr(origin_matrix[0][0][0]))

    print('max matrix axis 0'+ repr(np.max(origin_matrix,axis=0)))
    print('max matrix axis 1'+ repr(np.max(origin_matrix,axis=1)))
    print('max matrix axis 2'+ repr(np.max(origin_matrix,axis=2)))
    

def test_wordnet():
    poses = {'n':'noun','v':'verb','s':'adj(s)','a':'adj','r':'adv'} 
    for synset in wn.synsets("good"):
        print("{}:{}".format(poses[synset.pos()],",".join([l.name() for l in synset.lemmas()])))

def softmax(x):
    origin_shape = x.shapepy
    if len(origin_shape.shape) > 1:
        tmp = np.max(x,axis=1)
        x-=tmp.reshape((x.shape[0],1))
        x = np.exp(x)
        tmp = np.sum(x,axis=1)
        x /= tmp.reshape((x.shape[0],1))
    else:
        tmp = np.max(x)
        x-=tmp
        x = np.exp(x)
        tmp = np.sum(x)
        x /= tmp
    return x

#def sigmoid(x):
   

def main(argv):
    print(argv)
    while(True):
        input_text = get_prompt()
        if (input_text == "1"):
            learn_matrix_axis()
        elif (input_text == "exit()"):
            break
        
    

if __name__ == "__main__":
        main(sys.argv[1:])

