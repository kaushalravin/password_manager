#include<iostream>
#include<D:\kaushal notes\password_manager_folder\password_manager\class_type.cpp>
using namespace std;


int main(){
    Password a;
    string mas;
    ch1='y';
    while(ch1=='y'){
        cout<<"enter master password:";
        getline(cin,mas);
        a.getmaster();
        string master=a.return_master();
        if(master==mas){
            ch2='y';
            while(ch2=='y'){
                cout<<"\nOperations Available\n1.To Input username, password for an app\n2.To Write encrypted data to file\n3.To Read and decrypt specific entry from file\n4.To Display decrypted app, username and password\n5.To Delete specific app entry\n6.ToModify a specific app entry\n";
                int n;
                cout<<"Which options would you like to choose?:";
                cin>>n;
                switch(n){
                    case 1:
                        a.getdata();
                        break;
                    case 2:
                        a.writedata();
                        break;
                    case 3:
                        a.readdata();
                        break;
                    case 4:
                        a.putdata();
                        break;
                    case 5:
                        a.delete_line();
                        break;
                    case 6:
                        a.modify();
                        break;
                    default:
                        cout<<"Invalid option";
                }
                cout<<"Do you want to continue?Press y/n:";
                cin>>ch2;
            }
        }
        else{
            cout<<"Master Password is incorrect";
            cout<<"To enter again, Press y:";
            cin>>ch1;
            }
    }
    return 0;
}
