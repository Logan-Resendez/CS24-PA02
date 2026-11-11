// Winter'24
// Instructor: Diba Mirza
// Student name: Logan Resendez
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <vector>
#include <cstring>
#include <algorithm>
#include <limits.h>
#include <iomanip>
#include <set>
#include <queue>
#include <sstream>
using namespace std;

#include "utilities.h"
#include "movies.h"

bool parseLine(string &line, string &movieName, double &movieRating);

int main(int argc, char** argv){
    if (argc < 2){
        cerr << "Not enough arguments provided (need at least 1 argument)." << endl;
        cerr << "Usage: " << argv[ 0 ] << " moviesFilename prefixFilename " << endl;
        exit(1);
    }

    ifstream movieFile (argv[1]);
 
    if (movieFile.fail()){
        cerr << "Could not open file " << argv[1];
        exit(1);
    }
  
    MovieDatabase db;
    string line, movieName;
    double movieRating;

    while (getline (movieFile, line) && parseLine(line, movieName, movieRating)){
        db.addMovie(movieName, movieRating);
    }
    movieFile.close();

    db.sortAlphabetically();
    cout << fixed << setprecision(1);

    if (argc == 2){
            db.printAlphabetically();
            return 0;
    }

    ifstream prefixFile (argv[2]);

    if (prefixFile.fail()) {
        cerr << "Could not open file " << argv[2];
        exit(1);
    }

    vector<string> prefixes;
    while (getline (prefixFile, line)) {
        if (!line.empty()) {
            prefixes.push_back(line);
        }
    }
    prefixFile.close();

    db.searchByPrefix(prefixes);
    return 0;
}

/* 
Time and Space Complexity Analysis

    Parameters:
        - n: Number of movies
        - m: Number of prefixes
        - k: Max number of movies with any single prefix
        - l: Max length of movie title

    Time Complexity:
        Worst Case Time Complexity: O(m * l * (logn + klogk))

        Specific Run Times:
            input_20_random.csv: 6ms
            input_100_random.csv: 8ms
            input_1000_random.csv: 9ms
            input_76920_random.csv: 80ms

    Space Complexity:
        Auxilary Space: O(k + m * l)

    Tradeoffs Between Time/Space Complexity
        I designed my algorithm for both a low time and space complexity. I feel I was able to achieve this due to the
        single sorted vector that I stored combined with binary search and a pointer-based collection. Achieving low time
        complexity was harder since using a vector naturally allowed lower space complexity. 
*/


bool parseLine(string &line, string &movieName, double &movieRating) {
    int commaIndex = line.find_last_of(",");
    movieName = line.substr(0, commaIndex);
    movieRating = stod(line.substr(commaIndex+1));
    if (movieName[0] == '\"') {
        movieName = movieName.substr(1, movieName.length() - 2);
    }
    return true;
}