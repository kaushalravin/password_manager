#include<iostream>
#include<iomanip>
#include<fstream>
using namespace std;

// Password class handles storage, encryption, decryption, 
// and file operations for managing user passwords
class Password {
private:
    // User input fields
    string username, password, appname, master;

    // Encrypted versions of data
    string encrypt_username, encrypt_password, encrypt_appname, encrypt_master;

public:
    // Constructor to initialize all member variables
    Password() {
        master = "";
        encrypt_master = "";
        username = "";
        password = "";
        appname = "";
        encrypt_username = "";
        encrypt_password = "";
        encrypt_appname = "";
    }

    // Function declarations
    void getdata();               // Get app, username and password from user
    void putdata();              // Display decrypted app, username and password
    void encrypt();              // Encrypt user data using master password,no need to use in main function
    void decrypt();              // Decrypt user data using master password,,no need to use in main function
    void writedata();           // Write encrypted data to file
    void readdata();            // Read and decrypt specific entry from file
    void getmaster();           // Handle master password logic (create/read),use whenever a new object is created
    void encryption_master();   // Encrypt master password using a salt,no need to use in main function
    void decryption_master();   // Decrypt stored master password,no need to use in main function
    void delete_line();         // Delete specific app entry
    void modify();              // Modify a specific app entry
    string return_master();     // Return current master password,used to check if the entered password is correct or not
};

// Returns the master password
string Password::return_master() {
    return master;
}

// Encrypts the master password using a fixed salt
void Password::encryption_master() {
    encrypt_master = "";
    string salt = "objectorientedprogramming";
    for (int i = 0; i < master.length(); i++) {
        char key_char = salt[i % salt.length()];
        char encrypted_char = ((master[i] + key_char) % 256);
        encrypt_master += encrypted_char;
    }
}

// Decrypts the stored encrypted master password
void Password::decryption_master() {
    master = "";
    string salt = "objectorientedprogramming";
    for (int i = 0; i < encrypt_master.length(); i++) {
        char key_char = salt[i % salt.length()];
        char decrypted_char = ((encrypt_master[i] - key_char + 256) % 256);
        master += decrypted_char;
    }
}

// Get application credentials from the user
void Password::getdata() {
    cout << "Enter the appname: ";
    getline(cin, appname);
    cout << "Enter the username: ";
    getline(cin, username);
    cout << "Enter the password: ";
    getline(cin, password);
}

// Display decrypted credentials
void Password::putdata() {
    cout << "Appname: " << appname << endl;
    cout << "Username: " << username << endl;
    cout << "Password: " << password << endl;
}

// Encrypts appname, username, and password using master password
void Password::encrypt() {
    encrypt_appname = "";
    encrypt_username = "";
    encrypt_password = "";

    for (int i = 0; i < appname.length(); i++) {
        char key_char = master[i % master.length()];
        char encrypted_char = ((appname[i] + key_char) % 256);
        encrypt_appname += encrypted_char;
    }

    for (int i = 0; i < username.length(); i++) {
        char key_char = master[i % master.length()];
        char encrypted_char = ((username[i] + key_char) % 256);
        encrypt_username += encrypted_char;
    }

    for (int i = 0; i < password.length(); i++) {
        char key_char = master[i % master.length()];
        char encrypted_char = ((password[i] + key_char) % 256);
        encrypt_password += encrypted_char;
    }
}

// Decrypts the encrypted fields using master password
void Password::decrypt() {
    appname = "";
    username = "";
    password = "";

    for (int i = 0; i < encrypt_appname.length(); i++) {
        char key_char = master[i % master.length()];
        char decrypted_char = ((encrypt_appname[i] - key_char + 256) % 256);
        appname += decrypted_char;
    }

    for (int i = 0; i < encrypt_username.length(); i++) {
        char key_char = master[i % master.length()];
        char decrypted_char = ((encrypt_username[i] - key_char + 256) % 256);
        username += decrypted_char;
    }

    for (int i = 0; i < encrypt_password.length(); i++) {
        char key_char = master[i % master.length()];
        char decrypted_char = ((encrypt_password[i] - key_char + 256) % 256);
        password += decrypted_char;
    }
}

