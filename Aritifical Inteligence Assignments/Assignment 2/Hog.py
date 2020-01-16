from mlxtend.data import loadlocal_mnist
from sklearn.metrics import accuracy_score
from sklearn.svm import LinearSVC
from skimage.feature import hog
import numpy as np



trainImg, trainLabel = loadlocal_mnist('C:\\Users\\Muhammad Nouman\\.spyder-py3\\train-images.idx3-ubyte', 'C:\\Users\\Muhammad Nouman\\.spyder-py3\\train-labels.idx1-ubyte');

testImg, testLabel = loadlocal_mnist('C:\\Users\\Muhammad Nouman\\.spyder-py3\\t10k-images.idx3-ubyte', 'C:\\Users\\Muhammad Nouman\\.spyder-py3\\t10k-labels.idx1-ubyte');

trainImg = trainImg[1:1001, :];
trainLabel = trainLabel[1:1001];

testImg = testImg[1:101, :];
testLabel = testLabel[1:101];

testImg = testImg / 255;

trainImg = trainImg / 255;


def hogFeature(images):
    list_hog_fd = [hog(t.reshape((28, 28)), orientations=9, pixels_per_cell=(14, 14), cells_per_block=(1, 1),
                       visualise=False) for t in images]

    return np.array(list_hog_fd, dtype=np.float64)


def Experiments(train_images, train_labels, test_images, test_labels):

    train_hog_features = hogFeature(train_images)
    clf = LinearSVC()
    clf.fit(train_hog_features, train_labels)
    print("Training Completed!")

    test_hog_features = hogFeature(test_images)
    predicted_labels = clf.predict(test_hog_features)

    accuracy = accuracy_score(test_labels, predicted_labels) * 100

    print("Accuracy: %f" % accuracy, "%")
Experiments(trainImg, trainLabel, testImg, testLabel);