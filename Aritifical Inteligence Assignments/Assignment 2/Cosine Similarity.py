
#from mlxtend.data import loadlocal_mnist as loadData
import numpy as np
import math
from mnist import MNIST

mndata = MNIST('./')

trainImg, trainLabels=  mndata.load_training()
testImg, testLabels= mndata.load_training()
big_array = np.zeros((60000))
big_array_ = np.zeros((10))


def vector_cos5(v1, v2):
    x=0
    y=0
    z=0
    for h in range(len(v1)):
        q=v1[h]/255
        m=v2[h]/255
        x+=q*q
        y+=m*m
        z+=q*m
    return math.sqrt(z/math.sqrt(x*y))

for index_1 in range(0,100):
    for index in range(0,60000):
        big_array[index]=( vector_cos5(trainImg[index],testImg[index_1]))

    k = 0
    idx = np.argpartition(big_array, k)  
    
    
    index1=0;
    indecise = np.zeros((10))

    for index1 in range(60000-400,60000):
            if big_array[index1]>=0.7:
               indecise[trainLabels[idx[index1]]]= indecise[trainLabels[idx[index1]]]+1;
       
    result = np.where(indecise == np.amax(indecise))

    print(indecise)
    print('Predict Value')
    print(result[0])
    print('Actual Value')
    print(testLabels[index_1])
           