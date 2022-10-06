#include "fileManager.h"

#define filePath "D:\\Programas\\aeds2\\BTrees\\teste.dat"
#define tempFilePath "D:\\Programas\\aeds2\\BTrees\\temp.dat"
#define readableFile "D:\\Programas\\aeds2\\BTrees\\readable.txt"
#define indexPath "D:\\Programas\\aeds2\\BTrees\\index.txt"
#define saveFile "D:\\Programas\\aeds2\\BTrees\\saveFile.txt"
#define FORMAT_OUT "%s, %d, %.2f\n"
#define FORMAT_IN "%[^,\n], %d, %f, %p"
#define FORMAT_INDEX "%s, %p\n"

void keyIn(char key[5], char *id) {

    key[0] = id[0];
    key[1] = id[1];
    key[2] = id[strlen(id)-2];
    key[3] = id[strlen(id)-1];
    key[4] = '\0';

}

//struct teste keyOut(const char *key){
//
//    FILE *indexFile = fopen(indexPath, "r");
//    FILE *file = fopen(filePath, "r");
//    myKey tempIndex;
//    struct teste tempTest;
//    int found = false;
//    while(fread(&tempIndex, sizeof(struct indice), 1, indexFile)){
//        if(strcmp(key, tempIndex.chave) == 0){
//            tempTest = *tempIndex.registro;
//            found = true;
//            break;
//        }
//    }
//
//    if(!found){
//        printf("Key not Found!");
//        exit(1);
//    }
//
//    fclose(indexFile);
//    fclose(file);
//
//    return tempTest;
//}

//void findStruct(char* nome){
//    const char *key = keyIn(nome);
//    char newKey[5];
//    memcpy(newKey, key, 5);
//    struct teste temp;
//    temp = keyOut(newKey);
//    printf("\n%s, %d, %.2f, %p\n", temp.nome, temp.idade, temp.pesoKg, temp.next);
//}


void write(myRegistro *t, const char* file_path, const char* file_path_readable) {
    FILE *file = fopen(file_path, "a");
    FILE *rfile = fopen(file_path_readable, "a");
    FILE *indexFile = fopen(indexPath, "a");
    char key[5] = {"aaaa\0"};
    keyIn(key, t->nome);
    char *newkey;
    myKey tempIndex = {
            .pointer = t,
    };

    memcpy(tempIndex.chave, key, 4);
    fprintf(rfile, FORMAT_OUT, t->nome, t->idade, t->pesoKg);

    fwrite(t, sizeof(*t), 1, file);
    fwrite(&tempIndex, sizeof(tempIndex), 1, indexFile);

    fclose(file);
    fclose(rfile);
    fclose(indexFile);
}

bool isEqual(struct myregistro target, struct myregistro target2){
    if(target.idade == target2.idade && target2.pesoKg == target2.pesoKg){
        if(strcmp(target2.nome, target2.nome) == 0){
            return 1;
        }
    }
    return 0;
}

void purge(const char* file_Path, const char* readable_file_Path, const char* index_file_Path) {
    FILE *rfile = fopen(readable_file_Path, "w");
    fclose(rfile);
    FILE *file = fopen(file_Path, "w");
    fclose(file);
    FILE *ifile = fopen(index_file_Path, "w");
    fclose(ifile);
}


//void delete_from_file(char* key, char* target2, const char* file_Path, int mode){
//
//    FILE *newFile = fopen(tempFilePath, "w");
//    FILE *originalFile = fopen(file_Path, "r");
//
//    struct teste target = keyOut(key);
//    struct teste temp;
//
//    fseek(originalFile, 0, SEEK_SET);
//    fseek(newFile, 0, SEEK_SET);
//    int i = 0;
//    if(mode == 1) {
//        while (fread(&temp, sizeof(struct teste), 1, originalFile)) {
//            if (!isEqual(temp, target)) {
//                fwrite(&temp, sizeof(temp), 1, newFile);
//            }
//            i++;
//        }
//    }
//    if(mode == 2){
//        struct indice temp2;
//        while (fread(&temp2, sizeof(struct indice), 1, originalFile)) {
//            if (strcmp(temp2.chave, key) != 0) {
//                fwrite(&temp2, sizeof(temp2), 1, newFile);
//            }
//            i++;
//        }
//    }
//    int dump;
//    if(mode == 3){
//        while (fscanf(originalFile, "%[^,], %d, %f, %p", temp.nome, &temp.idade, &temp.pesoKg, &temp.next)){
//            dump = fgetc(originalFile);
//            if(dump == EOF){
//                break;
//            }
//            if (!(isEqual(temp, target))) {
//                fprintf(newFile, FORMAT_OUT, temp.nome, temp.idade, temp.pesoKg, temp .next);
//            }
//            i++;
//        }
//    }
//
//    fclose(originalFile);
//    fclose(newFile);
//
//    remove(file_Path);
//    rename(tempFilePath, file_Path);
//}

//void delete_element(char* key){
//    delete_from_file(key, key, readableFile, 3);
//    delete_from_file(key, key, filePath, 1);
//    delete_from_file(key, key, indexPath, 2);
//}
//
void printFile(const char* file_path){
    FILE *file = fopen(file_path, "r");
    struct myregistro temp;
    fseek(file, 0, SEEK_SET);
    while(fread(&temp, sizeof(struct myregistro), 1, file)) {
        printf("%s, %d, %.2f, %p\n", temp.nome, temp.idade, temp.pesoKg, temp.self);
    }
    fclose(file);
}


