#include<array>
#include<iostream>
#include<random>

#include"encryption.h"

std::string xorEncryption(std::string password, std::string key)
{
    std::string encrypted_password = password; // We do this to ensure size of each string is identical
    
    for (int i = 0; i < password.length(); i++)
    {
        encrypted_password[i] = password[i] ^ key[i % key.length()];
    }

    return encrypted_password;
}

std::string caesarEncryption(std::string password, int& shift)
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
        encrypted_password += (password[i] += shift);
    }

    return encrypted_password;
}

std::string reverseCaesarEncryption(std::string encrypted_password, int& shift)
{
    std::string decrypted_password;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(48, 58);
    
    for (int i = 0; i < encrypted_password.length(); i++)
    {
        decrypted_password += (encrypted_password[i] -= shift);
    }

    return decrypted_password;
}
