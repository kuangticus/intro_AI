#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <unordered_map>
#include <cmath>
#include <climits>
#include <sstream>
#include <cstdlib>

using namespace std;

int positiveTot = 0, negativeTot = 0;
int totalReviews = 0;

void parse (vector<string> *, int);
void featurize (vector<vector<int>> &, vector<string>, int);
vector<int> intialize(int);
void printer (vector<vector<int>> *, vector<string>, int);
int countReviews (const vector<vector<int>>, int, int);

// add the bayesian stuff here

int main (int argc, char** argv){ // maybe add a little of user input for file choosing

    // vectors for the test and training bank
    vector<string> wordBank;
    vector<vector<int>> featuresTraining, featuresTesting;
    
    parse( &wordBank, 0);
    featurize ( featuresTraining, wordBank, 0);

    totalReviews = featuresTraining.size();
    positiveTot = countReviews(featuresTraining, 1, wordBank.size());
    negativeTot = countReviews(featuresTraining, 0, wordBank.size() );


    // for ( int i = 0; i < wordBank.size(); i++){
    //     cout << wordBank[i] << ", ";
    // }
    // cout << endl;

    // for ( int i = 0; i < wordBank.size(); i++){
    //     cout << featuresTraining[0][i] << ", ";
    // }
    // cout << endl;

    return 0;
}

vector<int> initialize ( int size ){
    vector<int> tempVector;

    for(int i = 0; i < size; i++){
        tempVector.push_back(0);
    }

    return tempVector;
}

void parse(vector<string> *wordbank, int setting){
    ifstream infile1;
    string line, trash;
    string holder, word;
    vector<string> temp;
    unordered_map <string, string> uniqueWords;
    int store = 1;

    if ( setting == 0 )
        infile1.open("trainingSet.txt");
    else 
        infile1.open("testSet.txt");

    while ( getline(infile1, line, '\t') ){ // do get thing for parse
        getline(infile1,trash); // class label is trashed

        istringstream iss(line);
        while ( iss >> holder ){
            for ( int i=0; i < holder.length(); i++){
                if ( holder[i] != '\'' && holder[i] != '.' && holder[i] != ')' && holder[i] != '(' && holder[i] != '!' && holder[i] != '?' && holder[i] != '$' 
                     && holder[i] != ',' && holder[i] != '-' && holder[i] != ';' && holder[i] != ':' && holder[i] != '&' && holder[i] != '\"' && holder[i] != '*')
                {
                    word = word + holder[i];
                }
            }
            transform(word.begin(), word.end(), word.begin(), ::tolower); // lowercase words

            if (word != "" && (uniqueWords.find(word) == uniqueWords.end()) ) {
                wordbank->push_back(word);
                uniqueWords[word] = word; 
            }
            word="";
        }
}
    sort(wordbank->begin(), wordbank->end());
    wordbank->push_back("classlabel");
    infile1.close();
}

// 0 = training
// 1 = testing
void featurize ( vector<vector <int>> &features, vector<string> wordbank, int setting){
    ifstream infile1;
    string line, word = "";
    string classLabel;
    string holder;
    int sentenceNumber = 0;
    unordered_map <string, string> sentence;
    
    if ( setting == 0 )
        infile1.open("trainingSet.txt");
    else 
        infile1.open("testSet.txt");

    while( getline(infile1, line, '\t') ){
        getline(infile1, classLabel);

        features.push_back(initialize(wordbank.size()));

        istringstream iss(line);
        while ( iss >> holder ){

            for ( int i=0; i < holder.length(); i++){
                if ( holder[i] != '\'' && holder[i] != '.' && holder[i] != ')' && holder[i] != '(' && holder[i] != '!' && holder[i] != '?' && holder[i] != '$' 
                     && holder[i] != ',' && holder[i] != '-' && holder[i] != ';' && holder[i] != ':' && holder[i] != '&' && holder[i] != '\"' && holder[i] != '*')
                {
                    word = word + holder[i];
                }
            }
            transform(word.begin(), word.end(), word.begin(), ::tolower); // lowercase words

            if (word != "" && (sentence.find(word) == sentence.end()) ) {
                sentence[word] = word; 
            }
            word="";
        }   

        for(int i = 0; i < wordbank.size()-1; i++){
            if ( sentence.find(wordbank[i]) != sentence.end()  ){
                features[sentenceNumber][i] = 1; 
            }
        }
        features[sentenceNumber][wordbank.size()-1] = atoi(classLabel.c_str()); // maybe this needs to be checked lated
        
        sentenceNumber++;
        sentence.clear();
    }
}

int countReviews( const vector<vector<int>> features, int reviewType, int bankSize){
    int reviews = 0;
    
    for(int i = 0; i < features.size(); i++){
        if( features[i][bankSize - 1] == reviewType){
            reviews++;
        }
    }
    return reviews;
}

int countConditional(const vector<vector<int>> features, int word, int exists, int reviewType, int bankSize){
    int reviews = 0;

    for(int i = 0; i < features.size(); i++){
        if((features[i][word] == exists) && (features[i][bankSize - 1] == reviewType)){
            reviews++;
        }
    }
    return reviews;
}

float calculateProbPos(const vector<vector<int>> training, const vector<int> test, int bankSize){
    float prob = 0;
    float probConditional = 0;

    for(int i = 0; i < training.size(); i++){
        probConditional = probConditional + log( (countConditional(training, i, test[i], 1, bankSize)+1)/(positiveTot+2) );
    }
    prob = log(positiveTot/totalReviews) + probConditional;
    return prob;
}

float calculateProbNeg(const vector<vector<int>> training, const vector<int> test, int bankSize){
    float prob = 0;
    float probConditional = 0;

    for(int i = 0; i < training.size(); i++){
        probConditional = probConditional + log( (countConditional(training, i, test[i], 0, bankSize)+1)/(negativeTot+2) );
    }
    prob = log(negativeTot/totalReviews) + probConditional;
    return prob;
}