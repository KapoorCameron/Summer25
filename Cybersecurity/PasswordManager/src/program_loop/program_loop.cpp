#include<cstdint>
#include<fstream>
#include<iostream>
#include<sstream>
#include<string>
#include<vector>

#include"../auth_read_write/auth_read_write.h"
#include"../encoding/encoding.h"
#include"../encryption/encryption.h"
#include"../key/key.h"
#include"program_loop.h"

void writeCredentials(std::string& credentials)
{

}

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

    while (true)
    {
        std::cout << "Enter username: ";
        std::getline(std::cin, username);
        std::cout << '\n';

        if (username.empty() || (username.find(' ') != std::string::npos && username.find_first_not_of(' ') == std::string::npos))
        {
            std::cout << "Invalid username.\n\n";
            continue;
        }

        break;
    }

    std::string password;

    while (true)
    {
        std::cout << "Enter password: ";
        std::getline(std::cin, password);
        std::cout << '\n';

        if (password.empty())
        {
            std::cout << "Invalid input.\n\n";
            continue;
        }

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

    std::string encrypted_password;

    while (true)
    {
        std::string method;
        std::cout << "Choose encryption. Enter '1' for XOR, '2' for Caesar, '3' for XaesOR, or '4' for grid: ";
        std::getline(std::cin, method);
        std::cout << '\n';

        // XOR
        if (method == "1")
        {
            std::string key = makeKey();
            encrypted_password = xorEncryption(password, key);
            std::string original_password = xorEncryption(encrypted_password, key);

            std::cout << "Key: " << key << "\n\n";
            std::cout << "Encrypted password: " << encrypted_password << "\n\n";
            std::cout << "Confirm original password: " << original_password << "\n\n";

            std::string encoded_password;

            // writeCredentials(method, username, encrypted, key)
            std::ostringstream oss; 
            oss << method << ", " << username << ", " << encrypted_password << ", " << key <<";";
        }

        // CaesarCipher
        else if (method == "2")
        {
            int shift = 0;
            std::cout << "Shift before encryption: " << shift << "\n\n";

            encrypted_password = caesarEncryption(password, shift);
            std::string original_password = caesarDecryption(encrypted_password, shift);

            std::cout << "Shift after encryption: " << shift << "\n\n";
            std::cout << "Encrypted password: " << encrypted_password << "\n\n";
            std::cout << "Confirm original password: " << original_password << "\n\n";
        }

        // XaesOR
        else if (method == "3")
        {
            int shift = 0;
            std::string key = makeKey();

            encrypted_password = xaesorEncryption(password, shift, key);
            std::string original_password = caesarDecryption(xorEncryption(encrypted_password, key), shift);

            std::cout << "Encrypted password: " << encrypted_password << "\n\n";
            std::cout << "Confirm original password: " << original_password << "\n\n";
        }

        // Grid
        else if (method == "4")
        {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dist(2, 4);

            int key = dist(gen);

            // we need to keep track of the seed used for our MT so when we store the password and relevant data for sign in functionality, we can compare saved and entered encrypted passwords:
            std::random_device rd2;
            uint32_t seed = rd2(); // write this to file with method, username, password, etc.
            std::mt19937 gen2(seed);

            int shift = 0;
            int length;
            int original_password_length = password.length();

            std::vector<std::vector<char>> encrypted_password = gridEncryption(password, shift, key, gen2, length);
            std::string original_password = caesarDecryption(gridDecryption(encrypted_password, key, length, original_password_length), shift);

            std::cout << "Encrypted password: \n\n" << gridToString(encrypted_password, length) << "\n\n";
            std::cout << "Confirm original password: " << original_password << "\n\n";
        }

        else
        {
            std::cout << "Invalid input.\n\n";
            continue;
        }

        break;
    }
    
}

void signIn()
{
    std::string password;
    std::cout << "Simple encoding/decoding test: \n\n(NOT TIED TO ACTUAL CREDENTIALS YET)\n\n";

    std::cout << "Enter password: ";
    std::getline(std::cin, password);
    std::cout << '\n';

    std::string encoded = base64Encode(password);

    std::cout << "Encoded password: " << encoded << "\n\n";
    std::cout << "Decoded/original password: " << base64Decode(encoded) << "\n\n";
}

void mainMenu()
{
    while (true)
    {
        std::string input;
        std::cout << "Enter '1' to sign up, or enter '2' to sign in: ";
        std::getline(std::cin, input);
        std::cout << '\n';

        if (input == "1")
        {
            signUp();
        }

        else if (input == "2")
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

