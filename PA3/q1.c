#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE* file_ptr; // file pointer
    char word[20], c; // variables for the word and a character
    char text_line[20];

    // open the file for writting ("w")
    file_ptr = fopen("arquivo_palavra.txt", "w");
    if (file_ptr == NULL) {
        printf("error opening file for writing!\n");
        exit(1);
    }
    printf("enter a word to test file writing: ");
    scanf("%19s", word);
    
    //write the word to the file
    fprintf(file_ptr, "%s", word);
    fclose(file_ptr);
    printf("data written successfully!\n");

    //read the file character by character
    printf("\n");
    file_ptr = fopen("arquivo_palavra.txt", "r");
    if (file_ptr == NULL) {
        printf("error opening file for reading!\n");
        return 1;
    }
    printf("char by char:\n");
    while ((c = getc(file_ptr)) != EOF) {
        printf("%c", c);
    }
    fclose(file_ptr);

    printf("\n");

    // read the file line by line
    file_ptr = fopen("arquivo_palavra.txt", "r");
    if (file_ptr == NULL) {
        printf("error opening file for reading!\n");
        return 1;
    } 
    printf("line by line:\n");
    while (fgets(text_line, sizeof(text_line), file_ptr) != NULL) {
        printf("%s\n", text_line);
    }
    fclose(file_ptr);

    return 0;
}

/*
reads a word from the user
writes this word to a file called arquivo_palavra.txt
reads and prints the file content, first character by character, then line by line

time complexity: O(n) where n is the length of the word (linear for reading/writing)

space complexity: O(1), as only fixed-size buffers are used
(the length of received word is fixed)
*/