// Write encrypted credentials to file
void Password::writedata() {
    encrypt();
    fstream file;
    file.open("passwords.txt", ios::app);
    if (file.is_open()) {
        file << encrypt_appname << "*" << encrypt_username << "*" << encrypt_password << "\n";
        cout << "Stored successfully\n";
    } else {
        cout << "Did not store successfully\n";
    }
}

// Read and decrypt credentials for a specific appname
void Password::readdata() {
    cout << "Enter the appname to search: ";
    string ap;
    getline(cin, ap);

    ifstream file("passwords.txt");
    if (!file.is_open()) {
        cout << "File not opened properly\n";
        return;
    }

    string line;
    bool found = false;

    getline(file, line); // Skip master line

    while (getline(file, line)) {
        size_t pos1 = line.find('*');
        size_t pos2 = line.find('*', pos1 + 1);

        encrypt_appname = line.substr(0, pos1);
        encrypt_username = line.substr(pos1 + 1, pos2 - pos1 - 1);
        encrypt_password = line.substr(pos2 + 1);

        decrypt();

        if (appname == ap) {
            found = true;
            putdata();
            break;
        }
    }

    if (!found) {
        cout << "Appname not found\n";
    }
    file.close();
}

// Handle master password setup or decryption based on file content
void Password::getmaster() {
    fstream file;
    file.open("passwords.txt", ios::in | ios::ate);

    if (file.is_open()) {
        string a;
        if (file.tellg() == 0) {
            // File is empty, set new master password
            cout << "Enter the master password: ";
            getline(cin, a);
            master = a;
            encryption_master();
            fstream file1;
            file1.open("passwords.txt", ios::out);
            if (file1.is_open()) {
                file1 << encrypt_master << "\n";
                file1.close();
            } else {
                cout << "File not opened\n";
            }
        } else {
            // Read existing encrypted master password
            file.seekg(0);
            getline(file, a);
            encrypt_master = a;
            decryption_master();
        }
    } else {
        // File couldn't open, create new file and master
        string a;
        cout << "Enter the master password: ";
        getline(cin, a);
        master = a;
        encryption_master();
        fstream file1;
        file1.open("passwords.txt", ios::out);
        if (file1.is_open())
            file1 << encrypt_master << "\n";
        else
            cout << "File has not opened properly\n";
        file1.close();
    }

    file.close();
}

// Delete a specific app's credentials
void Password::delete_line() {
    cout << "Enter the appname to delete: ";
    string ap;
    getline(cin, ap);

    ifstream file("passwords.txt");
    ofstream temp("temp.txt");

    if (!file.is_open() || !temp.is_open()) {
        cout << "File error.\n";
        return;
    }

    string line;
    bool found = false;

    // Copy master password
    if (getline(file, line)) {
        temp << line << "\n";
    }

    while (getline(file, line)) {
        size_t pos1 = line.find('*');
        size_t pos2 = line.find('*', pos1 + 1);

        encrypt_appname = line.substr(0, pos1);
        encrypt_username = line.substr(pos1 + 1, pos2 - pos1 - 1);
        encrypt_password = line.substr(pos2 + 1);

        decrypt();

        if (appname == ap) {
            found = true;
            continue; // Skip writing this line (deleting it)
        }

        temp << line << "\n"; // Write other lines
    }

    file.close();
    temp.close();

    if (found) {
        remove("passwords.txt");
        rename("temp.txt", "passwords.txt");
        cout << "Entry deleted successfully.\n";
    } else {
        cout << "Appname not found.\n";
        remove("temp.txt");
    }
}

// Modify an existing entry by first deleting and then rewriting it
void Password::modify() {
    delete_line();               // Delete existing entry
    cout << "Enter the modified data:\n";
    getdata();                   // Get updated info
    writedata();                 // Write updated info
}
