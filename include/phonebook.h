#ifndef PHONEBOOK_H
#define PHONEBOOK_H

#define NAME_LEN 50
#define PHONE_LEN 20
#define MAX_CONTACTS 100

typedef struct {
    char name[NAME_LEN];
    char phone[PHONE_LEN];
} Contact;

void loadContacts(Contact contacts[], int *count, const char *filename);
void saveContacts(Contact contacts[], int count, const char *filename);
void addContact(Contact contacts[], int *count);
void listContacts(Contact contacts[], int count);
void searchContact(Contact contacts[], int count);
void deleteContact(Contact contacts[], int *count);

#endif
