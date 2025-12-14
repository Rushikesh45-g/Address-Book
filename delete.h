#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"
#include "validation.h"
#include "search.h"
#include "edit.h"

void deleteByName(AddressBook *addressBook);
void deleteByPhone(AddressBook *addressBook);
void deleteByEmail(AddressBook *addressBook);