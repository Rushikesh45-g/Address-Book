#include <stdio.h>
#include "contact.h"

int main() {
    int choice;
    AddressBook addressBook;
    initialize(&addressBook); // Initialize the address book

    do {
        printf("\n┌───────────────────────────────────┐\n");
        printf("│          Address Book Menu        │\n");
        printf("├───────────────────────────────────┤\n");
        printf("│ 1. Create contact                 │\n");
        printf("│ 2. Search contact                 │\n");
        printf("│ 3. Edit contact                   │\n");
        printf("│ 4. Delete contact                 │\n");
        printf("│ 5. List all contacts              │\n");
        printf("│ 6. Save contacts                  │\n");
        printf("│ 7. Exit                           │\n");
        printf("└───────────────────────────────────┘\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                createContact(&addressBook);
                break;
            case 2:
                searchContact(&addressBook);
                break;
            case 3:
                editContact(&addressBook);
                break;
            case 4:
                deleteContact(&addressBook);
                break;
            case 5:          
                listContacts(&addressBook, 0); //sortChoice
                break;
            case 6:
                printf("Saving...\n");
                saveContactsToFile(&addressBook);
                break;
            case 7:
                printf("Exiting AddressBook...\n");
                break;
            default:
                printf("\033[31mInvalid choice. Please try again.\033[0m\n");
                break;
        }
    } while (choice != 7);
    
       return 0;
}
