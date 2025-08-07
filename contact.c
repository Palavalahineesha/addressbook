#include <stdio.h>
#include <string.h>
#include "contact.h"
#include "populate.h"

void initialize(Addressbook *addressbook)
{
    addressbook->contactcount = 0;//intializing contact count to 0 
}

void listcontacts(Addressbook *addressbook)// to list all contacts in addressbook
{
    if (addressbook->contactcount == 0) {
        printf("No contacts to display.\n");
        return;
    }

     printf("\n%-6s %-18s %-15s %-25s\n", "S.No", "Name", "Phone", "Email");
    printf("---------------------------------------------------------------\n");

    for (int i = 0; i < addressbook->contactcount; i++)
    {
        printf("%-6d %-18s %-15s %-25s\n",
               i + 1,
               addressbook->contacts[i].name,
               addressbook->contacts[i].phone_num,
               addressbook->contacts[i].email);
    }
}

int validname(char *name)//to check for valid name
{
    int i = 0;
    while (name[i] != '\0') 
    {
        if (name[i] >= '0' && name[i] <= '9') 
        {
            return 0;
        }
        i++;
    }
    return 1;
}

int validphonenum(char *phone)//check for valid phone number 
{
    int i = 0;
    while (phone[i] != '\0') 
    {
        if (phone[i] < '0' || phone[i] > '9') 
        {
            return 0;
        }
        i++;
    }
    return (i == 10);
}

int isphoneexist(Addressbook *addressbook, char *phone)//check if phone number already exist
{
    for (int i = 0; i < addressbook->contactcount; i++) 
    {
        if (strcmp(addressbook->contacts[i].phone_num, phone) == 0) 
        {
            return 1;
        }
    }
    return 0;
}

int isemailexist(Addressbook *addressbook, char *email) //check if email already exist
{
    for (int i = 0; i < addressbook->contactcount; i++) 
    {
        if (strcmp(addressbook->contacts[i].email, email) == 0) 
        {
            return 1;
        }
    }
    return 0;
}

int validmail(char *email)//check for valid email
{
    int i = 0, atrateposition = -1, dotposition = -1;

    while (email[i] != '\0') 
    {
        if (email[i] == '@') 
        {
            atrateposition = i;
            break;
        }
        i++;
    }
    if (atrateposition <= 0) 
       return 0;

    i = atrateposition + 1;
    while (email[i] != '\0') 
    {
        if (email[i] == '.') 
        {
            dotposition = i;
            break;
        }
        i++;
    }
    if (dotposition == -1 || dotposition == atrateposition + 1 || email[dotposition + 1] == '\0') 
    {
        return 0;
    }
    return 1;
}

void createcontact(Addressbook *addressbook)//function to create contacts
{
    char name[50], phone_num[20], email[50];

    while (1) 
    {
        printf("Enter Name (numbers are not allowed): ");
        scanf(" %[^\n]", name); 
        getchar();
        if (name[0] == '\0') 
        {
            printf("Name cannot be empty\n");
            continue;
        }
        if (!validname(name))//check if name is valid
        {
            printf("Invalid input! Name should not have numbers\n");
            continue;
        }
        break;
    }

    while (1) 
    {
        printf("Enter Phone Number (should have 10 digits): ");
        scanf("%s", phone_num);

        if (!validphonenum(phone_num))//check for valid phone number
        {
            printf("Invalid input! Phone number should contain 10 digits\n");
            continue;
        }
        if (isphoneexist(addressbook, phone_num)) //check if phone num already exist
        {
            printf("Phone number already exists! Please enter a different number\n");
            continue;
        }
        break;
    }

    while (1) 
    {
        printf("Enter Email: ");
        scanf("%s", email);

        if (!validmail(email))//check for valid email
        {
            printf("Invalid Email! Please enter a valid one\n");
            continue;
        }
        if (isemailexist(addressbook, email)) //check if email already
        {
            printf("Email already exists! Please enter a different one\n");
            continue;
        }
        break;
    }

    strcpy(addressbook->contacts[addressbook->contactcount].name, name);
    strcpy(addressbook->contacts[addressbook->contactcount].phone_num, phone_num);
    strcpy(addressbook->contacts[addressbook->contactcount].email, email);

    addressbook->contactcount++;

    printf("Contact added successfully!\n");
}




