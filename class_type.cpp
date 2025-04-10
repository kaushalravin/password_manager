#include<iostream>
using namespace std;


class Password{
    private:
        string username,
        password,
        appname,
        encrypt_username,
        encrypt_password,
        encrypt_appname;
    public:
        Password(){
            username="";
            password="";
            appname="";
            encrypt_username="";
            encrypt_password="";
            encrypt_appname="";
        }
         void getdata();
         void putdata();
         void encrypt(string master);
         void decrypt(string master);
         void writedata();
         void readdata();
};


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
    cout<<"Password:"<<endl;
}

void Password :: encrypt(string master){
    char inter;
    string salt1="kaushal";
    string salt2="rangesh";
    string salt3="krishna";
    string salt4="sanjay";

    for (int i = 0; i < (int)appname.length(); ++i) {
        int sum = master[i % master.length()]
                + salt1[i % salt1.length()]
                + salt2[i % salt2.length()]
                + salt3[i % salt3.length()]
                + salt4[i % salt4.length()]
                + appname[i];
        char c = 'a' + (sum % 26);
        encrypt_appname += c;
    }



    for (int i = 0; i < (int)username.length(); ++i) {
        int sum = master[i % master.length()]
                + salt1[i % salt1.length()]
                + salt2[i % salt2.length()]
                + salt3[i % salt3.length()]
                + salt4[i % salt4.length()]
                + username[i];
        char c = 'a' + (sum % 26);
        encrypt_username += c;
    }
    


    for (int i = 0; i < (int)password.length(); ++i) {
        int sum = master[i % master.length()]
                + salt1[i % salt1.length()]
                + salt2[i % salt2.length()]
                + salt3[i % salt3.length()]
                + salt4[i % salt4.length()]
                + password[i];
        char c = 'a' + (sum % 26);
        encrypt_password += c;
    }
}
