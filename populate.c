
#include "contact.h"

static Contact dummycontacts[] = 
{
    {"Nandu", "1234516789", "nandu@gmail.com"},
    {"Kittu", "4532116789", "kittu@gmail.com"},
    {"pondu", "9876542321", "pondu@gmail.com"},
    {"Mani", "3425678943", "mani@gmail.com"},
    {"sahastra", "5432145621", "sahastra@gmail.com"},
    {"karthi", "9345231987", "karthi@gmail.com"},
    {"Teja", "9230985673", "teja@gmail.com"},
    {"Shiva", "7653267893", "shiva@gmail.com"},
    {"Rama", "8796543216", "rama@gmail.com"},
    {"Deva", "8976543289", "deva@gmail.com"},
};

void populateAddressBook(Addressbook *addressbook)//function initialzed with dummy contacts
{
    int numDummycontacts = sizeof(dummycontacts) / sizeof(dummycontacts[0]);
    for(int i = 0; i < numDummycontacts && addressbook -> contactcount < MAX_CONTACTS; i++)
    {
        addressbook -> contacts[addressbook ->contactcount++] = dummycontacts[i];
    }
}