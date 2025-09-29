#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/phonebook.h"

void loadContacts(Contact contacts[], int *count, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) return; // no file yet
    *count = 0;
    while (fscanf(file, "%49s %19s", contacts[*count].name, contacts[*count].phone) == 2) {
        (*count)++;
        if (*count >= MAX_CONTACTS) break;
    }
    fclose(file);
}

void saveContacts(Contact contacts[], int count, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Error: cannot open file for writing.\n");
        return;
    }
    for (int i = 0; i < count; i++) {
        fprintf(file, "%s %s\n", contacts[i].name, contacts[i].phone);
    }
    fclose(file);
}

void addContact(Contact contacts[], int *count) {
    if (*count >= MAX_CONTACTS) {
        printf("PhoneBook is full!\n");
        return;
    }

    printf("Enter name: ");
    scanf("%49s", contacts[*count].name);
    printf("Enter phone: ");
    scanf("%19s", contacts[*count].phone);

    (*count)++;
    printf("Contact added successfully.\n");
}

void listContacts(Contact contacts[], int count) {
    if (count == 0) {
        printf("No contacts found.\n");
        return;
    }
    printf("\n--- Contact List ---\n");
    for (int i = 0; i < count; i++) {
        printf("%d. %s - %s\n", i + 1, contacts[i].name, contacts[i].phone);
    }
    printf("--------------------\n");
}

void searchContact(Contact contacts[], int count) {
    char name[NAME_LEN];
    printf("Enter name to search: ");
    scanf("%49s", name);

    for (int i = 0; i < count; i++) {
        if (strcmp(contacts[i].name, name) == 0) {
            printf("Found: %s - %s\n", contacts[i].name, contacts[i].phone);
            return;
        }
    }
    printf("Contact not found.\n");
}

void deleteContact(Contact contacts[], int *count) {
    char name[NAME_LEN];
    printf("Enter name to delete: ");
    scanf("%49s", name);

    for (int i = 0; i < *count; i++) {
        if (strcmp(contacts[i].name, name) == 0) {
            for (int j = i; j < *count - 1; j++) {
                contacts[j] = contacts[j + 1];
            }
            (*count)--;
            printf("Contact deleted.\n");
            return;
        }
    }
    printf("Contact not found.\n");
}
