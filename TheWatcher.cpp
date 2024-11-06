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

    virtual void displayPrivileges() const {
        cout << "Standard user with no special privileges." << endl;
    }
};

int User::userCount = 0;

class PremiumUser : public User {  // Single Inheritance
public:
    PremiumUser(string n) : User(n) {}

    void displayPrivileges() const override {
        cout << "Premium user with ad-free experience and early access to episodes." << endl;
    }
};

class AdminUser : public PremiumUser {  // Multilevel Inheritance
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
    AdminUser admin("Abhishek");  // Admin user named Abhishek
    // admin.displayPrivileges();
    // admin.manageContent();

    string userName, userType;
    char choice;
    do {
        cout << "\nEnter the username and type of user (Standard/Premium) or type 'exit' to stop creating users:" << endl;
        cout << "Enter username: ";
        getline(cin, userName);

        if (userName == "exit") {
            break;
        }

        // Check if the entered name is the admin name
        User *user = nullptr;
        if (userName == "Abhishek") {
            user = &admin;  // Assigning the already created admin instance
            cout << "Welcome, Admin!" << endl;
            admin.displayPrivileges();
            admin.manageContent();  // Admin can manage content
        } else {
            cout << "Enter user type (Standard/Premium): ";
            getline(cin, userType);

            if (userType == "Standard") {
                user = new User(userName);  // Create a standard user
            } else if (userType == "Premium") {
                user = new PremiumUser(userName);  // Create a premium user
            } else {
                cout << "Invalid user type. Defaulting to Standard." << endl;
                user = new User(userName);  // Default to standard if input is invalid
            }
            user->displayPrivileges();  // Display privileges of the created user
        }

        // Anime interaction for users
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
            user->addAnime(anime);
            break;
        }
        case '2':
            user->displayWatchlist();
            break;
        case '3':
            cout << "Exiting program." << endl;
            break;
        default:
            cout << "Invalid choice. Please enter a number between 1 and 3." << endl;
            break;
        }

        // Clean up user memory if it's not the admin
        if (user != &admin) {
            delete user;
        }

    } while (choice != '3');

    return 0;
}
