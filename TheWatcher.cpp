#include <bits/stdc++.h>
using namespace std;

class Anime {
private:
    string title;
    int rating;
    static int animeCount;

public:
    Anime() : title("Unknown"), rating(0) {
        animeCount++;
    }

    Anime(string t, int r) : title(t), rating(r) {
        animeCount++;
    }

    ~Anime() {
        cout << "Anime destructor called for " << title << endl;
    }

    string getTitle() const {
        return title;
    }

    int getRating() const {
        return rating;
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
    User(string n) : name(n) {
        userCount++;
    }

    virtual ~User() {
        for (Anime *anime : watchlist) {
            delete anime;
        }
        cout << "User destructor called for " << name << endl;
    }

    string getName() const {
        return name;
    }

    // Function Overloading: Add anime either by passing title and rating, or by passing an Anime object.
    void addAnime(string title, int rating) {
        Anime *anime = new Anime(title, rating);
        watchlist.push_back(anime);
        cout << "Anime added: " << title << " with rating " << rating << endl;
    }

    void addAnime(Anime *anime) {
        watchlist.push_back(anime);
        cout << "Anime added: " << anime->getTitle() << " with rating " << anime->getRating() << endl;
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

    virtual void displayPrivileges() const {
        cout << "Standard user with no special privileges." << endl;
    }
};

int User::userCount = 0;

class PremiumUser : public User {
public:
    PremiumUser(string n) : User(n) {}

    void displayPrivileges() const override {
        cout << "Premium user with ad-free experience and early access to episodes." << endl;
    }
};

class AdminUser : public PremiumUser {
public:
    AdminUser(string n) : PremiumUser(n) {}

    void displayPrivileges() const override {
        cout << "Admin user with full access, including content management privileges." << endl;
    }

    void manageContent() const {
        cout << "Admin managing content: adding, removing, or updating anime." << endl;
    }
};

int main() {
    // Admin user Abhishek is hardcoded
    AdminUser admin("Abhishek");

    string userName, userType;
    char choice;
    do {
        cout << "\nEnter the username and type of user (Standard/Premium) or type 'exit' to stop creating users:" << endl;
        cout << "Enter username: ";
        getline(cin, userName);

        if (userName == "exit") {
            break;
        }

        User *user = nullptr;
        if (userName == "Abhishek") {
            user = &admin;  // Assigning the already created admin instance
            cout << "Welcome, Admin!" << endl;
            admin.displayPrivileges();
            admin.manageContent();
        } else {
            cout << "Enter user type (Standard/Premium): ";
            getline(cin, userType);

            if (userType == "Standard") {
                user = new User(userName);
            } else if (userType == "Premium") {
                user = new PremiumUser(userName);
            } else {
                cout << "Invalid user type. Defaulting to Standard." << endl;
                user = new User(userName);
            }
            user->displayPrivileges();
        }

        // Anime interaction for users
        cout << "\nMenu:" << endl;
        cout << "1. Add Anime by Title and Rating" << endl;
        cout << "2. Add Anime by Anime Object" << endl;
        cout << "3. Display Watchlist" << endl;
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

            user->addAnime(title, rating);  // Adding anime using title and rating
            break;
        }
        case '2': {
            string title;
            int rating;

            cout << "Enter anime title: ";
            getline(cin, title);

            cout << "Enter anime rating (1-10): ";
            cin >> rating;
            cin.ignore();

            Anime *anime = new Anime(title, rating);
            user->addAnime(anime);  // Adding anime using Anime object
            break;
        }
        case '3':
            user->displayWatchlist();
            break;
        case '4':
            cout << "Exiting program." << endl;
            break;
        default:
            cout << "Invalid choice. Please enter a number between 1 and 4." << endl;
            break;
        }

        if (user != &admin) {
            delete user;
        }

    } while (choice != '4');

    return 0;
}
