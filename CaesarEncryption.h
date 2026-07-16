#ifndef CAESARENCRYPTION_H
#define CAESARENCRYPTION_H

#include "IEncryption.h"

class CaesarEncryption : public IEncryption {
public:
    std::string encrypt(const std::string& data, const std::string& key) override;
    std::string decrypt(const std::string& data, const std::string& key) override;
};

#endif // CAESARENCRYPTION_H
