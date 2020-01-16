import pandas as pd
from sklearn.feature_extraction.text import CountVectorizer, TfidfVectorizer, TfidfTransformer
from sklearn.model_selection import train_test_split
from sklearn.naive_bayes import MultinomialNB


data = pd.read_csv("Question2 Dataset.tsv",delimiter='\t') 
index = 0

for i, row in enumerate(data.values):
    z, x, y = row
    text = y.replace('<br />','')
    text = text.replace('/','')
    text = text.replace('\\','')
    text = text.replace('<br','')
    text = text.replace('/>','')
    data.at[index,'review'] = text
    index = index + 1

X_train, Y_train, X_test, Y_test = train_test_split(data['review'], data['sentiment'])

count_vect = CountVectorizer()
X_train_counts = count_vect.fit_transform(X_train)
tfidf_transformer = TfidfTransformer()
X_train_tfidf = tfidf_transformer.fit_transform(X_train_counts)

clf = MultinomialNB().fit(X_train_tfidf, X_test)

clf2 = MultinomialNB().fit(X_train_counts, X_test)

Y_train = Y_train.values.tolist()
Y_test = Y_test.values.tolist()

index = 0
count = 0
count2 = 0

while (index < len(Y_train)):
       res = clf.predict(count_vect.transform(([Y_train[index]])))
       res1 = clf2.predict(count_vect.transform(([Y_train[index]])))
       if str(res[0]) == str(Y_test[index]):
          count = count + 1
       if str(res1[0]) == str(Y_test[index]):
          count2 = count2 + 1
       index = index + 1
print("Accuracy for TFID Model:", (count/ len(Y_test))*100)
print("Accuracy for Raw Count Model:", (count2/ len(Y_test))*100)


       
