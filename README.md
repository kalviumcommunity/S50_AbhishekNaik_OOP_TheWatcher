# S50_AbhishekNaik_OOP_TheWatcher

## Project Description

Develop a console-based application that showcases the core features of a Watchlist Tracker on CLI. This should include basic Create, Read, Update, Delete (CRUD) operations for user profiles, and Add, Rate, Manage, Remove functionalities for watched anime. The project will demonstrate key Object-Oriented Programming (OOP) concepts by arranging the system around multiple classes and how they interact with each other.

## Features to Be Implemented

### User Management
- Add a new User.
- Read and Display user.
- Update user details.
- Delete user.

### Anime Management
- Add an anime to the user's watchlist.
- Rate anime from 1 to 10.
- Remove anime from the user's watchlist.
- Display all the anime the user has watched and the rating given by them.

## Programming Language

The programming language used will be C++.

## Application of OOP Concepts

### Classes and Objects
- **Classes:** There will be classes like `User`, `Anime`, and `Watchlist`.
- **Objects:** The classes will instantiate to form objects representing individual users, anime entries, and watchlists.

### This Pointer
The `this` pointer will be used inside methods belonging to the class to refer to the current instance of the class, ensuring that instance variables are correctly accessed and modified.

### Four Pillars of OOP

- **Encapsulation:** All class attributes should be declared private, with public getter and setter methods to get and set the values. This will protect the integrity of the data and provide encapsulation of the internal state of objects from external modifications.

- **Inheritance:** Inheritance can be used where necessary, through specialized classes. For example, in the future, if I make a feature inheriting from the base class `User`, adding additional features to that.

- **Polymorphism:** Polymorphism will be demonstrated through method overloading and overriding. Different forms of a method for adding or removing anime might handle various scenarios of input.

- **Abstraction:** Abstract classes and interfaces will be used to define common methods that need to be implemented in subclasses. For example, a user-defined abstract class named `UserActions` may define common methods to be implemented in the `User` class, like `addAnime`, `rateAnime`, and `removeAnime`.
