#ifndef PASSWORDMANAGER_H
#define PASSWORDMANAGER_H

#include "IStorage.h"
#include "IEncryption.h"
#include <string>

class PasswordManager {
private:
    IStorage* storage;
    IEncryption* encryption;
    std::string masterPassword;
    const std::string SALT = "objectorientedprogramming";

public:
    PasswordManager(IStorage* storage, IEncryption* encryption);
    
    bool initialize(const std::string& enteredMaster);
    bool isNewSetup() const;
    void setupMasterPassword(const std::string& newMaster);
    
    void addEntry(const std::string& appname, const std::string& username, const std::string& password);
    bool getEntry(const std::string& appname, PasswordEntry& decryptedEntry);
    bool deleteEntry(const std::string& appname);
    void modifyEntry(const std::string& appname, const std::string& newUsername, const std::string& newPassword);
};

#endif // PASSWORDMANAGER_H
