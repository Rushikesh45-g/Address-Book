#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "contact.h"
#include "file.h"
#include "populate.h"
#include "validation.h"
#include "search.h"
#include "edit.h"
#include "delete.h"
//function to list contacts
void listContacts(AddressBook *addressBook, int sortCriteria)
{
    if (addressBook->contactCount == 0) {
        printf("\n\033[31mNo contacts to display.\033[0m\n");
        return;
    }

    // Title
    printf("\n┌──────────────────────────────────────────────────────────────┐\n");
    printf("│                     CONTACT LIST                             │\n");
    printf("└──────────────────────────────────────────────────────────────┘\n");

    // Header
    printf("┌─────┬──────────────────────┬───────────────┬──────────────────────────────────┐\n");
    printf("│ Id. │ Name                 │ Phone         │ Email                            │\n");
    printf("├─────┼──────────────────────┼───────────────┼──────────────────────────────────┤\n");

    // Display rows
    for (int i = 0; i < addressBook->contactCount; i++)
    { 
        printf("│ %-3d │ %-20s │ %-13s │ %-32s │\n",
               i + 1,
               addressBook->contacts[i].name,
               addressBook->contacts[i].phone,
               addressBook->contacts[i].email);
    }

    printf("└─────┴──────────────────────┴───────────────┴──────────────────────────────────┘\n");
    printf("\033[32mContacts displayed successfully!\033[0m\n");
}



// Initializes AddressBook and loads any existing data
void initialize(AddressBook *addressBook)
{
    addressBook->contactCount = 0;         // Start empty
    //populateAddressBook(addressBook);      
    loadContactsFromFile(addressBook);   // Load initial predefined contacts 
}

// Saves data to file and exits the program
void saveAndExit(AddressBook *addressBook)
{
    printf("\n\033[33mSaving data...\033[0m\n");
    saveContactsToFile(addressBook);       // Save contacts to file
    printf("\033[32m✔ Data saved successfully. Exiting...\033[0m\n");
    exit(EXIT_SUCCESS);
}

// Function to create multiple contacts
void createContact(AddressBook *addressBook)
{
    int nums;
    printf("\033[36mEnter the number of contacts you want to create: \033[0m");
    while(scanf("%d", &nums) != 1)
        {
            printf("\033[31mInvalid number! Enter numeric value\033[0m\n");
            while(getchar() != '\n');
            printf("\033[36mEnter the number of contacts you want to create: \033[0m");
            //return;
        }

    // Loop for number of contacts user wants to add
    for (int i = 1; i <= nums; i++)
    {
        char name[20], phone[20], mailid[30];
        int n, p, m, p1, m1;

        printf("\n\033[34m──────── Creating Contact %d ────────\033[0m\n", i);

        // Validate name
        do 
        {
            printf("\033[36mEnter Name: \033[0m");
            scanf(" %[^\n]", name);
            n = nameValidation(name);      // Check grammar rules
        } while (n != 0);

        // Validate phone number
        do 
        {
            printf("\033[36mEnter 10-digit Mobile Number: \033[0m");
            scanf(" %[^\n]", phone);

            p = phoneNumberValidation(phone);   // Check format

            if (p == 0)
                p1 = uniqueNumVaidation(addressBook, phone);   // Check uniqueness
            else
                p1 = 1;
        } while (p != 0 || p1 != 0);


        // Validate email
        do 
        {
            // Ask user to enter Gmail ID
            printf("\033[36mEnter Gmail ID: \033[0m");
            scanf(" %[^\n]", mailid);

            // Check email format
            m = mailIdValidation(mailid);

            if (m == 0)
                m1 = uniqueMailValidation(addressBook, mailid);   // Check uniqueness
            else
                m1 = 1;
        } while (m != 0 || m1 != 0);   // Repeat until valid and unique


        // Save final validated contact info
        strcpy(addressBook->contacts[addressBook->contactCount].name, name);
        strcpy(addressBook->contacts[addressBook->contactCount].phone, phone);
        strcpy(addressBook->contacts[addressBook->contactCount].email, mailid);
        addressBook->contactCount++;

        printf("\033[32m Contact %d created successfully!\033[0m\n", i);
    }

    printf("\n\033[32m All contacts created successfully!\033[0m\n");
}

