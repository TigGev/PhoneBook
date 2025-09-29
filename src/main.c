#include <stdio.h>
#include <stdlib.h>
#include "../include/phonebook.h"

#define DATA_FILE "data/contacts.txt"

int main() {
    Contact contacts[MAX_CONTACTS];
    int count = 0;
    int choice;

    loadContacts(contacts, &count, DATA_FILE);

    do {
        printf("\n--- PhoneBook Menu ---\n");
        printf("1. Add Contact\n");
        printf("2. List Contacts\n");
        printf("3. Search Contact\n");
        printf("4. Delete Contact\n");
        printf("5. Save & Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addContact(contacts, &count); break;
            case 2: listContacts(contacts, count); break;
            case 3: searchContact(contacts, count); break;
            case 4: deleteContact(contacts, &count); break;
            case 5: saveContacts(contacts, count, DATA_FILE);
                    printf("Contacts saved. Exiting...\n");
                    break;
            default: printf("Invalid option. Try again.\n");
        }
    } while (choice != 5);

    return 0;
}
