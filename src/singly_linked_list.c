#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Attendance {
    int studentID;
    char date[15];
    char status[10]; 
    struct Attendance *next;
} Attendance;
Attendance* head = NULL;
// Create new node
Attendance* createNode(int id, char *date, char *status) {
    Attendance *newNode = (Attendance*)malloc(sizeof(Attendance));
    newNode->studentID = id;
    strcpy(newNode->date, date);
    strcpy(newNode->status, status);
    newNode->next = NULL;
    return newNode;
}
// Add record
void addAttendance(int id, char *date, char *status) {
    Attendance *newNode = createNode(id, date, status);
    if (head == NULL) head = newNode;
    else {
        Attendance *temp = head;
        while (temp->next) temp = temp->next;
        temp->next = newNode;
    }
    printf("Record Added Successfully!\n");
}
// Delete record
void deleteAttendance(int id, char *date) {
    Attendance *temp = head, *prev = NULL;
    while (temp) {
        if (temp->studentID == id && strcmp(temp->date, date) == 0) {
            if (prev) prev->next = temp->next;
            else head = temp->next;
            free(temp);
            printf("Record Deleted!\n");
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    printf("Record Not Found!\n");
}
// Search record
void searchAttendance(int id, char *date) {
    Attendance *temp = head;
    while (temp) {
        if (temp->studentID == id && strcmp(temp->date, date) == 0) {
            printf("Found: ID=%d Date=%s Status=%s\n", temp->studentID, temp->date, temp->status);
            return;
        }
        temp = temp->next;
    }
    printf("Record Not Found!\n");
}
// Display records for a date
void displayByDate(char *date) {
    Attendance *temp = head;
    printf("Attendance for %s:\n", date);
    while (temp) {
        if (strcmp(temp->date, date) == 0)
            printf("ID=%d Status=%s\n", temp->studentID, temp->status);
        temp = temp->next;
    }
}
// Reverse display using recursion
void reverseDisplay(Attendance *node) {
    if (node == NULL) return;
    reverseDisplay(node->next);
    printf("ID=%d Date=%s Status=%s\n", node->studentID, node->date, node->status);
}
// Clone linked list
Attendance* cloneList() {
    if (!head) return NULL;
    Attendance *cloneHead = NULL, *cloneTail = NULL, *temp = head;
    while (temp) {
        Attendance *newNode = createNode(temp->studentID, temp->date, temp->status);
        if (!cloneHead) cloneHead = cloneTail = newNode;
        else {
            cloneTail->next = newNode;
            cloneTail = newNode;
        }
        temp = temp->next;
    }
    return cloneHead;
}
// Main Menu
int main() {
    int choice, id;
    char date[15], status[10];
    do {
        printf("\n1.Add 2.Delete 3.Search 4.DisplayByDate 5.ReverseDisplay 6.Clone 7.Exit\n");
        scanf("%d", &choice);
        switch(choice) {
            case 1:
                printf("Enter ID Date(DD-MM-YYYY) Status(Present/Absent): ");
                scanf("%d %s %s", &id, date, status);
                addAttendance(id, date, status);
                break;
            case 2:
                printf("Enter ID & Date to Delete: ");
                scanf("%d %s", &id, date);
                deleteAttendance(id, date);
                break;
            case 3:
                printf("Enter ID & Date to Search: ");
                scanf("%d %s", &id, date);
                searchAttendance(id, date);
                break;
            case 4:
                printf("Enter Date: ");
                scanf("%s", date);
                displayByDate(date);
                break;
            case 5:
                reverseDisplay(head);
                break;
            case 6: {
                Attendance *clone = cloneList();
                printf("Cloned List:\n");
                reverseDisplay(clone);
                break;
            }
        }
    } while(choice != 7);
    return 0;
}
