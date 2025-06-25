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



