#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

class Anime {
private:
    string title;
    int rating;

public:
    // Constructor
    Anime(string t, int r) : title(t), rating(r) {}

    // Member functions
    string getTitle() const {
        return title;
    }

    int getRating() const {
        return rating;
    }

    void setRating(int r) {
        rating = r;
    }

    // Save to file
    void saveToFile(ofstream& file) const {
        file << title << endl;
        file << rating << endl;
    }

    // Load from file
    static Anime loadFromFile(ifstream& file) {
        string t;
        int r;
        getline(file, t);
        file >> r;
        file.ignore();  // Ignore the newline character after the rating
        return Anime(t, r);
    }
};

class User {
private:
    string name;
    vector<Anime> watchlist;

public:
    // Constructor
    User(string n) : name(n) {}

    // Member functions
    void addAnime(const Anime& anime) {
        watchlist.push_back(anime);
    }

    void displayWatchlist() const {
        if (watchlist.empty()) {
            cout << "Watchlist is empty." << endl;
            return;
        }
        cout << "User: " << name << "'s Watchlist:" << endl;
        for (const Anime& anime : watchlist) {
            cout << "Title: " << anime.getTitle() << ", Rating: " << anime.getRating() << endl;
        }
    }

    // Save watchlist to file
    void saveToFile() const {
        ofstream file(name + "_watchlist.txt");
        if (file.is_open()) {
            for (const Anime& anime : watchlist) {
                anime.saveToFile(file);
            }
            file.close();
        } else {
            cerr << "Unable to open file for writing." << endl;
        }
    }

    // Load watchlist from file
    void loadFromFile() {
        ifstream file(name + "_watchlist.txt");
        if (file.is_open()) {
            watchlist.clear();  // Clear existing watchlist
            while (!file.eof()) {
                Anime anime = Anime::loadFromFile(file);
                if (file) {  // Check if read was successful
                    addAnime(anime);
                }
            }
            file.close();
        } else {
            cerr << "Unable to open file for reading." << endl;
        }
    }
};

int main() {
    string userName;
    cout << "Enter your username to register: ";
    getline(cin, userName);

    // Creating a User object
    User user(userName);

    // Load existing watchlist if available
    user.loadFromFile();

    char choice;
    do {
        cout << "\nMenu:" << endl;
        cout << "1. Add Anime" << endl;
        cout << "2. Display Watchlist" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice (1-3): ";
        cin >> choice;

        // Clear the input buffer
        cin.ignore();

        switch (choice) {
            case '1': {
                string title;
                int rating;

                cout << "Enter anime title: ";
                getline(cin, title);

                cout << "Enter anime rating (1-10): ";
                cin >> rating;

                // Clear the input buffer
                cin.ignore();

                // Creating Anime object and adding it to the User's watchlist
                Anime anime(title, rating);
                user.addAnime(anime);

                // Save the User's watchlist
                user.saveToFile();

                break;
            }
            case '2':
                // Display the User's watchlist
                user.displayWatchlist();
                break;
            case '3':
                // Exit
                cout << "Exiting program." << endl;
                break;
            default:
                cout << "Invalid choice. Please enter a number between 1 and 3." << endl;
                break;
        }
    } while (choice != '3');

    return 0;
}