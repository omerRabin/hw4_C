#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define NUM_LETTERS 26

typedef struct Node{
    char letter; // The letter go into the node
    int ends;  // count the num of words that ends in this node
    struct Node* children[NUM_LETTERS]; // an array to all the children of node
    int pos; // save the index of the letter in its word
} Node;

//----------newNode assign memory to the new node and insert a letter to p-> letter
Node* newNode(char c){
    Node* p = (Node*)malloc(sizeof(Node));
    if(p == NULL) {
        printf("No memory for create new node");
        exit(1);
    }
    p->letter = c; // insert the letter
    return p;
}
//------------ addWord pass the Trie and add the word to the Trie
void addWord(Node* root, char* s){
    int i = -1;
    while(*s){
        char current = tolower(*s);
        if(root->children[current-'a'] == NULL){ // if we now in a new word that was not exist before 
            root->children[current-'a'] = newNode(current); // define new node
            root->pos = i; // update the pos of current node to be the index of the letter in s (parameter)
        }
        root = root->children[current-'a']; // continue to the next node in the trie according to next char in s
        s++; // increse s pointer to the next character
        i++; // inscrese the index of s pointer
        if(!*s){ // if we finish to read str
            root->ends++; // increse ends
            root->pos = i; // save the index of the char
        }
    }
}
//--------printTrie print the Trie in ascending Lexicographic order
void printTrie(Node* root, char *str){
    if(root == NULL) return; // we finish pass the Trie
    str[root->pos] = root->letter; // Copies the letter from current node into str pointer by the original position of the letter in str
    if(root->ends){ // if in this node there is words that ends
        str[root->pos + 1] = 0; // put \0 in the end of the str
        printf("%s %d\n", str, root->ends);
    }
    for (int i = 0; i < NUM_LETTERS; i++){ 
        printTrie(root->children[i], str); // call recursive to printTrie, root->children[i] is the next node by ascending Lexicographic order
        //and str is the temporary pointer to the words
    }  
}
//----------printTrie_reversed print the Trie in descending Lexicographic order 
void printTrie_reversed(Node* root, char *str){
    if(root == NULL) return;
    str[root->pos] = root->letter;
    // first, call to printTrie_reversed recursive from the end(descending Lexicographic order) 
    for (int i = NUM_LETTERS-1 ; i >= 0; i--){ 
        printTrie_reversed(root->children[i], str); 
    }  
    // new print all words from after all the recursive calls
    if(root->ends){
        str[root->pos + 1] = 0;
        printf("%s %d\n", str, root->ends);
    }
}

void freeTrie(Node* root){//Free memory of trie
    if(root == NULL) return;
    for (int i = 0; i < NUM_LETTERS; i++){ // pass all the childern of root
        freeTrie(root->children[i]);
    }
    free(root); // after all recursive calls, we free all the children and root itself
}
int main(int argc, char const *argv[])
{
    //------------------------------- create the Trie
    Node* root = newNode(0); // initialize root to NULL (by aaski value 0)
    int i = 0;
    char *str = (char*)malloc(1); // initialize with one place in memory for \0
    while(1)
    {
        char c = getchar();
        if(isspace(c) || c == EOF){
            str = realloc(str, i+1); // add one place in memory for \0
            if(str == NULL){
                printf("realloc error");
                return 1;
            }
            str[i] = 0; //add \0 to the end of the string
            addWord(root, str);
            i=0;

            if(c == EOF) break;
        }
        else if(isalpha(c)){ // check if the char is alphabet or not
            c = tolower(c); // convert the char to be lower in case its not
            str = realloc(str, i+1); // add one place in memory for the new char
            if(str == NULL){
                printf("realloc error");
                return 1;
            }
            str[i] = c;
            i++;
        }
    }
//-------------------------------------
    if(argc == 1)
        printTrie(root, str);
    else if(argc == 2 && strcmp(argv[1],"r")==0) 
        printTrie_reversed(root, str);
    // free memory
    free(str);
    freeTrie(root);
    return 0;
}
