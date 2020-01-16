import bs4
import sys
from nltk.stem import PorterStemmer 
from os import listdir
from nltk.tokenize import regexp_tokenize
import operator
from collections import Counter
 
                           ###Global Variables  ###

mypath= str(sys.argv[1]) #"E:\\University\\semester 7\\Information Reterival\\Assignment\\corpus\\corpus";
termIds  = {}
List_indext_tuple=[]
List_index_HashTable={}
document = []
docCount = 1
             ###-------------------END OF GLOBAL VARIABLES---------------------###
def getTermCount(indexT):
    TermCount=[ [lis[0],lis[1]] for lis in indexT]
    counter={}
  
    for p in TermCount:
        counter[p[0]]=0
    for p in TermCount:
        counter[p[0]]=counter[p[0]]+1;
    return counter
           ###-------------------------------------------------------###
def getNoDocumentContainWord(List_tuple):
    tcc=[[lis[0],lis[2]] for lis in List_indext_tuple]
    k={}
    for p in tcc:
        k[p[0]]=[]
    for p in tcc:
        k[p[0]].append(p[1])
        k[p[0]]=list(dict.fromkeys(k[p[0]]))
    
    DictionaryCount={}
    for p in k:
        c=list(k.get(p));
        d=len(c)
        DictionaryCount[p]=d
    return DictionaryCount    
 ###--------------------------------------------------####
 
def getHtmlText(contents):
    contents2=bs4.BeautifulSoup(contents,'html.parser').find('html')
    
    if contents2  is not None:
        for script in contents2(["script", "style"]):
            script.extract()   
        text = contents2.get_text()
        st = text.lower();
        token = regexp_tokenize(st, "\w+(?:'\w+)?|[^\w\s]")
        return token;
    return None

            ###-------------------------------------------------------###
            
def getStemWords(tokens):
    ps = PorterStemmer()                # for steming
    stemWords= []
    for w in tokens: 
        stemWords.append(ps.stem(w))
    return stemWords
          ###-------------------------------------------------------###
                                       
def applyStopWordList(stopWords,Token):
    for sW in stopWords[:]:
        sW=sW.strip();      # To remove /n symbol
        Token=[element for element in Token if element != sW]
    return Token;

        ###-------------------------------------------------------###

def writeHashMapInFileWithDeltaEncoding(HashMap,countsIneCorpus,countNoDocument):
    f_CreateInvertedHashIndex=open("invertedIndexHash.txt","+w",encoding="utf8")
    for indexValue in HashMap:
        lis=list(HashMap[indexValue])
        lis.pop(1)
        lis.insert(1,countsInEntireCorpus[lis[0]])
        lis.insert(2,countNoDocument[lis[0]])
        f_CreateInvertedHashIndex.write(str(lis[0])+" "+str(lis[1])+" "+str(lis[2]))
        indexCounter=0
       
        f_CreateInvertedHashIndex.write(" "+str(int(lis[3][0]))+","+str(int(lis[3][1])))
        prvDocId=int(lis[3][0])
        prvPosId=int(lis[3][1])
        
        for everyElement in lis:
            if indexCounter > 3:
               if prvDocId == int(everyElement[0]):
                     f_CreateInvertedHashIndex.write(" "+str(int(everyElement[0]-prvDocId))+","+str(int(everyElement[1]-prvPosId)))
               else:
                     f_CreateInvertedHashIndex.write(" "+str(int(everyElement[0]))+","+str(int(everyElement[1])))
               prvDocId=everyElement[0]
               prvPosId=everyElement[1]
            indexCounter=indexCounter+1
      
        f_CreateInvertedHashIndex.write('\n')
        
    f_CreateInvertedHashIndex.close();     
       ###-------------------------------------------------------###
       
