#Group: members
#Chetan Dindukurthi
#WeiHao Kuang

import os
import sys
import math
import random
import re

## counts the positive reviews in the a given features list of list
## takes in list[[]] training
def countPosReviews(training):
    count = 0
    for i in range(0, len(training)):
        if training[i][-1] == 1:        ## simply will run through the training to find all pos. classlabels
            count = count + 1
    
    return count                        ## returns the # of pos. classlabels

## counts the negative reviews in the a given features list of list
## takes in list[[]] training
def countNegReviews(training):
    count = 0
    for i in range(0, len(training)):   
        if training[i][-1] == 0:       ## simpley will through the training to find all neg. classlabels
            count = count + 1
    
    return count                        ## returns the # of neg. classlabels

## takes the training and then calculates how many reviews have the given review type positive 
def conProbabilityPos(training, test, word, review):
    count = 0
    for i in range(0, len(training)):
        if(training[i][word] == test[review][word] and training[i][-1] == 1):   ## runs through and check for all of the 
            count = count + 1                                                   ## positive reviews for given word
    
    return count + 1        ## returns the dirichlet priors numerator (+1)

## takes the training and then calculates how many reviews have the given review type negative
def conProbabilityNeg(training, test, word, review):
    count = 0
    for i in range(0, len(training)):
        if(training[i][word] == test[review][word] and training[i][-1] == 0):  ## runes through and checks for all of the
            count = count + 1                                                  ## negative reviews for given word
    
    return count + 1   ## returns the dirichlet priors numerator (+1)


def probCalculate(training, test, review):
    positiveReviews = countPosReviews(training) ## getting the numerator postive reviews
    negativeReviews = countNegReviews(training) ## getting the numerator negative reviews
    totalReviews = len(training)                ## getting the denomintor without +Nj
    
    posProb = math.log10(float(positiveReviews)/float(totalReviews))    ## this is the firs part of the log where we get the prob of positive review
    negProb = math.log10(float(negativeReviews)/float(totalReviews))    ## this is the first part of the log where we get the prob of the negative review
    
    conProbPos = 0
    conProbNeg = 0
    
    ## the following for loop is the summation of all the logs for a review given a reviw type
    ## we are using logs since the probabilities are so small
    for i in range(0, len(test[0])-1):
        conProbPos = conProbPos + math.log10( float(conProbabilityPos(training, test, i, review))/float(positiveReviews + 2) )  ## this is for postive reviews
        conProbNeg = conProbNeg + math.log10( float(conProbabilityNeg(training, test, i, review))/float(negativeReviews + 2) )  ## this if for negative reviews

    posProb = posProb + conProbPos  ## here we simply add the firs term with the summation fo the logs for positive
    negProb = negProb + conProbNeg  ## here we simple add the first term with the summation of the logs for negative

    if posProb > negProb:           ## if the probabily of positive is greater return 1
        return 1
    elif negProb > posProb:         ## if the probability of negative is greater return 0
        return 0
    else:
        return random.randint(0,2)  ## if the probilites are equal randomly choose 0 or 1

def loopAll(training, test):
    prediction = 0
    count = 0
    for i in range(0, len(test)):                       # this will run through the len of passed in feature list list 
        prediction = probCalculate(training, test, i)   # we will call the probcal to get the predicted prob 
        if prediction == test[i][-1]:                   # comparing the predicted to the actual so that 
            count = count + 1                           # increment that total correct
    
    return count


