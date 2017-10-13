#include "lista.h"
#include <stdio.h>
#include <stdlib.h>

/*Funções internas---------*/
int sgn (int i);
void pt (node *head);

void pt (node *head)
{
  printf ("n: %d\n",*((int *) head->data));
  if (head->next != NULL)
    pt (head->next);
}

/*--------------------------*/
int sort (node **lista, int (*compare) (node *a, node *b))
{
  int i;
  int trocado = 0;
  int sz = getSize(*lista);
  
  
  
  if (*lista == NULL)
    return -1;
  
  
  do
    {
      trocado = 0;
      node *ant = NULL;
      node *atual =  *lista;
      node *prox = atual->next;
      
      for (i = 0; i < sz  -1; i++)
        {
            
          
             
              if ((*compare) (atual, prox) == 1)
                {
                    atual->next = prox->next;
                    prox->next = atual;

                  if (ant != NULL)
                    {
                      ant->next = prox;
                      ant = prox;
                      prox =  atual->next;
                    }
                    else
                    {
                      *lista = prox;
                      prox = atual->next;
                    }
                   
                  trocado = 1;
                }
                else
                  {
                    ant = atual;
                    atual = prox;
                    prox =  prox->next;
                  }

        }
          
        
    }
  while (trocado == 1);
 
}


node *new (void *data)
{
  node *no =  (node *)malloc (sizeof (node));
  if (no == NULL)
    {
      printf ("\t>>Não foi possível alocar memória!\n");
      return NULL;
    }
  no->data =  data;
  no->next = NULL;
  
  return no;
}

node *addAtTail (node *no, node **list_head)
{
  if (no != NULL)
    {
      node *tail = *list_head;
      if (*list_head != NULL)
        {
           while (tail->next != NULL)  /*chega ao ultimo nó*/
            tail = tail->next;
      
           tail->next = no;
        }
        else  /*não está vazio*/
          *list_head = no;
        
      return no;  /*se deu certo, retorna o ultimo elemento*/
    }
    else
      return NULL; /*senão retorna NULL*/
      
    
}

node *addAtHead (node *no, node **pt_to_head)
{
  if (no != NULL)
    {
      if (*pt_to_head != NULL)
        {
          no->next = *pt_to_head;
          *pt_to_head = no;
        }
        else
          *pt_to_head = no;
        
      return no;
    }
    else
      return NULL;
}

node *addAt (node *no, int position, node **pt_to_head)
{
  if (position*sgn(position) >= getSize(*pt_to_head))
    {
      printf (">>Posição %d inexistente!\n", position);
      return NULL;
    }
        
  node *anterior = getNode (position + (position > 0? -1: 0), *pt_to_head);
  node *pos  = anterior != NULL? anterior->next: NULL;
  
      
  if (no != NULL)
    {
      if (pt_to_head != NULL)
        {
          
        no->next = pos;
        anterior->next = no;
            
        }
        else
          *pt_to_head =  no;
  
      return no;
    }
    else
      return NULL;
        
}

int delAt (int position, node **pt_to_head)
{
  if (position*sgn(position) >= getSize(*pt_to_head))
    {
      printf (">>Posição %d inexistente!\n", position);
      return -1;
    }
  
  if (position == 0)
    {
      node *tmp =  *pt_to_head;
      *pt_to_head = (*pt_to_head)->next;
      free (tmp);
      return 0;
    }
    else
      {
        node *anterior = getNode (position -1, *pt_to_head);
        node *pos  = anterior != NULL? anterior->next: NULL;
        
        anterior->next = pos->next;
        free (pos);
        return 0;
      }
}

int getSize (node *head)
{
  
  int i = 0;
  node *tmp =  head;
  
  if (head == NULL)
    return 0;
  
  for (i = 1; tmp->next != NULL; i++)
    {
      tmp =  tmp->next;
    }
  return i;
}



node *getNode (int i, node *head)
{
  int size =  getSize (head);
  node *tmp =  head;
  
  
  if (sgn(i)*i < size)
    {
      int c;
      for (c = 0; c < i + (i < 0 ? size -1: 0) ; c++)
        tmp = tmp->next;
      return tmp;
    }
    
  return NULL;
}


node *split (int i, node *head)
{
  int sz = getSize(head);
  int pluspos = i + (i < 0 ? sz -1: 0) ;
  if (i*sgn(i) >= sz)
    {
      printf (">>Posicao %d inexistente!\n", i);
      printf (">> Possivelmente  a posição indicada referencia Head ou Tail!\n");
      return NULL;
    }
    else if (sz <= 1) /*Apenas 1/ou 0 elementos...*/
      {
       printf (">>Impossivel dividir a lista! menos de 2 elementos!\n");
       return NULL;
      }

   node *pos = getNode (i, head);
   node *after =  pos->next;
            
   pos->next = NULL; /*novo tail*/
   return after; /*novo head*/
        
}

node *join (node **head, node **main_head)
{
  node *tail_old = getNode (getSize(*main_head) -1, *main_head);
  
  if (tail_old == NULL)
    *main_head = *head;
  else
        tail_old->next = *head;
  
  return *main_head;
}


void revert (node **lista)
{
  node *last = getNode (getSize(*lista) - 1, *lista);
  node *after_head = NULL;
  
  do
    {
      after_head = (*lista)->next;
      (*lista)->next = last->next;
      last->next = *lista;
      
      *lista = after_head;
    }
  while ( *lista != last);
}


int sgn (int i)
{
  if (i > 0)
    return 1;
  else if (i < 0)
    return -1;
  else
    return 0;
}
