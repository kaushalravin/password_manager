#include<iostream>
#include<D:\kaushal notes\password_manager_folder\password_manager\class_type.cpp>
using namespace std;


int main(){
    Password a;
    string mas;
    cout<<"enter master password:";
    getline(cin,mas);
    a.getmaster();
    string master=a.return_master();
    if(master==mas){
    a.getdata();
    a.writedata();
    a.readdata();
    a.putdata();
    a.delete_line();
    a.modify();}
 
    return 0;
}