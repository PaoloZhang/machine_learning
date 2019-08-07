import matplotlib.pyplot as plt
import matplotlib.image as mpimg
import numpy as np

def compress(file_name="/Users/Mac/Downloads/test.jpg"):
    img_eg = mpimg.imread(file_name)
    img_tmp = img_eg.reshape(img_eg.shape[0],img_eg.shape[1]*img_eg.shape[2])
    U,Sigma,VT = np.linalg.svd(img_tmp)
    sval_num = 10
    img_restruct1 = (U[:,0:sval_num]).dot(np.diag(Sigma[0:sval_num])).dot(VT[0:sval_num,:])
    img_restruct1 = img_restruct1.reshape(img_eg.shape[0],img_eg.shape[1],img_eg.shape[2])


    sval_num = 60
    img_restruct2 = (U[:,0:sval_num]).dot(np.diag(Sigma[0:sval_num])).dot(VT[0:sval_num,:])
    img_restruct2 = img_restruct2.reshape(img_eg.shape[0],img_eg.shape[1],img_eg.shape[2])


    sval_num = 200
    img_restruct3 = (U[:,0:sval_num]).dot(np.diag(Sigma[0:sval_num])).dot(VT[0:sval_num,:])
    img_restruct3 = img_restruct3.reshape(img_eg.shape[0],img_eg.shape[1],img_eg.shape[2])

    fig, ax = plt.subplots(2,2,figsize = (24,32))
    
    ax[0][0].imshow(img_eg)
    ax[0][0].set(title = "src")

    ax[0][1].imshow(img_restruct1.astype(np.uint8))
    ax[0][1].set(title = "nums of sigma = 10")

    ax[1][0].imshow(img_restruct2.astype(np.uint8))
    ax[1][0].set(title = "nums of sigma = 60")

    ax[1][1].imshow(img_restruct3.astype(np.uint8))
    ax[1][1].set(title = "nums of sigma = 200")
    plt.show()
  