if __name__ == '__main__':

    training = open("trainingSet.txt")

    wordBank = []
    table = {}

    for words in training:                  ## ruuning through the training.txt
        string = words.split('\t')          ## spliting off the tab and the words
        wordList = string[0].split(' ')     ## splitting off by the space
        wordList.remove('')                 ## removing the empty strings
        for i in wordList:                  ## running through word to check for words
            word  = re.sub(r'[^\w\s]','',i) ## removing all the unicode punctuation from the words
            if ( word == '' ):              ## removing al the empty strings after punctuation manipulations
                continue
            else:                   
                word = word.lower()         ## then we change each word to lower case
                if ( not(word in table) ):  ## checking to see if the word exists in the dictionary table
                    wordBank.append(word)   ## if the word in not in the dictionary add the word to wordBank
                    table[word] = word     ## also update the dictionary with the word used to check for repeats
        
    wordBank.sort()                         ## sorting the wordBank in alphabetical order
    training.close()                        ## closing the file that wer are reading from

    ## featurize 

    trainingF = []                          
    testingF = [] 
     
    testing = open("testSet.txt")           ## opening the testset.txt for featurization
    training = open("trainingSet.txt")      ## opening the training.txt again for featuriztion

    for words in training:                  ## run through the lines in trainingtxt
        features = []                       ## making an empty list for storing review features
        string = words.split('\t')          ## splitin the string by tab again
        classLabel = string[-1]             ## classLabel extraction from the review 
        wordList = string[0].split(' ')     ## spliting the string by spaces
        wordList.remove('')                 ## removing all the empty strings

        compare = {}                        ## making a dictionary for comparison wordBank against review
        for i in wordList:
            
            word = re.sub(r'[^\w\s]','',i)  ## stripping punctuation from the words
            if ( word == '' ):              ## removing empty strings
                continue
            else:
                word = word.lower()         ## changing them to lower case
                compare[word] = word        ## adding the word in compare dictionary
        
        for i in wordBank:                  ## comparing the wordBank against the review dictionary
            if ( i in compare ):
                features.append(1)          ## if the word exists in the review append 1 to features list
            else:   
                features.append(0)          ## if the word does not exists in review append to features list 0

        features.append(int(classLabel[1])) ## at the very end of the features list append the classlabel from earlier    
        trainingF.append(features)          ## append each featurized review into the featurized review bank

    training.close()


    ## the code below is outputting the preprocessed training information into files
    f = open("preprocessed_train.txt", "w")
    for i in wordBank:                      ## outputting all the words in the bank
        print(i, file=f, end='')            ## 
        print(', ', file=f, end='')
    print("... ,classlabel", file=f)        ## adding the field classlabel at the end

    for i in trainingF:                     ## outputting the all the features
        for x in range(0,(len(i)-1)):       
            print(i[x], file=f, end='')
            print(", ", file=f, end='')
        print("...,", i[-1], file=f )
    f.close()                               

    ## end of outputting to files

    for words in testing:                   ## going through all lines in the tesing
        features = []                       ## empty list for later user from featurization
        string = words.split('\t')          ## split by tabs
        classLabel = string[-1]             # classLabel extraction
        wordList = string[0].split(' ')     ## split the remaining by space
        wordList.remove('')                 ## remove all empty strings

        compare = {}                        ## used for later comparison
        for i in wordList:
            word = re.sub(r'[^\w\s]','',i)  ## removing all punctuation from word
            if ( word == '' ):              ## ignoreing empty strings
                continue
            else:
                word = word.lower()         ## lower case words
                compare[word] = word        ## add to compare dictionary
        
        for i in wordBank:
            if ( i in compare ):            ## if the word exits in review append one to features list
                features.append(1)
            else:
                features.append(0)          ## if the word DNE in review append zero to features list

        features.append(int(classLabel[1])) ## append the classlabel to the features list
        testingF.append(features)

    testing.close()


    ## printing out to the file called preprocessed_test.txt
    f1 = open("preprocessed_test.txt", "w")
    for i in wordBank:                      ## printing all of the words in the wordBank
        print(i, file=f1, end='') 
        print(', ', file=f1, end='')
    print("... ,classlabel", file=f1)

    for i in testingF:
        for x in range(0,(len(i)-1)):       ## printing all of the features 
            print(i[x], file=f1, end='')
            print(", ", file=f1, end='')
        print("...,", i[-1], file=f1 )
    f1.close()
    

    f2 = open("results.txt", "w")
    ## following function calcualate using bayes net, and the we output the accuracies here as well
    correct = loopAll(trainingF, trainingF)             ## calling the loopAll for prob calculation
    print("Training # correct: ", correct, "/", len(trainingF), file=f2)
    print("Percent Accuracy: ", 100* (float(correct)/float(len(trainingF))), file=f2)

    print("Training # correct: ", correct, "/", len(trainingF))
    print("Percent Accuracy: ", 100* (float(correct)/float(len(trainingF))))




    correct = loopAll(trainingF, testingF)
    print("Testing # correct: ", correct, "/", len(testingF), file=f2)   ## calling the loopAll for prob calculation
    print("Percent Accuracy: ", 100*(float(correct)/float(len(testingF))), file=f2)

    print("Testing # correct: ", correct, "/", len(testingF))   ## calling the loopAll for prob calculation
    print("Percent Accuracy: ", 100*(float(correct)/float(len(testingF))))

    print("Results have been written in results.txt")