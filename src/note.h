typedef struct note {
    char *note_name;
    char *note_data;
    bool completed;
} note;

bool checkValidity(char *note_data);
note *parseInput(char *notes);
void displayNotes(note *notes, int count);
void displayNoteContext(note note_to_use);
int getNotesLength(note *notes);
void displayNoteCap();
char *assignNoteValue(char buffer[], int limit);

bool checkValidity(char *note_data) {
    int offset = 0;
    int length_before_new_line = 0;
    int new_lines = 0;

    // check if there is any data at all
    if (*note_data == '\0')
        return false;

    // check the contents of the file
    while (*(note_data + offset) != '\0') {
        if (*(note_data + offset) == '\n') {
            // check if the title / context and status are intact
            if (length_before_new_line == 0) {
                return false;
            } else if (length_before_new_line != 1 && (new_lines + 1) % 3 == 0) {
                return false;
            }

            length_before_new_line = 0;
            new_lines++;
        } else {
            length_before_new_line++;
        }

        offset++;
    }

    // if the new lines are not divisible by three (aka there is some data missing) return false
    if (new_lines % 3 != 0)
        return false;

    return true;
}

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

    while ((notes + toReturn)->note_name != NULL)
        toReturn++;

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

void displayNoteContext(note note_to_use) {
    printf("\nContext ---\n");
    printf("%s\n", note_to_use.note_data);
    printf("\n");
}

// rework this junk as well
void displayNoteCap() {
    printf("+");

    for (int i = 0; i < 20; i++)
        printf("-");

    printf("+");

    for (int i = 0; i < 3; i++)
        printf("-");

    printf("+");

    for (int i = 0; i < 53; i++)
        printf("-");

    printf("+");
    printf("\n");
}

char *assignNoteValue(char buffer[], int limit) {
    char *toReturn = malloc(sizeof(char) * limit);
    
    for (int i = 0; i < limit; i++)
        *(toReturn + i) = buffer[i];

    return toReturn;
}