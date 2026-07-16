#ifndef IENCRYPTION_H
#define IENCRYPTION_H

#include <string>

class IEncryption {
public:
    virtual ~IEncryption() = default;
    
    virtual std::string encrypt(const std::string& data, const std::string& key) = 0;
    virtual std::string decrypt(const std::string& data, const std::string& key) = 0;
};

#endif // IENCRYPTION_H
