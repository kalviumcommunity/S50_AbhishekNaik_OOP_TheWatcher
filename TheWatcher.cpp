#include <bits/stdc++.h>
using namespace std;

class Anime {
private:
    string title;  // The name of the anime
    int rating;    // The rating of the anime

    //how many Anime objects have been created
    static int animeCount;

public:
    // Constructor
    Anime(string t = "", int r = 0) : title(t), rating(r) {
        animeCount++; // counter++ whenever a new Anime is created
    }

    // Accessor title
    string getTitle() const {
        return title;
    }

    // Mutator title
    void setTitle(const string& t) {
        title = t;
    }

    // Accessor rating
    int getRating() const {
        return rating;
    }

    // Mutator rating
    void setRating(int r) {
        rating = r;
    }

    // Saves the Anime's title and rating to a file
    void saveToFile(ofstream& file) const {
        file << title << endl;
        file << rating << endl;
    }

    // Loads an Anime from a file and returns it
    static Anime loadFromFile(ifstream& file) {
        string t;
        int r;
        getline(file, t);
        file >> r;
        file.ignore(); // Ignore leftover newline character
        return Anime(t, r);
    }

    // Static function to get the total number of Anime objects created so far
    static int getAnimeCount() {
        return animeCount;
    }
};

// Initialize the static variable to 0
int Anime::animeCount = 0;

class User {
private:
    string name;  // The name of the user
    vector<Anime*> watchlist;  // The user's list of Anime

    // Keeps track of how many User objects have been created
    static int userCount;

public:
    // Constructor
    User(string n) : name(n) {
        userCount++; // Increase the counter whenever a new User is created
    }

    // Destructor
    ~User() {
    for (Anime* anime : watchlist) {
            delete anime;
        }
    }

    // Accessor name
    string getName() const {
        return name;
    }

    // Mutator name
    void setName(const string& n) {
        name = n;
    }

    // Adds a new Anime to the user's watchlist
    void addAnime(Anime* anime) {
        watchlist.push_back(anime);
    }

    // Shows all the Anime in the user's watchlist
    void displayWatchlist() const {
        if (watchlist.empty()) {
            cout << "Watchlist is empty." << endl;
            return;
        }
        cout << "User: " << name << "'s Watchlist:" << endl;
        for (const Anime* anime : watchlist) {
            cout << "Title: " << anime->getTitle() << ", Rating: " << anime->getRating() << endl;
        }
    }

    // Saves the user's watchlist to a file
    void saveToFile() const {
        ofstream file(name + "_watchlist.txt");
        if (file.is_open()) {
            for (const Anime* anime : watchlist) {
                anime->saveToFile(file);
            }
            file.close();
        } else {
            cerr << "Unable to open file for writing." << endl;
        }
    }

    // Loads the user's watchlist from a file
    void loadFromFile() {
        ifstream file(name + "_watchlist.txt");
        if (file.is_open()) {
            watchlist.clear(); // Clear the current watchlist
            while (!file.eof()) {
                Anime anime = Anime::loadFromFile(file);
                if (file) {
                    addAnime(new Anime(anime)); // Add the loaded Anime to the watchlist
                }
            }
            file.close();
        } else {
            cerr << "Unable to open file for reading." << endl;
        }
    }

    // total number of User objects created so far
    static int getUserCount() {
        return userCount;
    }
};

// Initialize the static variable to 0
int User::userCount = 0;

int main() {
    string userName;
    cout << "Enter your username to register: ";
    getline(cin, userName);

    User user(userName);  // Create a new User with the entered name
    user.loadFromFile();  // Load the user's watchlist from a file

    char choice;
    do {
        cout << "\nMenu:" << endl;
        cout << "1. Add Anime" << endl;
        cout << "2. Display Watchlist" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice (1-3): ";
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

                Anime* anime = new Anime(title, rating);  // Create a new Anime object
                user.addAnime(anime);  // Add the Anime to the user's watchlist
                user.saveToFile();  // Save the updated watchlist to a file
                break;
            }
            case '2':
                user.displayWatchlist();  // Show the user's watchlist
                break;
            case '3':
                cout << "Exiting program." << endl;
                break;
            default:
                cout << "Invalid choice. Please enter a number between 1 and 3." << endl;
                break;
        }
    } while (choice != '3');  // Keep showing the menu until the user chooses to exit

    return 0;
}
