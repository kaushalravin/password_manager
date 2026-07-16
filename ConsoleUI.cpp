#include "ConsoleUI.h"
#include <iostream>
#include <limits>

ConsoleUI::ConsoleUI(PasswordManager& m) : manager(m) {}

void ConsoleUI::run() {
    std::string ch1 = "y";

    while (ch1 == "y") {
        std::string mas;
        if (manager.isNewSetup()) {
            std::cout << "No master password found. Enter a new master password to setup: ";
        } else {
            std::cout << "Enter master password: ";
        }
        std::getline(std::cin, mas);

        if (manager.initialize(mas)) {
            std::string ch2 = "y";
            while (ch2 == "y") {
                displayMenu();
                int n;
                std::cout << "Which options would you like to choose?: ";
                std::cin >> n;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                switch (n) {
                    case 1:
                        addEntry();
                        break;
                    case 2:
                        readEntry();
                        break;
                    case 3:
                        deleteEntry();
                        break;
                    case 4:
                        modifyEntry();
                        break;
                    default:
                        std::cout << "Invalid option\n";
                }

                std::cout << "Do you want to continue? Press y/n: ";
                std::getline(std::cin, ch2);
            }
        } else {
            std::cout << "Master Password is incorrect, To enter again, Press y: ";
            std::getline(std::cin, ch1);
        }
    }
}

void ConsoleUI::displayMenu() {
    std::cout << "\nOperations Available\n"
              << "1. To Input and Save a new app login (username & password)\n"
              << "2. To Read and Display stored entries from file\n"
              << "3. To Delete a specific app entry\n"
              << "4. To Modify a specific app entry\n";
}

void ConsoleUI::addEntry() {
    std::string appname, username, password;
    std::cout << "Enter the appname: ";
    std::getline(std::cin, appname);
    std::cout << "Enter the username: ";
    std::getline(std::cin, username);
    std::cout << "Enter the password: ";
    std::getline(std::cin, password);

    manager.addEntry(appname, username, password);
    std::cout << "Stored successfully\n";
}

void ConsoleUI::readEntry() {
    std::string appname;
    std::cout << "Enter the appname to search: ";
    std::getline(std::cin, appname);

    PasswordEntry entry;
    if (manager.getEntry(appname, entry)) {
        std::cout << "Appname: " << entry.appname << "\n";
        std::cout << "Username: " << entry.username << "\n";
        std::cout << "Password: " << entry.password << "\n";
    } else {
        std::cout << "Appname not found\n";
    }
}

void ConsoleUI::deleteEntry() {
    std::string appname;
    std::cout << "Enter the appname to delete: ";
    std::getline(std::cin, appname);

    if (manager.deleteEntry(appname)) {
        std::cout << "Entry deleted successfully.\n";
    } else {
        std::cout << "Appname not found or could not be deleted.\n";
    }
}

void ConsoleUI::modifyEntry() {
    std::string appname;
    std::cout << "Enter the appname to modify: ";
    std::getline(std::cin, appname);
    
    // Check if it exists before asking for new data
    PasswordEntry entry;
    if (!manager.getEntry(appname, entry)) {
         std::cout << "Appname not found.\n";
         return;
    }

    std::string username, password;
    std::cout << "Enter the modified data:\n";
    std::cout << "Enter the new username: ";
    std::getline(std::cin, username);
    std::cout << "Enter the new password: ";
    std::getline(std::cin, password);

    manager.modifyEntry(appname, username, password);
    std::cout << "Entry modified successfully.\n";
}
