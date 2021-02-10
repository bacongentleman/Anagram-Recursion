#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <cassert>

using namespace std;

const int MAXDICTWORDS=30000;
const int MAXRESULTS=30;
int permuteRecur(string word, const string dict[], int size, string results[]);
int loadDictionary(istream &dictfile, string dict[]);
void Perm(string prefix, string rest, const string dict[], const int &size, int &tally, string results[]);
void printRecur(const string results[], int size);
void loopPerm (int start, int end, string prefix, string rest, const string dict[], const int &size, int &tally, string results[]);
void loopPerm_2 (int start, int end, string &prefix, string &rest, const string dict[], const int &size, int &tally, string results[]);
void loopRemoveDups1(int start, int end, string results[]);
void loopRemoveDups2(const int initial, const int ending, string results[]);


int main(){
    ifstream infile("words.txt");
    if(!infile)
        cerr<<"file not opened properly"<<endl;
    
    string dictionary[MAXDICTWORDS]{};
    string permResults[MAXRESULTS]{};
    int numWords = loadDictionary(infile, dictionary);
    assert(dictionary[0]=="10th");
    string word;
    string permArr[1000]{};
    string results[30]{};
    
    cout << "Please enter a word for your anagram: ";
    cin >> word;
    
    int numMatches = permuteRecur(word, dictionary, numWords, results);
    
    if(numMatches==0)
        cout << "No matches found" << endl;
    else{
    loopRemoveDups1(0, MAXRESULTS-1, results);
    printRecur(results, numMatches);
    }
    
}



int loadDictionary(istream &dictfile, string dict[]){
    if(!(getline(dictfile,dict[0])))
        return 0;
    return 1 + (loadDictionary(dictfile, dict+1));
}

int permuteRecur(string word, const string dict[], int size, string results[])
{
    int resultCount{};
    Perm("", word, dict, size, resultCount, results);
    return resultCount;
}



void Perm(string prefix, string rest, const string dict[], const int &size, int &tally, string results[]) {
    if (rest == "") {
        loopPerm(0, size, prefix, rest, dict, size, tally, results);
    }
    else{
        loopPerm_2(0, rest.size(), prefix, rest, dict, size, tally, results);
        }
    }


void printRecur(const string results[], int size){
    if(size==0)
        return;
    cout << results[size-1] << endl;
    printRecur(results, size-1);
}

void loopPerm (int start, int end, string prefix, string rest, const string dict[], const int &size, int &tally, string results[]){ // function checks if permutation is equal to a dictionary word, if so it places it in the results array and increments to next position
    if(start>=end)
        return;
    if(prefix==dict[start]){
        results[tally]=prefix;
        tally+=1;
    }
    loopPerm(start+1, end, prefix, rest, dict, size, tally, results);
}

void loopPerm_2 (int start, int end, string &prefix, string &rest, const string dict[], const int &size, int &tally, string results[]){ // takes in same parameters as permuteRecur and a count and tally to help return number of found results
    
    if(start>=end)
        return;
    
    string next = prefix + rest[start];
    string remaining = rest.substr(0, start) + rest.substr(start+1);
    Perm(next, remaining, dict, size, tally, results); // function to find all permutations
    
    loopPerm_2(start+1, end, prefix, rest, dict, size, tally, results);
}

void loopRemoveDups1(int start, int end, string results[]){ // this will be equivalent to an outer for loop to check if there are any duplicates in results array
    if(start>=end)
        return;
           if (results[start]==results[start+1])
               loopRemoveDups2(start, end, results);
    loopRemoveDups1(start+1, end, results);
}

void loopRemoveDups2(const int initial, const int ending, string results[]){ // this will be equivalenet to an inner for loop to move everything down one element to get rid of a duplicate string
    if(initial >= ending)
        return;
    results[initial] = results[initial+1];
    loopRemoveDups2(initial+1, ending, results);
}
