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
    Anime(string t = "", int r = 0) : title(t), rating(r) {}

    // Member functions
    string getTitle() const {
        return this->title;
    }

    int getRating() const {
        return this->rating;
    }

    void setRating(int r) {
        this->rating = r; // Using `this` pointer to refer to the object's rating attribute
    }

    // Save to file
    void saveToFile(ofstream& file) const {
        file << this->title << endl; // Using `this` pointer to access title
        file << this->rating << endl; // Using `this` pointer to access rating
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
        this->watchlist.push_back(anime); // Using `this` pointer to refer to the watchlist
    }

    void displayWatchlist() const {
        if (this->watchlist.empty()) {
            cout << "Watchlist is empty." << endl;
            return;
        }
        cout << "User: " << this->name << "'s Watchlist:" << endl;
        for (const Anime& anime : this->watchlist) {
            cout << "Title: " << anime.getTitle() << ", Rating: " << anime.getRating() << endl;
        }
    }

    // Save watchlist to file
    void saveToFile() const {
        ofstream file(this->name + "_watchlist.txt");
        if (file.is_open()) {
            for (const Anime& anime : this->watchlist) {
                anime.saveToFile(file);
            }
            file.close();
        } else {
            cerr << "Unable to open file for writing." << endl;
        }
    }

    // Load watchlist from file
    void loadFromFile() {
        ifstream file(this->name + "_watchlist.txt");
        if (file.is_open()) {
            this->watchlist.clear();  // Clear existing watchlist
            while (!file.eof()) {
                Anime anime = Anime::loadFromFile(file);
                if (file) {  // Check if read was successful
                    this->addAnime(anime);
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

    const int MAX_ANIMES = 100; // Define the maximum number of animes in the array
    Anime animeArray[MAX_ANIMES]; // Array of Anime objects
    int animeCount = 0;

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
                if (animeCount < MAX_ANIMES) {
                    string title;
                    int rating;

                    cout << "Enter anime title: ";
                    getline(cin, title);

                    cout << "Enter anime rating (1-10): ";
                    cin >> rating;

                    // Clear the input buffer
                    cin.ignore();

                    // Create an Anime object and add it to the array
                    Anime anime(title, rating);
                    animeArray[animeCount++] = anime;

                    // Add the Anime object to the User's watchlist
                    user.addAnime(anime);

                    // Save the User's watchlist
                    user.saveToFile();
                } else {
                    cout << "Maximum number of animes reached." << endl;
                }
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
