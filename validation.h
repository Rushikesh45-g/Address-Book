#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"
int nameValidation(char *name);
int phoneNumberValidation(char *number);
int mailIdValidation(char *mailid);
int uniqueNumVaidation(AddressBook *addressBook,char *number);
int uniqueMailValidation(AddressBook *addressBook,char *mailid);