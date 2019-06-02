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
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

using namespace std;

//global variables
double positiveTot = 0, negativeTot = 0;
double totalReviews = 0;

void parse (vector<string> *, int);
void featurize (vector<vector<int>> &, vector<string>, int);
vector<int> intialize(int);
void printer (vector<vector<int>> *, vector<string>, int);
double countReviews (const vector<vector<int>>, int, int);

double countConditional(const vector<vector<int>> , int , int , int , int );
double calculateProbPos(const vector<vector<int>> , const vector<int> , int );
double calculateProbNeg(const vector<vector<int>> , const vector<int> , int );
double predict(const vector<vector<int>> , const vector<vector<int>> , int );
// add the bayesian stuff here

int main (int argc, char** argv){ // maybe add a little of user input for file choosing

    srand (time(NULL));
    ofstream fileout1, fileout2;

    
    vector<string> wordBank; //vector that stores the vocabulary
    vector<vector<int>> featuresTraining, featuresTesting; //vector that stores the features of each review for training data and testing data respectively

    // fileout1.open("preprocessed_train.txt");
    // fileout2.open("preprocessed_test.txt");
    
    parse( &wordBank, 0); //parses and creates the vocabulary
    featurize ( featuresTraining, wordBank, 0);
    //featurize ( featuresTesting, wordBank, 2);

    totalReviews = featuresTraining.size(); //total number of reviews
    positiveTot = countReviews(featuresTraining, 1, wordBank.size()); //total number of positive reviews
    negativeTot = countReviews(featuresTraining, 0, wordBank.size()); //total number of negative reviews

    cout << "Total Reviews: " << totalReviews << endl;
    cout << "positive Reviews: " << positiveTot << endl;
    cout << "negative Reviews: " << negativeTot << endl;

    // cout << countConditional(featuresTraining, wordBank.size()-2, 0, 0, wordBank.size()) << endl;
    
    // for ( int i = 0; i < wordBank.size(); i++){
    //     fileout1 << wordBank[i] << ", ";
    // }
    // fileout1 << endl;
    // for(int j = 0; j < 5; j++){
    //     for ( int i = 0; i < wordBank.size(); i++){
    //         fileout1 << featuresTraining[j][i] << ", ";
    //     }
    // fileout1 << endl;
    // }

    // for ( int i = 0; i < wordBank.size(); i++){
    //     fileout1 << wordBank[i] << ", ";
    // }
    // fileout1 << endl;
    // for(int j = 0; j < 5; j++){
    //     for ( int i = 0; i < wordBank.size(); i++){
    //         fileout1 << featuresTesting[j][i] << ", ";
    //     }
    // fileout1 << endl;
    // }
    
    //fileout1 << endl;
    //fileout1 << 100*predict(featuresTraining, featuresTraining, wordBank.size()); << endl;
    
    //right now this is called on the training data
    predict(featuresTraining, featuresTraining, wordBank.size()); //predicts whether a review is positive or negative for all reviews in a dataset
    
    //fileout2 << endl;
    //fileout2 << 100*predict(featuresTraining, featrizedTesting, wordBank.size()); << endl;

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

    if ( setting == 0 ){  // setting for the training data
        infile1.open("trainingSet.txt"); 
    }
    else if (setting == 1){ // setting for the testining data for debugging
        infile1.open("testforFinal.txt");
    }
    else { // setting for the testing data for the program
        infile1.open("testSet.txt");
    }
    while ( getline(infile1, line, '\t') ){ // do get thing for parse
        getline(infile1,trash); // class label is trashed

        istringstream iss(line); // this will break apart the string via white space 
        while ( iss >> holder ){ 
            for ( int i=0; i < holder.length(); i++){  // this if statement gets rid of the punctunation
                if ( holder[i] != '\'' && holder[i] != '.' && holder[i] != ')' && holder[i] != '(' && holder[i] != '!' && holder[i] != '?' && holder[i] != '$' 
                     && holder[i] != ',' && holder[i] != '-' && holder[i] != ';' && holder[i] != ':' && holder[i] != '&' && holder[i] != '\"' && holder[i] != '*')
                {
                    word = word + holder[i];
                }
            }
            transform(word.begin(), word.end(), word.begin(), ::tolower); // lowercase words

            // throw the words in hash table to check for repeat of 2+ iterations
            if (word != "" && (uniqueWords.find(word) == uniqueWords.end()) ) {
                wordbank->push_back(word);
                uniqueWords[word] = word; 
            }
            word="";
        }
}
    // sorting the word bank into alphabetical order
    sort(wordbank->begin(), wordbank->end());
    wordbank->push_back("classlabel");
    infile1.close();
}

