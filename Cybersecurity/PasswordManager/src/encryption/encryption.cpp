#include<array>
#include<iostream>
#include<random>
#include<vector>

#include"encryption.h"

std::string xorEncryption(const std::string& password, std::string key)
{
    std::string encrypted_password = password; // We do this to ensure size of each string is identical
    
    for (int i = 0; i < password.length(); i++)
    {
        encrypted_password[i] = password[i] ^ key[i % key.length()];
    }

    return encrypted_password;
}

std::string caesarEncryption(const std::string& password, int& shift)
{
    std::string encrypted_password;

    // create random num engine:
    std::random_device rd;
    std::mt19937 gen(rd());

    // choose range:
    std::uniform_int_distribution<> dist(48, 58);

    // RNG to assign value to shift:
    shift = dist(gen);

    for (int i = 0; i < password.length(); i++)
    {
        encrypted_password += password[i] + shift;
    }

    return encrypted_password;
}

std::string reverseCaesarEncryption(const std::string& encrypted_password, int& shift)
{
    std::string decrypted_password;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(48, 58);
    
    for (int i = 0; i < encrypted_password.length(); i++)
    {
        decrypted_password += (encrypted_password[i] - shift);
    }

    return decrypted_password;
}

std::vector<std::vector<char>> gridEncryption(const std::string& password, int key, std::mt19937 gen, int& length)
{
    std::vector<std::vector<char>> grid;

    // even side lengths squared = number of valid coordinates -> for a given password.length(), we must ensure < even length squared

    // password must be at least 4 chars, unless we hardcode (b/c of n^2 logic.)
    int valid_coordinates = 4;
    int count = 2;
    length = 4;

    while (valid_coordinates < password.length())
    {
        length += 2;
        count++;
        valid_coordinates = count * count;
    }
    
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
                    grid[i][j] = password[index];

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

std::string gridDecryption(const std::vector<std::vector<char>>& encrypted, int key, int length)
{
    std::string decrypted;

    for (int i = 0; i < length; i++)
    {
        for (int j = 0; j < length; j++)
        {
            if ((i + j) % key == 0)
            {
                decrypted += encrypted[i][j];
            }
        }
    }

    return decrypted;
}