//
// Created by Gabriel on 01/01/2022.
//

#ifndef UNTITLED_FILEMANAGAR_H
#define UNTITLED_FILEMANAGAR_H
#include "myB+.h"
void keyIn(char key[5], char *id);

struct teste keyOut(const char *key);

void findStruct(char* nome);

void write(myRegistro *t, const char* file_path, const char* file_path_readable);

bool isEqual(struct myregistro target, struct myregistro target2);

void delete_from_file(char* key, char* target2, const char* file_Path, int mode);

void delete_element(char* key);

void purge(const char* file_Path, const char* readable_file_Path, const char* index_file_Path);

void printFile(const char* file_path);

#endif //UNTITLED_FILEMANAGAR_H
