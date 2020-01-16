import numpy as np
import math
from mnist import MNIST
mndata = MNIST('./')

trainImg, trainLabels= mndata.load_training();
testImg, testLabels=mndata.load_training();
big_array = np.zeros((60000))
big_array_ = np.zeros((10))
u=0;
d=0;

def findEuclideanDistance(a, b):
    p=0;
    d=0;
    c=0;
    for g in range(0,len(a)):
        p+=a[g]*a[g]
        d+=b[g]*b[g]
        c+=a[g]*b[g]
    
    l=p+d-2*c;
    if l > 0:
       return math.sqrt(l);
    else:
        return 0

for o in range(0,100):
    for index in range(0,60000):
        big_array[index] = findEuclideanDistance(trainImg[index],testImg[o])
    result = np.where(big_array == np.amin(big_array))
    k = 0
    idx = np.argpartition(big_array, k)  
    index1=0;
    indecise = np.zeros((10))
    maxElment=np.max(big_array)
    for index1 in range(0,350):
        if big_array[index1]<=maxElment/2+200:
           indecise[trainLabels[idx[index1]]]= indecise[trainLabels[idx[index1]]]+1;
    
    result = np.where(indecise == np.amax(indecise))
    print(indecise)
    print('Predict Value')
    print(result[0])
    print('Actual Value')
    print(testLabels[o])
    
    
    