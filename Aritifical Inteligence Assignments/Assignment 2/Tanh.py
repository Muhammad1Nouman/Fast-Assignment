from mlxtend.data import loadlocal_mnist
import numpy as np

trainImg, trainLabel = loadlocal_mnist('C:\\Users\\Muhammad Nouman\\.spyder-py3\\train-images.idx3-ubyte', 'C:\\Users\\Muhammad Nouman\\.spyder-py3\\train-labels.idx1-ubyte');

testImg, testLabel = loadlocal_mnist('C:\\Users\\Muhammad Nouman\\.spyder-py3\\t10k-images.idx3-ubyte', 'C:\\Users\\Muhammad Nouman\\.spyder-py3\\t10k-labels.idx1-ubyte');

trainImg = trainImg[1:1001, :];
trainLabel = trainLabel[1:1001];

testImg = testImg[1:101, :];
testLabel = testLabel[1:101];

testImg = testImg / 255;

trainImg = trainImg / 255;


def tanCal(x):
    return np.tanh(x);


def learnSigmoid(trainImg, trainLabel):
    r = trainImg.shape[0];
    c = trainImg.shape[1];
    Trained = np.zeros((10, c + 1));
    appen = np.ones((r, 1));
    trainImg = np.append(appen, trainImg, axis=1);
    Weights = np.zeros((c + 1, 1));

    for i in range(10):
        weights = gradient_descent(trainImg, trainLabel == i, Weights);
        Trained[i, :] = weights.T;

    return Trained;


def gradient_descent(imge, labe, W):
    m = imge.shape[0];

    labe = labe[:, np.newaxis];

    for i in range(1000):
        for q in range(m):
            x = imge[q, :];
            x = x[:, np.newaxis];
            y = tanCal(np.dot(W.T, x));
            h = (labe[q] - y) * (1 - y ** 2);

            gradient = (0.0001 * h * x);

            W = W + gradient;

    return W;


def Predict(X_test, Trained_Weights, Y_test):
    labels = np.zeros((X_test.shape[0], 10));
    train = np.zeros((X_test.shape[0], 1));
    a = np.ones((X_test.shape[0], 1));
    X_test = np.append(a, X_test, axis=1);
    labels = tanCal(np.mat(X_test) * np.mat(Trained_Weights.T));
    train = np.argmax(labels, axis=1);

    result = 0;

    truePositive = 0
    trueNegative = 0
    falsePositive = 0
    falseNegative = 0

    for i in range(len(train)):
        if train[i] == Y_test[i]:
            result = result + 1;
            truePositive += 1
            trueNegative += 9
        else:
            falsePositive += 1
            falseNegative += 1
            trueNegative += 8

    # Show accuracy#
    print('TruePositive:' + str(truePositive));
    print('TrueNegative:' + str(trueNegative));
    print('falseNegative:' + str(falseNegative));
    print('FalsePositive:' + str(falsePositive));

    # Show accuracy#
    percent = (result / testImg.shape[0]) * 100;
    print('Accuracy is : ' + str(percent));
    return;

    # Main define


Weight = learnSigmoid(trainImg, trainLabel);
Predict(testImg, Weight, testLabel);
