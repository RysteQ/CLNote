#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {false, true} bool;

#include "note.h"
#include "input.h"
#include "file.h"

int main (int argc, char **argv) {
    char *note_data;
    char *file_name;

    if (argc != 2) {
        printf("No input / output file detected\n");
        printf("Creating a blank file\n");
        printf("Filename -> ");

        // create the new file
        char to_create[100];
        getString(to_create, 100);
        createFile(to_create);

        file_name = to_create;
    } else {
        file_name = argv[1];
    }

    // read the input file and parse the data
    note_data = readFile(file_name);
    note *notes = parseInput(note_data);
    int notes_count = getNotesLength(notes);
    
    // main loop
    while (true) {
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

                notes = realloc(notes, sizeof(note) * (notes_count + 2));
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
                saveFile(file_name, notes, notes_count);
                break;
            
            // help
            case 'h':
                printf("\n");
                printf("u: update\n");
                printf("n: new\n");
                printf("d: delete\n");
                printf("c: copy\n");
                printf("s: save\n");
                printf("l: show notes\n");
                printf("i: inspect note\n");
                printf("q: quit\n");
                printf("h: help\n");
                printf("\n");

                break;

            // show notes
            // will probably add some code in the future to inform the user if there are more than 10 notes and display those 10 notes
            // if the user wants more than 10 notes they will have to do a certain action
            case 'l':
                displayNotes(notes, notes_count);
                break;

            case 'i':
                int note_to_inspect;
                
                // get the note index
                printf("Note -> ");
                note_to_inspect = getInt() - 1;

                // check if the note index is valid or note
                if (note_to_inspect > notes_count) {
                    printf("Invalid note index\n");
                    break;
                }

                displayNoteContext(*(notes + note_to_inspect));

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