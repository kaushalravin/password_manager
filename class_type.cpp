#include<iostream>
using namespace std;


class Password{
    private:
        string username,
        password,
        encrypt_username,
        encrypt_password;
    public:
         void getdata();
         void putdata();
         void encrypt();
         void decrypt();
         void writedata();
         void readdata();
};


void Password :: getdata(){
    cout<<"Enter the username";
    getline(cin,username);
    cout<<"Enter the psassword:";
    getline(cin,password);
}