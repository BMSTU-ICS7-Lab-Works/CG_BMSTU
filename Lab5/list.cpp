#include "list.h"
#include <cstdlib>

struct list * init(float x, float dx, int dy)
{
  struct list *lst;
  // выделение памяти под корень списка
  lst = (struct list*)malloc(sizeof(struct list));
  lst->x = x;
  lst->dx = dx;
  lst->dy = dy;
  lst->ptr = NULL;
  return(lst);
}

struct list * addelem(list *lst, float x, float dx, int dy)
{
  struct list *temp, *p;
  temp = (struct list*)malloc(sizeof(list));
  p = lst->ptr; // сохранение указателя на следующий узел
  lst->ptr = temp; // предыдущий узел указывает на создаваемый
  temp->x = x;
  temp->dx = dx;
  temp->dy = dy;
  temp->ptr = p; // созданный узел указывает на следующий элемент
  return(temp);
}

struct list * deletelem(list *lst, list *root)
{
  struct list *temp;
  temp = root;
  while (temp->ptr != lst) // просматриваем список начиная с корня
  { // пока не найдем узел, предшествующий lst
    temp = temp->ptr;
  }
  temp->ptr = lst->ptr; // переставляем указатель
  free(lst); // освобождаем память удаляемого узла
  return(temp);
}

struct list *deleteall(list *list)
{
    struct list *next, *temp;
    temp = list;
    next = list;
    do
    {
        temp = next;
        next = temp->ptr;
        free(temp);
    } while (next != NULL);
    return temp;
}
