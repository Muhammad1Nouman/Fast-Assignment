import xml.etree.ElementTree as ET
from nltk.stem import PorterStemmer 
import ast
from collections import Counter
import math
import operator

class DocDetail:
      documentLengths = {}
      documentAvg = None
      def __init__(self, file_path):
          with open(file_path, "r") as data:
               self.documentLengths = ast.literal_eval(data.read())
               self.documentAvg = self.documentLengths[0]

class IndexDetail:
      term_id = None
      document_freqency = None
      term_frequency = None
      documentList = []
      positionList = []
      
      def __init__(self, list_doc):
          if list_doc == None:
              print ('Invalid document list found')
          else:
               doc_split = list_doc.rstrip().split(' ')
               self.term_id = int(doc_split[0])
               self.term_frequency = int(doc_split[1])
               self.document_freqency = int(doc_split[2])
               iter_doc = iter(doc_split)
               old_doc = 0
               old_pos = 0
               count = -1
               for word in iter_doc:
                   count = count + 1
                   if count > 2:
                       doc_post = word.split(',')
                       new_doc = int(doc_post[0]) + old_doc
                       new_pos = int(doc_post[1]) + old_pos
                       self.documentList.append(new_doc)
                       self.positionList.append(new_pos)
                       old_doc = new_doc
                       old_pos = new_pos
        
                       

class Dirichletsmoothing:
      corpusLength = None
      index_data = None  #Index detail
      doc_detail = None  
      term_frequency_doc = None # contain frequency of term in every doc
      
      def __init__(self, index_data, docdetail):
           self.term_frequency_doc = Counter(index_data.documentList)  #Contain document frquency
           self.corpusLength = sum(self.term_frequency_doc .values())    #Finding courpus length
           self.doc_detail = docdetail
           self.index_data = index_data
           
           
      def computeSmoothingScore(self):
          doc_rank = {}
          for keys in  self.term_frequency_doc:
              lamda1, lamda2 = self.computeLamda(self.doc_detail.documentLengths[int(keys)])
              probaility_of_query =  self.term_frequency_doc[keys]/self.doc_detail.documentLengths[int(keys)] 
              probaility_of_corpus = self.index_data.term_frequency/self.corpusLength
              doc_rank[keys] = probaility_of_query + probaility_of_corpus
          return doc_rank  

          
        
      def computeLamda(self,docL):
          lamda1 = docL/(docL + self.doc_detail.documentAvg)
          return lamda1, (1.0-lamda1)
           
          

class BM25:
      k1 = None
      k2 = None
      b = None
      D = None
      docF = None
      docLen = None
      
      def __init__(self, k1, k2, b, D, docF, docLen):
          self.k1 = k1
          self.k2 = k2
          self.b = b
          self.D = D
          self.docF = docF
          self.docLen = docLen
     
          
      def calcualteScor(self, queryCount):
          docFrequecy = Counter(self.docF.documentList)  #Contain document frquency for each term
          doc_rank = {}
          for keys in docFrequecy:
              log_s = math.log(((3495 + 0.5)/( self.docF.document_freqency + 0.5)),2)
              K = self.calculateKValue(self.docLen.documentLengths[int(keys)], self.docLen.documentLengths[0]) #0 Mean Average
              term2 = ((1.0 + self.k1)*float(docFrequecy[keys])) / (K+float(docFrequecy[keys]))
              term3 = (1 + self.k2)/ (self.k2+1)
              doc_rank[keys] = float(log_s) *float( term2) * float(term3 )
          return doc_rank 
          

      def calculateKValue(self,docLength,avgLength):
          return float(self.k1)*((1.0-float(self.b))+float(self.b)*(float(docLength)/float(avgLength)))
      
      

def getStemWords(tokens):
    ps = PorterStemmer()                
    stemWords= []
    for w in tokens: 
        stemWords.append(ps.stem(w))
    return stemWords
     

                                       
def applyStopWordList(stopWords,Token):
    for sW in stopWords[:]:
        sW=sW.strip();      # To remove /n symbol
        Token=[element for element in Token if element != sW]
    return Token;


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
    
def readDocumentId():
    termFile = open("docids.txt","r",encoding="utf8")
    dictionary = {}
    word=[]
    for line in termFile:
        word = line.split('\n');
        singleWord = word[0].split('\t');
        dictionary[int(singleWord[0])]=singleWord[1]
    return dictionary


tree = ET.parse("topics.xml")
f_StopList=open("stoplist.txt")
termIds = readTermIDs()
invertedIndex = readInvertedIndex()
documentIds = readDocumentId()
docLenDic = DocDetail("docLength.txt")



stop_list= f_StopList.readlines()
root = tree.getroot()
listOfTestQuery = {}

for child in root:
    x = root.find("./topic[@number=\""+child.attrib['number']+"\"]/")
    wordList = x.text.lower().rstrip().split(' ')
    listOfTestQuery[child.attrib['number']] = applyStopWordList(stop_list,getStemWords(wordList))
    


f_Diric=open("DiricheltAlgorithm.txt","+w",encoding="utf8")
for p in listOfTestQuery:
    termlist =listOfTestQuery[p]
    print ('Proccseing query', p)
    score = {}
    
    for term in termlist:
        tremid = termIds[term]
        test = IndexDetail(invertedIndex[tremid])
      
        dirismo = Dirichletsmoothing(test, docLenDic)
        dirscore = dirismo.computeSmoothingScore()
        for rank in dirscore:
            if rank not in score:
                score[rank] = dirscore[rank]
            else:
                 score[rank] = score[rank] * dirscore[rank]
    sorted_x = sorted(score.items(), key=operator.itemgetter(1), reverse=True)
    counter = 1
    
    for docid,score in sorted_x:
        f_Diric.write(str(p) + ' ' +str(documentIds[docid]) + ' ' + str(counter) + ' '+ str(score) + "\n")
        counter = counter + 1 


f_BM25=open("BM25.txt","+w",encoding="utf8")
for p in listOfTestQuery:
    termlist =listOfTestQuery[p]
    print ('Proccseing query', p)
    score = {}
    for term in termlist:
        tremid = termIds[term]
        test = IndexDetail(invertedIndex[tremid])
        bm = BM25(1.2, 400, 0.75, 3495, test, docLenDic)
        bmScore = bm.calcualteScor(1)
        for rank in bmScore:
            if rank not in score:
                score[rank] = bmScore[rank]
            else:
                 score[rank] = score[rank] + bmScore[rank]
    sorted_x = sorted(score.items(), key=operator.itemgetter(1), reverse=True)
    counter = 1
    
    for docid,score in sorted_x:
        f_BM25.write(str(p) + ' ' +str(documentIds[docid]) + ' ' + str(counter) + ' '+ str(score)  + "\n")
        counter = counter + 1 

