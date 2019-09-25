#include <stdio.h>

int check_anagram(char word1[], char word2[]){
  int first[26] = {0}, second[26] = {0}, i = 0;
 
  while (word1[i] != '\0') {
    first[word1[i]-'a']++;
    i++;
  }
 
  i = 0;
 
  while (word2[i] != '\0') {
    second[word2[i]-'a']++;
    i++;
  }
 
  for (i = 0; i < 26; i++) {
    if (first[i] != second[i])
    return 0;
  } 
  return 1;
}

int main() {
    //CREATE ARRAYS
    char word1[42], word2[42];
    //GET WORDS
    printf("First word: ");
    scanf("%s", word1);
    printf("Second word: ");
    scanf("%s", word2);
    //CHECK WORDS
    int check;
    check = check_anagram(word1, word2);
    if (check == 1)
        printf("%s and %s are anagrams\n", word1, word2);
    else
        printf("%s and %s are not anagrams\n", word1, word2);
    return 0;
}
