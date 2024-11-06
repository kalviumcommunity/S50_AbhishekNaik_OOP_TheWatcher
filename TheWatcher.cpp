#include <bits/stdc++.h>
using namespace std;

class Anime {
private:
    string title;
    int rating;
    static int animeCount;

public:
    // Default constructor
    Anime() : title("Unknown"), rating(0) {
        animeCount++;
        cout << "Anime default constructor called." << endl;
    }

    // Parameterized constructor
    Anime(string t, int r) : title(t), rating(r) {
        animeCount++;
        cout << "Anime parameterized constructor called." << endl;
    }

    // Destructor
    ~Anime() {
        cout << "Anime destructor called for " << title << endl;
    }

    string getTitle() const {
        return title;
    }

    void setTitle(const string &t) {
        title = t;
    }

    int getRating() const {
        return rating;
    }

    void setRating(int r) {
        rating = r;
    }

    void saveToFile(ofstream &file) const {
        file << title << endl;
        file << rating << endl;
    }

    static Anime loadFromFile(ifstream &file) {
        string t;
        int r;
        getline(file, t);
        file >> r;
        file.ignore();
        return Anime(t, r);
    }

    static int getAnimeCount() {
        return animeCount;
    }
};

int Anime::animeCount = 0;

class User {
private:
    string name;
    vector<Anime *> watchlist;
    static int userCount;

public:
    // Parameterized constructor
    User(string n) : name(n) {
        userCount++;
        cout << "User constructor called for " << name << endl;
    }

    // Destructor
    ~User() {
        for (Anime *anime : watchlist) {
            delete anime;
        }
        cout << "User destructor called for " << name << endl;
    }

    string getName() const {
        return name;
    }

    void setName(const string &n) {
        name = n;
    }

    void addAnime(Anime *anime) {
        watchlist.push_back(anime);
    }

    void displayWatchlist() const {
        if (watchlist.empty()) {
            cout << "Watchlist is empty." << endl;
            return;
        }
        cout << "User: " << name << "'s Watchlist:" << endl;
        for (const Anime *anime : watchlist) {
            cout << "Title: " << anime->getTitle() << ", Rating: " << anime->getRating() << endl;
        }
    }

    void saveToFile() const {
        ofstream file(name + "_watchlist.txt");
        if (file.is_open()) {
            for (const Anime *anime : watchlist) {
                anime->saveToFile(file);
            }
            file.close();
        } else {
            cerr << "Unable to open file for writing." << endl;
        }
    }

    void loadFromFile() {
        ifstream file(name + "_watchlist.txt");
        if (file.is_open()) {
            watchlist.clear();
            while (!file.eof()) {
                Anime anime = Anime::loadFromFile(file);
                if (file) {
                    addAnime(new Anime(anime));
                }
            }
            file.close();
        } else {
            cerr << "Unable to open file for reading." << endl;
        }
    }

    static int getUserCount() {
        return userCount;
    }
};

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

            Anime *anime = new Anime(title, rating);
            user.addAnime(anime);
            user.saveToFile();
            break;
        }
        case '2':
            user.displayWatchlist();
            break;
        case '3':
            cout << "Exiting program." << endl;
            break;
        default:
            cout << "Invalid choice. Please enter a number between 1 and 3." << endl;
            break;
        }
    } while (choice != '3');

    return 0;
}
