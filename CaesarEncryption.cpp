#include "CaesarEncryption.h"

std::string CaesarEncryption::encrypt(const std::string& data, const std::string& key) {
    std::string encrypted = "";
    if (key.empty() || data.empty()) return data;

    for (size_t i = 0; i < data.length(); i++) {
        char key_char = key[i % key.length()];
        char encrypted_char = ((data[i] + key_char) % 256);
        encrypted += encrypted_char;
    }
    return encrypted;
}

std::string CaesarEncryption::decrypt(const std::string& data, const std::string& key) {
    std::string decrypted = "";
    if (key.empty() || data.empty()) return data;

    for (size_t i = 0; i < data.length(); i++) {
        char key_char = key[i % key.length()];
        char decrypted_char = ((data[i] - key_char + 256) % 256);
        decrypted += decrypted_char;
    }
    return decrypted;
}
