#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <boost/algorithm/string.hpp>

using namespace std;

void parse (vector<string> *, int);
void compare (vector<int> *);

// add the bayesian stuff here

int main (int argc, char**argv){ // maybe add a little of user input for file choosing

    // vectors for the test and training bank
    vector<string> wordbankTraining, wordbankTesting;
    vector<int> featuresTraining, featuresTesting;
    

    parse( &wordbankTraining, 0);
    parse( &wordbankTesting, 1);



    return 0;
}

void parse(vector<string> *wordbank, int setting){
    ifstream infile1;
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
                    word = word + holder[i];
            }
            if (word != "")
                wordbank->push_back(word);

            word="";
        } 
    }
    infile1.close();
}