#include <stdio.h>

#include <stdlib.h>

#include <string.h>

# define SIZE 20
struct node {
    int key;
    char name[100];
    char number[100];
    char mail[100];
    struct node * next;
};
typedef struct node * NODE;
struct hash {
    struct node * head;
    int count;
};
struct hash * hashTable = NULL; //initialising all pointers in Hash Table to NULL
NODE createNode(int key, char * name, char * number, char * mail) {
    NODE temp;
    temp = (NODE) malloc(sizeof(struct node));
    temp -> key = key;
    strcpy(temp -> number, number);
    strcpy(temp -> name, name);
    strcpy(temp -> mail, mail);
    temp -> next = NULL;
    return temp;
}
void insertToHash(int key, char * name, char * number, char * mail) {
    int hashIndex = key % SIZE;
    NODE newnode = createNode(key, name, number, mail); // head of list for the array element with index "hashIndex"
    if (!hashTable[hashIndex].head) {
        hashTable[hashIndex].head = newnode;
        hashTable[hashIndex].count = 1;
        return;
    }
    newnode -> next = (hashTable[hashIndex].head); // adding new node to the list
    hashTable[hashIndex].head = newnode; //incrementing number of nodes in List
    hashTable[hashIndex].count++;
    return;
}
NODE modify(int key, char * name) {
    int hashIndex = key % SIZE, choice;
    char new_no[100], new_mail[100];
    NODE cur = hashTable[hashIndex].head;
    while (cur != NULL && cur -> name != name)
        cur = cur -> next;
    printf("What do you to modify\n 1:Number 2:Mail ID?\n");
    scanf("%d", & choice);

    switch (choice) {
    case 1:
        printf("Enter updated number\n");
        scanf("%s", new_no);
        strcpy(cur -> number, new_no);
        break;
    case 2:
        printf("Enter updated Mail ID\n");
        scanf("%s", new_mail);
        break;
    }
    return cur;
}
void deleteFromHash(int key, char * name) {
    int hashIndex = key % SIZE, flag = 0; // finding the index using hash key
    NODE temp, cur;
    cur = hashTable[hashIndex].head; // cur pointing to first node of the hash index
    if (!cur) {
        printf("Given data is not present in hash Table!!\n");
        return;
    }
    temp = cur;
    while (cur != NULL) {
        if (cur -> key == key && strcmp(cur -> name, name) == 0) // delete the node with given key and name
        {
            flag = 1;
            if (cur == hashTable[hashIndex].head)
                hashTable[hashIndex].head = cur -> next;
            else
                temp -> next = cur -> next;
            hashTable[hashIndex].count--;
            free(cur);
            break;
        }
        temp = cur;
        cur = cur -> next;
    }
    if (flag)
        printf("Data deleted successfully from Hash Table\n");
    else
        printf("Given data is not present in hash Table!!!!\n");
    return;
}
void searchInHash(int key) {
    int hashIndex = key % SIZE, flag = 0;
    NODE myNode;
    myNode = hashTable[hashIndex].head;
    if (myNode == NULL) {
        printf("Search element unavailable in hash table\n");
        return;
    }
    while (myNode != NULL) {
        if (myNode -> key == key) {
            printf("Name : %s\n", myNode -> name);
            printf("Number : %s\n", myNode -> number);
            printf("Mail ID : %s\n", myNode -> mail);
            flag = 1;
            break;
        }
        myNode = myNode -> next;
    }
    if (!flag)
        printf("Search element unavailable in hash table\n");
    return;
}
void display() {
    NODE myNode;
    int i;
    for (i = 0; i < SIZE; i++) {
        if (hashTable[i].count == 0)
            continue;
        myNode = hashTable[i].head;
        if (!myNode)
            continue;
        printf("\nData at index %d in Hash Table:\n", i);
        printf("Name Number Mail ID \n");
        printf("--------------------------------------------\n");
        while (myNode != NULL) {
            printf("%-15s", myNode -> name);
            printf("%s\t\t", myNode -> number);
            printf("%s\n", myNode -> mail);
            myNode = myNode -> next;
        }
    }
    return;
}
typedef struct n {
    struct n * children[26];
    int isEnd;
}
trie;
void insert_trie(trie * ele, char * word) {
    trie * root = ele;
    int len = strlen(word);
    for (int i = 0; i < len; i++) {
        trie * curr = ele -> children[word[i] % 97];
        if (curr == NULL) {
            curr = malloc(sizeof(trie));
            curr -> isEnd = 0;
            for (int i = 0; i < 26; i++) curr -> children[i] = NULL;
        }
        if (i + 1 == len) curr -> isEnd = 1;

        ele -> children[word[i] % 97] = curr;
        ele = ele -> children[word[i] % 97];
    }
    ele = root;
}
char * append(char * slice, char part) {
    char * str = malloc(sizeof(char) * (strlen(slice) + 2));
    int i = 0;
    while (slice[i] != '\0') str[i] = slice[i++];
    str[i++] = part;
    str[i] = '\0';
    return str;
}
void print(trie * ele, char * slice) {
    if (ele == NULL) return;
    if (ele -> isEnd) printf("%s\n", slice);
    for (int i = 0; i < 26; i++)
        if (ele -> children[i] != NULL)
            print(ele -> children[i], append(slice, i + 97));
}
void autocomplete(trie * ele, char * prefix) {
    int len = strlen(prefix);
    for (int i = 0; i < len; i++) ele = ele -> children[prefix[i] % 97];
    print(ele, prefix);
}
int main() 
{ //init_array(hash_table);
    int i;
    char name[20], number[20];
    int c;
    trie n;
    n.isEnd = 0;
    for (int i = 0; i < 26; i++) n.children[i] = NULL;
    char input[100], mail[100];
    char choice = 'y', d;
    hashTable = (NODE) calloc(SIZE, sizeof(struct hash));
    char name_select[20], e, f = 'y';
    int ch;
    for (;;) {
        printf("\n 1:Add New Contact\n 2:View all the contacts\n 3:View/modify/delete existing contact \n 4.exit \n");
        scanf("%d", & ch);
        switch (ch) 
        {
            case 1:
                printf("\nEnter new contact name: ");
                scanf("%s", name);
                insert_trie( & n, name);

                int key = 0;
                for (i = 0; name[i] != '\0'; i++) {
                    key = key + (name[i] - '0');
                }
                printf("Enter new contact number: ");
                scanf("%s", number);
                printf("Enter the mail ID\n");
                scanf("%s", mail);
                insertToHash(key, name, number, mail);
                break;
            case 2:
                display();break;
            case 3:
                printf("---->Enter the name suggestion<----\n ");
                scanf("%s", input);
                printf("The suggestions are\n");
                autocomplete( & n, input);
                printf("\nSelect the contact you want to access \n");
                scanf("%s", name_select);
                int i;
                int key1 = 0;
                for (i = 0; name_select[i] != '\0'; i++)
                    key1 = key1 + (name_select[i] - '0');
                printf("\n 1:View 2:Delete 3:Modify 4:Dispaly all contacts\n");
                scanf("%d", & c);
                switch (c) 
                {
                    case 1:
                        searchInHash(key1);
                        break;
                    case 2:
                        deleteFromHash(key1, name_select);
                        break;
                    case 3:
                        modify(key1, name_select);
                        break;
                    case 4:
                        display();
                        break;
                    default:
                        break;
                }
                break;
            case 4:
                exit(0);
    }
    
    }
    return 0;
}
