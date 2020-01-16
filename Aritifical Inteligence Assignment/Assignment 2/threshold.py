from mlxtend.data import loadlocal_mnist as loadData
import numpy as np

    
trainImg, trainLabels= loadData(  'train-images.idx3-ubyte', 'train-labels.idx1-ubyte');
testImg, testLabels=loadData( 't10k-images.idx3-ubyte', 't10k-labels.idx1-ubyte');

trainImg=trainImg/255
testImg=testImg/255
    


def threshold_output(theta, imag,threshold,label):
    desiredoutput=0;
    #print(np.dot(theta, imag))
    out =0
    if (np.dot(theta, imag) >= threshold):
       desiredoutput= 1;
    else: 
        desiredoutput= 0;
     
    out=label-desiredoutput
    if out!=0:
         theta = theta + ((0.1*out)*imag.T)
         threshold = threshold - (0.1*out)
   
    return threshold,theta;
         
#sigmoid activation function
def sigmoid_output(theta,imag,threshold,label):
    sigm=np.zeros((1,784))
    sigm=np.dot(theta,imag)
    desiredoutput=0
    reusl=0;
    sigm= (1 / (1 + np.exp(-sigm)))
    
    reusl=sigm-desiredoutput
   
    if  desiredoutput!=0:
        theta = theta + ((0.01*reusl)*imag.T)
        threshold = threshold - (0.01*reusl)
        
    return threshold,theta;

def changeWeights(LabelForTrainImages,ImagesToTrain,weight,accuracy,threshold):
    accuracy_1 = 0
    vectorization=(np.dot(ImagesToTrain, weight.T)) >= threshold
    
    for i in range(0, ImagesToTrain.shape[0]):
        if (vectorization[i] == 1 and vectorization[i] == LabelForTrainImages[i]):
            accuracy_1 += 1
                
    if accuracy_1 > accuracy:
        return threshold, weight,accuracy_1
    else:
         return threshold, weight,accuracy
         
              
    

    
def trainPreceptron(ImagesToTrain,LabelForTrainImages,currI):
    Weights = np.zeros((1, 784))
    threshold = 0
    accuracy=0;
    thresholdBst=0;
    BstWeights=0
    
    for i in range(0, 10):
        for image, label in zip(ImagesToTrain, LabelForTrainImages):
            image = image[:, np.newaxis]
            #print(np.dot(Weights, image))
            threshold,Weights=threshold_output(Weights,image,threshold,label)
        thresholdBst, BstWeights,accuracy= changeWeights(LabelForTrainImages,ImagesToTrain,Weights,accuracy,0.01)
    
    print('Accuracy for value : '+ str(currI) +' '+  str((accuracy/ImagesToTrain.shape[0])*100))
    
    return BstWeights, thresholdBst
  
    




weightsE = np.zeros((10, 784))
thresholdsE = np.zeros((10, 1))
num = 0

for i in range(0, 10):
   # print("for label " + str(i))
    weightsE[i, :], thresholdsE[i] = trainPreceptron(
        trainImg, trainLabels == i,i)




thresholdMatrix = np.repeat(thresholdsE.T, testImg.shape[0], 0)#numpy.matlib.repmat(thresholds, 1000, thresholds.shape[0])

Matrix = (np.dot(testImg, (weightsE).T)) >= thresholdMatrix

results = np.argmax(Matrix, axis=1)
for j in range(0, testImg.shape[0]):
    value = results[j]
    flag = np.dot(testImg[j], weightsE[value, :].T) >= thresholdsE[value]
    if testLabels[j] == value and flag == 1:
        num += 1



print('Accuracy on testing data is : ' + str((num/testImg.shape[0])*100))