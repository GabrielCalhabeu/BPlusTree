#include "myB+.h"
#include "fileManager.h"
#define FORMAT_IN "%[^,\n], %d, %f"
int myOrder = 3;
myNode *myQueue = NULL;


void myEnqueue(myNode *new_node) {
    myNode *c;
    if (myQueue == NULL) {
        myQueue = new_node;
        myQueue->next = NULL;
    } else {
        c = myQueue;
        while (c->next != NULL) {
            c = c->next;
        }
        c->next = new_node;
        new_node->next = NULL;
    }
}

// Dequeue
myNode *myDequeue(void) {
    myNode *n = myQueue;
    myQueue = myQueue->next;
    n->next = NULL;
    return n;
}

int pathToLeaves(myNode *const root, myNode *child) {
    int length = 0;
    myNode *c = child;
    while (c != root) {
        c = c->parent;
        length++;
    }
    return length;
}
myNode* importTree(myNode *root){


    //Codigo que importa do aqruivo
    //recebe um arquivo e le cada entrada
    int i = 0;
    struct myregistro *input;
    input = malloc(1 * sizeof(myRegistro));
    if (input == NULL) {
        perror("Input Intake.");
        exit(EXIT_FAILURE);
    }
    char key[5] = {"aaaa\0"};

    FILE* fp = fopen(readableFile, "r");
    if (fp == NULL) {
        perror("Failure to open input file.");
        exit(EXIT_FAILURE);
    }
    fseek(fp, 0, SEEK_SET);

    int dump;
    while (fscanf(fp, "%[^,], %d, %f", input->nome, &input->idade, &input->pesoKg)){

        dump = fgetc(fp);
        if(dump == EOF){
               break;
            }
        input->self = input;
        keyIn(key, input->nome);
        if(i == 4){
            root = inserir(root, key, *input);
        }
        root = inserir(root, key, *input);
        i++;

        input = malloc(1 * sizeof(myRegistro));
        if (input == NULL) {
            perror("Input Intake.");
            exit(EXIT_FAILURE);
        }
    }
    fclose(fp);
    free(input);

    return root;
}

void saveTree(myNode *const root) {

    //Salva a arvore, percorrendo por toda ela, em um arquivo

    purge(filePath, saveFile, indexPath);
    myNode *n = NULL;
    int i = 0;
    int rank = 0;
    int new_rank = 0;

    if (root == NULL) {
        printf("Empty tree.\n");
        return;
    }
    myQueue = NULL;
    myEnqueue(root);
    while (myQueue != NULL) {
        n = myDequeue();
        if (n->parent != NULL && n == n->parent->pointers[0]) {
            new_rank = pathToLeaves(root, n);
            if (new_rank != rank) {
                rank = new_rank;

            }
        }
        for (i = 0; i < n->num_chaves; i++) {
            myRegistro *record_pointer = NULL;
            record_pointer = Find(root, n->chaves[i].chave, NULL);
            if(n->is_leaf)
                write(record_pointer , filePath, saveFile);

        }
        if (!n->is_leaf)

            for (i = 0; i <= n->num_chaves; i++)
                myEnqueue(n->pointers[i]);

    }

    printf("\n");

}

void printTree(myNode *const root) {

    //Separa cada nodulo numa Queue, percorre
    //Pela arvore e printa na tela cada entrada.
    myNode *n = NULL;
    int i = 0;
    int rank = 0;
    int new_rank = 0;

    if (root == NULL) {
        printf("Empty tree.\n");
        return;
    }
    myQueue = NULL;
    myEnqueue(root);
    while (myQueue != NULL) {
        n = myDequeue();
        if (n->parent != NULL && n == n->parent->pointers[0]) {
            new_rank = pathToLeaves(root, n);
            if (new_rank != rank) {
                rank = new_rank;
                printf("\n");
            }
        }
        for (i = 0; i < n->num_chaves; i++) {

            printf("%s ", n->chaves[i].chave);

        }
        if (!n->is_leaf)

            for (i = 0; i <= n->num_chaves; i++)
                myEnqueue(n->pointers[i]);
        printf("| ");
        }

    printf("\n");
}
myNode *makeMyNode(void) {

    //Cria um nodulo.


    myNode *new_node;
    new_node = malloc(sizeof(myNode));
    if (new_node == NULL) {
        perror("Node creation"); //Falha em criar
        exit(EXIT_FAILURE);
    }
    new_node->chaves = malloc((myOrder - 1) * sizeof(myKey));
    if (new_node->chaves == NULL) {
        perror("New node keys array");
        exit(EXIT_FAILURE);
    }
    new_node->pointers = malloc(myOrder * sizeof(void *));
    if (new_node->pointers == NULL) {
        perror("New node pointers array");
        exit(EXIT_FAILURE);
    }
    new_node->is_leaf = false;
    new_node->num_chaves = 0;
    new_node->parent = NULL;
    new_node->next = NULL;
    return new_node;
}

