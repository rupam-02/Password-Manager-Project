#include <bits/stdc++.h>
using namespace std;

class PasswordManager
{
public:
    string filename;
    string username;

private:
    string password;
    string encrypt(const string &text)
    {
        /*
        This takes a password (a string) and returns the encrypted form of the
        password.

        We will use the following encryption algorithm:
        The XOR operator (^) in C++ takes two char arguments and returns a char.
        For every character in the input string, apply the XOR operator ^ with the
        character ‘2’. For example: str[i] ^ ‘2’;
        */

        string encrypted_text;
        for (int i = 0; i < text.length(); i++)
        {
            encrypted_text.push_back(text[i] ^ '2');
        }
        return encrypted_text;
    }

    string decrypt(const string &text)
    {
        string decrypted_text;
        for (int i = 0; i < text.length(); i++)
        {
            decrypted_text.push_back(text[i] ^ '2');
        }
        return decrypted_text;
    }

    bool verifyPassword(string text)
    {
        /*
        This takes a string (a password) and returns true if it meets the
        following criteria:
        • it is at least 8 characters long
        • it contains at least one letter
        • it contains at least one digit
        • it contains at least one of these four characters: <, >, @, !
        Otherwise it returns false.
        */

        // length check
        if (text.length() < 8)
        {
            cout << "Password must contain atleast 8 characters" << endl;
            return false;
        }

        // letter check
        bool check = 0;
        for (int i = 0; i < text.length(); i++)
        {
            if ((text[i] >= 'A' && text[i] <= 'Z') || (text[i] >= 'a' && text[i] <= 'z'))
                check = 1;
        }
        if (!check)
        {
            cout << "Password must contain a letter\n";
            return false;
        }

        // digit check
        check = 0;
        for (int i = 0; i < text.length(); i++)
        {
            if ((text[i] >= '0' && text[i] <= '9'))
                check = 1;
        }
        if (!check)
        {
            cout << "Password must contain a digit\n";
            return false;
        }

        // special char check
        for (char ch : text)
        {
            if (ch == '>' || ch == '<' || ch == '@' || ch == '!')
                return true;
        }
        cout << "Password must contain atleast one of these special characters - <,>,@,!\n";
        return false;
    }

public:
    PasswordManager(const string &file, const string &name, const string &passwd)
    {
        filename = file;
        username = name;
        if (verifyPassword(passwd))
            password = encrypt(passwd);
        else
        {
            password = encrypt("user@1234");
            cout << "\"user@1234\" set as default password because your password was invalid\n";
        }
    }

    // Destructor
    ~PasswordManager()
    {
        cout << "Account with Username " << username << " logged out.\nThank you" << endl;
    }
    /* (a setter function) takes a string (an encrypted password) and stores it in the member variable. */
    void setEncryptedPassword(string text)
    {
        password = text;
    }

    /* (a getter function) returns the value of the encrypted password stored in the member variable. */
    string getPassword()
    {
        return password;
    }

    /*takes a string (a proposed password). If it meets the criteria in verifyPassword, it encrypts the password and stores it in the member variable and returns true. Otherwise returns false. */
    bool setNewPassword(string text)
    {
        if (verifyPassword(text))
        {
            setEncryptedPassword(encrypt(text));
            return true;
        }
        else
        {
            return false;
        }
    }

    /*takes a string (a password) and returns true if, once encrypted, it matches the encrypted string stored in the the member variable. Else returns false.*/
    bool validatePassword(string text)
    {
        string encrypted_text = encrypt(text);
        if (encrypted_text == password)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    void saveToFile()
    {
        ofstream outFile(filename);
        outFile << username << "," << (password) << ","
                << "\n";
        outFile.close();
    }
};

main()
{
    cout << "Create your account\n";

    string username;
    cout << "Username - ";
    cin >> username;

    cout << "Password must satisfy the conditions below - \n";
    cout << "It is at least 8 characters long\nIt contains at least one letter\nIt contains at least one digit\nIt contains at least one of these four characters: <, >, @, !\n";

    string password;
    cout << "Password - ";
    cin >> password;

    PasswordManager pwd("password.txt", username, password);
    cout << "\n\nPassword Manager\nUsername - " << username << "\n";

    cout << "Log in? (press 1 for yes and 0 for no) - ";
    bool login;
    cin >> login;
    if (!login)
    {
        return 0;
    }
    while (true)
    {
        // string username, password;
        cout << "Username - ";
        cin >> username;
        cout << "Password - ";
        cin >> password;
        if (username == pwd.username && pwd.validatePassword(password))
        {
            cout << "\nLogin Successfull\n";
            break;
        }
        else
        {
            cout << "Incorrect Username or Password. Try Again \n";
        }
    }
    int choice;
    do
    {
        cout << "\n1. Change Password\n2. Validate Password\n3. View Password\n4. Save Password\n5. Exit/Logout\n";
        cout << "---------------------------------------------------------------------\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            cout << "Enter Previous Password - ";
            string prevpwd;
            cin >> prevpwd;
            string passwd;
            if (pwd.validatePassword(prevpwd))
            {
                cout << "Password must satisfy the conditions below - \n";
                cout << "It is at least 8 characters long\nIt contains at least one letter\nIt contains at least one digit\nIt contains at least one of these four characters: <, >, @, !\n";
                cout << "Enter your new password - ";
                cin >> passwd;
                pwd.setNewPassword(passwd);
            }
        }
        break;
        case 2:
        {
            string demopwd;
            cout << "Enter your password - ";
            cin >> demopwd;
            if (!pwd.validatePassword(demopwd))
            {
                cout << "Incorrect Password.\n";
            }
            else
            {
                cout << "Correct Password\n";
            }
        }
        break;
        case 3:
        {
            cout << "Your Password (shown in encrypted form) - " << pwd.getPassword() << endl;
        }
        break;
        case 4:
        {
            pwd.saveToFile();
        }
        break;
        case 5:
        {
            cout << "Exiting...\n";
        }
        break;
        default:
            cout << "Invalid choice!\n";
        }
    } while (choice != 5);

    return 0;
}