// 0 = training
// 2 = testing
void featurize ( vector<vector <int>> &features, vector<string> wordbank, int setting){
    ifstream infile1;
    string line, word = "";
    string classLabel;
    string holder;
    int sentenceNumber = 0;
    unordered_map <string, string> sentence;
    
    // the follow if states are option modes for the featurize function
    if ( setting == 0 )
        infile1.open("trainingSet.txt");
    else if (setting == 1)
        infile1.open("testforFinal.txt");
    else 
        infile1.open("testSet.txt");

    // using getline to grab a whole line from the file
    while( getline(infile1, line, '\t') ){
        getline(infile1, classLabel); // we will use the class label later

        features.push_back(initialize(wordbank.size())); // we are pushing back 0 int vectorcs ro init

        istringstream iss(line);
        while ( iss >> holder ){

            for ( int i=0; i < holder.length(); i++){  // these get rid of the punctuation in the words
                if ( holder[i] != '\'' && holder[i] != '.' && holder[i] != ')' && holder[i] != '(' && holder[i] != '!' && holder[i] != '?' && holder[i] != '$' 
                     && holder[i] != ',' && holder[i] != '-' && holder[i] != ';' && holder[i] != ':' && holder[i] != '&' && holder[i] != '\"' && holder[i] != '*')
                {
                    word = word + holder[i];
                }
            }
            transform(word.begin(), word.end(), word.begin(), ::tolower); // lowercase words

            // again we use a hash table to check for repeats
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
        // changing the features for the class labels and storing them to end of the featurize vector
        features[sentenceNumber][wordbank.size()-1] = atoi(classLabel.c_str()); // maybe this needs to be checked lated
        
        sentenceNumber++;
        sentence.clear(); // clear the hash table map
    }
}


//bayesian functions
double countReviews( const vector<vector<int>> features, int reviewType, int bankSize){ // counts the number of reviews for a certain type of review 
    int reviews = 0;                                                                    //counts the number of positive reviews or negative reviews based on reviewType (1 for positive, 0 for negative)
       
    for(int i = 0; i < features.size(); i++){
        if( features[i][bankSize - 1] == reviewType){
            reviews++;
        }
    }
    return reviews;
} // think it works

double countConditional(const vector<vector<int>> features, int word, int exists, int reviewType, int bankSize){ //counts the number of reviews with a specific value of a word and 
    int reviews = 0;                                                                                            //the specific value of the review (i.e. counts the number of reviews that contain the word 'file' 
                                                                                                                //and are positive)

    // runs through the featurized list and looks for the specific value of the word and reviewtype
    for(int i = 0; i < features.size(); i++){
        if((features[i][word] == exists) && (features[i][bankSize - 1] == reviewType)){
            reviews++;
        }
    }

    return reviews;
} // think it works

double calculateProbPos(const vector<vector<int>> training, const vector<int> test, int bankSize){ //find probability of classlabel being positive given the words in the review
    double prob = 0;
    double probConditional = 0;

    for(int i = 0; i < training.size(); i++){
        probConditional = probConditional + log10( (countConditional(training, i, test[i], 1, bankSize)+1)/(positiveTot+2) ); 
    }
    prob = log10(positiveTot/totalReviews) + probConditional;
    
    // cout<< "Positive: " << prob <<endl;
    return prob;
}

double calculateProbNeg(const vector<vector<int>> training, const vector<int> test, int bankSize){ //find probability of classlabel being negative given the words in the review
    double prob = 0;
    double probConditional = 0;

    // finding the dirichelet 
    for(int i = 0; i < training.size(); i++){
        probConditional = probConditional + log10( (countConditional(training, i, test[i], 0, bankSize)+1)/(negativeTot+2) );
    }
    prob = log10(negativeTot/totalReviews) + probConditional; // adding the summation of the dirichlet
    
    // cout<< "Negative: " << prob <<endl;
    return prob;
}

// this function will call the calculateProbNeg and calculateProbPos and then compare, and the we will compare then to the actual to get the running accuracy
double predict(const vector<vector<int>> training, const vector<vector<int>> test, int bankSize){
    int correct = 0;
    int prediction;
    double positive;
    double negative;
    
    cout << "Test size: " << test.size() << endl;
    for(int i = 0; i < test.size(); i++){
        // getting the probability for the negative review and positive review
        positive = calculateProbPos(training, test[i], bankSize);
        negative = calculateProbNeg(training, test[i], bankSize);
        // cout<< "Positive: " << positive <<endl;
        // cout<< "Negative: " << negative <<endl;
        if( positive > negative){  // is positive review
            prediction = 1;
        }
        else if(positive < negative){ // is negative review
            prediction = 0;
        }
        else if (positive == negative) { // this if only for when the positive and negative are ==
            prediction = rand() % 2;
        }

        //cout << "Prediction: " << prediction << endl;

        // if the prediction is correct we add it to a running total for accuracy uses later
        if(prediction == test[i][bankSize-1]){
            correct++;
        }
    }
    
    cout << correct << "/" << test.size() << endl;
    // returns accuracy in decimal form
    return double(correct) / double(test.size());
}