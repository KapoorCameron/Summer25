#include<bitset>
#include<iostream>
#include<string>

#include"encoding.h"

std::string base64Encode(std::string& credential)
{
    /*
        1) build a std::string bit_string by concatenating binary representation of each char in credentials 

        2) split bit_string into groups of 6 bits, padding any remainder with "=": while (bit_string.length() % 3 != 0) {bit_string += "="};

        3) convert each 6-bit chunk into whatever its binary value maps to in base64 (based on index in base64 string), and concatenate that value into new output_string. 
    */

    std::string base64 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    std::string bit_string;
    std::string encoded;

    for (char c : credential)
    {
        bit_string += std::bitset<8>(c).to_string(); // takes 8-bit binary value of character and concatenates it to bit_string.
    }

    while (bit_string.length() % 6 != 0) // I pad bit_string to be divisible by 6 (base64 reads input in blocks of 6 bits.)
    {
        bit_string += "0";
    }

    for (int i = 0; i < bit_string.length(); i += 6)
    {
        std::string six_bits = bit_string.substr(i, 6);
        int index = std::stoi(six_bits, nullptr, 2);
        encoded += base64[index];
    }

    // I need to make sure output is divisible by four characters. FOUR 6-bit characters = 24 bits, which is 3 bytes, which is THREE 8-bit ASCII characters. Base64 uses "=" padding for each missing character in the last 4-character  clump.
    int pad_count = 0;
    while (encoded.length() % 4 != 0)
    {
        if (pad_count < 2)
        {
            encoded += "=";
            pad_count++;
        }

        else
        {
            break;
        }
    }

    return encoded;
}

std::string base64Decode(std::string& encoded)
{
    std::string base64 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    std::string bit_string = "";
    std::string decoded = "";

    for (char c : encoded)
    {
        if (c == '=') {break;}
        int index = base64.find(c);
        bit_string += std::bitset<6>(index).to_string();
    }

    for (int i = 0; i <= bit_string.size() - 8; i += 8)
    {
        std::string byte = bit_string.substr(i, 8);

        char ch = static_cast<char>(std::stoi(byte, nullptr, 2));

        decoded += ch;
    }

    return decoded;
}

int main()
{
    std::cout << "BooyAHz\n\n";
    std::string credentials = "big baller";
    std::cout << "Decoded: " << base64Encode(credentials) << "\n\n" << "Original: " << base64Decode(base64Encode(credentials));

} // cl testing_main.cpp /Fe:tm