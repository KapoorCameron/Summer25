#include<iostream>
#include<string>

#include"program_loop.h"

void mainMenu()
{
    std::cout << "Phrasing baller!\n";
    
    while (true)
    {
        int action;
        std::cout << "Enter '1' to sign up, enter '2' to sign in: ";
        std::cin >> action;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clears all characters up until newline. If we only did "cin.ignore(...max())," it would ignore any future input as well 
        std::cout << "\n";

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
            std::cout << "Invalid input.\n";
            continue; 
        }
    }
}

void signUp()
{
        std::string username;
        std::cout << "Enter username: ";
        std::getline(std::cin, username);
        std::cout << "\n";

            while (true)
    {
        std::string password;
        std::cout << "Enter password: ";
        std::getline(std::cin, password);
        std::cout << "\n";

        std::string password_confirm;
        std::cout << "Confirm password: ";
        std::getline(std::cin, password_confirm);
        std::cout << "\n";

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
}

void signIn()
{

}