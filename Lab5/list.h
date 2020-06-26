#ifndef LIST_H
#define LIST_H

struct list
{
  float dx; // поле данных
  int dy;
  float x;
  struct list *ptr; // указатель на следующий элемент
};

struct list * init(float x, float dx, int dy);
struct list * addelem(list *lst, float x, float dx, int dy);
struct list * deletelem(list *lst, list *root);

#endif // LIST_H
