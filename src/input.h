char getChar();
int getInt();
void getString(char buffer[], int limit);

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