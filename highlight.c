#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define COLOR_RED   "\x1b[31m"
#define COLOR_GREEN "\x1b[32m"
#define COLOR_BLUE  "\x1b[34m"  
#define COLOR_RESET "\x1b[0m"

# define STR_LIMIT 1000

void colorWordsInLine(char* text, char* word, char* color);
char* coloredToken(char* word, char* compareTo, char* color);
char* getColor(char* color);
char* getColoredWord(char* word, char* color);
char* substring(char* str,  int to);

int main(int argc, char *argv[]){
  
  char* word = argv[1]; // To convert the string into a lowercase character.
  char* color = argv[2];
  char* filePath = argv[3];

  FILE *file;
  file = fopen(filePath, "r");
 
  char line[STR_LIMIT];

  if(file == NULL){
    printf("Failed to open file.\n");
    return 1;
  }
  
  while(fgets(line, STR_LIMIT, file)){
    colorWordsInLine(line, word, color);
  }
  
  fclose(file);
  
  return 0;
}


void colorWordsInLine(char* text, char* word, char* color){
  char delim[] = " ";

  char *token = strtok(text, delim);
  char lines[200] = "";
  
  while(token != NULL){
    if(token[strlen(token) - 1] == '\n'){
      strcat(lines, coloredToken(substring(token, strlen(token) - 1), word, color));  
            strcat(lines, "\n");
    }
    else{
      strcat(lines, coloredToken(token, word, color));  
    }
    
    strcat(lines, " ");
    token = strtok(NULL, delim);
  }
  printf("%s\n", lines);
}

char* coloredToken(char* word, char* compareTo, char* color){
    char temp[strlen(compareTo) + 1];

    strcpy(temp, compareTo);

    if(!strcmp(word, temp)){
        return getColoredWord(compareTo, color);
    }
    else if(!strcmp(word, strcat(temp, "."))){
        return strcat(getColoredWord(compareTo, color), ".");
    }
    else if(!strcmp(word, strcat(strcpy(temp, compareTo), ","))){
        return strcat(getColoredWord(compareTo, color), ",");
    }
    else if(!strcmp(word, strcat(strcpy(temp, compareTo), "!"))){
        return strcat(getColoredWord(compareTo, color), "!");
    }
    else if(!strcmp(word, strcat(strcpy(temp, compareTo), "?"))){
        return strcat(getColoredWord(compareTo, color), "?");
    }
    
    return word;
}

char* getColor(char* color){
    if(!strcmp(color, "r")){
        return COLOR_RED;
    }
    else if(!strcmp(color, "g")){
        return COLOR_GREEN;
    }
    else if(!strcmp(color, "b")){
        return COLOR_BLUE;
    }
    return NULL;
}

char* getColoredWord(char* word, char* color){
    char* c = getColor(color);
    char str[100] = "";

    strcat(str, c);
    strcat(str, word);
    
    return strcat(str, COLOR_RESET);
}

/**
 * Given a string, start and end indecies, returns a substring according to the indecies.
 * @param  str      A string to extract a substring from.
 * @param  to       The index of the end of the substring.
 * @return          Returns a substring of a given string.
 */
char* substring(char* str,  int to){
  char* sub = malloc(sizeof(char) * to);
  int j = 0;
  while(j < to){
    sub[j] = str[j];
    j++;
  }
  sub[j] = '\0'; 
  return strcat(sub, "");
}