myNode *makeMyLeaf(void) {

    //Cria uma folha
    myNode *leaf = makeMyNode();
    leaf->is_leaf = true;
    return leaf;
}

bool isSmaller(const char * a, const char *b){

    //Compara duas strings.
    if(strcmp(a, b) == -1){
        return 1;
    }
    return 0;
}

void strcopy(char a[], const char *b, int size){

    //Copia uma string.
    for(int i = 0 ; i < size; i++){
        a[i] = b[i];
    }
    a[size] = '\0';
}

myNode *findMyLeaf(myNode *const root, const char* key) {
    if (root == NULL) {
        return root;
    }

    //Tenta achar a folha com a chave, percorrendo a arvore.
    int i = 0;
    myNode *c = root;
    while (!c->is_leaf) {
        i = 0;
        while (i < c->num_chaves) {
            if (!isSmaller(key, c->chaves[i].chave))
                i++;
            else
                break;
        }
        c = (myNode *)c->pointers[i];
    }
    return c;
}

myRegistro *Find(myNode *root, const char* key, myNode **leaf_out) {
    if (root == NULL) {
        if (leaf_out != NULL) {
            *leaf_out = NULL;
        }
        return NULL;
    }

    int i = 0;
    myNode *leaf = NULL;

    leaf = findMyLeaf(root, key);

    for (i = 0; i < leaf->num_chaves; i++)
        if (strcmp(leaf->chaves[i].chave, key) == 0)
            break;
    if (leaf_out != NULL) {
        *leaf_out = leaf;
    }
    if (i == leaf->num_chaves)
        return NULL;
    else {
        myRegistro leaf1 = *(myRegistro *) leaf->pointers[i];
        return ((myRegistro *) leaf1.self);
    }
}

myNode *NewTree(const char * key, myRegistro *pointer) {
    //Cria uma nova arvore,
    //Cria o nodulo cabeca e nulifica ele.
    myNode *root = makeMyLeaf();
    strcopy(root->chaves[0].chave, key, 5);
    root->chaves[0].pointer = pointer;
    root->pointers[0] = pointer;
    root->pointers[myOrder - 1] = NULL;
    root->parent = NULL;
    root->num_chaves++;
    return root;
}

myRegistro *makeMyRecord(myRegistro a) {
    //Cria um novo registro, usando malloc para instanciar um novo espaço na memoria
    myRegistro *new_record = (myRegistro *)malloc(sizeof(myRegistro));
    if (new_record == NULL) {
        perror("Record creation.");
        exit(EXIT_FAILURE);
    } else {
        //Copia o registro a para o novo registro instanciado.
        strcopy(new_record->nome, a.nome, strlen(a.nome));
        new_record->pesoKg = a.pesoKg;
        new_record->idade = a.idade;
        new_record->self = a.self;
    }
    return new_record;
}


myNode *insertIntoLeaf(myNode *leaf, const char* key, myRegistro *pointer) {
    //Insere um registro em uma folha, passando sua chave/
    int i, insertion_point;

    //Ponto de Insercao 0, e procura-se pela chave, ou seja a posicao do
    //registro na arvore.
    insertion_point = 0;
    while (insertion_point < leaf->num_chaves && isSmaller(leaf->chaves[insertion_point].chave, key))
        insertion_point++;

    for (i = leaf->num_chaves; i > insertion_point; i--) {
        leaf->chaves[i] = leaf->chaves[i - 1];
        leaf->pointers[i] = leaf->pointers[i - 1];
    }

    //Insere o registro na posicao de insercao.
    strcopy(leaf->chaves[insertion_point].chave, key, 5);
    leaf->chaves[insertion_point].pointer = pointer;
    leaf->pointers[insertion_point] = pointer;
    leaf->num_chaves++;
    return leaf;
}
//Divide corretamente em 2.
int myCut(int length) {
    if (length % 2 == 0)
        return length / 2;
    else
        return length / 2 + 1;
}

