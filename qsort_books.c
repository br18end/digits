#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct book {
  char title[80];
  char autor[80];
  int pages;
};

int comparator(const void * a, const void *b)
{
  struct book * ia = (struct book*)a;
  struct book * ib = (struct book*)b;
  return (strcmp(ia->autor, ib->autor));
}

int main(int argc, char ** argv)
{
  int c = 3;
  int i;

  //Pointer to array of struct pointers, malloc for 2 structs
  struct book* ptr = (struct book*) malloc(c*sizeof(struct book));

  if (ptr == NULL) {
    printf("Could not allocate data\n");
    return 1;
  }

  for (i = 0;i<c;i++) {
    printf("Title: ");
    scanf("%s", ptr[i].title);
    printf("Autor: ");
    scanf("%s", ptr[i].autor);
  }
  for (i = 0;i < c;i++) {
    printf("Before Quick sort Autor: %s, Title : %s \n", ptr[i].autor, ptr[i].title);
  }
  qsort(ptr, c, sizeof(struct book), comparator);
  printf("QSORT Done...\n\n");
  for (i = 0;i<c;i++) {
    printf("TEST");
    printf("After quick sort: Autor: %s, Title: %s \n", ptr[i].autor, ptr[i].title);
  }

  free(ptr);

  return 0;
}