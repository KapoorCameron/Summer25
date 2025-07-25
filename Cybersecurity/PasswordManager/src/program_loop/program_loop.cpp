#include<algorithm>
#include<cstdint>
#include<cstdlib>
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

bool usernameExists(const std::string& encodedUsername)
{
    std::ifstream credentials("credentials.txt");

    if (!credentials)
    {
        std::cerr << "File error-- check state or accessibility.\n\n";
        return 1;
    }

    std::string line;

    while (std::getline(credentials, line))
    {
        if (line.empty())
        {
            continue;
        }

        std::stringstream ss(line);
        std::string cred;
        std::vector<std::string> creds;

        while(std::getline(ss, cred, ','))
        {
            creds.push_back(cred);
        }

        if (creds[1] == encodedUsername)
        {
            return true;
        }
    }

    return false;
}

void signUp()
{
    std::string username;
    std::string encoded_username;
    std::string password;

    while (true)
    {
        std::cout << "Enter username: ";
        std::getline(std::cin, username);
        encoded_username = base64Encode(username);


        if (username.empty() || (username.find(' ') != std::string::npos && username.find_first_not_of(' ') == std::string::npos))
        {
            std::cout << "Invalid username.\n\n";
            continue;
        }

        bool invalidUsername = usernameExists(base64Encode(username));

        if (invalidUsername)
        {
            std::cout << "Username already in use.\n\n";
            continue;
        }

        break;
    }

    while (true)
    {
        std::cout << "Enter password: ";
        std::getline(std::cin, password);

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

            std::string encoded_key = base64Encode(key);
            std::string encoded_encrypted_password = base64Encode(encrypted_password);

            // writeCredentials(method, username, encrypted, key)
            std::ostringstream oss; 
            oss << method << "," << encoded_username << "," << encoded_encrypted_password << "," << encoded_key <<"\n";

            std::ofstream credentials("credentials.txt", std::ios::app);
            credentials << oss.str();
            credentials.close();
        }

        // CaesarCipher
        else if (method == "2")
        {
            // create random num engine:
            std::random_device rd;
            std::mt19937 gen(rd());

            // choose range:
            std::uniform_int_distribution<> dist(48, 58);

            // RNG to assign value to shift:
            int shift = dist(gen);
            encrypted_password = caesarEncryption(password, shift);
            std::string original_password = caesarDecryption(encrypted_password, shift);

            std::string encoded_encrypted_password = base64Encode(encrypted_password);

            std::ostringstream oss;
            oss << method << "," << encoded_username << "," << encoded_encrypted_password << "," << base64Encode(std::to_string(shift)) << "\n";

            std::ofstream credentials("credentials.txt", std::ios::app);
            credentials << oss.str();
            credentials.close();

        }

        // XaesOR
        else if (method == "3")
        {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dist(48, 58);

            int shift = dist(gen);
            std::string key = makeKey();

            encrypted_password = xaesorEncryption(password, shift, key);
            std::string original_password = caesarDecryption(xorEncryption(encrypted_password, key), shift);

            std::cout << "Encrypted password: " << encrypted_password << "\n\n";
            std::cout << "Confirm original password: " << original_password << "\n\n";

            std::ostringstream oss;

            oss << method << "," << base64Encode(username) << "," << base64Encode(encrypted_password) << "," << base64Encode(std::to_string(shift)) << "," << base64Encode(key) << "\n";

            std::ofstream credentials("credentials.txt", std::ios::app);
            credentials << oss.str();
            credentials.close();
        }

        // Grid
        else if (method == "4")
        {
            std::random_device rd1; 
            std::mt19937 gen1(rd1()); 
            std::uniform_int_distribution<> dist1(48, 58);

            int shift = dist1(gen1);

            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dist(2, 4);

            int key = dist(gen);

            // we need to keep track of the seed used for our MT so when we store the password and relevant data for sign in functionality, we can compare saved and entered encrypted passwords:
            std::random_device rd2;
            uint32_t seed = rd2();
            std::mt19937 gen2(seed);
            
            int length;
            int original_password_length = password.length();

            std::vector<std::vector<char>> encrypted_password = gridEncryption(password, shift, key, gen2, length);
            std::string original_password = caesarDecryption(gridDecryption(encrypted_password, key, length, original_password_length), shift);

            std::cout << "Encrypted password: \n\n" << gridToString(encrypted_password, length) << "\n\n";
            std::cout << "Confirm original password: " << original_password << "\n\n";

            std::string grid_string = gridToString(encrypted_password, length);

            std::ostringstream oss;
            oss << method << "," << base64Encode(username) << "," << base64Encode(grid_string) << "," << base64Encode(std::to_string(shift)) << "," << base64Encode(std::to_string(key)) << "," << base64Encode(std::to_string(seed)) << "," << base64Encode(std::to_string(length)) << "\n";

            std::ofstream credentials("credentials.txt", std::ios::app);
            credentials << oss.str();
            credentials.close();
        }

        else
        {
            std::cout << "Invalid input.\n\n";
            continue;
        }

        break;
    }
    
}