myNode *insertIntoNewRoot(myNode *left, const char* key, myNode *right) {
    //Insere numa nova raiz.
    myNode *root = makeMyNode();
    strcopy(root->chaves[0].chave, key, 5);
    root->pointers[0] = left;
    root->pointers[1] = right;
    root->num_chaves++;
    root->parent = NULL;
    left->parent = root;
    right->parent = root;
    return root;
}
int getLeftIndex(myNode *parent, myNode *left) {

    //Acha o indice do item a esquerda.
    int left_index = 0;
    while (left_index <= parent->num_chaves &&
           parent->pointers[left_index] != left)
        left_index++;
    return left_index;
}

myNode *insertIntoNode(myNode *root, myNode *n, int left_index, const char *key, myNode *right) {
    //Insere o nodulo corretamente.
    int i;

    for (i = n->num_chaves; i > left_index; i--) {
        n->pointers[i + 1] = n->pointers[i];
        n->chaves[i] = n->chaves[i - 1];
    }
    //O ponteiro next do nodulo e apontado para o nodulo da direita.
    n->pointers[left_index + 1] = right;
    strcopy(n->chaves[left_index].chave, key, 5);
    n->num_chaves++;
    return root;
}
myNode *insertIntoNodeAfterSplitting(myNode *root, myNode *old_node, int left_index, const char* key, myNode *right) {
    int i, j, split;
    myNode *new_node, *child;
    char* *temp_keys;
    char* k;
    myNode **temp_pointers;


    //Criando Lista de ponteiro e chaves temporarias.
    temp_pointers = malloc((myOrder + 1) * sizeof(myNode *));
    if (temp_pointers == NULL) {
        exit(EXIT_FAILURE);
    }
    temp_keys = malloc(myOrder * sizeof(int));
    if (temp_keys == NULL) {
        exit(EXIT_FAILURE);
    }

    //Passsando para os temp os valores do bloco.
    for (i = 0, j = 0; i < old_node->num_chaves + 1; i++, j++) {
        if (j == left_index + 1)
            j++;
        temp_pointers[j] = old_node->pointers[i];
    }

    for (i = 0, j = 0; i < old_node->num_chaves; i++, j++) {
        if (j == left_index)
            j++;
        temp_keys[j] = old_node->chaves[i].chave;
    }


    temp_pointers[left_index + 1] = right;
    temp_keys[left_index] = key;

    //Acha o lugar onde deve-se cortar.
    split = myCut(myOrder);

    //Criando novo nodulo
    new_node = makeMyNode();
    old_node->num_chaves = 0;

    //Passando dos temporarios de volta para o bloco ate o corte.
    for (i = 0; i < split - 1; i++) {
        old_node->pointers[i] = temp_pointers[i];
        strcopy(old_node->chaves[i].chave, temp_keys[i], 5);
        old_node->num_chaves++;
    }
    old_node->pointers[i] = temp_pointers[i];
    k = temp_keys[split - 1];
    k = temp_keys[split -1];

    //Passando dos temporarios para o novo nodulo.
    for (++i, j = 0; i < myOrder; i++, j++) {
        new_node->pointers[j] = temp_pointers[i];
        strcopy(new_node->chaves[j].chave, temp_keys[i], 5);
        new_node->num_chaves++;
    }

    new_node->pointers[j] = temp_pointers[i];
    //Free nos temporarios
    free(temp_pointers);
    free(temp_keys);
    new_node->parent = old_node->parent;
    for (i = 0; i <= new_node->num_chaves; i++) {
        child = new_node->pointers[i];
        child->parent = new_node;
    }
    //Chama insercao na folha pai.
    return insertIntoParent(root, old_node, k, new_node);
}

myNode *insertIntoParent(myNode *root, myNode *left, const char* key, myNode *right) {

    //Alinha a folha pai para apontar para a fohla filho.
    int left_index;
    myNode *parent;

    parent = left->parent;

    if (parent == NULL)
        return insertIntoNewRoot(left, key, right);

    left_index = getLeftIndex(parent, left);

    if (parent->num_chaves < myOrder - 1)
        return insertIntoNode(root, parent, left_index, key, right);

    return insertIntoNodeAfterSplitting(root, parent, left_index, key, right);
}

