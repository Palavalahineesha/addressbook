#include<stdio.h>
#include"contact.h"
#include"populate.h"

int main()
{
   int choice;
   Addressbook addressbook;
   initialize(&addressbook);//intializing with count 0
   load_contact(&addressbook); // loading contacts from csv file 

do
{
   //menu displayed in loop to use it multiple times
    printf("\nAddress Book Menu\n");
    printf("1. Create Contact\n");
    printf("2. search Contact\n");
    printf("3. edit Contact\n");
    printf("4. delete Contact\n");
    printf("5. list of Contacts\n");
    printf("6. save & Exit\n");

    printf("Enter your choice: ");
    scanf("%d", &choice);
   
    switch(choice)//switch case to work according to user choice
    {
        case 1:
           createcontact(&addressbook);
           break;
        case 2:
           searchcontact(&addressbook);
           break;
        case 3:
           editcontact(&addressbook);
           break;
        case 4:
           deletecontact(&addressbook);
           break;
        case 5:
           listcontacts(&addressbook);
           break;
        case 6:
           save_contact(&addressbook);
           printf("Exiting...\n");
           break;

        default:
           printf("Invalid choice. Please try again\n");                
    } 
} 
while (choice != 6);
return 0;
}
