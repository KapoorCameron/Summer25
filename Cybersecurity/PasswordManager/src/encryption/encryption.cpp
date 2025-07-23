#include <array>
#include <iostream>
#include <random>
#include <vector>

#include "encryption.h"

std::string xorEncryption(const std::string& password, const std::string& key)
{
    std::string encrypted_password = password; // We do this to ensure size of each string is identical
    
    for (int i = 0; i < password.length(); i++)
    {
        encrypted_password[i] = password[i] ^ key[i % key.length()];
    }

    return encrypted_password;
}

std::string caesarEncryption(const std::string& password, int shift)
{
    std::string encrypted_password;

    for (int i = 0; i < password.length(); i++)
    {
        encrypted_password += password[i] + shift;
    }

    return encrypted_password; 
}

std::string caesarDecryption(const std::string& encrypted_password, int& shift)
{
    std::string decrypted_password;
    
    for (int i = 0; i < encrypted_password.length(); i++)
    {
        decrypted_password += (encrypted_password[i] - shift);
    }

    return decrypted_password;
}

std::string xaesorEncryption(const std::string& password, int shift, const std::string& key)
{
    std::string caesarCipher = caesarEncryption(password, shift);
    std::string encrypted = xorEncryption(caesarCipher, key);
    return encrypted;
}

std::vector<std::vector<char>> gridEncryption(const std::string& password, int &shift, int &key, std::mt19937 &gen, int &length)
{
    std::vector<std::vector<char>> grid;

    std::string caesarCipher = caesarEncryption(password, shift);

    int charCount = 0;
    for (char c : caesarCipher)
    {
        charCount++;
    }

    std::cout << charCount << "\n\n";

    // even side lengths squared = number of valid coordinates -> for a given password.length(), we must ensure < even length squared:
    int valid_coordinates = 0;
    int count = 0;
    length = 0;

    while (valid_coordinates < password.length())
    {
        length += 2;
        count++;
        valid_coordinates = count * count;
    }

    std::cout << "Length: " << length << "\n\n";
    
    grid.assign(length, std::vector<char>(length));

    int index = 0;

    std::uniform_int_distribution<> dist(0, 255);

    for (int i = 0; i < length; i++)
    {
        for (int j = 0; j < length; j++)
        {
            if ((i + j) % key == 0)
            {
                if (index < password.length())
                {
                    grid[i][j] = caesarCipher[index];

                    index++;
                }

                else
                {

                }
            }

            else
            {
                grid[i][j] = static_cast<char>(dist(gen));
            }
        }
    }

    return grid;
}

std::string gridDecryption(const std::vector<std::vector<char>>& encrypted, int key, const int& length, const int& original_password_length)
{
    std::string decrypted;

    for (int i = 0; i < length; i++)
    {
        for (int j = 0; j < length; j++)
        {
            if ((i + j) % key == 0 && decrypted.length() < original_password_length)
            {
                decrypted += encrypted[i][j];
            }
        }
    }

    int charCount = 0;
    for (char c : decrypted)
    {
        charCount++;
    }

    std::cout << charCount << "\n\n";

    return decrypted;
}