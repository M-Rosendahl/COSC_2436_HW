#include "ArgumentManager.h"
#include "Playlist.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
using namespace std;

Song::Song(string t, int d, bool fav) : title(t), duration(d), fav_status(fav) {}

    // No-Arg Constructor
Playlist::Playlist()  : head(nullptr), tail(nullptr) {}

    // Destructor
Playlist::~Playlist() {
    Song* current = head;
    while (current) {               // Keep track of the next node before deleting the current one
        Song* nextSong = current -> next;
        delete current;
        current = nextSong;
    }
}

    // Function to add a song to the end of the playlist
void Playlist::AddSong(string title, int duration, bool fav_status) {
    Song* newSong = new Song(title, duration, fav_status);

    // If list is empty, this song becomes both head and tail
    if (head == nullptr)
        head = tail = newSong;
    else {
        tail -> next = newSong; // Connect last song to the new song
        newSong -> prev = tail; // Set the new song's prev pointer
        tail = newSong;         // Update tail to the new song
    }
}

    // Function to print the whole playlist
void Playlist::PrintPlaylist(ofstream &outFile) {
    Song* current = head;
    outFile << "[";
    while (current) {
        outFile << current->title;
        if (current->next)  // Only add a comma if there is another song
        outFile << ", ";
        current = current->next;
    }
    outFile << "]\n";
}


    // Function to print the playlist in reverse order
void Playlist::PrintReversedPlaylist(ofstream &outFile) {
    Song* current = tail;
    outFile << "[";
    while (current) {
        outFile << current -> title;
        if (current -> prev)
            outFile << ", ";
        current = current -> prev;                  // Moves backwards until reaching the beginning (nullptr)
    }
    outFile << "]\n";
}
    
    // Function to delete a song from the playlist and update the links by traversing the list from the head
void Playlist::DeleteSong(string title) {
    Song* current = head;                           // Create temporary node "current"
    while (current && current -> title != title)    // Checks if the title of the current song node matches temp node
        current = current -> next;
    if (!current) return;                           // Song not found

    // Updating links if the song is at the start or the end
    if (current == head)
        head = head -> next;
    if (current == tail)
        tail = tail -> prev;
    
    // Adjusting next and prev pointers to remove the song
    if (current -> prev)
        current -> prev -> next = current -> next;
    if (current -> next)
        current -> next -> prev = current -> prev;
    delete current;
}


    // Function to create a smart playlist which orders by prioritizing favorite songs first, given a time limit
void Playlist::CreateSmartPlaylist(int time_limit, ofstream &outFile) {

    // Iterating through favorite songs and adding them until time limit is reached
    vector<Song*> smart_playlist;
    int total_time = 0;                         // Utilizing counter
    
    // Adding favorite songs in their original order first
    Song* current = head;
    while (current) {
        if (current -> fav_status) {
            if (total_time + current -> duration <= time_limit) {
                smart_playlist.push_back(current);
                total_time += current -> duration;
            }
        }
        current = current -> next;
    }

    // Then, adding non-favorite songs if there is time left
    current = head;                     // Reset to the head of the list
    while (current) {
        if (!current -> fav_status) {
            if (total_time + current -> duration <= time_limit) {
                smart_playlist.push_back(current);
                total_time += current -> duration;
            }
        }
        current = current -> next;
    }
    
    // Printing the smart playlist
    outFile << "[";
    for (size_t i = 0; i < smart_playlist.size(); i++) {
        outFile << smart_playlist[i] -> title;
        if (i != smart_playlist.size() - 1)
        outFile << ", ";
    }
    outFile << "]\n";        
}

// Function to read input file commands
void readInputFile(Playlist &playlist, const string &filename, ofstream &outFile) {
    ifstream inFile(filename);
    if (!inFile) {
        cerr << "Error opening input file: " << filename << endl;
        return;
    }

    string line, command, args;
    while (getline(inFile, line)) {
        // Find if parentheses exist for the command with parameters
        size_t openParen = line.find('(');
        size_t closeParen = line.find(')');

        if (openParen != string::npos && closeParen != string::npos) {
            command = line.substr(0, openParen);                            // Extract command name
            args = line.substr(openParen + 1, closeParen - openParen - 1);  // Extract arguments
        } else {
            command = line;                                                 
            args = "";
        }

        stringstream ss(args);
        if (command == "AddSong") {
            string title;
            int duration;
            bool fav_status;
            char comma;                                                     // To handle commas in input

            getline(ss, title, ',');                                        // Capture the title, including spaces, until the first comma
            ss >> duration >> comma >> boolalpha >> fav_status;             // Parse the remaining fields for duration and favorite status

            // Add the song with the parsed values
            playlist.AddSong(title, duration, fav_status);
        } 
        else if (command == "DeleteSong") {
            // Trim leading spaces
            size_t first = args.find_first_not_of(' ');         // Find first non-space character
            if (first != string::npos) {                        // Check for any chars
                args = args.substr(first);                      // Extract substr from 'first' to end of string
            }

            // Trim trailing spaces
            size_t last = args.find_last_not_of(' ');
            if (last != string::npos) {
                args = args.substr(0, last + 1);
            }  
            playlist.DeleteSong(args);
        } 
        else if (command == "PrintPlaylist") {
            playlist.PrintPlaylist(outFile);
        } 
        else if (command == "PrintReversedPlaylist") {
            playlist.PrintReversedPlaylist(outFile);
        } 
        else if (command == "CreateSmartPlaylist") {
            int time_limit = stoi(args);
            playlist.CreateSmartPlaylist(time_limit, outFile);
        }
    }

    inFile.close();
}


int main(int argc, char *argv[]) {
    ArgumentManager am(argc, argv);
    
   // string inputFile = am.get("input");
   //  string outputFile = am.get("output");

    string inputFile = "input1.txt";
    string outputFile = "output1.txt";

    Playlist myPlaylist;
    ofstream outFile(outputFile);
    if (!outFile) {
        cout << "Error: Could not open output file!" << endl;
        return 1;
    }

    // Read input songs from file
    readInputFile(myPlaylist, inputFile, outFile);
    outFile.close();

    return 0;
}
