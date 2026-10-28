#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *next;
} node;

void insert_end(node **start, int val);
void insert_start(node **start, int val);
void insert_after(node **start, int target, int val);
void insert_before(node **start, int target, int val);
void display(node *start);
void delete_end(node **start);
void delete_start(node **start);
void delete_after(node **start, int target);
void delete_before(node **start, int target);
int count_elements(node *start);

int main(void) {
    node *head = NULL;
    int choice, val, target;

    while (1) {
        printf("\n--- Linked List Menu ---\n");
        printf("1. Insert A New Node (End)\n");
        printf("2. Display the linked list\n");
        printf("3. Insert in the Beginning\n");
        printf("4. Count Number of Elements\n");
        printf("5. Delete from the End\n");
        printf("6. Insert After a given Node\n");
        printf("7. Insert Before a given Node\n");
        printf("8. Delete Before a given Node\n");
        printf("9. Delete Start\n");
        printf("10. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value: "); scanf("%d", &val);
                insert_end(&head, val); break;
            case 2:
                display(head); break;
            case 3:
                printf("Enter value: "); scanf("%d", &val);
                insert_start(&head, val); break;
            case 4:
                printf("Total elements: %d\n", count_elements(head)); break;
            case 5:
                delete_end(&head); break;
            case 6:
                printf("Enter target: "); scanf("%d", &target);
                printf("Enter value: "); scanf("%d", &val);
                insert_after(&head, target, val); break;
            case 7:
                printf("Enter target: "); scanf("%d", &target);
                printf("Enter value: "); scanf("%d", &val);
                insert_before(&head, target, val); break;
            case 8:
                printf("Enter target: "); scanf("%d", &target);
                delete_before(&head, target); break;
            case 9:
                delete_start(&head); break;
            case 10:
                exit(0);
        }
    }
    return 0;
}

void insert_start(node **start, int val) {
    node *new_node = (node*)malloc(sizeof(node));
    new_node->data = val;
    new_node->next = *start;
    *start = new_node;
}

void insert_end(node **start, int val) {
    node *new_node = (node*)malloc(sizeof(node));
    new_node->data = val;
    new_node->next = NULL;
    if (*start == NULL) {
        *start = new_node;
        return;
    }
    node *temp = *start;
    while (temp->next != NULL) temp = temp->next;
    temp->next = new_node;
}

void insert_after(node **start, int target, int val) {
    node *temp = *start;
    while (temp != NULL && temp->data != target) temp = temp->next;
    if (temp == NULL) return;
    node *new_node = (node*)malloc(sizeof(node));
    new_node->data = val;
    new_node->next = temp->next;
    temp->next = new_node;
}

void insert_before(node **start, int target, int val) {
    if (*start == NULL) return;
    if ((*start)->data == target) {
        insert_start(start, val);
        return;
    }
    node *temp = *start;
    while (temp->next != NULL && temp->next->data != target) temp = temp->next;
    if (temp->next == NULL) return;
    node *new_node = (node*)malloc(sizeof(node));
    new_node->data = val;
    new_node->next = temp->next;
    temp->next = new_node;
}

void delete_start(node **start) {
    if (*start == NULL) return;
    node *temp = *start;
    *start = (*start)->next;
    free(temp);
}

void delete_end(node **start) {
    if (*start == NULL) return;
    if ((*start)->next == NULL) {
        free(*start); *start = NULL; return;
    }
    node *temp = *start;
    while (temp->next->next != NULL) temp = temp->next;
    free(temp->next);
    temp->next = NULL;
}

void delete_before(node **start, int target) {
    if (*start == NULL || (*start)->next == NULL) return;
    if ((*start)->next->data == target) {
        delete_start(start);
        return;
    }
    node *temp = *start;
    while (temp->next->next != NULL && temp->next->next->data != target)
        temp = temp->next;
    if (temp->next->next == NULL) return;
    node *to_delete = temp->next;
    temp->next = temp->next->next;
    free(to_delete);
}

void display(node *start) {
    node *temp = start;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

int count_elements(node *start) {
    int count = 0;
    while (start != NULL) { count++; start = start->next; }
    return count;
}