myNode *insertIntoLeafAfterSplitting(myNode *root, myNode *leaf, const char* key, myRegistro *pointer) {
    myNode *new_leaf;
    char **temp_keys;
    void **temp_pointers;
    int insertion_index, split, i, j;
    char new_key[5] = {"aaaa\0"};
    char ne[5] = {"aaaa\0"};

    //Criando folha nova
    new_leaf = makeMyLeaf();

    //Alocando espaco para lista de itens e chaves temporarias.
    temp_keys = malloc(myOrder * sizeof(int));
    temp_pointers = malloc(myOrder * sizeof(void *));


    //Achando ponto de insercao
    insertion_index = 0;
    while (insertion_index < myOrder - 1 && (isSmaller(leaf->chaves[insertion_index].chave, key)))
        insertion_index++;

    //Copia da folha para os temporarios ate, pulando o ponto de insercao
    for (i = 0, j = 0; i < leaf->num_chaves; i++, j++) {
        if (j == insertion_index)
            j++;
        temp_keys[j] = leaf->chaves[i].chave;
        temp_pointers[j] = leaf->pointers[i];
    }
    //No ponto de insercao e inserido os itens apropriados na lista de temporarios.
    temp_keys[insertion_index] = key;
    temp_pointers[insertion_index] = pointer;


    if(insertion_index == 0){
        strcopy(ne, temp_keys[1], 5);
    }


    leaf->num_chaves = 0;

    //Corta no meio
    split = myCut(myOrder - 1);

    //Do inico ao corte copia dos temporarios para a folha
    for (i = 0; i < split; i++) {
        leaf->pointers[i] = temp_pointers[i];
        strcopy(leaf->chaves[i].chave, temp_keys[i], 5);
        leaf->num_chaves++;
    }

    //Do corte ate o resto copie
    for (i = split, j = 0; i < myOrder; i++, j++) {

        new_leaf->pointers[j] = temp_pointers[i];
        strcopy(new_leaf->chaves[j].chave, temp_keys[i], 5);
        new_leaf->num_chaves++;
        if(insertion_index == 0){
            strcopy(new_leaf->chaves[0].chave, ne, 5);
        }
    }

    free(temp_pointers);
    free(temp_keys);

    new_leaf->pointers[myOrder - 1] = leaf->pointers[myOrder - 1];
    leaf->pointers[myOrder - 1] = new_leaf;

    for (i = leaf->num_chaves; i < myOrder - 1; i++)
        leaf->pointers[i] = NULL;
    for (i = new_leaf->num_chaves; i < myOrder - 1; i++)
        new_leaf->pointers[i] = NULL;

    //Alinhado o ponteiro que aponta para a folha pai.
    new_leaf->parent = leaf->parent;
    strcopy(new_key, new_leaf->chaves[0].chave, 5);
    //Insere a nova folha.
    return insertIntoParent(root, leaf, new_key, new_leaf);
}


myNode *inserir(myNode *root, const char* key, myRegistro a) {

    //Funcao cabeca de insercao.
    //Cria um ponteiro para registro
    //Cria um ponteiro para a folha
    myRegistro *record_pointer = NULL;
    myNode *leaf = NULL;
    record_pointer = Find(root, key, NULL);
    if (record_pointer != NULL) {
        return root;
    }

    //Ponteiro do item aponta para o local de memoria do registro
    record_pointer = a.self;

    //Se cabeca for vazia cria uma nova arvore.
    if (root == NULL)
       return NewTree(key, record_pointer);

    //Tente achar a folha.
    leaf = findMyLeaf(root, key);

    if (leaf->num_chaves < myOrder - 1) {
        leaf = insertIntoLeaf(leaf, key, record_pointer);
        return root;
    }
    //Chama o resto das funcoes.
    return insertIntoLeafAfterSplitting(root, leaf, key, record_pointer);
}

int get_neighbor_index(myNode * n) {

    int i;


    /* Retorna o indice da chave a esquerda
     * do ponteiro no pai apontando para n.
    */
    for (i = 0; i <= n->parent->num_chaves; i++)
        if (n->parent->pointers[i] == n)
            return i - 1;

    // Erro
    printf("Search for nonexistent pointer to node in parent.\n");
    printf("Node:  %#lx\n", (unsigned long)n);
    exit(EXIT_FAILURE);
}

