// movies.h
// Student Name: Logan Resendez
#ifndef MOVIES_H
#define MOVIES_H

#include <string>
#include <vector>

struct Movie
{
    std::string name;
    double rating;
    bool operator<(const Movie& other) const
    {
        return name < other.name;
    }
};

class MovieDatabase
{
public:
    MovieDatabase() = default;
    void addMovie(const std::string& name, double rating);
    void sortAlphabetically();
    void printAlphabetically() const;
    void searchByPrefix(const std::vector<std::string>& prefixes) const;

private:
    std::vector<Movie> movies;
    static bool startsWith(const std::string& str, const std::string& prefix);
};

#endif
