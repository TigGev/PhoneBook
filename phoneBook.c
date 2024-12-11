#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/uio.h>
#include <sys/mman.h>
#include <errno.h>
#include <ctype.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#define NAME_LENGTH 50
#define PHONE_NUM_LENGTH 15
#define EMAIL_LENGTH 50
#define MAX_CONTACT_COUNT 300


typedef struct {
    char name[NAME_LENGTH];
    char phone[PHONE_NUM_LENGTH];
    char email[EMAIL_LENGTH];
} contact;

void contact_arr_init (contact** arr, int* size) {
    *arr = malloc(MAX_CONTACT_COUNT * sizeof(contact));
    if (arr == NULL) {
        perror("Contact_arr_init");
        exit(EXIT_FAILURE);
    }
    int count = 0;
    FILE* book = fopen("./phoneBook.txt", "r+");
    while (fgets((*arr)[count].name, NAME_LENGTH, book)) {
        fgets((*arr)[count].phone, PHONE_NUM_LENGTH, book);
        fgets((*arr)[count++].email, EMAIL_LENGTH, book);
    }
    *arr = realloc(*arr, count * sizeof(contact));
    *size = count;
    fclose(book);
}

void contact_arr_destroy (contact* arr) {
    free(arr);
}

int count;
contact* allContacts;


int my_strcmp(const char *str1, const char *str2) {

	while (toupper(*str1) == toupper(*str2)) {
		if(*str1 == '\0') return 0;
		str1++;
		str2++;
	}
	return toupper(*str1) - toupper(*str2);
}

int my_strncmp(const char *str1, const char *str2, size_t n) {
	const char * tmp = str1;
        while (toupper(*str1) == toupper(*str2)) {
                if((str1 - tmp) == (n-1)) return 0;
                str1++;
                str2++;
        }
        return toupper(*str1) - toupper(*str2);
	
}

void sortByName (void) {

    for (int i = 0; i < count - 1; ++i) {
        for (int j = i + 1; j < count; ++j) {
            if (my_strcmp(allContacts[j].name, allContacts[i].name) < 0) {
                contact tmp = allContacts[j];
               allContacts[j] = allContacts[i];
               allContacts[i] = tmp;
            }
        }
    }

    FILE* book = fopen("./phoneBook.txt", "r+");
    for (int i = 0; i < count; ++i) {
        fprintf(book, "%s%s%s", allContacts[i].name, allContacts[i].phone, allContacts[i].email);
    }

    fclose(book);
}

void addContact(void) {
    contact newContact;
    getchar();
    printf("Enter contact name: ");
    fgets(newContact.name, NAME_LENGTH, stdin);
    fflush(stdin);
    printf("Enter contact phone number: ");
    fgets(newContact.phone, NAME_LENGTH, stdin);
    fflush(stdin);
    printf("Enter contacr email address: ");
    fgets(newContact.email, EMAIL_LENGTH, stdin);
    fflush(stdin);
    putchar(10);

    

    allContacts = realloc(allContacts, (count + 1) * sizeof(contact));
    strcpy(allContacts[count].name, newContact.name);
    strcpy(allContacts[count].phone, newContact.phone);
    strcpy(allContacts[count++].email, newContact.email);

    sortByName();

    FILE* book = fopen("./phoneBook.txt", "w");
    for (int i = 0; i < count; ++i) {
        fprintf(book, "%s", allContacts[i].name);
        fprintf(book, "%s", allContacts[i].phone);
        fprintf(book, "%s", allContacts[i].email);
    }

    fclose(book);


    printf("The operation was successful.\n");
    putchar(10);
}

void deleteContact(void) {
    printf("Enter the name of the contact you want to delete: ");
    char delName[NAME_LENGTH];
    getchar();
    fgets(delName, NAME_LENGTH, stdin);
    putchar(10);
    int flag = 0;
    for (int i = 0; i < count; ++i) {
        if (strcmp(delName, allContacts[i].name) == 0) {
            if (i == count) {
                flag = 1;
                allContacts = realloc(allContacts, --count * sizeof(contact));
            }
            else {
                flag = 1;
                for (int j = i ; j < count - 1; ++j) {
                    allContacts[j] = allContacts[j + 1];
                }
                allContacts = realloc(allContacts, --count * sizeof(contact));
            }
        }
    }
    if (flag == 0) {
        printf("There is no such contact\n\n");
        return;
    }
    FILE* book = fopen("./phoneBook.txt", "w");
    for (int i = 0; i < count; ++i) {
        fprintf(book, "%s", allContacts[i].name);
        fprintf(book, "%s", allContacts[i].phone);
        fprintf(book, "%s", allContacts[i].email);
    }
    fclose(book);
    printf("The operation was successful.\n\n");
}

