#include <stdio.h>
#include <string.h>
#include "contact.h"
#include "validation.h"
#include "file.h"

void listContacts(AddressBook *addressBook, int showIndex);
int uniqueNumVaidation(AddressBook *addressBook, char *phone);
int uniqueMailValidation(AddressBook *addressBook, char *mailid);


//Edit Contact by name
void editByName(AddressBook *addressBook)
{
    // Editing not possible if there are no contacts
    if (addressBook->contactCount == 0) 
    {
        printf("\033[31mNo contacts available to edit.\033[0m\n");
        return;
    }

    // Show contact list so user knows entries
    listContacts(addressBook, 1);

    char name[50];
    int matchCount = 0;
    int indices[addressBook->contactCount];

    // Ask which name the user wants to edit
    printf("Enter Name to edit: ");
    scanf(" %[^\n]", name);

    // Validate input name
    if (nameValidation(name)) 
    {
        printf("\033[31mInvalid name format.\033[0m\n");
        return;
    }

    // Find all contacts with matching name
    for (int i = 0; i < addressBook->contactCount; i++) 
    {
        if (strcmp(addressBook->contacts[i].name, name) == 0)
            indices[matchCount++] = i;
    }

    // If no matches found
    if (matchCount == 0) {
        printf("\033[31mNo contact found with name '%s'.\033[0m\n", name);
        return;
    }

    int chosenIndex;

    // If multiple contacts have same name, ask which one to edit
    if (matchCount > 1) {
        printf("\nMultiple contacts found:\n");
        for (int i = 0; i < matchCount; i++) 
        {
            printf("%d. %s | %s | %s\n",
                i + 1,
                addressBook->contacts[indices[i]].name,
                addressBook->contacts[indices[i]].phone,
                addressBook->contacts[indices[i]].email
            );
        }

        int choice;
        printf("Select contact number to edit: ");
        scanf("%d", &choice);
        if(choice > matchCount)
        {
            printf("Invalid Choice ! Try again...");
            return;
        }

        chosenIndex = indices[choice - 1];
    }
    else {
        // Only one matching contact
        chosenIndex = indices[0];
    }

    // Ask for updated name
    printf("Enter new Name: ");
    scanf(" %[^\n]", addressBook->contacts[chosenIndex].name);

    // Validate updated name
    if (nameValidation(addressBook->contacts[chosenIndex].name)) 
    {
        printf("\033[31mInvalid name. Name not updated.\033[0m\n");
        return;
    }

    printf("\033[32mName updated successfully!\033[0m\n");
    listContacts(addressBook, 0);
}


// Edit Contact by phone number
void editByPhone(AddressBook *addressBook)
{
    // Ensure contacts exist
    if (addressBook->contactCount == 0) 
    {
        printf("\033[31mNo contacts available to edit.\033[0m\n");
        return;
    }

    char phone[15];
    int index = -1;  // Used to detect if match is found

    // Ask user which phone number to edit
    printf("Enter Phone to edit: ");
    scanf(" %[^\n]", phone);

    // Validate input number
    if (phoneNumberValidation(phone)) 
    {
        printf("\033[31mInvalid phone number.\033[0m\n");
        return;
    }

    // Search for phone number
    for (int i = 0; i < addressBook->contactCount; i++) 
    {
        if (strcmp(addressBook->contacts[i].phone, phone) == 0) 
        {
            index = i;
            break;
        }
    }

    // If no contact found with this number
    if (index == -1) 
    {
        printf("\033[31mPhone number not found.\033[0m\n");
        return;
    }

    char newPhone[15];

    // Ask for updated number
    printf("Enter new Phone: ");
    scanf(" %[^\n]", newPhone);

    // Validate the updated number
    if (phoneNumberValidation(newPhone)) 
    {
        printf("\033[31mInvalid phone number.\033[0m\n");
        return;
    }

    // Check if new number already exists in another contact
    if (uniqueNumVaidation(addressBook, newPhone) && strcmp(newPhone, addressBook->contacts[index].phone) != 0)
    {
        printf("\033[31mPhone number already exists.\033[0m\n");
        return;
    }

    // Update phone number
    strcpy(addressBook->contacts[index].phone, newPhone);

    printf("\033[32mPhone updated successfully!\033[0m\n");
    listContacts(addressBook, 0);
}


//Edit contact by Mailid
void editByEmail(AddressBook *addressBook)
{
    // Editing email is not possible if list is empty
    if (addressBook->contactCount == 0) 
    {
        printf("\033[31mNo contacts available to edit.\033[0m\n");
        return;
    }

    char email[50];
    int index = -1;

    // Ask which email user wants to modify
    printf("Enter Email to edit: ");
    scanf(" %[^\n]", email);

    // Validate email format
    if (mailIdValidation(email)) 
    {
        printf("\033[31mInvalid email format.\033[0m\n");
        return;
    }

    // Look for matching email
    for (int i = 0; i < addressBook->contactCount; i++) 
    {
        if (strcmp(addressBook->contacts[i].email, email) == 0) 
        {
            index = i;
            break;
        }
    }

    // If email not found
    if (index == -1) {
        printf("\033[31mEmail not found.\033[0m\n");
        return;
    }

    char newEmail[50];

    // Ask user for updated email
    printf("Enter new Email: ");
    scanf(" %[^\n]", newEmail);

    // Validate updated email
    if (mailIdValidation(newEmail)) {
        printf("\033[31mInvalid email format.\033[0m\n");
        return;
    }

    // Check if this email is already used by some other contact
    if (uniqueMailValidation(addressBook, newEmail) && strcmp(newEmail, addressBook->contacts[index].email) != 0)
    {
        printf("\033[31mEmail already exists.\033[0m\n");
        return;
    }

    // Update email
    strcpy(addressBook->contacts[index].email, newEmail);

    printf("\033[32mEmail updated successfully!\033[0m\n");
    listContacts(addressBook, 0);
}

