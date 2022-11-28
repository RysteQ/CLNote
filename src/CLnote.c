#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {false, true} bool;

struct notes {
    char *note_name;
    char *note_data;
    bool completed;
};

char *readFile(char *filename);
struct notes *parseInput(char *notes);
void displayNotes(struct notes *notes, int count);
int getNotesLength(struct notes *notes);
void displayNoteCap();
char getChar();
int getInt();
void getString(char buffer[], int limit);
char *assignNoteValue(char buffer[], int limit);
void saveFile(char *filename, struct notes *notes, int notes_count);

int main (int argc, char **argv) {
    if (argc != 2) {
        printf("No input / output file detected\n");
        return -1;
    }

    // read the input file and parse the data
    char *note_data = readFile(argv[1]);
    struct notes *notes = parseInput(note_data);
    int notes_count = getNotesLength(notes);

    // main loop
    while (true) {
        displayNotes(notes, notes_count);

        // get the user input (this will be reworked in the future)
        printf("Command -> ");
        char user_input = getChar();

        switch (user_input)
        {
            // update
            case 'u':
                printf("-> ");
                int to_update = getInt();

                // check if the index is within bounds
                if (to_update > notes_count || to_update < 1) {
                    printf("Error, incorrect index\n");
                    break;
                }

                // flip the current completed status
                to_update--;
                (notes + to_update)->completed = !(notes + to_update)->completed;

                // inform the user of the change
                printf("\nChanged the status from completed (%s) to (%s)\n\n", (notes + to_update)->completed ? "true" : "false", !(notes + to_update)->completed ? "true" : "false");

                break;
            
            // new
            case 'n':
                printf("Title -> ");
                char title[100];
                getString(title, 100);
                (notes + notes_count)->note_name = assignNoteValue(title, 100);

                printf("Contents -> ");
                char contents[2000];
                getString(contents, 2000);
                (notes + notes_count)->note_data = assignNoteValue(contents, 2000);

                notes = realloc(notes, sizeof(struct notes) * (notes_count + 2));
                notes_count++;

                break;

            // delete
            case 'd':
                printf("-> ");
                int to_delete = getInt();

                // check if the index is within bounds
                if (to_delete > notes_count || to_delete < 1) {
                    printf("Error, incorrect index\n");
                    break;
                }

                // delete the note data
                (notes + to_delete - 1)->note_name = NULL;
                (notes + to_delete - 1)->note_data = NULL;

                break;

            // copy
            case 'c':
                char filename[100];

                // save a copy of the notes data
                printf("-> ");
                getString(filename, 100);

                FILE *outputFile = fopen(filename, "w");

                saveFile(filename, notes, notes_count);

                break;

            // save
            case 's':
                saveFile(argv[1], notes, notes_count);

                break;
            
            // help
            case 'h':
                printf("\n");
                printf("u: update\n");
                printf("n: new\n");
                printf("d: delete\n");
                printf("c: copy\n");
                printf("s: save\n");
                printf("q: quit\n");
                printf("h: help\n");
                printf("\n");

                break;

            // quit
            case 'q':
                return 0;
                break;
            
            default:
                printf("\nError, press h for help\n\n");
                break;
        }
    }

    return 0;
}

char *readFile(char *filename) {
    FILE *inputFile = fopen(filename, "r");
    char *note_data;
    char charRead;
    int size = 1;

    // allocate memory
    note_data = malloc(sizeof(char));

    // read the file
    while ((charRead = fgetc(inputFile)) != EOF) {
        *(note_data + size - 1) = charRead;
        note_data = realloc(note_data, size + 1);
        size++;
    }

    // end the string with a null terminator
    *(note_data + size) = '\0';
    fclose(inputFile);

    return note_data;
}

struct notes *parseInput(char *notes) {
    struct notes *toReturn;
    int toReturnOffset = 0;
    char *title;
    char *contents;
    char *completed;

    /*
    * First line = note title
    * Second line = note contents
    */

    toReturn = malloc(sizeof(struct notes));
    title = strtok(notes, "\n");

    // analyze the file
    do {
        contents = strtok(NULL, "\n");
        completed = strtok(NULL, "\n");
        toReturnOffset++;


        // save the note title and contents
        (toReturn + toReturnOffset - 1)->note_name = title;
        (toReturn + toReturnOffset - 1)->note_data = contents;
        (toReturn + toReturnOffset - 1)->completed = true;

        // analyze the completed status flag
        if (*completed == 'F') {
            (toReturn + toReturnOffset - 1)->completed = false;
        }

        // allocate more memory
        toReturn = realloc(toReturn, sizeof(struct notes) * (toReturnOffset + 1));
    } while ((title = strtok(NULL, "\n")) != NULL);

    // This is the "cap" of the struct
    (toReturn + toReturnOffset)->note_name = NULL;
    (toReturn + toReturnOffset)->note_data = NULL;

    return toReturn;
}

int getNotesLength(struct notes *notes) {
    int toReturn = 0;

    while ((notes + toReturn)->note_name != NULL) {
        toReturn++;
    }

    return toReturn;
}

void displayNotes(struct notes *notes, int count) {
    int index = 0;

    displayNoteCap();

    while (index < count) {
        if ((notes + index)->note_name == NULL) {
            index++;
            continue;
        }

        if (strlen((notes + index)->note_name) > 15) {
            printf("| %i - %-12.12s...|", index + 1, (notes + index)->note_name);
        } else {
            printf("| %i - %-15s|", index + 1, (notes + index)->note_name);
        }

        if ((notes + index)->completed) {
            printf(" F | ");
        } else {
            printf(" T | ");
        }

        if (strlen((notes + index)->note_data) > 52) {
            printf("%-52.49s...|", (notes + index)->note_data);
        } else {
            printf("%-52s|", (notes + index)->note_data);
        }

        printf("\n");

        index++;
    }

    displayNoteCap();
}

void displayNoteCap() {
    printf("+");

    for (int i = 0; i < 20; i++)
        printf("-");

    printf("+");

    for (int i = 0; i < 57; i++)
        printf("-");

    printf("+");
    printf("\n");
}

char getChar() {
    char toReturn;
    char junk;

    scanf("%c", &toReturn);
    scanf("%c", &junk);

    return toReturn;
}

int getInt() {
    int toReturn;
    char junk;

    scanf("%i", &toReturn);
    scanf("%c", &junk);

    return toReturn;
}

void getString(char buffer[], int limit) {
    char junk;

    for (int i = 0; i < limit; i++) {
        buffer[i] = '\0';
    }

    scanf("%s", buffer);
    scanf("%c", &junk);
}

char *assignNoteValue(char buffer[], int limit) {
    char *toReturn = malloc(sizeof(char) * limit);
    
    for (int i = 0; i < limit; i++) {
        *(toReturn + i) = buffer[i];
    }

    return toReturn;
}

void saveFile(char *filename, struct notes *notes, int notes_count) {
    FILE *outputFile = fopen(filename, "w");

    // iterate through every note struct and write its contents to the output file
    for (int i = 0; i < notes_count; i++) {
        if ((notes + i)->note_name != NULL) {
            fprintf(outputFile, "%s\n", (notes + i)->note_name);
            fprintf(outputFile, "%s\n", (notes + i)->note_data);
                        
            if ((notes + i)->completed) {
                fprintf(outputFile, "T\n");
            } else {
                    fprintf(outputFile, "F\n");
            }
        }
    }

    fclose(outputFile);
}