void searchcontact(Addressbook *addressbook)//function to search contact
{
    int choice;
    char input[50];
    printf("Search by:\n1. Name\n2. Phone Number\n3. Email\nEnter choice: ");
    scanf("%d", &choice); 
    getchar();

    int found = 0, match_index[10], count = 0;

    printf("Enter value to search: ");
    if (choice == 1) 
    {
        scanf("%[^\n]", input); 
        getchar();
        for (int i = 0; i < addressbook->contactcount; i++) 
        {
            if (strcmp(addressbook->contacts[i].name, input) == 0) 
            {
                printf("%d. %s  %s  %s\n", ++count,
                       addressbook->contacts[i].name,
                       addressbook->contacts[i].phone_num,
                       addressbook->contacts[i].email);
                match_index[count - 1] = i;
                found = 1;
            }
        }
    } 
    else if (choice == 2 || choice == 3) 
    {
        scanf("%s", input);
        for (int i = 0; i < addressbook->contactcount; i++) 
        {
            char *field = (choice == 2) ? addressbook->contacts[i].phone_num : addressbook->contacts[i].email;
            if (strcmp(field, input) == 0) 
            {
                printf("%s  %s  %s\n",
                       addressbook->contacts[i].name,
                       addressbook->contacts[i].phone_num,
                       addressbook->contacts[i].email);
                found = 1;
                break;
            }
        }
    }

    if (!found) printf("Contact not found!\n");
}

void editcontact(Addressbook *addressbook)//function to edit contact 
{
    int choice, edit_choice;
    char input[50];
    printf("Edit by:\n1. Name\n2. Phone Number\n3. Email\nEnter choice: ");
    scanf("%d", &choice); 
    getchar();

    int found = 0, match_index[10], count = 0;

    printf("Enter value to search: ");
    if (choice == 1) {
        scanf("%[^\n]", input); 
        getchar();
        for (int i = 0; i < addressbook->contactcount; i++) 
        {
            if (strcmp(addressbook->contacts[i].name, input) == 0) 
            {
                printf("%d. %s  %s  %s\n", ++count,
                       addressbook->contacts[i].name,
                       addressbook->contacts[i].phone_num,
                       addressbook->contacts[i].email);
                match_index[count - 1] = i;
                found = 1;
            }
        }
        if (found) 
        {
            int pick;
            printf("Choose which one to edit (1-%d): ", count);
            scanf("%d", &pick);
            getchar();
            if (pick < 1 || pick > count)//condition to check for pick value
            {
                printf("Invalid choice!\n");
                return;
            }
            int idx = match_index[pick - 1];

            printf("Edit: 1.Name 2.Phone 3.Email\nEnter choice: ");
            scanf("%d", &edit_choice); 
            getchar();//to remove \n

            if (edit_choice == 1) 
            {
                printf("Enter new name: ");
                scanf("%[^\n]", input); 
                getchar();
                if (validname(input)) 
                {
                    strcpy(addressbook->contacts[idx].name, input);
                    printf("Contact updated successfully!\n");
                } 
                else 
                {
                    printf("Invalid name!\n");
                }
            } 
            else if (edit_choice == 2) 
            {
                printf("Enter new phone: ");
                scanf("%s", input);
                if (validphonenum(input) && !isphoneexist(addressbook, input)) 
                {
                    strcpy(addressbook->contacts[idx].phone_num, input);
                    printf("Contact updated successfully!\n");
                } 
                else 
                {
                    printf("Invalid or duplicate phone number!\n");
                }
            } 
            else if (edit_choice == 3) 
            {
                printf("Enter new email: ");
                scanf("%s", input);
                if (validmail(input) && !isemailexist(addressbook, input)) 
                {
                    strcpy(addressbook->contacts[idx].email, input);
                    printf("Contact updated successfully!\n");
                }
                else 
                 
                {
                    printf("Invalid or duplicate email!\n");
                }
            }
        }
    }
    else
    {
        scanf("%s", input);
        for (int i = 0; i < addressbook->contactcount; i++)
        {
            char *field = (choice == 2) ? addressbook->contacts[i].phone_num : addressbook->contacts[i].email;
            if (strcmp(field, input) == 0) 
            {
                printf("%s  %s  %s\n", addressbook->contacts[i].name,
                       addressbook->contacts[i].phone_num,
                       addressbook->contacts[i].email);
                printf("Edit: 1.Name 2.Phone 3.Email\nEnter choice: ");
                scanf("%d", &edit_choice); 
                getchar();
                if (edit_choice == 1) 
                {
                    printf("Enter new name: ");
                    scanf("%[^\n]", input); getchar();
                    if (validname(input)) 
                    {
                        strcpy(addressbook->contacts[i].name, input);
                        printf("Contact updated successfully!\n");
                    } 
                    else 
                    {
                        printf("Invalid name!\n");
                    }
                } else if (edit_choice == 2) 
                {
                    printf("Enter new phone: ");
                    scanf("%s", input);
                    if (validphonenum(input) && !isphoneexist(addressbook, input)) 
                    {
                        strcpy(addressbook->contacts[i].phone_num, input);
                        printf("Contact updated successfully!\n");
                    } 
                    else 
                    {
                        printf("Invalid or duplicate phone number!\n");
                    }
                } 
                else if (edit_choice == 3) 
                {
                    printf("Enter new email: ");
                    scanf("%s", input);
                    if (validmail(input) && !isemailexist(addressbook, input)) 
                    {
                        strcpy(addressbook->contacts[i].email, input);
                        printf("Contact updated successfully!\n");
                    } 
                    else 
                    {
                        printf("Invalid or duplicate email!\n");
                    }
                }
                found = 1;
                break;
            }
        }
    }

    if (!found) printf("Contact not found for edit!\n");
}