myNode * remove_entry_from_node(myNode * n, const char* key, myNode * pointer) {

    int i, num_pointers;

    // Remove a chave e arrasta o resto de maneira apropriada.
    i = 0;
    while (strcmp(n->chaves[i].chave, key) != 0)
        i++;
    for (++i; i < n->num_chaves; i++)
        strcopy(n->chaves[i -1].chave, n->chaves[i].chave, 5);

    // Remove o ponteiro e arrasta o resto.
    // Determina, primeiro, o numero de ponteiros.
    num_pointers = n->is_leaf ? n->num_chaves : n->num_chaves + 1;
    i = 0;
    while (n->pointers[i] != pointer)
        i++;
    for (++i; i < num_pointers; i++)
        n->pointers[i - 1] = n->pointers[i];


    // Diminui o numero de chaves
    n->num_chaves--;

    // Faz com que os outros ponteiros sejam null
    // A folha usa o ultimo ponteiro para apontar para o proximo.
    if (n->is_leaf)
        for (i = n->num_chaves; i < myOrder - 1; i++)
            n->pointers[i] = NULL;
    else
        for (i = n->num_chaves + 1; i < myOrder; i++)
            n->pointers[i] = NULL;

    return n;
}

myNode * adjust_root(myNode * root) {

    myNode * new_root;

    /* Caso esteja vazio, faca nada.
     */

    if (root->num_chaves > 0)
        return root;



    // Se tiver um filho promova
    // o primeiro filho como nova raiz.

    if (!root->is_leaf) {
        new_root = root->pointers[0];
        new_root->parent = NULL;
    }

        // Se nao tiver um filho
        // entao a arvore inteira esta vazia..

    else
        new_root = NULL;

    free(root->chaves);
    free(root->pointers);
    free(root);

    return new_root;
}
myNode * coalesce_nodes(myNode * root, myNode * n, myNode * neighbor, int neighbor_index, const char* k) {

    int i, j, neighbor_insertion_index, n_end;
    myNode * tmp;



    /* Troca de lugar se o nodulo estiver a extrema esquerda
     * e o vizinho estiver a direita.
     */

    if (neighbor_index == -1) {
        tmp = n;
        n = neighbor;
        neighbor = tmp;
    }

   //Ponto onde ira comecar a copiar chaves.
    neighbor_insertion_index = neighbor->num_chaves;



    if (!n->is_leaf) {

        /* Copia K.
         */


        strcopy(neighbor->chaves[neighbor_insertion_index].chave, k, 5);
        neighbor->num_chaves++;


        n_end = n->num_chaves;

        for (i = neighbor_insertion_index + 1, j = 0; j < n_end; i++, j++) {
            strcopy(neighbor->chaves[i].chave, n->chaves[j].chave, 5);
            neighbor->pointers[i] = n->pointers[j];
            neighbor->num_chaves++;
            n->num_chaves--;
        }



        neighbor->pointers[i] = n->pointers[j];

        /* Alinha os filhos para apontarem para o mesmo pai.
         */

        for (i = 0; i < neighbor->num_chaves + 1; i++) {
            tmp = (myNode *)neighbor->pointers[i];
            tmp->parent = neighbor;
        }
    }

        /* Na folha, copia as chaves e ponteiros do vizinho de n.
         * Faz com que o ultimo ponteiro do vizinho aponte para
         * o que o ultimo vizinho a direita de n era.
         */

    else {
        for (i = neighbor_insertion_index, j = 0; j < n->num_chaves; i++, j++) {
            strcopy(neighbor->chaves[i].chave, n->chaves[j].chave, 5);
            neighbor->pointers[i] = n->pointers[j];
            neighbor->num_chaves++;
        }
        neighbor->pointers[myOrder - 1] = n->pointers[myOrder - 1];
    }

    root = delete_entry(root, n->parent, k, n);
    free(n->chaves);
    free(n->pointers);
    free(n);
    return root;
}
myNode * redistribute_nodes(myNode  * root, myNode * n, myNode * neighbor, int neighbor_index,
                          int k_prime_index, const char* k) {

    int i;
    myNode * tmp;


    //Puxa o par ponteiro-chave do vizinho (ultimo par), da
    //esquerda de n, para ele.

    if (neighbor_index != -1) {
        if (!n->is_leaf)
            n->pointers[n->num_chaves + 1] = n->pointers[n->num_chaves];
        for (i = n->num_chaves; i > 0; i--) {
            strcopy(n->chaves[i].chave, n->chaves[i-1].chave, 5);
            n->pointers[i] = n->pointers[i - 1];
        }
        if (!n->is_leaf) {
            n->pointers[0] = neighbor->pointers[neighbor->num_chaves];
            tmp = (myNode *)n->pointers[0];
            tmp->parent = n;
            neighbor->pointers[neighbor->num_chaves] = NULL;
            strcopy(n->chaves[0].chave, k, 5);

            strcopy(n->parent->chaves[k_prime_index].chave, neighbor->chaves[neighbor->num_chaves - 1].chave, 5);
        }
        else {
            n->pointers[0] = neighbor->pointers[neighbor->num_chaves - 1];
            neighbor->pointers[neighbor->num_chaves - 1] = NULL;

            strcopy(n->chaves[0].chave, neighbor->chaves[neighbor->num_chaves - 1].chave, 5 );

            strcopy(n->parent->chaves[k_prime_index].chave, n->chaves[0].chave, 5);
        }
    }



        //Pega-se o par ponteiro-chave do vizinho a direita.
        //Move o par pon-cha do vizinho, para o maximo a direita de n.

    else {
        if (n->is_leaf) {

            strcopy(n->chaves[n->num_chaves].chave, neighbor->chaves[0].chave, 5);
            n->pointers[n->num_chaves] = neighbor->pointers[0];

            strcopy(n->parent->chaves[k_prime_index].chave, neighbor->chaves[1].chave, 5);
        }
        else {

            strcopy(n->chaves[n->num_chaves].chave, k, 5);
            n->pointers[n->num_chaves + 1] = neighbor->pointers[0];
            tmp = (myNode *)n->pointers[n->num_chaves+ 1];
            tmp->parent = n;

            strcopy(n->parent->chaves[k_prime_index].chave, neighbor->chaves[0].chave, 5);
        }
        for (i = 0; i < neighbor->num_chaves - 1; i++) {

            strcopy(neighbor->chaves[i].chave, neighbor->chaves[i + 1].chave, 5);
            neighbor->pointers[i] = neighbor->pointers[i + 1];
        }
        if (!n->is_leaf)
            neighbor->pointers[i] = neighbor->pointers[i + 1];
    }

    /* n agora tem mais um ponteiro e uma chave
     * o vizinho tem menos um de cada.
     */

    n->num_chaves++;
    neighbor->num_chaves--;

    return root;
}
myNode * delete_entry(myNode * root, myNode * n, const char* key, void * pointer) {

    int min_keys;
    myNode * vizinho;
    int vizinho_index;
    int k_prime_index;
    int capacity;
    char k[5] = {"aaaa\0"};

    // Remove chave e ponteiro do nodulo

    n = remove_entry_from_node(n, key, pointer);


    if (n == root)
        return adjust_root(root);



    /* Determina o menor tamanho permitido do nodulo,
     */

    min_keys = n->is_leaf ? myCut(3 - 1) : myCut(3) - 1;


    if (n->num_chaves >= min_keys)
        return root;



    //Acha o vizinho correto para alinhar.
    //Tbm acha o valor da chave k, no pai entre o ponteiro que aponta
    //para n e o que aponta para o vizinho.

    vizinho_index = get_neighbor_index(n);
    k_prime_index = vizinho_index == -1 ? 0 : vizinho_index;
    strcopy(k,n->parent->chaves[k_prime_index].chave, 5);
    vizinho = vizinho_index == -1 ? n->parent->pointers[1] :
               n->parent->pointers[vizinho_index];

    capacity = n->is_leaf ? 3 : 3 - 1;



    if (vizinho->num_chaves + n->num_chaves < capacity)
        return coalesce_nodes(root, n, vizinho, vizinho_index, k);



    else
        return redistribute_nodes(root, n, vizinho, vizinho_index, k_prime_index, k);
}


myNode * delete(myNode * root, const char* key) {
    //Funcao pai de delecao
    myNode * key_leaf = NULL;
    myRegistro * key_registro = NULL;

    key_registro = Find(root, key,  &key_leaf);


    if (key_registro != NULL && key_leaf != NULL) {
        root = delete_entry(root, key_leaf, key, key_registro);
        free(key_registro);
    }
    return root;
}