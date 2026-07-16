#include <iostream>
#include "class_type.cpp" // Ideally, use a header file, but keeping it as per your prompt

using namespace std;

int main() {
    Password a;
    string mas;
    string ch1, ch2;
    ch1 = "y";

    while (ch1 == "y") {
        cout << "enter master password:";
        getline(cin, mas);  // use getline for full line input
        a.getmaster();
        string master = a.return_master();

        if (master == mas) {
            ch2 = "y";
            while (ch2 == "y") {
                cout << "\nOperations Available\n"
                     << "1. To Input and Save a new app login (username & password)\n"
                     << "2. To Read and Display stored entries from file\n"
                     << "3. To Delete a specific app entry\n"
                     << "4. To Modify a specific app entry\n";

                int n;
                cout << "Which options would you like to choose?:";
                cin >> n;
                cin.ignore(); // ignore the leftover newline from cin

                switch (n) {
                    case 1:
                        a.getdata();
                        a.writedata();
                        break;
                    case 2:
                        a.readdata();
                        a.putdata();
                        break;
                    case 3:
                        a.delete_line();
                        break;
                    case 4:
                         a.modify();
                        break;
                    
                    default:
                        cout << "Invalid option\n";
                }

                cout << "Do you want to continue?Press y/n:";
                getline(cin, ch2);
            }
        } else {
            cout << "Master Password is incorrect";
            cout << ",To enter again, Press y:";
            getline(cin, ch1);
        }
    }

    return 0;
}
