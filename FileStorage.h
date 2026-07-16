#ifndef FILESTORAGE_H
#define FILESTORAGE_H

#include "IStorage.h"
#include <string>

class FileStorage : public IStorage {
private:
    std::string filename;
public:
    FileStorage(const std::string& file = "passwords.txt");
    
    std::string readMasterPassword() override;
    void saveMasterPassword(const std::string& encrypted_master) override;
    
    void saveEntry(const PasswordEntry& entry) override;
    bool getEntry(const std::string& appname, PasswordEntry& entry) override;
    bool deleteEntry(const std::string& appname) override;
    std::vector<PasswordEntry> getAllEntries() override;
};

#endif // FILESTORAGE_H
