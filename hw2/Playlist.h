#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <string>

using namespace std;

struct Song {
    string title;
    int duration;
    bool fav_status;
    Song* next;
    Song* prev;

    // Constructor to initialize a song
    Song(string t, int d, bool fav);
};

class Playlist {
private:
    Song* head;
    Song* tail;

public:
    // No-Arg Constructor
    Playlist();

    // Destructor
    ~Playlist();

    // Function to add a song to the end of the playlist
    void AddSong(string title, int duration, bool fav_status);

    // Function to print the whole playlist
    void PrintPlaylist(ofstream &outFile);

    // Function to print the playlist in reverse order
    void PrintReversedPlaylist(ofstream &outFile);

    // Function to delete a song from the playlist
    void DeleteSong(string title);

    // Function to create a smart playlist by prioritizing favorite songs
    void CreateSmartPlaylist(int time_limit, ofstream &outFile);
};

// Function to read songs from the input files
void readInputFile(Playlist &playlist, const string &filename, ofstream &outFile);

#endif