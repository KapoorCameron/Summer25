#pragma once

#include<random>
#include<string>
#include<vector>

std::string xorEncryption(const std::string& password, std::string key);
std::string caesarEncryption(const std::string& password, int& shift);
std::string reverseCaesarEncryption(const std::string& encrypted_password, int& shift);
std::vector<std::vector<char>> gridEncryption(const std::string& password, int key, std::mt19937 gen, int& length);
std::string gridDecryption(const std::vector<std::vector<char>>& encrypted, int key, int length);