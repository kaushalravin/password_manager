#include "FileStorage.h"
#include "CaesarEncryption.h"
#include "PasswordManager.h"
#include "ConsoleUI.h"

int main() {
    FileStorage storage("passwords.txt");
    CaesarEncryption encryption;
    PasswordManager manager(&storage, &encryption);
    
    ConsoleUI ui(manager);
    ui.run();

    return 0;
}
