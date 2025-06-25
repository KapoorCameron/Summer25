#pragma once

#include<random>
#include<string>

std::string xorEncryption(std::string password, std::string key);
std::string caesarEncryption(std::string password, int& shift);
std::string reverseCaesarEncryption(std::string encrypted_password, int& shift);