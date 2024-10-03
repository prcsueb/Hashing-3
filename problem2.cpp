/*
Time Complexity (TC):

    The time complexity is O(U * S + G * S), where:

        U is the number of users.

        S is the number of songs.

        G is the number of genres.

Space Complexity (SC):

    The space complexity is O(S + U * G), where:

        S is the number of songs (for songToGenre map).

        U * G is the space for storing the genre counts for each user.
*/

#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

unordered_map<string, vector<string>> favoritegenre(unordered_map<string, vector<string>>& userSongs, unordered_map<string, vector<string>>& songGenres) {
    unordered_map<string, string> songToGenre;
    for (auto& genre : songGenres) {
        for (auto& song : genre.second) {
            songToGenre[song] = genre.first;
        }
    }

    unordered_map<string, vector<string>> result;

    for (auto& user : userSongs) {
        unordered_map<string, int> genreCount;
        int maxCount = 0;

        for (auto& song : user.second) {
            string genre = songToGenre[song];
            genreCount[genre]++;
            maxCount = max(maxCount, genreCount[genre]);
        }

        vector<string> favoriteGenres;
        for (auto& genre : genreCount) {
            if (genre.second == maxCount) {
                favoriteGenres.push_back(genre.first);
            }
        }

        result[user.first] = favoriteGenres;
    }

    return result;
}

int main() {
    unordered_map<string, vector<string>> userSongs = {
        {"David", {"song1", "song2", "song3", "song4", "song8"}},
        {"Emma", {"song5", "song6", "song7"}}
    };

    unordered_map<string, vector<string>> songGenres = {
        {"Rock", {"song1", "song3"}},
        {"Dubstep", {"song7"}},
        {"Techno", {"song2", "song4"}},
        {"Pop", {"song5", "song6"}},
        {"Jazz", {"song8", "song9"}}
    };

    unordered_map<string, vector<string>> res = favoritegenre(userSongs, songGenres);

    for (auto& user : res) {
        cout << user.first << ": ";
        for (auto& genre : user.second) {
            cout << genre << " ";
        }
        cout << endl;
    }

    return 0;
}