def writeSortInvertdIndexInFileWithDeltaEncoding(List_index,countsEntireCorpus,countNoDocument):
        
    f_CreateIndex = open("invertedIndex.txt","+w",encoding="utf8")
    currId=int(List_index[0][0])
    prvId=int(List_index[0][0])
    
    stTple=List_index[0]
    lis=list(stTple)
    lis.pop(1)
    lis.insert(1,countsEntireCorpus[stTple[0]])
    lis.insert(2,countNoDocumentInWhichWordPresent[lis[0]])
        
    f_CreateIndex.write(str(str(lis[0]) + " " + str(lis[1])+" "+str(lis[2])+" "+str(lis[3])+","+str(lis[4]) ))
    
    
    check=1;
    prvDocId=int(str(lis[3]))
    prvPosId=int((lis[4]))
    
    for indexValue in List_index:
        
         if check!=1:
            lis=list(indexValue)
            currId=int(indexValue[0])
            lis.pop(1)
            lis.insert(1,countsEntireCorpus[lis[0]])
            lis.insert(2,countNoDocumentInWhichWordPresent[lis[0]])
            if currId==prvId:
             
                if prvDocId==int(lis[3]):    
                   f_CreateIndex.write(str(" "+str(int(int(lis[3])-prvDocId))+","+str(int(int(lis[4])-prvPosId)) ))
                else:
                    f_CreateIndex.write(str(" "+str(int(int(lis[3])))+","+str(int(int(lis[4]))) ))
               
            else:
                f_CreateIndex.write('\n')
                f_CreateIndex.write(str(str(lis[0]) + " " + str(lis[1])+" "+str(lis[2])+" "+str(lis[3])+","+str(lis[4]) ))
            prvId=int(indexValue[0])
            prvDocId=int(lis[3])
            prvPosId=int(lis[4])
         check=0      
    f_CreateIndex.close();   

        ###-----------------------------------------------------------------####
def writingTermsInFile(terms):
    termFile = open("termids.txt","+w",encoding="utf8")
    termCount=0
    for term in terms:
        termCount=termCount+1;
        termFile.write( str(termCount) + "\t" + term+"\n");
    termFile.close();
                ###--------------------------------------------####    

                                 ###MAIN###

#f_StopList=open("E:\\University\\semester 7\\Information Reterival\\Assignment\\stoplist.txt")
f_StopList=open(mypath+"\\"+"stoplist.txt")

stop_list= f_StopList.readlines()
f_StopList.close();

wordInDic=1;
docFile = open("docids.txt","+w",encoding="utf8")

for file in listdir(mypath):
    
    print("Processing current doc "+str(docCount)+"\t" + file +"\n" ); 
   
    docFile.write(str(docCount)+"\t"+file+"\n");              
    f= open(mypath+'\\'+file,encoding="latin-1")
    contents =f.read()    
        
    text=getHtmlText(contents)                                        
    
    if text != None: 
        Word=getStemWords(text)                                      
        f.close();                                                   
        afterRemove=applyStopWordList(stop_list,Word);               
        wordCounter=0 
        
        countWord=Counter(afterRemove)
        
        for eachWord in afterRemove:
            wordCounter=wordCounter+1
            if eachWord not in termIds:
               termIds[eachWord]=wordInDic
               wordInDic=wordInDic+1
               List_index_HashTable[eachWord]=[termIds[eachWord],countWord[eachWord],[docCount,wordCounter]]
            else:
                List_index_HashTable[eachWord].append([docCount,wordCounter])
               
            tp=( termIds[eachWord],countWord[eachWord],docCount,wordCounter)
            List_indext_tuple.append(tp)
    docCount= docCount+1
       
docFile.close();

termCount=0

print("Now writing termids...");

countsInEntireCorpus=getTermCount(List_indext_tuple)
countNoDocumentInWhichWordPresent=getNoDocumentContainWord(List_indext_tuple)

writingTermsInFile(termIds)


print('Start sorting...'+'\n')
List_indext_tuple.sort(key = operator.itemgetter(0))
print('Sorting completed...'+'\n')

print('Writing in sorting based inverted index file with delta encoding'+'\n');
writeSortInvertdIndexInFileWithDeltaEncoding(List_indext_tuple,countsInEntireCorpus,countNoDocumentInWhichWordPresent)


print('Now Writing in Hash based inverted index file with delta encoding'+'\n');
writeHashMapInFileWithDeltaEncoding(List_index_HashTable,countsInEntireCorpus,countNoDocumentInWhichWordPresent)

print('Done...')

