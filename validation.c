#include "validation.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

// Function to validate name input
int nameValidation(char *name)
{
    int len = strlen(name);

    // Check if name is empty
    if (len == 0)
    {
        printf("\033[31mError: Name cannot be empty.\033[0m\n");
        return 1;
    }

    // Check first letter is uppercase
    if (name[0] < 'A' || name[0] > 'Z')
    {
        printf("\033[31mError: The first character must be an uppercase letter (A-Z).\033[0m\n");
        return 1;
    }

    // Check first and last character not space
    if (name[0] == ' ' || name[len - 1] == ' ')
    {
        printf("\033[31mError: Name cannot start or end with space.\033[0m\n");
        return 1;
    }

    // Check each character and prevent consecutive spaces
    for (int i = 0; i < len; i++)
    {
        char ch = name[i];

        // Allow only alphabets and space
        if (!((ch >= 'a' && ch <= 'z') ||
              (ch >= 'A' && ch <= 'Z') ||
              ch == ' '))
        {
            printf("\033[31mError: Name can contain only alphabets and spaces.\033[0m\n");
            return 1;
        }

        // Check for consecutive spaces
        if (ch == ' ' && name[i + 1] == ' ')
        {
            printf("\033[31mError: Name cannot contain consecutive spaces.\033[0m\n");
            return 1;
        }
    }

    return 0; // Valid name
}

// Function to validate phone number
int phoneNumberValidation(char *phone)
{
    int len = strlen(phone);

    // Must be exactly 10 digits
    if (len != 10)
    {
        printf("\033[31mError: Mobile number must be exactly 10 digits.\033[0m\n");
        return 1;
    }

    // Check all characters are digits
    for (int i = 0; i < len; i++)
    {
        if (phone[i] < '0' || phone[i] > '9')
        {
            printf("\033[31mError: Mobile number must contain digits only.\033[0m\n");
            return 1;
        }
    }

    return 0; // Valid phone
}

// Function to validate Gmail ID
int mailIdValidation(char *mailid)
{
    int len = strlen(mailid);

    // Minimum length check
    if (len < 11)
    {
        printf("\033[31mError: Email too short. Must be username@gmail.com\033[0m\n");
        return 1;
    }

    // Check for spaces
    for (int i = 0; i < len; i++)
    {
        if (mailid[i] == ' ')
        {
            printf("\033[31mError: Email must not contain spaces.\033[0m\n");
            return 1;
        }
    }

    // Email must end with "@gmail.com"
    if (strcmp(&mailid[len - 10], "@gmail.com") != 0)
    {
        printf("\033[31mError: Email must end with @gmail.com\033[0m\n");
        return 1;
    }

    // Check username part before @gmail.com
    int localLen = len - 10;
    if (localLen < 1)
    {
        printf("\033[31mError: Email must contain username before @gmail.com\033[0m\n");
        return 1;
    }

    // Username can contain lowercase letters, digits, dot, underscore
    for (int i = 0; i < localLen; i++)
    {
        char ch = mailid[i];

        if (!((ch >= 'a' && ch <= 'z') ||
              (ch >= '0' && ch <= '9') ||
              ch == '.' || ch == '_'))
        {
            printf("\033[31mError: Username can contain only a-z, 0-9, dot (.), underscore (_).\033[0m\n");
            return 1;
        }
    }

    return 0; // Valid email
}

// Function to check duplicate phone number
int uniqueNumVaidation(AddressBook *addressBook, char *phone)
{
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(addressBook->contacts[i].phone, phone) == 0)
        {
            printf("\033[31mError: Duplicate Mobile Number!\033[0m\n");
            return 1;
        }
    }
    return 0; // Unique number
}

// Function to check duplicate email ID
int uniqueMailValidation(AddressBook *addressBook, char *mailid)
{
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(addressBook->contacts[i].email, mailid) == 0)
        {
            printf("\033[31mError: Duplicate Email ID!\033[0m\n");
            return 1;
        }
    }
    return 0; // Unique email
}
