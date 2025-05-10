#include<iostream>
#include<iomanip>
#include<fstream>
using namespace std;


class Password{
    private:
        string username,
        password,
        appname,
        master,
        encrypt_username,
        encrypt_password,
        encrypt_appname,
        encrypt_master;
    public:
        Password(){
            master="";
            encrypt_master="";
            username="";
            password="";
            appname="";
            encrypt_username="";
            encrypt_password="";
            encrypt_appname="";
        }
         void getdata();
         void putdata();
         void encrypt(); 
         void decrypt();
         void writedata();
         void readdata();
         void getmaster();
         void encryption_master();
         void decryption_master();
         string return_master();
};

string Password::return_master(){
    return master;
}

void Password::encryption_master(){
    encrypt_master="";
    string salt="objectorientedprogramming";
    for (int i = 0; i < master.length(); i++) {
        char key_char = salt[i % salt.length()];
        char encrypted_char = ((master[i] + key_char) % 256);  // Use full ASCII
        encrypt_master += encrypted_char;
    }
}

void Password::decryption_master(){
    master="";
    string salt="objectorientedprogramming";
    for(int i = 0; i < encrypt_master.length(); i++) {
        char key_char = salt[i % salt.length()];
         char decrypted_char = ((encrypt_master[i] - key_char + 256) % 256);
         master+= decrypted_char;
}
}




void Password :: getdata(){
    cout<<"Enter the appname:";
    getline(cin,appname);
    cout<<"Enter the username:";
    getline(cin,username);
    cout<<"Enter the password:";
    getline(cin,password);
}

void Password :: putdata(){
    cout<<"Appname:"<<appname<<endl;
    cout<<"Username:"<<username<<endl;
    cout<<"Password:"<<password<<endl;
}
void Password::encrypt() {
    encrypt_appname = "";
    encrypt_username = "";
    encrypt_password = "";

    for (int i = 0; i < appname.length(); i++) {
        char key_char = master[i % master.length()];
        char encrypted_char = ((appname[i] + key_char) % 256);  // Use full ASCII
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


void Password::decrypt() {
    appname = "";
    username = "";
    password = "";

    for(int i = 0; i < encrypt_appname.length(); i++) {
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



void Password::writedata(){
    encrypt();
    fstream file;
    file.open("passwords.txt",ios::app);
    if(file.is_open()){
        file << (encrypt_appname) << "*" << (encrypt_username) << "*" << (encrypt_password) << "\n";
        cout<<"stored successfully\n";
    }
    else{
        cout<<"didnt store successfully\n";
    }
}

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
    getline(file,line);

    while (getline(file, line)) {
        size_t pos1 = line.find('*');
        size_t pos2 = line.find('*', pos1 + 1);

        encrypt_appname = (line.substr(0, pos1));
        encrypt_username = (line.substr(pos1 + 1, pos2 - pos1 - 1));
        encrypt_password = (line.substr(pos2 + 1));
        

        decrypt();

        if (appname == ap) {
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Appname not found\n";
    }
    file.close();
}



void Password::getmaster(){

    fstream file;
    file.open("passwords.txt",ios::in|ios::ate);

    if(file.is_open()){
        string a;
        if(file.tellg()==0){
            cout<<"Enter the master password:";
            getline(cin,a);
            master=a;
            encryption_master();
            fstream file1;
            file1.open("passwords.txt",ios::out);
            if(file1.is_open()){
                file1<<encrypt_master<<"\n";
                file1.close();
            }
            else{
                cout<<"file no opened\n";
            }
            
        }
        else{
            file.seekg(0);
            getline(file,a);
            encrypt_master=a;
            decryption_master(); 
        }
    }

    else{
        string a;
        cout<<"Enter the master password:";
            getline(cin,a);
            master=a;
            encryption_master();
            fstream file1;
            file1.open("passwords.txt",ios::out);
            if(file1.is_open())
                file1<<encrypt_master<<"\n";
            else
                cout<<"file has not opened properly\n";
            file1.close();

    }
    
    file.close();

}


