#include<stdio.h>

#include<stdlib.h>

#include<string.h>

#include<ctype.h>

int isNum(char buffer[]) {
    int f = 0;
    for (int i = 0; buffer[i] != '\0'; i++) {
        if (isdigit(buffer[i]))
            f = 1;
        else {
            f = 0;
            break;
        }
    }
    return f;
}

int isKeyword(char buffer[]) {
    char keywords[32][10] = {
        "auto",
        "break",
        "case",
        "char",
        "const",
        "continue",
        "default",
        "do",
        "double",
        "else",
        "enum",
        "extern",
        "float",
        "for",
        "goto",
        "if",
        "int",
        "long",
        "register",
        "return",
        "short",
        "signed",
        "sizeof",
        "printf",
        "struct",
        "switch",
        "typedef",
        "union",
        "unsigned",
        "void",
        "scanf",
        "while"
    };
    int i, flag = 0;
    for (i = 0; i < 32; ++i) {
        if (strcmp(keywords[i], buffer) == 0) {
            flag = 1;
            break;
        }
    }
    return flag;
}

int main() {
    char character, buffer[15], operators[] = "+-*/%=";
    char dummy;
    FILE * fp;
    int i, j = 0;
    fp = fopen("code.txt", "r");
    if (fp == NULL) {
        printf("error while opening the file\n");
        exit(0);
    }
    int lno = 2;
    printf("\nLine No: 1..............\n");
    while ((character = fgetc(fp)) != EOF) {

        if (character == '\n') {
            printf("\nLine No: %i..............\n", lno);
            lno++;
        }

        if (character == '{' || character == '}')
            printf("%c : special charachter\n", character);
        for (i = 0; i < 6; ++i) {
            if (character == operators[i]) {
                if (character == '=') {

                    dummy = fgetc(fp);
                    printf("%c\n", dummy);

                    if (dummy == '=') printf("%c%c : relational operator\n", character, dummy);
                    else {
                        printf("%c :  arithemetic operator\n", character);
                        fseek(fp, -1, SEEK_CUR);
                    }
                } else {
                    printf("%c : arithemetic operator\n", character);
                }
            }
        }

        if (character == '>' || character == '<' || character == '!') {
            dummy = fgetc(fp);
            if (dummy == '=')
                printf("%c%c : relational operator\n", character, dummy);
            else {
                printf("%c : arithemetic operator\n", character);
                fseek(fp, -1, SEEK_CUR);
            }
        }

        if (isalnum(character)) {
            buffer[j++] = character;
        } else if ((character == ',' || character == '\n' || character == ' ' || character == ';' || character == '(' || character == ')') && (j !=
                0)) {
            if (character == ',' || character == ';') printf("%c : separator\n", character);
            buffer[j] = '\0';
            j = 0;

            if (isKeyword(buffer) == 1)
                printf("%s : keyword\n", buffer);
            else {
                if (isalpha(buffer[0]) || buffer[0] == '_')
                    printf("%s : indentifier\n", buffer);
                else if (isNum(buffer)) printf("%s : constant\n", buffer);
                else
                    printf("%s : not an indentifier\n", buffer);
            }
        }
    }
    fclose(fp);
    return 0;
}