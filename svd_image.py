import matplotlib.pyplot as plt
import matplotlib.image as mpimg
import numpy as np

'''
    -Dimension must be 2 or 3.
'''
def svd_compress(data,sval):
    if data.all() == None:
        raise Exception('None Data.')

    shape = data.shape
    shape_size = len(data.shape)
    if ((shape_size < 2) or (shape_size > 3)):
        raise Exception('Dimension is:'+str(len(data.shape)) + 'must be 2 or 3.')
 
    if shape_size == 3:
        data = data.reshape(data.shape[0],data.shape[1] * data.shape[2])
        

    '''The sval must be less than shape[0]'''
    if sval > data.shape[0]:
        sval = data.shape[0]
    
    U,Sigma,VT = np.linalg.svd(data)
       
    img_restruct = (U[:,0:sval]).dot(np.diag(Sigma[0:sval])).dot(VT[0:sval,:])

    if len(shape) == 3:
        img_restruct = img_restruct.reshape(shape[0],shape[1],shape[2])
    return sval,img_restruct
