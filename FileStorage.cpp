#include "FileStorage.h"
#include <fstream>
#include <iostream>

FileStorage::FileStorage(const std::string& file) : filename(file) {}

std::string FileStorage::readMasterPassword() {
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string master;
        if (std::getline(file, master)) {
            return master;
        }
    }
    return "";
}

void FileStorage::saveMasterPassword(const std::string& encrypted_master) {
    std::ofstream file(filename);
    if (file.is_open()) {
        file << encrypted_master << "\n";
    } else {
        std::cerr << "File not opened properly\n";
    }
}

void FileStorage::saveEntry(const PasswordEntry& entry) {
    std::ofstream file(filename, std::ios::app);
    if (file.is_open()) {
        file << entry.appname << "*" << entry.username << "*" << entry.password << "\n";
    } else {
        std::cerr << "File not opened properly\n";
    }
}

bool FileStorage::getEntry(const std::string& appname, PasswordEntry& entry) {
    std::ifstream file(filename);
    if (!file.is_open()) return false;

    std::string line;
    std::getline(file, line); // Skip master password

    while (std::getline(file, line)) {
        size_t pos1 = line.find('*');
        if (pos1 == std::string::npos) continue;
        size_t pos2 = line.find('*', pos1 + 1);
        if (pos2 == std::string::npos) continue;

        std::string current_appname = line.substr(0, pos1);
        if (current_appname == appname) {
            entry.appname = current_appname;
            entry.username = line.substr(pos1 + 1, pos2 - pos1 - 1);
            entry.password = line.substr(pos2 + 1);
            return true;
        }
    }
    return false;
}

bool FileStorage::deleteEntry(const std::string& appname) {
    std::ifstream file(filename);
    std::ofstream temp("temp.txt");

    if (!file.is_open() || !temp.is_open()) {
        return false;
    }

    std::string line;
    bool found = false;

    // Copy master password
    if (std::getline(file, line)) {
        temp << line << "\n";
    }

    while (std::getline(file, line)) {
        size_t pos1 = line.find('*');
        if (pos1 != std::string::npos) {
            std::string current_appname = line.substr(0, pos1);
            if (current_appname == appname) {
                found = true;
                continue; // Skip this line
            }
        }
        temp << line << "\n";
    }

    file.close();
    temp.close();

    if (found) {
        std::remove(filename.c_str());
        std::rename("temp.txt", filename.c_str());
        return true;
    } else {
        std::remove("temp.txt");
        return false;
    }
}

std::vector<PasswordEntry> FileStorage::getAllEntries() {
    std::vector<PasswordEntry> entries;
    std::ifstream file(filename);
    if (!file.is_open()) return entries;

    std::string line;
    std::getline(file, line); // Skip master password

    while (std::getline(file, line)) {
        size_t pos1 = line.find('*');
        if (pos1 == std::string::npos) continue;
        size_t pos2 = line.find('*', pos1 + 1);
        if (pos2 == std::string::npos) continue;

        PasswordEntry entry;
        entry.appname = line.substr(0, pos1);
        entry.username = line.substr(pos1 + 1, pos2 - pos1 - 1);
        entry.password = line.substr(pos2 + 1);
        entries.push_back(entry);
    }
    return entries;
}
