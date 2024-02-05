#include <stdio.h>
#include <stdlib.h>

// Structure for a list node
typedef struct Node {
    char data;            // Character
    struct Node* next;    // Pointer to the next node
} Node;

// Function to append a node to the end of the list
Node* appendToList(Node* head, char data) {
   Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
       fprintf(stderr, "Memory allocation error\n");
    exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;

    if (!head) {
        return newNode; // If the list is empty, the new node becomes the head
    }

    Node* current = head;
    while (current->next) {
        current = current->next;
    }

    current->next = newNode;
    return head;
}

// Function to check if a character is a vowel
int isVowel(char c) {
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
            c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U');
}

// Function to remove consonants from a string (list)
Node* removeConsonants(Node* head) {
    Node* current = head;
    Node* prev = NULL;

    while (current) {
        char c = current->data;

        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
            if (isVowel(c)) {
                prev = current;
                current = current->next;
            } else {
                Node* temp = current;
                current = current->next;

                if (prev) {
                    prev->next = current;
                } else {
                    head = current;
                }

                free(temp);
            }
        } else {
            prev = current;
            current = current->next;
        }
    }

    return head;
}

// Function to print the list within quotes
void printList(Node* head) {
    putchar('"');
    while (head) {
        putchar(head->data);
        head = head->next;
    }
    putchar('"');
    putchar('\n');
}

int main() {
    Node* head = NULL;
    int c;

    printf("Enter strings (end of input - Ctrl+D):\n");

    // Input strings using getchar()
    while ((c = getchar()) != EOF) {
        head = appendToList(head, (char)c);
    }

    // Remove consonants
    head = removeConsonants(head);

    // Print the original string
    printf("Original string: ");
    printList(head);

    // Free the memory allocated for the list
    while (head) {
        Node* temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}