#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ENTRIES 10 // Maximum number of entries

struct node {
    char firstname[20];
    char lastname[20];
    char number[15];
    struct node* next;
};

struct node* start = NULL;
int entryCount = 0; // Counter for the number of entries

struct node* getnode() {
    return (struct node*)malloc(sizeof(struct node));
}

void display(struct node* start) {
    struct node* temp;
    temp = start;
    while (temp != NULL) {
        printf("FIRST NAME: %s\n", temp->firstname);
        printf("LAST NAME: %s\n", temp->lastname);
        printf("PHONE NUMBER: %s\n", temp->number);
        temp = temp->next;
    }
}

void update() {
    char f[20], l[20];
    printf("Enter first name to update:\n");
    scanf("%s", f);
    printf("Enter last name to update:\n");
    scanf("%s", l);
    struct node* temp = start;

    while (temp != NULL) {
        if (strcmp(temp->firstname, f) == 0 && strcmp(temp->lastname, l) == 0) {
            printf("Enter new information:\n");
            printf("New First Name: ");
            scanf("%s", temp->firstname);
            printf("New Last Name: ");
            scanf("%s", temp->lastname);
            printf("New Phone Number: ");
            scanf("%s", temp->number);
            printf("Contact updated successfully.\n");
            return;
        }
        temp = temp->next;
    }
    printf("Contact not found.\n");
}





void sort() {
    struct node* current;
    struct node* next;
    char temp[20];

    if (start == NULL) {
        printf("List is empty.\n");
        return;
    }

    for (current = start; current != NULL; current = current->next) {
        for (next = current->next; next != NULL; next = next->next) {
            if (strcmp(current->lastname, next->lastname) > 0) {
                // Swap the last names
                strcpy(temp, current->lastname);
                strcpy(current->lastname, next->lastname);
                strcpy(next->lastname, temp);

                // Swap the first names
                strcpy(temp, current->firstname);
                strcpy(current->firstname, next->firstname);
                strcpy(next->firstname, temp);

                // Swap the numbers
                strcpy(temp, current->number);
                strcpy(current->number, next->number);
                strcpy(next->number, temp);
            }
        }
    }
    printf("List sorted by last name:\n");
    display(start);
}


void insert() {
    if (entryCount >= MAX_ENTRIES) {
        printf("Maximum number of entries reached (10 entries).\n");
        return;
    }

    struct node* temp, * nn;
    nn = getnode();
    temp = start;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    printf("ENTER FIRST NAME:\n");
    scanf("%s", nn->firstname);
    printf("ENTER LAST NAME:\n");
    scanf("%s", nn->lastname);
    printf("ENTER NUMBER:\n");
    scanf("%s", nn->number);
    temp->next = nn;
    nn->next = NULL;
    entryCount++;
    display(start);
}

struct node* create() {
    struct node* nn;
    nn = getnode();
    start = nn;
    printf("Enter First name:\n");
    scanf("%s", nn->firstname);
    printf("Enter Last name:\n");
    scanf("%s", nn->lastname);
    printf("Enter number:\n");
    scanf("%s", nn->number);
    nn->next = NULL;
    display(start);
    return start;
}

void search() {
    struct node* temp;
    char f[20], l[20];
    temp = start;
    printf("Enter first name to be searched:\n");
    scanf("%s", f);
    printf("Enter last name to be searched:\n");
    scanf("%s", l);
    while (temp != NULL) {
        if (strcmp(temp->firstname, f) == 0 && strcmp(temp->lastname, l) == 0) {
            printf("First Name: %s\n", temp->firstname);
            printf("Last Name: %s\n", temp->lastname);
            printf("Number: %s\n", temp->number);
            return;
        }
        temp = temp->next;
    }
    printf("Contact not found.\n");
}

void del() {
    struct node* pretemp, * temp;
    char f[20], l[20];
    temp = start;
    pretemp = start;

    if (start == NULL) {
        printf("List is empty.\n");
        return;
    }

    printf("Enter first name to be deleted:\n");
    scanf("%s", f);
    printf("Enter last name to be deleted:\n");
    scanf("%s", l);

    if (strcmp(start->firstname, f) == 0 && strcmp(start->lastname, l) == 0) {
        start = start->next;
        free(temp);
        printf("Contact deleted successfully.\n");
        return;
    }

    while (temp != NULL) {
        if (strcmp(temp->firstname, f) == 0 && strcmp(temp->lastname, l) == 0) {
            pretemp->next = temp->next;
            free(temp);
            printf("Contact deleted successfully.\n");
            return;
        }
        pretemp = temp;
        temp = temp->next;
    }
    printf("Contact not found.\n");
}


int main() {
    int op, ch;
    do {
        printf("-------PHONEBOOK--------\n");
        printf("1.Create\n2.Insert\n3.Display\n4.Delete\n5.Search\n6.Sort\n7.Update\n");
        printf("Enter your choice:");
        scanf("%d", &ch);
        switch (ch) {
            case 1:
                start = create();
                entryCount = 1; // Reset the count when creating a new entry
                break;
            case 2:
                insert();
                break;
            case 3:
                display(start);
                break;
            case 4:
                del();
                break;
            case 5:
                search();
                break;
            case 6:
                sort();
                break;
            case 7:
                update();
                break;
        }
        if (entryCount >= MAX_ENTRIES) {
            printf("Maximum number of entries reached (10 entries).\n");
            break; 
        }
        printf("Do you want to continue? 1 for yes / 0 for no:");
        scanf("%d", &op);
    } while (op != 0 && entryCount < MAX_ENTRIES);
    return 0;
}
