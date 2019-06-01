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

using namespace std;

int positiveTot = 0, negativeTot = 0;

void parse (vector<string> *, int);
void featurize (vector<vector<int>> *, vector<string>, int);
void printer (vector<vector<int>> *, vector<string>, int);

// add the bayesian stuff here

int main (int argc, char** argv){ // maybe add a little of user input for file choosing

    // vectors for the test and training bank
    vector<string> wordbankTraining, wordbankTesting;
    vector<vector<int>> featuresTraining, featuresTesting;
    
    parse( &wordbankTraining, 0);
    // parse( &wordbankTesting, 1);
    featurize ( &featuresTraining, wordbankTraining, 0);

    // for ( int i = 0; i < wordbankTraining.size(); i++){
    //     cout << wordbankTraining[i] << endl;
    // }
    // return 0;
}

void parse(vector<string> *wordbank, int setting){
    ifstream infile1;
    vector<string> temp;
    unordered_map <string, string> uniqueWords;
    int store = 1;

    string holder, word;

    if ( setting == 0 )
        infile1.open("trainingSet.txt");
    else 
        infile1.open("testSet.txt");

    while ( infile1 >> holder ){

        if ( holder[0] == '0' || holder[0] == '1' ){
            store = 0;
        }

        else {
            for ( int i = 0; i < holder.length(); i++){
                if ( holder[i] != '\'' && holder[i] != '.' && holder[i] != ')' && holder[i] != '(' && holder[i] != '!' && holder[i] != '?' && holder[i] != '$' 
                     && holder[i] != ',' && holder[i] != '-' && holder[i] != ';' && holder[i] != ':' && holder[i] != '&' && holder[i] != '\"' && holder[i] != '*')
                {
                    word = word + holder[i];
                }    

                transform(word.begin(), word.end(), word.begin(), ::tolower);     
            }
            
            if (word != "" && (uniqueWords.find(word) == uniqueWords.end()) ) {
                wordbank->push_back(word);
                uniqueWords[word] = word; 
            }   
            word="";
        }
    }
    sort(wordbank->begin(), wordbank->end());
    infile1.close();
}

// 0 = training
// 1 = testing
void featurize ( vector<vector <int>> *features, vector<string> wordbank, int setting){
    ifstream infile1;
    string line, word;
    unordered_map <string, string> sentence;

    int wordBanklength = wordbank.size();
    
    if ( setting == 0 )
        infile1.open("trainingSet.txt");
    else 
        infile1.open("testSet.txt");
    
    getline(infile1, line);

        istringstream iss(line);
        while ( iss >> word ){
            for ( int i = 0; i < word.length(); i++){
                if ( word[i] != '\'' && word[i] != '.' && word[i] != ')' && word[i] != '(' && word[i] != '!' && word[i] != '?' && word[i] != '$' 
                     && word[i] != ',' && word[i] != '-' && word[i] != ';' && word[i] != ':' && word[i] != '&' && word[i] != '\"' && word[i] != '*')
                {
                    word = word + word[i];
                }
                transform(word.begin(), word.end(), word.begin(), ::tolower);     
            }

            if (word != "" && (sentence.find(word) == sentence.end()) ) {
                sentence[word] = word; 
            }
        }
        // cout << line << endl;
}
