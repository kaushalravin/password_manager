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
         void getdata();
         void putdata();
         void encrypt();
         void decrypt();
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