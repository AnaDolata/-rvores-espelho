#include <stdio.h>
#include <stdlib.h>

typedef struct arvore {
   char info;
   struct arvore *esq;
   struct arvore *dir;
} Arvore;


Arvore*  cria_arv_vazia (void);
Arvore*  arv_constroi (char c, Arvore* e, Arvore* d);
int      verifica_arv_vazia (Arvore* a);
Arvore*  arv_libera (Arvore* a);
int      arv_pertence (Arvore* a, char c);
void     arv_imprime (Arvore* a);
int      eh_espelho(Arvore *arv_a, Arvore *arv_b);
Arvore*  cria_espelho(Arvore *arv_a);


Arvore* cria_arv_vazia (void) {
   return NULL;
}

Arvore* arv_constroi (char c, Arvore* e, Arvore* d) {
  Arvore* a = (Arvore*)malloc(sizeof(Arvore));
  a->info = c;
  a->esq = e;
  a->dir = d;
  return a;
}

int verifica_arv_vazia (Arvore* a) {
  return (a == NULL);
}

Arvore* arv_libera (Arvore* a) {
  if (!verifica_arv_vazia(a)) {
    arv_libera (a->esq);
    arv_libera (a->dir);
    free(a);
  }
  return NULL;
}

int eh_espelho(Arvore *arv_a, Arvore *arv_b) {
    if (arv_a != NULL && arv_b != NULL) {
        if (arv_a->info == arv_b->info && eh_espelho(arv_a->esq, arv_b->dir) && eh_espelho(arv_a->dir, arv_b->esq))
            return 1;
        return 0;
    }
    return 1;
}

Arvore *cria_espelho(Arvore *arv_a) {
    if (arv_a != NULL) {
        Arvore *a, *a_dir, *a_esq;

        if (arv_a->esq == NULL)
            a_dir = cria_arv_vazia();
        else
            a_dir = cria_espelho(arv_a->esq);


        if (arv_a->dir == NULL)
            a_esq = cria_arv_vazia();
        else
            a_esq = cria_espelho(arv_a->dir);

        a = arv_constroi(arv_a->info, a_esq, a_dir);
        return a;
    }

}

void arv_imprime(Arvore *arv) {
    if (arv != NULL) {
        printf("%c ", arv->info);
        arv_imprime(arv->esq);
        arv_imprime(arv->dir);
    }
}


int main (int argc, char *argv[]) {
  Arvore *a, *a1, *a2, *a3, *a4, *a5;
  a1 = arv_constroi('d',cria_arv_vazia(),cria_arv_vazia());
  a2 = arv_constroi('b',cria_arv_vazia(),a1);
  a3 = arv_constroi('e',cria_arv_vazia(),cria_arv_vazia());
  a4 = arv_constroi('f',cria_arv_vazia(),cria_arv_vazia());
  a5 = arv_constroi('c',a3,a4);
  a  = arv_constroi('a',a2,a5);

  Arvore *b;

  b = cria_espelho(a);

  arv_imprime(a);
  printf("\n");
  arv_imprime(b);
  printf("\n");
  printf("%d", eh_espelho(a, b));
  return 0;
}

