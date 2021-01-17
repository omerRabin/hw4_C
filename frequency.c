#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define NUM_LETTERS 26
typedef struct node{
    char letter; // The letter go into the node
    int wordsCount;  // count the num of words that ends in this node
    struct node* children[NUM_LETTERS]; // an array to all the children of node
    int index; // save the index of the letter in its word
} node;


//----------createNode assign memory to the new node and insert a letter to p-> letter
node* createNode(char c){
    node* n = (node*)malloc(sizeof(node));
    if(n == NULL) {
        printf("No memory for create new node");
        exit(1);
    }
    n->letter = c; // insert the letter
    return n;
}

//--------TriePrinter print the Trie in ascending Lexicographic order
void TriePrinter(node* head, char *str){
    if(head == NULL) return; // we finish pass the Trie
    int originalIndex = head->index;
    int numOfWords = head->wordsCount;
    str[originalIndex] = head->letter; // Copies the letter from current node into str pointer by the original position of the letter in str
    if(numOfWords){ // if in this node there is words that ends
        str[originalIndex + 1] = 0; // put \0 in the end of the str
        printf("%s %d\n", str, numOfWords);
    }
    for (int i = 0; i < NUM_LETTERS; i++){ 
        TriePrinter(head->children[i], str); // call recursive to TriePrinter, head->children[i] is the next node by ascending Lexicographic order
        //and str is the temp pointer to the words
    }  
}

//----------TriePrinterInReverse print the Trie in descending Lexicographic order 
void TriePrinterInReverse(node* head, char *str){
    if(head == NULL) return;
    int originalIndex =head->index;
    str[originalIndex] = head->letter;
    // first, call to TriePrinterInReverse recursive from the end(descending Lexicographic order) 
    for (int i = NUM_LETTERS-1 ; i >= 0; i--){ 
        TriePrinterInReverse(head->children[i], str); 
    }  
    // new print all words from after all the recursive calls
    if(head->wordsCount){
        str[originalIndex + 1] = 0;
        printf("%s %d\n", str, head->wordsCount);
    }
}

//------------ addWord pass the Trie and add the word to the Trie
void addWord(node* head, char* word){
    int index = -1;
    while(*word!=0){
        char current = tolower(*word);
        if(head->children[current-'a'] == NULL){ // if we now in a new word that was not exist before 
            head->children[current-'a'] = createNode(current); // define new node
            head->index = index; // update the index of current node to be the index of the letter in s (parameter)
        }
        index++; // inscrese the index of s pointer
        word++; // increse s pointer to the next character
        head = head->children[current-'a']; // continue to the next node in the trie according to next char in s
        if(!*word){ // if we finish to read str
            head->wordsCount++; // increse ends
            head->index = index; // save the index of the char
        }
    }
}
void freeTrie(node* head){//Free memory of trie
    if(head == NULL) return;
    for (int i = 0; i < NUM_LETTERS; i++){ // pass all the childern of head
        freeTrie(head->children[i]);
    }
    free(head); // after all recursive calls, we free all the children and head itself
}
int main(int argc, char const *argv[])
{
    //------------------------------- create the Trie
    node* head = createNode(0); // initialize head to NULL (by aaski value 0)
    int i = 0;
    char *str = (char*)malloc(1); // initialize str for storage the input 
    if(str == NULL){
        printf("There is no memory for malloc str");
        return 1;
    }
    while(1)
    {
        char ch = getchar(); 
        if(ch == EOF || isspace(ch)){
            str = realloc(str, i+1); // add one place in memory for \0
            if(str == NULL){
                printf("realloc error");
                return 1;
            }
            str[i] = 0; //add \0 to the end of the string
            addWord(head, str);
            i=0;

            if(ch == EOF) break;
        }
        else if(isalpha(ch)){ // check if the char is alphabet or not
            ch = tolower(ch); // convert the char to be lower in case its not
            str = realloc(str, i+1); // add one place in memory for the new char
            if(str == NULL){
                printf("realloc error");
                return 1;
            }
            str[i] = ch;
            i++;
        }
    }
//-------------------------------------
    if(argc == 1)
        TriePrinter(head, str);
    else if(argc == 2 && strcmp(argv[1],"r")==0)
        TriePrinterInReverse(head, str);
    // free memory
    free(str);
    freeTrie(head);
    return 0;
}
