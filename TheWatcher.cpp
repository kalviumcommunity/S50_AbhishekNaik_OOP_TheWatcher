#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

class Anime {
private:
    string title;
    int rating;

    // Static variable to count the number of Anime objects created
    static int animeCount;

public:
    // Constructor
    Anime(string t = "", int r = 0) : title(t), rating(r) {
        animeCount++; // Increment the counter each time an Anime object is created
    }

    // Member functions
    string getTitle() const {
        return this->title;
    }

    int getRating() const {
        return this->rating;
    }

    void setRating(int r) {
        this->rating = r;
    }

    void saveToFile(ofstream& file) const {
        file << this->title << endl;
        file << this->rating << endl;
    }

    static Anime loadFromFile(ifstream& file) {
        string t;
        int r;
        getline(file, t);
        file >> r;
        file.ignore();
        return Anime(t, r);
    }

    // Static function to get the current count of Anime objects
    static int getAnimeCount() {
        return animeCount;
    }
};

// Initialize static variable
int Anime::animeCount = 0;

class User {
private:
    string name;
    vector<Anime*> watchlist;

    // Static variable to count the number of User objects created
    static int userCount;

public:
    // Constructor
    User(string n) : name(n) {
        userCount++; // Increment the counter each time a User object is created
    }

    ~User() {
        for (Anime* anime : watchlist) {
            delete anime;
        }
    }

    void addAnime(Anime* anime) {
        this->watchlist.push_back(anime);
    }

    void displayWatchlist() const {
        if (this->watchlist.empty()) {
            cout << "Watchlist is empty." << endl;
            return;
        }
        cout << "User: " << this->name << "'s Watchlist:" << endl;
        for (const Anime* anime : this->watchlist) {
            cout << "Title: " << anime->getTitle() << ", Rating: " << anime->getRating() << endl;
        }
    }

    void saveToFile() const {
        ofstream file(this->name + "_watchlist.txt");
        if (file.is_open()) {
            for (const Anime* anime : this->watchlist) {
                anime->saveToFile(file);
            }
            file.close();
        } else {
            cerr << "Unable to open file for writing." << endl;
        }
    }

    void loadFromFile() {
        ifstream file(this->name + "_watchlist.txt");
        if (file.is_open()) {
            this->watchlist.clear();
            while (!file.eof()) {
                Anime anime = Anime::loadFromFile(file);
                if (file) {
                    this->addAnime(new Anime(anime)); // Add dynamically allocated Anime object
                }
            }
            file.close();
        } else {
            cerr << "Unable to open file for reading." << endl;
        }
    }

    // Static function to get the current count of User objects
    static int getUserCount() {
        return userCount;
    }
};

// Initialize static variable
int User::userCount = 0;

int main() {
    string userName;
    cout << "Enter your username to register: ";
    getline(cin, userName);

    User user(userName);
    user.loadFromFile();

    char choice;
    do {
        cout << "\nMenu:" << endl;
        cout << "1. Add Anime" << endl;
        cout << "2. Display Watchlist" << endl;
        cout << "3. Display Object Counts" << endl;  // New menu option
        cout << "4. Exit" << endl;
        cout << "Enter your choice (1-4): ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case '1': {
                string title;
                int rating;

                cout << "Enter anime title: ";
                getline(cin, title);

                cout << "Enter anime rating (1-10): ";
                cin >> rating;
                cin.ignore();

                Anime* anime = new Anime(title, rating);  // Dynamically allocate Anime
                user.addAnime(anime);
                user.saveToFile();
                break;
            }
            case '2':
                user.displayWatchlist();
                break;
            case '3':  // Display object counts
                cout << "Total number of Anime objects: " << Anime::getAnimeCount() << endl;
                cout << "Total number of User objects: " << User::getUserCount() << endl;
                break;
            case '4':
                cout << "Exiting program." << endl;
                break;
            default:
                cout << "Invalid choice. Please enter a number between 1 and 4." << endl;
                break;
        }
    } while (choice != '4');

    return 0;
}