// Shows search menu and calls respective functions
void searchContact(AddressBook *addressBook)
{
    int choice;

    do {
        printf("\n┌───────────────────────────────┐\n");
        printf("│         SEARCH CONTACT        │\n");
        printf("└───────────────────────────────┘\n");

        printf("┌───────────────┬─────────────────────────────┐\n");
        printf("│ Option Number │          Operation          │\n");
        printf("├───────────────┼─────────────────────────────┤\n");
        printf("│      1        │ Search by Name              │\n");
        printf("│      2        │ Search by Phone Number      │\n");
        printf("│      3        │ Search by Email ID          │\n");
        printf("│      4        │ Exit Search                 │\n");
        printf("└───────────────┴─────────────────────────────┘\n");

        printf("\n\033[36mEnter choice: \033[0m");
        while(scanf("%d", &choice) != 1)
        {
            printf("\033[31mInvalid choice! Enter 1-4.\033[0m\n");
            while(getchar() != '\n');
            printf("\n\033[36mEnter choice: \033[0m");
            //return;
        }
        // Call appropriate function based on choice
        switch (choice)
        {
            case 1: searchByName(addressBook); break;
            case 2: searchByPhone(addressBook); break;
            case 3: searchByEmail(addressBook); break;
            case 4: printf("[33mExiting search...\n"); break;
            default: printf("\033[31mInvalid choice! Enter 1-4.\033[0m\n");
        }

    } while (choice != 4);
}

// Shows edit menu
void editContact(AddressBook *addressBook)
{
    int choice;

    do {
        printf("\n┌───────────────────────────────┐\n");
        printf("│            EDIT MENU          │\n");
        printf("└───────────────────────────────┘\n");

        printf("┌───────────────┬─────────────────────────────┐\n");
        printf("│ Option Number │          Operation          │\n");
        printf("├───────────────┼─────────────────────────────┤\n");
        printf("│      1        │ Edit Name                   │\n");
        printf("│      2        │ Edit Phone Number           │\n");
        printf("│      3        │ Edit Email ID               │\n");
        printf("│      4        │ Exit                        │\n");
        printf("└───────────────┴─────────────────────────────┘\n");


        printf("\n\033[36mEnter choice: \033[0m");
        while(scanf("%d", &choice) != 1)
        {
            printf("\033[31mInvalid choice! Enter 1-4.\033[0m\n");
            while(getchar() != '\n');
            printf("\n\033[36mEnter choice: \033[0m");
            //return;
        }

        // Call proper editing function
        switch (choice)
        {
            case 1: editByName(addressBook); break;
            case 2: editByPhone(addressBook); break;
            case 3: editByEmail(addressBook); break;
            case 4: printf("\033[33mExiting Edit...\033[0m\n"); break;
            default: printf("\033[31mInvalid choice! Enter 1-4.\033[0m\n");
        }

    } while (choice != 4);
}

// Shows delete menu
void deleteContact(AddressBook *addressBook)
{
    int choice;

    do {
        printf("\n┌───────────────────────────────┐\n");
        printf("│        DELETE CONTACT         │\n");
        printf("└───────────────────────────────┘\n");

        printf("┌───────────────┬─────────────────────────────┐\n");
        printf("│ Option Number │          Operation          │\n");
        printf("├───────────────┼─────────────────────────────┤\n");
        printf("│      1        │ Delete by Name              │\n");
        printf("│      2        │ Delete by Phone Number      │\n");
        printf("│      3        │ Delete by Email ID          │\n");
        printf("│      4        │ Exit                        │\n");
        printf("└───────────────┴─────────────────────────────┘\n");

        printf("\n\033[36mEnter choice: \033[0m");
        while(scanf("%d", &choice) != 1)
        {
            printf("\033[31mInvalid choice! Enter 1-4.\033[0m\n");
            while(getchar() != '\n');
            printf("\n\033[36mEnter choice: \033[0m");
            //return;
        }

        // Call respective delete functions
        switch (choice)
        {
            case 1: deleteByName(addressBook); break;
            case 2: deleteByPhone(addressBook); break;
            case 3: deleteByEmail(addressBook); break;
            case 4: printf("Exiting delete menu...\n"); break;
            default: printf("\033[31mInvalid choice! Try again.\033[0m\n");
        }

    } while (choice != 4);
}
