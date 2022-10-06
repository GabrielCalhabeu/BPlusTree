#ifndef BTREES_MYB_H
#define BTREES_MYB_H
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define filePath "D:\\Programas\\aeds2\\BTrees\\teste.dat"
#define tempFilePath "D:\\Programas\\aeds2\\BTrees\\temp.dat"
#define readableFile "D:\\Programas\\aeds2\\BTrees\\readable.txt"
#define indexPath "D:\\Programas\\aeds2\\BTrees\\index.txt"
#define saveFile "D:\\Programas\\aeds2\\BTrees\\saveFile.txt"
#define BUFFER_SIZE 256


//Registro
typedef struct myregistro{
    char nome[50];
    int idade;
    float pesoKg;
    struct myregistro *self;
} myRegistro;

typedef struct myKey{
    char chave[5];
    myRegistro *pointer;
} myKey;

//Nodulo
typedef struct mynode{
    void **pointers;
    myKey *chaves;
    struct mynode *parent;
    bool is_leaf;
    int num_chaves;
    struct mynode *next;
} myNode;

void strcopy(char a[], const char *b, int size);

myNode *inserir(myNode *root, const char* key, myRegistro a);

myRegistro *Find(myNode *root, const char* key, myNode **leaf_out);

void saveTree(myNode *const root);

myNode *insertIntoParent(myNode *root, myNode *left, const char* key, myNode *right);

myNode *insertIntoLeafAfterSplitting(myNode *root, myNode *leaf, const char* key, myRegistro *pointer);

myNode *insertIntoNodeAfterSplitting(myNode *root, myNode *old_node, int left_index, const char* key, myNode *right);

myNode *insertIntoNode(myNode *root, myNode *n, int left_index, const char *key, myNode *right);

int getLeftIndex(myNode *parent, myNode *left);

myNode *insertIntoNewRoot(myNode *left, const char* key, myNode *right);

int myCut(int length);

myNode *insertIntoLeaf(myNode *leaf, const char* key, myRegistro *pointer);

myRegistro *makeMyRecord(myRegistro a);

myNode *NewTree(const char * key, myRegistro *pointer);

myNode *findMyLeaf(myNode *const root, const char* key);

myNode *insereToNode(myNode *root, myNode *n, int left_index, const char *key, myNode *right);

myNode *insereToLeaf(myNode *leaf, const char *key, myRegistro *pointer);

bool isSmaller(const char * a, const char *b);

myNode *makeMyLeaf(void);

void printTree(myNode *const root);

int pathToLeaves(myNode *const root, myNode *child);

myNode *makeMyNode(void);

myNode *myDequeue(void);

void myEnqueue(myNode *new_node);

myNode * delete_entry(myNode * root, myNode * n, const char* key, void * pointer);

myNode * delete(myNode * root, const char* key);

myNode* importTree(myNode *root);

#endif //BTREES_MYB_H
