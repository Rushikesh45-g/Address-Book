#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"
#include "search.h"
#include "validation.h"


void searchByPhone(AddressBook *addressBook);
void searchByEmail(AddressBook *addressBook);

// Search contact by name (partial match allowed)
void searchByName(AddressBook *addressBook)
{
    listContacts(addressBook, 0); // Show all contacts

    char name[50];
    int ret;

    // Input loop: get valid name
    do
    {
        printf("\033[36mEnter Name to search (0 to cancel): \033[0m");
        scanf(" %[^\n]", name);

        if(strcmp(name, "0") == 0) // User cancels
            return;

        ret = nameValidation(name); // Validate format
        if(ret)
            printf("\033[31mInvalid name! Try again.\033[0m\n");

    } while(ret);

    int foundIndexes[50], foundCount = 0;

    // Search for matching names 
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strstr(addressBook->contacts[i].name, name) != NULL)
            foundIndexes[foundCount++] = i;
    }

    // No match found
    if (foundCount == 0)
    {
        printf("\033[31mNo contact found with this name.\033[0m\n");
        return;
    }

    // Single match found
    if (foundCount == 1)
    {
        int i = foundIndexes[0];
        printf("\033[32m\nContact Found!\033[0m\n");
        printf("Name  : %s\nPhone : %s\nEmail : %s\n",
               addressBook->contacts[i].name,
               addressBook->contacts[i].phone,
               addressBook->contacts[i].email);
        return;
    }

    // Multiple matches found  showed in table box
    printf("\033[33m\nMultiple contacts found:\033[0m\n");
    printf("┌─────┬─────────────────┬──────────────┬──────────────────────────────┐\n");
    printf("│ No. │ Name            │ Phone        │ Email                        │\n");
    printf("├─────┼─────────────────┼──────────────┼──────────────────────────────┤\n");
    for (int j = 0; j < foundCount; j++)
    {
        int i = foundIndexes[j];
        printf("│ %-3d │ %-15s │ %-12s │ %-28s │\n",
               j + 1,
               addressBook->contacts[i].name,
               addressBook->contacts[i].phone,
               addressBook->contacts[i].email);
    }
    printf("└─────┴─────────────────┴──────────────┴──────────────────────────────┘\n");

    // Refine search options
    printf("┌───────────────────────────────┐\n");
    printf("│         REFINE SEARCH         │\n");
    printf("├───────────────────────────────┤\n");
    printf("│ 1. Search by Phone            │\n");
    printf("│ 2. Search by Email            │\n");
    printf("└───────────────────────────────┘\n");

    printf("Enter choice: ");
    int choice;
    scanf("%d", &choice);

    if (choice == 1)
        searchByPhone(addressBook);
    else if (choice == 2)
        searchByEmail(addressBook);
    else
        printf("\033[31mInvalid choice!\033[0m\n");
}


// Search contact by exact phone number
void searchByPhone(AddressBook *addressBook)
{
    listContacts(addressBook, 0); // Show all contacts

    char phone[20];
    int ret;

    // Input loop: get valid phone number
    do
    {
        printf("\033[36mEnter Phone Number to search (0 to cancel): \033[0m");
        scanf(" %[^\n]", phone);

        if(strcmp(phone,"0") == 0) return; // Cancel

        ret = phoneNumberValidation(phone); // Validate phone
        if(ret)
            printf("\033[31mInvalid phone number! Try again.\033[0m\n");

    } while(ret);

    // Search for exact match
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(addressBook->contacts[i].phone, phone) == 0)
        {
            printf("\033[32m\nContact Found!\033[0m\n");
            printf("Name  : %s\nPhone : %s\nEmail : %s\n",
                   addressBook->contacts[i].name,
                   addressBook->contacts[i].phone,
                   addressBook->contacts[i].email);
            return;
        }
    }

    printf("\033[31mNo contact found with this number.\033[0m\n");
}


// Search contact by exact email
void searchByEmail(AddressBook *addressBook)
{
    listContacts(addressBook, 0); // Show all contacts

    char email[50];
    int ret;

    // Input loop: get valid email
    do
    {
        printf("\033[36mEnter Email ID to search (0 to cancel): \033[0m");
        scanf(" %[^\n]", email);

        if(strcmp(email,"0") == 0) return; // Cancel

        ret = mailIdValidation(email); // Validate email
        if(ret)
            printf("\033[31mInvalid email! Try again.\033[0m\n");

    } while(ret);

    // Search for exact match
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(addressBook->contacts[i].email, email) == 0)
        {
            printf("\033[32m\nContact Found!\033[0m\n");
            printf("Name  : %s\nPhone : %s\nEmail : %s\n",
                   addressBook->contacts[i].name,
                   addressBook->contacts[i].phone,
                   addressBook->contacts[i].email);
            return;
        }
    }

    printf("\033[31mNo contact found with this email ID.\033[0m\n");
}
