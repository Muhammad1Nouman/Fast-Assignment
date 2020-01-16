from gensim.parsing.preprocessing import preprocess_documents
import gensim
with open("Question1.txt", "r", encoding='ISO-8859-1') as f:
     f_reader = f.readlines()
i = 0
lisOfLine = []
for k in f_reader:
    tokenList = preprocess_documents([k])
    lisOfLine.append(tokenList[0])
print("tokenization completed")
t = gensim.models.Word2Vec(lisOfLine,window=5, size=32,min_count = 1, workers = 20)


testingList = preprocess_documents(["Clean Unclean Amazed friendly"])

for word in testingList[0]:
    print('Similarity for word ',word )
    print(t.most_similar(word))
