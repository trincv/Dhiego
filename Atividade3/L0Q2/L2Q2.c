#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define SEPARATOR 32

typedef struct Node{
    int key;
    struct Node * right;
    struct Node * left;
    struct Node * mother;
}Node;

typedef struct my_tree{
    Node * root;
}my_tree;

my_tree * Create_tree(my_tree * t){
    t = (my_tree *) malloc(sizeof(my_tree));
    t->root = NULL;
    return t;
}

void Search_all_tree(FILE *, Node *);
int Sum_Tree(Node *, int);
my_tree * Insert_Tree(my_tree *, int);

int main(){

    FILE * file_in = fopen("L2Q2.in", "r");
    
    if(file_in == NULL) printf("Arquivo L2Q2.in não encontrado para abrir");
    else{
        FILE * file_out = fopen("L2Q2.out", "w");

        if(file_out == NULL) printf("Arquivo L2Q2.out não foi criado");
        else{

            char buffer[100];

            while(fgets(buffer, sizeof(buffer), file_in) != NULL){

                my_tree * Tree = Create_tree(Tree);
                char * copy = strdup(buffer);
                
                if(!copy){ 
                    printf("Alocação de memória falhou");
                    return 1;
                }

                char separator[2] = {SEPARATOR, '\0'};

                char * token = strtok(copy, separator);

                while(token != NULL){
                    Tree = Insert_Tree(Tree, atoi(token));
                    token = strtok(NULL, separator);
                }

                Search_all_tree(file_out, Tree->root);
                fprintf(file_out, "\n");
                // copy = strdup(buffer);

                // if(!copy){ 
                //     printf("Alocação de memória falhou");
                //     return;
                // }
                // token = strtok(copy, separator);
                // int tam;
                // while(token != NULL){
                //     tam = search_heights(Tree->root, atoi(token));
                //     fprintf(file_out, "%d ", tam);
                //     token = strtok(NULL, copy);
                // }
                // fprintf(file_out, "\n");
            }
            fclose(file_out);
        }
        fclose(file_in);
    }

}

my_tree * Insert_Tree(my_tree * t, int key){
    
    if(t == NULL)
       t = Create_tree(t);
    
    Node * new = (Node *) malloc(sizeof(Node));
    new->right = NULL;
    new->left = NULL;
    new->key = key;
    
    Node * sacrifice = t->root;
    Node * mother = t->root;
    
    while(sacrifice != NULL && sacrifice->key != key){
        mother = sacrifice;
        
        if(key > sacrifice->key) sacrifice = sacrifice->right;
        else sacrifice = sacrifice->left;
    }
    if(sacrifice != NULL && sacrifice->key == key){
        free(new);
        return t;
    }
    if(mother == NULL){
        new->mother = mother;
        t->root = new;
        return t;
    }
    if(key >= mother->key) mother->right = new;
    else mother->left = new;
    
    new->mother = mother;
    return t;
}
// int search_heights(Node * root, int key){

//     while(key != root->key || root->num == 1){

//         if(key < root->key) root = root->left;
//         else root = root->right;
//     }
//     root->num = 1;
//     return root->tam;
// }
// void Search_all_tree(Node * root){
//     if(root != NULL){
//         Search_all_tree(root->left);
//         printf("%d\n", root->key);
//         Search_all_tree(root->right);
//     }
// }
void Search_all_tree(FILE * file_out, Node * root){
    if(root != NULL){
        int sum_left = 0;
        int sum_right = 0;
        Search_all_tree(file_out, root->left);
        sum_left = Sum_Tree(root->left, sum_left);
        sum_right = Sum_Tree(root->right, sum_right);
        fprintf(file_out, "%d (%d) ", root->key, sum_right - sum_left);
        Search_all_tree(file_out, root->right);
    }
}
int Sum_Tree(Node * root, int sum){
    if(root != NULL){
        sum = Sum_Tree(root->left, sum);
        sum += root->key;
        sum = Sum_Tree(root->right, sum);
    }
    else sum += 0;

    return sum;
}