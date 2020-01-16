import sys

def readTermIDs():
    termFile = open("termids.txt","r",encoding="utf8")
    dictionary = {}
    for line in termFile:
        termid, word = line.split('\t')
        wordWithnextLine=word.split('\n');
        dictionary[wordWithnextLine[0]] = int(termid)
        
    return dictionary

def readInvertedIndex():
    termFile = open("invertedIndex.txt","r",encoding="utf8")
    dictionary = {}
    word=[]
    for line in termFile:
        word = line.split('\n');
        singleWord = word[0].split(' ');
        dictionary[int(singleWord[0])]=word[0]
    return dictionary

                            ##Main##
                            
termIds=readTermIDs()
invertedIndex=readInvertedIndex()
getWord= str(sys.argv[1]);
print('Word: '+getWord);
print('Listing for term:'+ str(getWord))
if getWord not in termIds:
   print('No record found');
else:
    termid=termIds[getWord]
    print('TERMID:' + str(termid))
    frequency=invertedIndex[termid].split(' ');
    print('Number of documents containing term:' + str(frequency[2]))
    print('Word frequency in entire corpus:' + str(frequency[1]))


