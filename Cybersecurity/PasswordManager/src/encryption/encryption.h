#pragma once

#include<random>
#include<string>
#include<vector>

std::string xorEncryption(const std::string& password, const std::string& key);
std::string caesarEncryption(const std::string& password, int& shift);
std::string caesarDecryption(const std::string& encrypted_password, int& shift);
std::string xaesorEncryption(const std::string& password, int& shift, const std::string& key);
std::vector<std::vector<char>> gridEncryption(const std::string& password, int& shift, int key, std::mt19937 gen, int& length);
std::string gridDecryption(const std::vector<std::vector<char>>& encrypted, int key, const int& length, const int& original_password_length);