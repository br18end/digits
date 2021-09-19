/*
    Program:      sumarray.c
    Description:  Reads two arrays from two separate files and performs the sum of both. The resultant
                  array is write into a file.
               
    Use:         ./sumarray file1 file2 file3
    
               where::
               
                      file1:  text file containig the array A     (argv[1])
                      file2:  text file containig the array B     (argv[2])
                      file3:  output file containing array A+B    (argv[3])
               
    Author:     Arnoldo Diaz Ramirez
    Date:       Feb 2010
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int get_array_size(char * filename, int * col);
int create_array(int ** array, int col);
int read_array_from_file(char * filename, int ** array, int col);
void print_array_data(int * array, int col);
void add_arrays(int * arrraya, int * arrayb, int ** arrayc, int col);
int write_array_to_file(char * filename, int * array, int col);


int main(int argc, char *argv[] )
{
   
   int *a, *b, *c;
   int ca, cb;
   
   /*
      Check if user provides input and output file names
   */
   
   if (argc != 4) {
      fprintf(stderr,"Error. Must be used this way:  %s file1 file2 file3\n", argv[0]);
      return 0;
   }
   /*
      Determine array A size
   */
   
   if ( !get_array_size(argv[1], &ca) ) {
      fprintf(stderr,"Error: Unable to open %s input file\n", argv[1]);
      return 0;
   }

   /*
      Determine array B size
   */
   
   if ( !get_array_size(argv[2], &cb) ) {
      fprintf(stderr,"Error: Unable to open %s input file\n", argv[2]);
      return 0;
   }

   /*
      Check if we can perform A + B
   */
   /*
   if ( (ca != cb) ) {
      fprintf(stderr,"Error: array sizes do not match\n");
      return 0;
   }   
   */
   /*
      Create memory space to allocate array A
   */
   
   if ( !create_array(&a, ca) ) {
      fprintf(stderr,"Error: Unable to create array A area\n");
      return 0;
   }
    
   /*
      Create memory space to allocate array B
   */
   
   if ( !create_array(&b, cb) ) {
      fprintf(stderr,"Error: Unable to create array B area\n");
      return 0;
   }
   
   /*
      Create memory space to allocate array A + B
   */
   
   if ( !create_array(&c, cb) ) {
      fprintf(stderr,"Error: Unable to create array A + B area\n");
      return 0;
   } 
   
   /*
      Read array A data from file
   */
   
   if ( !read_array_from_file(argv[1], &a, ca) ) {
      fprintf(stderr,"Error: Unable to read array data from %s input file\n", argv[1]);
      return 0;
   }
   
   /*
      Print array A data from memory
   */
   printf("The array A is:\n");
   print_array_data(a, ca);
   
   /*
      Read array B data from file
   */
   
   if ( !read_array_from_file(argv[2], &b, cb) ) {
      fprintf(stderr,"Error: Unable to read array data from %s input file\n", argv[2]);
      return 0;
   }
   
   /*
      Print array B from memory
   */
   printf("The array B is:\n");
   print_array_data(b, cb);
   
   /*
      Do A + B
   */

   add_arrays(a, b, &c, cb);
   
   /*
      Print array A+B from memory
   */

   printf("The array A + B is:\n");   
   print_array_data(c, cb);   

   /*
      Write array A+B into output file
   */
   
   if ( !print_array_to_file(argv[3], c, ca) ) {
      fprintf(stderr,"Error: Unable to create %s output file", argv[3]);
      return 0;
   }
   
   return 1;
   
}

int get_array_size(char * filename, int * c)
{
   FILE *in_file;
   char *ans, *line, str1[256]; 
   int col_count, i;
   
   in_file = fopen(filename, "r");
   if ( !in_file ) {
      return 0;
   }
   
   col_count = 0;
   *c = 1;         // number of columns
int renglones = 0;
while ( fgets(str1, sizeof(str1),  in_file) ) {  // read first line of file into string str1
    //if ( !fgets(str1, sizeof(str1),  in_file) ) {  // read first line of file into string str1
    //return 0;
	renglones = renglones + 1;
    }
   line = str1;
   while (!col_count) {   // while there are still columns to read
      ans = strchr(line,'\t');  // read number before tab and store it in ans
      if (!ans) {
         col_count = 1;   // no more columns
      } else {
         line = ans+1;    // move forwrd line pointer, to read next number
         *c = *c + 1;     // increase column counter
      }
   
   }      
   fclose(in_file);
   return 1;
}

int create_array(int **array, int c)
{

   (*array) = (int *) malloc(c * sizeof(int));
   if ( !(*array) ) {
      return 0;
   }
   return 1;
}

int read_array_from_file(char * filename, int ** array, int c)
{
   FILE * in_file;
   char * ans, * line, str1[256], no[80]; 
   int j, k, l, n;
   
   in_file = fopen(filename, "r");
   if ( !in_file ) {
      return 0;
   }
   
   if ( !fgets(str1, sizeof(str1),  in_file) ) {
      return 0;
   } else {
      line = str1;
      for (j=0; j<c-1; j++) {
    memset(no, '\0', strlen(no));   // firts, we make zero every bit of variable no (clean it)
    ans = strchr(line,'\t');        // try to store string in ans
    if ( ans ) {                    // if we got a string, process it
       k = strlen(ans);
       l = strlen(line);
       strncpy(no, line, l-k);      // now, we got the number in string format
       n = atoi(no);                // convert it to integer
       (*array)[j] = n;             // store it in array
       line = ans+1;                // move pointer forward to "point" to the next string (number)
    }
      }
      // finally, we process last number, which has no tab after it but end of line character
      memset(no, '\0', strlen(no));
      ans = strchr(line,'\n');
      k = strlen(ans);
      l = strlen(line);
      strncpy(no, line, l-k);
      n = atoi(no);
      (*array)[j] = n;      
   }
   fclose(in_file);
   return 1;
}

void print_array_data(int * array, int c)
{
   int i;
   
   for (i=0; i<c; i++) {
      printf("%d\t", array[i]);
    }
    printf("\n");
}

void add_arrays(int * arraya, int * arrayb, int ** arrayc, int col)
{
   int i, j;
   
   for (i=0; i<col; i++) {
      (*arrayc)[i] = arraya[i] + arrayb[i];
      //printf("arrayc%d\n", (*arrayc)[i]);
   }
}

int print_array_to_file(char * filename, int * array, int col)
{
   FILE * ou_file; 
   int i;
   
   ou_file = fopen(filename, "w");
   if ( !ou_file ) {
      return 0;
   }
   
   for (i=0; i<col; i++) {
       fprintf(ou_file,"%d\t", array[i]);
   }
   fprintf(ou_file,"\n");
}
  