void search(void) {
    putchar(10);
    int action;
    do {
        printf("1.Search by name\n");
        printf("2.Search by phone\n");
        printf("3.Search by email\n");
        printf("\n>");
        scanf("%d", &action);
    }
    while (action < 0 && action > 4);
    char search[NAME_LENGTH];
    switch (action) {
        case 1:
            printf("Enter the name of the contact you are looking for: ");
            break;
        case 2:
            printf("Enter the phone number of the contact you are looking for: ");
            break;
        case 3:
            printf("Enter the email of the contact you are looking for: ");
            break;
    }
            getchar();
            fgets(search, NAME_LENGTH, stdin);

    for (int i = 0; i < count; ++i) {
        if (action == 1 && strcmp(search, allContacts[i].name) == 0) {
            putchar(10);
            printf("Name: %sPhone: %sEmail: %s\n", allContacts[i].name, allContacts[i].phone, allContacts[i].email);
            putchar(10);
            return;
        }
        else if (action == 2 && strcmp(search, allContacts[i].phone) == 0) {
            putchar(10);
            printf("Name: %sPhone: %sEmail: %s\n", allContacts[i].name, allContacts[i].phone, allContacts[i].email);
            putchar(10);
            return;
        }
        else if (action == 2 && strcmp(search, allContacts[i].email) == 0) {
            putchar(10);
            printf("Name: %sPhone: %sEmail: %s\n", allContacts[i].name, allContacts[i].phone, allContacts[i].email);
            putchar(10);
            return;
        }
    }
    printf("\nThere is no such contact\n\n");
}

void aditional_search (void)  {
    char name[NAME_LENGTH];
    printf("Enter the first letters of the contact you are looking for: ");
    getchar();
    fgets(name, NAME_LENGTH, stdin);
    name[strcspn(name, "\n")] = 0;
    int flag = 0;
    for (int i = 0; i < count; ++i) {
        if (my_strncmp(name, allContacts[i].name, strlen(name)) == 0) {
            flag = 1;
            putchar(10);
            printf("Name: %sPhone: %sEmail: %s\n", allContacts[i].name, allContacts[i].phone, allContacts[i].email);
            putchar(10);
        }
    }
    if (flag == 0) {
        printf("There is no such contact\n");
    }
}

void view_all_contacts(void) {
    for (int i = 0; i < count; ++i) {
        putchar(10);
        printf("Name: %sPhone: %sEmail: %s\n", allContacts[i].name, allContacts[i].phone, allContacts[i].email);
        putchar(10);
    }
}

void update_contact(void) {
    char name[NAME_LENGTH];
    printf("Enter the name of the contact you want to update: ");
    getchar();
    fgets(name, NAME_LENGTH, stdin);
    for (int i = 0; i < count; ++i) {
        if (strcmp(name, allContacts[i].name) == 0) {
            int action;
            do {
                printf("1.Update name\n");
                printf("2.Update phone\n");
                printf("3.Update email\n");
                printf("\n>");
                scanf("%d", &action);
            }
            while (action < 0 && action > 4);
            switch (action) {
                case 1:
                    printf("Enter the new name: ");
                    break;
                case 2:
                    printf("Enter the new phone: ");
                    break;
                case 3:
                    printf("Enter the new email: ");
                    break;
            }
            getchar();
            fgets(name, NAME_LENGTH, stdin);

            switch (action) {
                case 1:
                    strcpy(allContacts[i].name, name);
                    sortByName();
                    return;
                case 2:
                    strcpy(allContacts[i].phone, name);
                    break;
                case 3:
                    strcpy(allContacts[i].email, name);
                    break;
            }
            FILE* book = fopen("./phoneBook.txt", "w");
            for (int i = 0; i < count; ++i) {
                fprintf(book, "%s", allContacts[i].name);
                fprintf(book, "%s", allContacts[i].phone);
                fprintf(book, "%s", allContacts[i].email);
            }
            fclose(book);
            printf("The operation was successful.\n\n");
            return;
        }
    }

    printf("There is no such contact\n");

}

int main() {
    int fd = open("phoneBook.txt", O_RDWR | O_CREAT | O_EXCL, 0666);
    if (fd != -1) {
        close(fd);
    }
    contact_arr_init(&allContacts, &count);
    int actionNumber;
    while (1) {
        printf("What action do you want to take?\n");
        printf("1. Add Contact\n");
        printf("2. Delete Contact\n");
        printf("3. Search contact\n");
        printf("4. Aditional Search\n");
        printf("5. View all contacts\n");
        printf("6. Update contact\n");
        printf("7. Exit\n");
        // printf("\n>");
        do {
            printf("Enter the action number:> ");
            scanf("%d", &actionNumber);
            putchar(10);
            if (actionNumber <= 0 || actionNumber > 7) {
                printf("There is no such thing.\n\n");
                continue;
            }
        }
        while (actionNumber <= 0 || actionNumber > 7);
        switch (actionNumber) {
            case 1:
                addContact();
                break;
            case 2:
                deleteContact();
                break;
            case 3:
                search();
                break;            
            case 4:
                aditional_search();
                break;                
            case 5:
                view_all_contacts();
                break;                
            case 6:
                update_contact();
                break;                
            case 7: 
                exit(0);
        }
    }
}