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
            int first_line = 1;

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
                if(!first_line){
                    fprintf(file_out, "\n");
                }
                Search_all_tree(file_out, Tree->root);
                first_line = 0;
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
void Search_all_tree(FILE * file_out, Node * root){
    if(root != NULL){
        int sum_left = 0;
        int sum_right = 0;
        Search_all_tree(file_out, root->left);
        sum_left = Sum_Tree(root->left, sum_left);
        sum_right = Sum_Tree(root->right, sum_right);
        fprintf(file_out, "%d (%d)", root->key, sum_right - sum_left);
        if(root->left != NULL || root->right != NULL)
            fprintf(file_out, " ");
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