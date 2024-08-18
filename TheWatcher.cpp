#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

class Anime {
private:
    string title;  // The name of the anime
    int rating;    // The rating of the anime

    // Keeps track of how many Anime objects have been created
    static int animeCount;

public:
    // Constructor: This function runs whenever a new Anime object is created.
    // It sets the title and rating, and also increases the animeCount by 1.
    Anime(string t = "", int r = 0) : title(t), rating(r) {
        animeCount++; // Increase the counter whenever a new Anime is created
    }

    // Gets the title of the Anime
    string getTitle() const {
        return this->title;
    }

    // Gets the rating of the Anime
    int getRating() const {
        return this->rating;
    }

    // Updates the rating of the Anime
    void setRating(int r) {
        this->rating = r;
    }

    // Saves the Anime's title and rating to a file
    void saveToFile(ofstream& file) const {
        file << this->title << endl;
        file << this->rating << endl;
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

// Initialize the static variable to 0 (no Anime objects created yet)
int Anime::animeCount = 0;

class User {
private:
    string name;  // The name of the user
    vector<Anime*> watchlist;  // The user's list of Anime

    // Keeps track of how many User objects have been created
    static int userCount;

public:
    // Constructor: This function runs whenever a new User object is created.
    // It sets the user's name and increases the userCount by 1.
    User(string n) : name(n) {
        userCount++; // Increase the counter whenever a new User is created
    }

    // Destructor: This function runs when a User object is deleted.
    // It makes sure all the Anime objects in the watchlist are deleted too.
    ~User() {
        for (Anime* anime : watchlist) {
            delete anime;
        }
    }

    // Adds a new Anime to the user's watchlist
    void addAnime(Anime* anime) {
        this->watchlist.push_back(anime);
    }

    // Shows all the Anime in the user's watchlist
    void displayWatchlist() const {
        if (this->watchlist.empty()) {  // If the watchlist is empty
            cout << "Watchlist is empty." << endl;
            return;
        }
        cout << "User: " << this->name << "'s Watchlist:" << endl;
        for (const Anime* anime : this->watchlist) {
            cout << "Title: " << anime->getTitle() << ", Rating: " << anime->getRating() << endl;
        }
    }

    // Saves the user's watchlist to a file
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

    // Loads the user's watchlist from a file
    void loadFromFile() {
        ifstream file(this->name + "_watchlist.txt");
        if (file.is_open()) {
            this->watchlist.clear(); // Clear the current watchlist
            while (!file.eof()) {  // Keep loading until the end of the file
                Anime anime = Anime::loadFromFile(file);
                if (file) {  // If loading was successful
                    this->addAnime(new Anime(anime)); // Add the loaded Anime to the watchlist
                }
            }
            file.close();
        } else {
            cerr << "Unable to open file for reading." << endl;
        }
    }

    // Static function to get the total number of User objects created so far
    static int getUserCount() {
        return userCount;
    }
};

// Initialize the static variable to 0 (no User objects created yet)
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

                Anime* anime = new Anime(title, rating);  // Create a new Anime object
                user.addAnime(anime);  // Add the Anime to the user's watchlist
                user.saveToFile();  // Save the updated watchlist to a file
                break;
            }
            case '2':
                user.displayWatchlist();  // Show the user's watchlist
                break;
            case '3':  // Show the total number of Anime and User objects created
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
    } while (choice != '4');  // Keep showing the menu until the user chooses to exit

    return 0;
}