void deletecontact(Addressbook *addressbook)//function to delete contact 
{
    int choice;
    char input[50];
    printf("Delete by:\n1. Name\n2. Phone Number\n3. Email\nEnter choice: ");
    scanf("%d", &choice);
     getchar();

    int found = 0, match_index[10], count = 0;

    printf("Enter value to delete: ");
    if (choice == 1) 
    {
        scanf("%[^\n]", input); 
        getchar();
        for (int i = 0; i < addressbook->contactcount; i++) 
        {
            if (strcmp(addressbook->contacts[i].name, input) == 0) 
            {
                printf("%d. %s  %s  %s\n", ++count,
                       addressbook->contacts[i].name,
                       addressbook->contacts[i].phone_num,
                       addressbook->contacts[i].email);
                match_index[count - 1] = i;
                found = 1;
            }
        }
        if (found) 
        {
            int catch;
            printf("Choose which one to delete (1-%d): ", count);
            scanf("%d", &catch);
             if (catch < 1 || catch > count) 
            {
                printf("Invalid choice!\n");
                return;
            }
            int idx = match_index[catch - 1];

            for (int j = idx; j < addressbook->contactcount - 1; j++)
                addressbook->contacts[j] = addressbook->contacts[j + 1];
            addressbook->contactcount--;

            printf("Contact deleted.\n");
        }
    } 
    else
    {
        scanf("%s", input);
        for (int i = 0; i < addressbook->contactcount; i++) 
        {
            char *field = (choice == 2) ? addressbook->contacts[i].phone_num : addressbook->contacts[i].email;
            if (strcmp(field, input) == 0) 
            {
                for (int j = i; j < addressbook->contactcount - 1; j++)
                    addressbook->contacts[j] = addressbook->contacts[j + 1];
                addressbook->contactcount--;
                printf("Contact deleted.\n");
                found = 1;
                break;
            }
        }
    }

    if (!found) printf("Contact not found to delete!\n");
}
void save_contact(Addressbook *addressbook)//function to save contact
{
    FILE *fp = fopen("contact.csv", "w");
    if (fp == NULL)
    {
        printf("Warning: Unable to open file to save contacts.\n");
        return;
    }

    
    fprintf(fp, "%d\n", addressbook->contactcount);

    
    for (int i = 0; i < addressbook->contactcount; i++)
    {
        fprintf(fp, "%s,%s,%s\n",
                addressbook->contacts[i].name,
                addressbook->contacts[i].phone_num,
                addressbook->contacts[i].email);
    }

    fclose(fp);
    printf("Contacts saved successfully !!!\n");
}

void load_contact(Addressbook *addressbook)//function to load contacts along with dummy contacts
{
    FILE *fp = fopen("contact.csv", "r");
    if (fp == NULL)
    {
        printf("No saved contacts found. Loading dummy contacts...\n");
        
        populateAddressBook(addressbook); 
        return;
    }

    fscanf(fp, "%d\n", &addressbook->contactcount);
    for (int i = 0; i < addressbook->contactcount; i++)
    {
        fscanf(fp, "%[^,],%[^,],%[^\n]\n",
               addressbook->contacts[i].name,
               addressbook->contacts[i].phone_num,
               addressbook->contacts[i].email);
    }

    fclose(fp);
    printf("Contacts loaded successfully !!!\n");
}
