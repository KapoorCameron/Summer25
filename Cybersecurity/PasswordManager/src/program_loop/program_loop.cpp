#include<iostream>
#include<string>

#include"../encryption/encryption.h"
#include"../key/key.h"
#include"program_loop.h"

void signUp()
{
    std::string username;
    std::cout << "Enter username: ";
    std::getline(std::cin, username);
    std::cout << '\n';

    std::string password;


    while (true)
    {
        std::cout << "Enter password: ";
        std::getline(std::cin, password);
        std::cout << '\n';

        std::string password_confirm;
        std::cout << "Confirm password: ";
        std::getline(std::cin, password_confirm);
        std::cout << '\n';

        if (password == password_confirm)
        {
            std::cout << "Passwords match.\n\n";
            // encrypt(password);
            // write username and encrypted password to credentials.txt
            break;
        }

        else
        {
            std::cout << "Passwords didn't match.\n\n";
            continue;
        }
    }

    std::string method;
    std::cout << "Choose encryption. Enter '1' for XOR, or enter '2' for Caesar: ";
    std::cin >> method;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << '\n';

    std::string key = makeKey();
    std::string encrypted_password = xorEncryption(password, key);
    std::string original_password = xorEncryption(encrypted_password, key);


    std::cout << "Key: " << key << "\n\n";
    std::cout << "Encrypted password: " << encrypted_password << "\n\n";
    std::cout << "Confirm original password: " << original_password << "\n\n";
}

void signIn()
{

}

void mainMenu()
{
    while (true)
    {
        std::string input;
        std::cout << "Enter '1' to sign up, or enter '2' to sign in: ";
        std::cin >> input;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clears all characters up until newline. If we only did "cin.ignore(...max())," it would ignore any future input as well 
        std::cout << '\n';

        int action;
        try 
        {
            action = std::stoi(input); // string to int
        }

        catch (...) // catches ANY acception
        {
            std::cout << "Invalid input.\n\n";
            continue;
        }

        if (action == 1)
        {
            signUp();
        }

        else if (action == 2)
        {
            signIn();
        }

        else
        {
            std::cout << "Invalid input.\n\n";
            continue; 
        }
    }
}

