#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int verificar_fila(int sudo[9][9]) {
    for (int i = 0; i < 9; i++) {
        int vistos[10] = {0};
        for (int j = 0; j < 9; j++) {
            int val = sudo[i][j];
            if (val == 0) continue;
            if (vistos[val]) return 0;
            vistos[val] = 1;
        }
    }
    return 1;
}

int verificar_columna(int sudo[9][9]) {
    for (int j = 0; j < 9; j++) {
        int vistos[10] = {0};
        for (int i = 0; i < 9; i++) {
            int val = sudo[i][j];
            if (val == 0) continue;
            if (vistos[val]) return 0;
            vistos[val] = 1;
        }
    }
    return 1;
}

int verificar_cuadro(int sudo[9][9]) {
    for (int k = 0; k < 9; k++) {
        int vistos[10] = {0};
        for (int p = 0; p < 9; p++) {
            int i = 3 * (k / 3) + (p / 3);
            int j = 3 * (k % 3) + (p % 3);
            int val = sudo[i][j];
            if (val == 0) continue;
            if (vistos[val]) return 0;
            vistos[val] = 1;
        }
    }
    return 1;
}



int is_valid(Node* n) {
    return verificar_fila(n->sudo) && verificar_columna(n->sudo) && verificar_cuadro(n->sudo);
}



List* get_adj_nodes(Node* n){
    List* list=createList();
    int fila = -1, col = -1;
    for(int i = 0 ; i < 9 && fila == -1 ; i++){
      for (int j = 0; j < 9; j++){
        if(n->sudo[i][j] == 0){
          fila = i;
          col = j;
          break;
        }
      }
    }
    if(fila == -1) return list;
    
    for(int val = 1; val <= 9; val++){
      Node* nuevo = copy(n);
      nuevo->sudo[fila][col] = val;
      if(is_valid(nuevo)){
        pushBack(list, nuevo);
      }else{
        free(nuevo);
      }
    }
    return list;
}


int is_final(Node* n){
  for (size_t i = 0; i < 9; i++){
    for(size_t j = 0; j < 9; j++){
      if(n->sudo[i][j] == 0){
        return 0;
      }
    }
  }
  return 1;
}


Node* DFS(Node* initial, int* cont){
  return NULL;
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/