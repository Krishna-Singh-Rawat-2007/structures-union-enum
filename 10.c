
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Enum to track the type of data stored

typedef enum {
    TYPE_EMPTY, INT, FLOAT, CHAR, STRING
} DataType;

// Union to store different types of data

typedef union {
    int int_value;
    float float_value;
    char char_value;
    char *string_value;
} Data;

// Struct to encapsulate the data and its type

typedef struct {
    Data data;
    DataType type;
} Container;

// Function declarations

void container_init(Container *c);
int set_int(Container *c, int value);
int set_float(Container *c, float value);
int set_char(Container *c, char value);
int set_string(Container *c, const char *value);
int get_int(const Container *c, int *out_value);
int get_float(const Container *c, float *out_value);
int get_char(const Container *c, char *out_value);
int get_string(const Container *c, const char **out_value);

void container_clear(Container *c);
int container_copy(Container *destination, const Container *source);
void container_print(const Container *c);
const char* container_type_name(DataType type);

int main() {

    Container containers[6];
    Container copied;
    Container transition;

    // Initializing all containers

    for (int i = 0; i < 6; i++) {
        container_init(&containers[i]);
    }

    container_init(&copied);
    container_init(&transition);

    // Setting different types of data

    set_int(&containers[0], 10);
    set_float(&containers[1], 3.14);
    set_char(&containers[2], 'A');
    set_string(&containers[3], "Hello");
    set_int(&containers[4], 0);
    set_string(&containers[5], "Data");

    // Displaying all containers

    printf("\n----- CONTAINER ARRAY -----\n");

    for (int i = 0; i < 6; i++) {

        printf("\nIndex: %d\n", i);
        printf("Type: %s\n", container_type_name(containers[i].type));
        printf("Value: ");

        container_print(&containers[i]);
    }

    // Copying a container

    printf("\n----- DEEP COPY -----\n");

    if (container_copy(&copied, &containers[5])) {

        printf("Original: ");
        container_print(&containers[5]);

        set_string(&containers[5], "Changed Data");

        printf("After changing original: ");
        container_print(&containers[5]);

        printf("Copied value: ");
        container_print(&copied);
    }
    else {
        printf("Copy failed.\n");
    }

    // Demonstrating different type transitions

    printf("\n----- TYPE TRANSITIONS -----\n");

    set_string(&transition, "Hello");

    printf("String: ");
    container_print(&transition);

    set_int(&transition, 25);

    printf("Integer: ");
    container_print(&transition);

    set_string(&transition, "New String");

    printf("String: ");
    container_print(&transition);

    set_float(&transition, 3.14);

    printf("Float: ");
    container_print(&transition);

    // Testing wrong type getter

    int value;

    if (!get_int(&containers[1], &value)) {
        printf("\nWrong type getter detected.\n");
    }

    // Free any allocated memory

    for (int i = 0; i < 6; i++) {
        container_clear(&containers[i]);
    }

    container_clear(&copied);
    container_clear(&transition);

    printf("\nAll containers cleared successfully.\n");

    return 0;
}

// Function definitions

void container_init(Container *c) {

    if (c == NULL) {
        return;
    }

    c->type = TYPE_EMPTY;
    c->data.string_value = NULL;
}

void container_clear(Container *c) {

    if (c == NULL) {
        return;
    }

    if (c->type == STRING) {
        free(c->data.string_value);
    }

    c->data.string_value = NULL;
    c->type = TYPE_EMPTY;
}

int set_int(Container *c, int value) {

    if (c == NULL) {
        return 0;
    }

    container_clear(c);

    c->data.int_value = value;
    c->type = INT;

    return 1;
}

int set_float(Container *c, float value) {

    if (c == NULL) {
        return 0;
    }

    container_clear(c);

    c->data.float_value = value;
    c->type = FLOAT;

    return 1;
}

int set_char(Container *c, char value) {

    if (c == NULL) {
        return 0;
    }

    container_clear(c);

    c->data.char_value = value;
    c->type = CHAR;

    return 1;
}

int set_string(Container *c, const char *value) {

    if (c == NULL || value == NULL) {
        return 0;
    }

    // Allocate memory for the new string

    int length = strlen(value);

    char *new_string = malloc((length + 1) * sizeof(char));

    if (new_string == NULL) {
        return 0;
    }

    strcpy(new_string, value);

    // Free previous string if any

    if (c->type == STRING) {
        free(c->data.string_value);
    }

    c->data.string_value = new_string;
    c->type = STRING;

    return 1;
}

int get_int(const Container *c, int *out_value) {

    if (c == NULL || out_value == NULL) {
        return 0;
    }

    if (c->type != INT) {
        return 0;
    }

    *out_value = c->data.int_value;

    return 1;
}

int get_float(const Container *c, float *out_value) {

    if (c == NULL || out_value == NULL) {
        return 0;
    }

    if (c->type != FLOAT) {
        return 0;
    }

    *out_value = c->data.float_value;

    return 1;
}

int get_char(const Container *c, char *out_value) {

    if (c == NULL || out_value == NULL) {
        return 0;
    }

    if (c->type != CHAR) {
        return 0;
    }

    *out_value = c->data.char_value;

    return 1;
}

int get_string(const Container *c, const char **out_value) {

    if (c == NULL || out_value == NULL) {
        return 0;
    }

    if (c->type != STRING) {
        return 0;
    }

    *out_value = c->data.string_value;

    return 1;
}

int container_copy(Container *destination, const Container *source) {

    if (destination == NULL || source == NULL) {
        return 0;
    }

    if (destination == source) {
        return 1;
    }

    // Copying string requires separate memory allocation

    if (source->type == STRING) {

        char *new_string = malloc(strlen(source->data.string_value) + 1);

        if (new_string == NULL) {
            return 0;
        }

        strcpy(new_string, source->data.string_value);

        container_clear(destination);

        destination->data.string_value = new_string;
        destination->type = STRING;
    }
    else if (source->type == INT) {

        int value = source->data.int_value;

        container_clear(destination);

        destination->data.int_value = value;
        destination->type = INT;
    }
    else if (source->type == FLOAT) {

        float value = source->data.float_value;

        container_clear(destination);

        destination->data.float_value = value;
        destination->type = FLOAT;
    }
    else if (source->type == CHAR) {

        char value = source->data.char_value;

        container_clear(destination);

        destination->data.char_value = value;
        destination->type = CHAR;
    }
    else if (source->type == TYPE_EMPTY) {

        container_clear(destination);
    }
    else {
        return 0;
    }

    return 1;
}

const char* container_type_name(DataType type) {

    if (type == INT) {
        return "INT";
    }
    else if (type == FLOAT) {
        return "FLOAT";
    }
    else if (type == CHAR) {
        return "CHAR";
    }
    else if (type == STRING) {
        return "STRING";
    }
    else {
        return "EMPTY";
    }
}

void container_print(const Container *c) {

    if (c == NULL) {
        printf("Invalid container.\n");
        return;
    }

    if (c->type == INT) {
        printf("%d\n", c->data.int_value);
    }
    else if (c->type == FLOAT) {
        printf("%f\n", c->data.float_value);
    }
    else if (c->type == CHAR) {
        printf("%c\n", c->data.char_value);
    }
    else if (c->type == STRING) {
        printf("%s\n", c->data.string_value);
    }
    else {
        printf("Container is empty.\n");
    }
}
