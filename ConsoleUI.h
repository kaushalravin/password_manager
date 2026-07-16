#ifndef CONSOLEUI_H
#define CONSOLEUI_H

#include "PasswordManager.h"
#include <string>

class ConsoleUI {
private:
    PasswordManager& manager;

public:
    ConsoleUI(PasswordManager& m);
    void run();
    
private:
    void displayMenu();
    void addEntry();
    void readEntry();
    void deleteEntry();
    void modifyEntry();
};

#endif // CONSOLEUI_H