int signIn()
{
    bool validUsername = false;

    std::string username;
    std::cout << "Enter username: ";
    std::getline(std::cin, username);

    std::string encoded_username = base64Encode(username);

    std::ifstream credentials("credentials.txt");

    if (!credentials)
    {
        std::cerr << "File error-- check state or accessibility.\n\n";
        return 1;
    }

    std::string line;

    while (std::getline(credentials, line))
    {
        if (line.empty())
        {
            continue;
        }

        std::stringstream ss(line);
        std::string cred;
        std::vector<std::string> creds;

        // We use getline to take characters from ss and parse them into substrings that we place into "cred" using the delimiter ',' to separate said substrings and push_back into creds vector:
        while(std::getline(ss, cred, ','))
        {
            creds.push_back(cred);
        }

        if (creds[1] == encoded_username)
        {
            validUsername = true;
            std::string correctPassword = creds[2];
                if (creds[0] == "1") // XOR
                {
                    int attempts = 0;
                    while (attempts++ < 3) // automatically increments
                    {
                        std::string password;
                        std::cout << "Enter password: ";
                        std::getline(std::cin, password);
                        std::cout << "\n";

                        password = base64Encode(xorEncryption(password, base64Decode(creds[3])));

                        if (password == correctPassword)
                        {
                            std::cout << "Successfully signed in.\n\n";
                            return 0;
                        }

                        std::cout << "Incorrect password, try again.\n\n";
                    }

                    std::cout << "Program quit, too many failed password attempts.\n\n";
                    exit(1);
                }

                else if (creds[0] == "2") // Caesar 
                {
                    int attempts = 0;
                    while (attempts++ < 3)
                    {
                        std::string password;
                        std::cout << "Enter password: ";
                        std::getline(std::cin, password);
                        std::cout << "\n";

                        password = base64Encode(caesarEncryption(password, std::stoi(base64Decode(creds[3]))));

                        if (password == correctPassword)
                        {
                            std::cout << "Successfully signed in.\n\n";
                            return 0;
                        }

                            std::cout << "Incorrect password, try again.\n\n";
                    }

                    std::cout << "Program quit, too many failed password attempts.\n\n";
                    exit(1);
                }

                else if (creds[0] == "3") // XaesOR
                {
                    int attempts = 0;
                    while (attempts++ < 3)
                    {
                        std::string password;
                        std::cout << "Enter password: ";
                        std::getline(std::cin, password);
                        std::cout << "\n";

                        password = base64Encode(xaesorEncryption(password, std::stoi(base64Decode(creds[3])), base64Decode(creds[4])));

                        if (password == correctPassword)
                        {
                            std::cout << "Successfully signed in.\n\n";
                            return 0;
                        }

                            std::cout << "Incorrect password, try again.\n\n";
                    }

                    std::cout << "Program quit, too many failed password attempts.\n\n";
                    exit(1);
                }

                else if (creds[0] == "4")
                {
                    int attempts = 0;
                    while (attempts++ < 3)
                    {
                        std::string password;
                        std::cout << "Enter password: ";
                        std::getline(std::cin, password);
                        std::cout << "\n";

                        int shift = std::stoi(base64Decode(creds[3]));
                        int key = std::stoi(base64Decode(creds[4]));
                        uint32_t seed = static_cast<uint32_t>(std::stoul(base64Decode(creds[5])));
                        std::mt19937 gen(seed);
                        int length = std::stoi(base64Decode(creds[6]));

                        std::vector<std::vector<char>> grid = gridEncryption(password, shift, key, gen, length);

                        password = base64Encode(gridToString(grid, length));

                        if (password == correctPassword)
                        {
                            std::cout << "Successfully signed in.\n\n";
                            return 0;
                        }

                            std::cout << "Incorrect password, try again.\n\n";
                    }

                    std::cout << "Program quit, too many failed password attempts.\n\n";
                    exit(1);
                }
            }
    }

    if (!validUsername) std::cout << "\nInvalid username.\n\n";

    return 1;
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

