#ifndef CONTACT_H
#define CONTACT_H

#define MAX_CONTACTS 100  //macro for maximum contacts

typedef struct
{
    char name[50];
    char phone_num[20];
    char email[50];
}Contact;

typedef struct
{
    Contact contacts[MAX_CONTACTS];  // usage of macro 
    int contactcount;
}Addressbook;

void createcontact(Addressbook *addressbook);
void searchcontact(Addressbook *addressbook);
void editcontact(Addressbook *addressbook);
void deletecontact(Addressbook *addressbook);
void initialize(Addressbook *addressbook);
void populateAddressBook(Addressbook *addressbook); 
void listcontacts(Addressbook *addressbook);
void save_contact(Addressbook *addressbook);
void load_contact(Addressbook *addressbook);


#endif
