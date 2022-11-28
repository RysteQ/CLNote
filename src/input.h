char getChar();
int getInt();
void getString(char buffer[], int limit);

char getChar() {
    char toReturn = getchar();
    getchar();

    return toReturn;
}

int getInt() {
    int toReturn;
    char junk;

    scanf("%i", &toReturn);
    scanf("%c", &junk);

    return toReturn;
}

// to be reworked so it uses dynamic memory allocation instead of this junk
void getString(char buffer[], int limit) {
    char junk;

    for (int i = 0; i < limit; i++) {
        buffer[i] = '\0';
    }

    scanf("%s", buffer);
    scanf("%c", &junk);
}