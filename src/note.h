typedef struct note {
    char *note_name;
    char *note_data;
    bool completed;
} note;

note *parseInput(char *notes);
void displayNotes(note *notes, int count);
int getNotesLength(note *notes);
void displayNoteCap();
char *assignNoteValue(char buffer[], int limit);

note *parseInput(char *notes) {
    note *toReturn;
    int toReturnOffset = 0;
    char *title;
    char *contents;
    char *completed;

    /*
    * First line = note title
    * Second line = note contents
    */

    toReturn = malloc(sizeof(note));
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
        toReturn = realloc(toReturn, sizeof(note) * (toReturnOffset + 1));
    } while ((title = strtok(NULL, "\n")) != NULL);

    // This is the "cap" of the struct
    (toReturn + toReturnOffset)->note_name = NULL;
    (toReturn + toReturnOffset)->note_data = NULL;

    return toReturn;
}

int getNotesLength(note *notes) {
    int toReturn = 0;

    while ((notes + toReturn)->note_name != NULL) {
        toReturn++;
    }

    return toReturn;
}

void displayNotes(note *notes, int count) {
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

char *assignNoteValue(char buffer[], int limit) {
    char *toReturn = malloc(sizeof(char) * limit);
    
    for (int i = 0; i < limit; i++) {
        *(toReturn + i) = buffer[i];
    }

    return toReturn;
}