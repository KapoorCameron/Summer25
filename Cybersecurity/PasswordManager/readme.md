## overview:

I will learn about encryption and file handling by making a simple password manager. 

This program will have two options, A) Sign up, and B) sign in:

A) Sign up

1) Users will enter a username and password combo.

2) Program will encrypt password using the mtheod the user selects.

3) Program will write username/encrypted password combo to credetnials.txt.

B) 

1) User enters username.

2) User enters password.

3) Program checks to see if password matches credentials in "database." 

Example usernames and encrypted passwords will appear in example_output.txt, while real output will be stored in credentials.cpp which I will exclude from version control using .gitignore. This is to A) familiarize myself with .gitignore, and B) to develop good habits and prevent bad ones.

Project sign in/sign up flow looks like:

(starting at sign-up menu) 
1) user enters username
2) user enters password
3) user selects encryption method
4) password is encrypted
5) password is encoded
6) method, username, encoded encrypted password, and other relevant data is inserted into an oss and converted to string
7) string is passed into writeCredentials()
8) string is written to credentials.txt
9) user navigates to sign in menu 
10) user enters username
11) code checks database for that username 
12) if there's a match, code prompts for password
13) user enters password
14) code takes the password the user entered, encrypts it based on the method specified in first        parameter of my database syntax, and then encodes it with Base64 or something, and then compares that encoded version of the encrypted password with the encoded encrypted password in the database, allowing sign in if they match?

----
## Syntax:

directories- snake_case
files-       snake_case
functions-   camelCase
variables-   camelCase

----
## Encryption methods:

) XOR- 

) Caesar-

) XaesOR- 

) "Grid"- 



