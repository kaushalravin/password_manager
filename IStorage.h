#ifndef ISTORAGE_H
#define ISTORAGE_H

#include <string>
#include <vector>
#include "PasswordEntry.h"

class IStorage {
public:
    virtual ~IStorage() = default;
    
    virtual std::string readMasterPassword() = 0;
    virtual void saveMasterPassword(const std::string& encrypted_master) = 0;
    
    virtual void saveEntry(const PasswordEntry& entry) = 0;
    virtual bool getEntry(const std::string& appname, PasswordEntry& entry) = 0;
    virtual bool deleteEntry(const std::string& appname) = 0;
    virtual std::vector<PasswordEntry> getAllEntries() = 0;
};

#endif // ISTORAGE_H
