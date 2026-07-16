#include "PasswordManager.h"
#include <iostream>

PasswordManager::PasswordManager(IStorage* s, IEncryption* e) : storage(s), encryption(e) {}

bool PasswordManager::isNewSetup() const {
    return storage->readMasterPassword().empty();
}

void PasswordManager::setupMasterPassword(const std::string& newMaster) {
    masterPassword = newMaster;
    std::string encryptedMaster = encryption->encrypt(newMaster, SALT);
    storage->saveMasterPassword(encryptedMaster);
}

bool PasswordManager::initialize(const std::string& enteredMaster) {
    if (isNewSetup()) {
        setupMasterPassword(enteredMaster);
        return true;
    }

    std::string encryptedStoredMaster = storage->readMasterPassword();
    std::string decryptedStoredMaster = encryption->decrypt(encryptedStoredMaster, SALT);

    if (enteredMaster == decryptedStoredMaster) {
        masterPassword = enteredMaster;
        return true;
    }
    return false;
}

void PasswordManager::addEntry(const std::string& appname, const std::string& username, const std::string& password) {
    PasswordEntry encryptedEntry;
    encryptedEntry.appname = encryption->encrypt(appname, masterPassword);
    encryptedEntry.username = encryption->encrypt(username, masterPassword);
    encryptedEntry.password = encryption->encrypt(password, masterPassword);
    
    storage->saveEntry(encryptedEntry);
}

bool PasswordManager::getEntry(const std::string& appname, PasswordEntry& decryptedEntry) {
    std::string encryptedAppnameToSearch = encryption->encrypt(appname, masterPassword);
    PasswordEntry encryptedEntry;
    
    if (storage->getEntry(encryptedAppnameToSearch, encryptedEntry)) {
        decryptedEntry.appname = encryption->decrypt(encryptedEntry.appname, masterPassword);
        decryptedEntry.username = encryption->decrypt(encryptedEntry.username, masterPassword);
        decryptedEntry.password = encryption->decrypt(encryptedEntry.password, masterPassword);
        return true;
    }
    return false;
}

bool PasswordManager::deleteEntry(const std::string& appname) {
    std::string encryptedAppname = encryption->encrypt(appname, masterPassword);
    return storage->deleteEntry(encryptedAppname);
}

void PasswordManager::modifyEntry(const std::string& appname, const std::string& newUsername, const std::string& newPassword) {
    deleteEntry(appname);
    addEntry(appname, newUsername, newPassword);
}
