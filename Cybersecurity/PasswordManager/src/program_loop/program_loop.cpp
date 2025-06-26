#include<iostream>
#include<sstream>
#include<string>
#include<vector>

#include"../encryption/encryption.h"
#include"../key/key.h"
#include"program_loop.h"

std::string gridToString(const std::vector<std::vector<char>>& grid, int length)
{
    std::ostringstream oss;

    for (int i = 0; i < length; i++)
    {
        for (int j = 0; j < length; j++)
        {
            oss << grid[i][j];
        }

        oss << '\n';
    }

    return oss.str();
}

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

    while (true)
    {
        char method;
        std::cout << "Choose encryption. Enter '1' for XOR, '2' for Caesar, '3' for XaesOR, or '4' for grid: ";
        std::cin >> method;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << '\n';

        if (method == '1')
        {
            std::string key = makeKey();
            std::string encrypted_password = xorEncryption(password, key);
            std::string original_password = xorEncryption(encrypted_password, key);

            std::cout << "Key: " << key << "\n\n";
            std::cout << "Encrypted password: " << encrypted_password << "\n\n";
            std::cout << "Confirm original password: " << original_password << "\n\n";
        }

        else if (method == '2')
        {
            int shift = 0;
            std::cout << "Shift before encryption: " << shift << "\n\n";

            std::string encrypted_password = caesarEncryption(password, shift);
            std::string original_password = reverseCaesarEncryption(encrypted_password, shift);

            std::cout << "Shift after encryption: " << shift << "\n\n";
            std::cout << "Encrypted password: " << encrypted_password << "\n\n";
            std::cout << "Confirm original password: " << original_password << "\n\n";
        }

        else if (method == '4')
        {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dist(2, 4);

            int key = dist(gen);

            std::random_device rd2;
            std::mt19937 gen2(rd2());

            int length;
            std::vector<std::vector<char>> encrypted_password = gridEncryption(password, key, gen2, length);

            std::cout << "Encrypted password: \n\n" << gridToString(encrypted_password, length) << "\n\n";

            std::string original_password = gridDecryption(encrypted_password, key, length);

            std::cout << "Confirm original password: " << original_password << "\n\n";
        }

        else
        {
            std::cout << "Invalid input.\n\n";
            continue;
        }
    }
    
}

void signIn()
{

}

void mainMenu()
{
    while (true)
    {
        char input;
        std::cout << "Enter '1' to sign up, or enter '2' to sign in: ";
        std::cin >> input;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clears all characters up until newline. If we only did "cin.ignore(...max())," it would ignore any future input as well 
        std::cout << '\n';

        if (input == '1')
        {
            signUp();
        }

        else if (input == '2')
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

