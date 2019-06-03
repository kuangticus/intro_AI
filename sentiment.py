import os
import sys
import math
import random
import re

def countPosReviews(training):
    count = 0
    
    for i in range(0, len(training)):
        #print( "int for loop" , i)
        #print("Count: ", training[i][-1])
        if training[i][-1] == 1:
            count = count + 1
    
    return count
    
def countNegReviews(training):
    count = 0
    for i in range(0, len(training)):
        if training[i][-1] == 0:
            count = count + 1
    
    return count

def conProbabilityPos(training, test, word, review):
    count = 0
    for i in range(0, len(training)):
        if(training[i][word] == test[review][word] and training[i][-1] == 1):
            count = count + 1
    
    return count + 1 

def conProbabilityNeg(training, test, word, review):
    count = 0
    for i in range(0, len(training)):
        if(training[i][word] == test[review][word] and training[i][-1] == 0):
            count = count + 1
    
    return count + 1   


def probCalculate(training, test, review):
    positiveReviews = countPosReviews(training)
    negativeReviews = countNegReviews(training)
    totalReviews = len(training)

    # print(positiveReviews)
    # print(negativeReviews)
    # print(totalReviews)
    
    posProb = math.log10(float(positiveReviews)/float(totalReviews))
    negProb = math.log10(float(negativeReviews)/float(totalReviews))
    
    conProbPos = 0
    conProbNeg = 0
    
    for i in range(0, len(test[0])-1):
        conProbPos = conProbPos + math.log10( float(conProbabilityPos(training, test, i, review))/float(positiveReviews + 2) )
        conProbNeg = conProbNeg + math.log10( float(conProbabilityNeg(training, test, i, review))/float(negativeReviews + 2) )

    posProb = posProb + conProbPos 
    negProb = negProb + conProbNeg

    if posProb > negProb:
        return 1
    elif negProb > posProb:
        return 0
    else:
        return random.randint(0,2)

def loopAll(training, test):
    prediction = 0
    count = 0
    for i in range(0, len(test)):
        prediction = probCalculate(training, test, i)
        if prediction == test[i][-1]:
            count = count + 1
    
    return count

    
if __name__ == '__main__':

    training = open("trainingSet.txt")

    wordBank = []
    table = {}

    for words in training:
        string = words.split('\t')
        wordList = string[0].split(' ')
        wordList.remove('')
        for i in wordList:
            word  = re.sub(r'[^\w\s]','',i)
            word = word.lower()
            if ( not(word in table) ):
                wordBank.append(word)
                table[word] = word;
        
    wordBank.sort()
    training.close()

    # for i in wordBank:
    #     print(i)

    ## featurize 

    trainingF = []
    testingF = [] 
     
    testing = open("testSet.txt")
    training = open("trainingSet.txt")

    for words in training:
        features = []
        string = words.split('\t')
        # print ( string )
        classLabel = string[-1]             # classLabel
        # print ( classLabel[1] )             ## we wan classLabel 1
        ## gotten class label

        wordList = string[0].split(' ')
        wordList.remove('')

        compare = {}
        for i in wordList:
            word = re.sub(r'[^\w\s]','',i)
            word = word.lower()
            compare[word] = word;
        
        for i in wordBank:
            if ( i in compare ):
                features.append(1)
            else:
                features.append(0)

        features.append(int(classLabel[1]))
        trainingF.append(features)

    # for i in wordBank:
    #     print(i, end='')
    #     print(", ", end='')
    
    # print()

    # for i in trainingF:
    #     print(*i, sep=", ")



    for words in testing:
        features = []
        string = words.split('\t')
        # print ( string )
        classLabel = string[-1]             # classLabel
        # print ( classLabel[1] )             ## we wan classLabel 1
        ## gotten class label

        wordList = string[0].split(' ')
        wordList.remove('')

        compare = {}
        for i in wordList:
            word = re.sub(r'[^\w\s]','',i)
            word = word.lower()
            compare[word] = word;
        
        for i in wordBank:
            if ( i in compare ):
                features.append(1)
            else:
                features.append(0)

        features.append(classLabel[1])
        testingF.append(features)

    # for i in wordBank:
    #     print(i, end='')
    #     print(" ,", end='')
    
    # print()

    # for i in testingF:
    #     print(*i, sep=", ")

    print("# correct: ", loopAll(trainingF, trainingF))


    
    
                



    
