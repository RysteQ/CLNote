char *readFile(char *filename);
void saveFile(char *filename, note *notes, int notes_count);
void createFile(char filename[]);

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

    // if size is one (aka there were no data to read) decrement it
    if (size == 1)
        size--;

    // end the string with a null terminator
    *(note_data + size) = '\0';
    fclose(inputFile);

    return note_data;
}

void saveFile(char *filename, note *notes, int notes_count) {
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

void createFile(char filename[]) {
    FILE *new_file = fopen(filename, "w");
    fclose(new_file);
}