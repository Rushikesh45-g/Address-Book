#include <stdio.h>
#include "file.h"

// Function to save all contacts to a file
void saveContactsToFile(AddressBook *addressBook) 
{
    FILE *fptr;

    // Open file in write mode
    if ((fptr = fopen("contacts.txt", "w") ) == NULL)
    {
        fprintf (stderr, "Can't open input file file.txt!\n") ; // Error if file can't be opened
        return;
    }

    // First line: store total number of contacts
    fprintf(fptr,"#%d\n",addressBook->contactCount);

    // Write each contact in the format: name,phone,email
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        fprintf(fptr, "%s,%s,%s\n",
                addressBook->contacts[i].name,
                addressBook->contacts[i].phone,
                addressBook->contacts[i].email);
    }

    fclose(fptr); // Close file after writing
}


// Function to load contacts from a file
void loadContactsFromFile(AddressBook *addressBook) 
{
    FILE *fptr;

    // Open file in read mode
    if ((fptr = fopen("contacts.txt", "r") ) == NULL)
    {
        fprintf (stderr, "Can't open input file file.txt!\n"); // Error if file can't be opened
        return;
    }

    // Read first line to get total number of contacts
    fscanf(fptr,"#%d\n",&addressBook->contactCount);

    // Read each contact line in format: name,phone,email
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        fscanf(fptr, "%[^,],%[^,],%[^\n]\n",
                addressBook->contacts[i].name,
                addressBook->contacts[i].phone,
                addressBook->contacts[i].email);
    }

    fclose(fptr); // Close file after reading
}
