#include <stdio.h>

#include "fileManager.h"
#include "myB+.h"


#define filePath "D:\\Programas\\aeds2\\BTrees\\teste.dat"
#define tempFilePath "D:\\Programas\\aeds2\\BTrees\\temp.dat"
#define readableFile "D:\\Programas\\aeds2\\BTrees\\readable.txt"
#define saveFile "D:\\Programas\\aeds2\\BTrees\\saveFile.txt"
#define indexPath "D:\\Programas\\aeds2\\BTrees\\index.txt"

#define FORMAT_OUT "%s, %d, %.2f, %p\n"
#define FORMAT_IN "%[^,\n], %d, %f, %p"
#define FORMAT_INDEX "%s, %p\n"

int main() {

    myRegistro t1= {
            .nome= "Gabriel Augusto",
            .idade = 19,
            .pesoKg = 54,
            .self = &t1,
    };

    myRegistro t2= {
            .nome= "Miguel Filippo",
            .idade = 23,
            .pesoKg = 103,
            .self = &t2,
    };

    myRegistro t3= {
            .nome= "Jose Alencar",
            .idade = 49,
            .pesoKg = 203,
            .self = &t3,
    };

    myRegistro t4= {
            .nome= "Antonio Silva",
            .idade = 29,
            .pesoKg = 74,
            .self = &t4,
    };

    myRegistro t5= {
            .nome= "Edjane Santos",
            .idade = 47,
            .pesoKg = 60,
            .self = &t5,
    };

    myRegistro t6= {
            .nome= "Anderson Muniz",
            .idade = 47,
            .pesoKg = 60,
            .self = &t6,
    };


    myNode *root1;

    root1 = NULL;

    root1 = importTree(root1);

    printTree(root1);printf("\n");
    saveTree(root1);
    root1 = delete(root1, "Edos");
    root1 = delete(root1, "Gato");
    root1 = delete(root1, "Mipo");
    printTree(root1);printf("\n");

    root1 = delete(root1, "Aniz");
    root1 = delete(root1, "Anva");
    root1 = delete(root1, "Joar");


    myRegistro *teste2 = Find(root1, "Mipo", NULL);
    if(teste2 == NULL){
        printf("Target not found\n\n");
    }else{
        printf("%s, %d, %f, %p\n", teste2->nome, teste2->idade, teste2->pesoKg, teste2->self);
    }

    char key[5] = {"aaaa\0"};
    keyIn(key, t1.nome);
    root1 = inserir(root1, key, t1);
    keyIn(key, t2.nome);
    root1 = inserir(root1, key, t2);
    keyIn(key, t3.nome);
    root1 = inserir(root1, key, t3);
    keyIn(key, t4.nome);
    root1 = inserir(root1, key, t4);
    keyIn(key, t5.nome);
    root1 = inserir(root1, key, t5);
    keyIn(key, t6.nome);
    root1 = inserir(root1, key, t6);

    keyIn(key, "Miguel Filippo");
    teste2 = Find(root1, key, NULL);
    if(teste2 == NULL){
        printf("Target not found\n\n");
    }else{
        printf("%s, %d, %f, %p\n", teste2->nome, teste2->idade, teste2->pesoKg, teste2->self);
    }

    printTree(root1);

    return 0;
}
