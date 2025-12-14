#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "validation.h"
#include "file.h"
#include "delete.h"

// listing function
void listContacts(AddressBook *addressBook, int showIndex);

void deleteByName(AddressBook *addressBook)
{
    // nothing to delete if list is empty
    if (addressBook->contactCount == 0)
    {
        printf("\nNo contacts available to delete.\n");
        return;
    }

    // show everything so user knows what they're deleting
    listContacts(addressBook, 1);

    char name[50];
    printf("\nEnter Name to delete: ");
    scanf(" %[^\n]", name);

    // name format check
    if (nameValidation(name))
        return;

    int matchCount = 0;
    int matchedIndexList[addressBook->contactCount];

    // find all contacts that have the same name
    // (keeping indexes so we can delete the correct one)
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(addressBook->contacts[i].name, name) == 0)
            matchedIndexList[matchCount++] = i;
    }

    // name not found at all
    if (matchCount == 0)
    {
        printf("No contact found with name '%s'.\n", name);
        return;
    }

    int selectedIndex = 0;

    // if there are duplicates, let the user choose which exact one to remove
    if (matchCount > 1)
    {
        printf("\nMultiple contacts found:\n");

        for (int i = 0; i < matchCount; i++)
        {
            int id = matchedIndexList[i];

            // showing full details so the user picks the right one
            printf("%d. %s | %s | %s\n",
                i + 1,
                addressBook->contacts[id].name,
                addressBook->contacts[id].phone,
                addressBook->contacts[id].email);
        }

        int choice;
        printf("Choose which one to delete: ");
        scanf("%d", &choice);
        if(choice > matchCount)
        {
            printf("Invalid Choice ! Try again...");
            return;
        }

        // convert choice to actual array index
        selectedIndex = matchedIndexList[choice - 1];
    }
    else
    {
        // only one match - delete it directly
        selectedIndex = matchedIndexList[0];
    }

    // shift all contacts to the left after deleting chosen one
    for (int i = selectedIndex; i < addressBook->contactCount - 1; i++)
    {
        addressBook->contacts[i] = addressBook->contacts[i + 1];
    }

    addressBook->contactCount--;

    printf("\nContact deleted successfully!\n");
    listContacts(addressBook, 0);
}



void deleteByPhone(AddressBook *addressBook)
{
    // nothing inside - nothing to delete
    if (addressBook->contactCount == 0)
    {
        printf("\nNo contacts available to delete.\n");
        return;
    }

    char phone[15];
    printf("\nEnter Phone to delete: ");
    scanf(" %[^\n]", phone);

    //  format check
    if (phoneNumberValidation(phone))
        return;

    int index = -1;

    //  search for matching phone number
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(addressBook->contacts[i].phone, phone) == 0)
        {
            index = i;
            break;  // found it, no need to continue scanning
        }
    }

    if (index == -1)
    {
        printf("No contact found with phone '%s'.\n", phone);
        return;
    }

    // remove the contact by shifting everything left
    for (int i = index; i < addressBook->contactCount - 1; i++)
    {
        addressBook->contacts[i] = addressBook->contacts[i + 1];
    }

    addressBook->contactCount--;

    printf("\nContact deleted successfully!\n");
    listContacts(addressBook, 0);
}



void deleteByEmail(AddressBook *addressBook)
{
    // nothing stored - nothing to delete
    if (addressBook->contactCount == 0)
    {
        printf("\nNo contacts available to delete.\n");
        return;
    }

    char email[50];
    printf("\nEnter Email to delete: ");
    scanf(" %[^\n]", email);

    // quick check for proper email format
    if (mailIdValidation(email))
        return;

    int index = -1;

    // find which contact has this email
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(addressBook->contacts[i].email, email) == 0)
        {
            index = i;
            break;
        }
    }

    if (index == -1)
    {
        printf("No contact found with email '%s'.\n", email);
        return;
    }

    // delete by shifting
    for (int i = index; i < addressBook->contactCount - 1; i++)
    {
        addressBook->contacts[i] = addressBook->contacts[i + 1];
    }

    addressBook->contactCount--;

    printf("\nContact deleted successfully!\n");
    listContacts(addressBook, 0);
}
