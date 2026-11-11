// movies.cpp
// Student Name: Logan Resendez
#include "movies.h"

#include <iostream>
#include <algorithm>

using namespace std;

void MovieDatabase::addMovie(const string& name, double rating)
{
    movies.push_back({name, rating});
}

void MovieDatabase::sortAlphabetically()
{
    sort(movies.begin(), movies.end());
}

void MovieDatabase::printAlphabetically() const
{
    for(const auto& movie : movies)
    {
        cout << movie.name << ", " << movie.rating << '\n';
    }
}

bool MovieDatabase::startsWith(const string& str, const string& prefix)
{
    if(prefix.size() > str.size()) {return false;}
    return str.compare(0, prefix.size(), prefix) == 0;
}

void MovieDatabase::searchByPrefix(const vector<string>& prefixes) const
{
    vector<pair<string, const Movie*>> bestMovies;

    for(const auto& prefix : prefixes)
    {
        auto it = lower_bound(movies.begin(), movies.end(), prefix, [](const Movie& m, const string& p){return m.name < p;});

        vector<const Movie*> matches;

        for(; it != movies.end() && startsWith(it->name, prefix); it++)
        {
            matches.push_back(&(*it));
        }

        if(matches.empty())
        {
            cout << "No movies found with prefix " << prefix << '\n';
        } else
        {
            sort(matches.begin(), matches.end(), [](const Movie* a, const Movie* b)
            {
                if(a->rating != b->rating)
                {
                    return a->rating > b->rating;
                }
                return a->name < b->name;
            });

            for(const auto* moviePtr : matches)
            {
                cout << moviePtr->name << ", " << moviePtr->rating << '\n';
            }

            bestMovies.push_back({prefix, matches[0]});
            cout << '\n';
        }
    }

    for(const auto& entry : bestMovies)
    {
        cout << "Best movie with prefix " << entry.first << " is: " << entry.second->name << " with rating " << entry.second->rating << '\n';
    }
}