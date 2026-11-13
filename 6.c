
// Structures and Unions - 3
#include <stdio.h>
#include <stddef.h>

typedef union {
    int integer;
    float decimal;
    char character;
} UnionData;

typedef struct {
    int integer;
    float decimal;
    char character;
} StructData;

typedef enum {
    INTEGER,
    DECIMAL,
    CHARACTER
} ValueType;

typedef struct {
    ValueType type;
    UnionData data;
} TaggedValue;

// Displaying union values
void display_union(UnionData u, ValueType type) {
    if (type == INTEGER) {
        printf("Integer value: %d\n", u.integer);
    }
    else if (type == DECIMAL) {
        printf("Float value: %.2f\n", u.decimal);
    }
    else if (type == CHARACTER) {
        printf("Character value: %c\n", u.character);
    }
}

// Displaying structure values
void display_structure(StructData s) {
    printf("Integer: %d\n", s.integer);
    printf("Float: %.2f\n", s.decimal);
    printf("Character: %c\n", s.character);
}

// Setting tagged union values
void set_value(TaggedValue *value, ValueType type) {
    value->type = type;

    if (type == INTEGER) {
        printf("Enter an integer: ");
        scanf("%d", &value->data.integer);
    }
    else if (type == DECIMAL) {
        printf("Enter a float: ");
        scanf("%f", &value->data.decimal);
    }
    else if (type == CHARACTER) {
        printf("Enter a character: ");
        scanf(" %c", &value->data.character);
    }
}

int main() {

    UnionData u;
    StructData s;
    TaggedValue value;

    printf("----- STRUCTURE AND UNION MEMORY -----\n");

    // Structure initialization
    s.integer = 10;
    s.decimal = 20.5;
    s.character = 'A';

    // Union initialization
    u.integer = 10;

    printf("\nStructure values:\n");
    display_structure(s);

    printf("\nUnion value:\n");
    display_union(u, INTEGER);

    // Memory sizes
    printf("\n----- MEMORY SIZES -----\n");

    printf("Size of integer: %zu bytes\n", sizeof(int));
    printf("Size of float: %zu bytes\n", sizeof(float));
    printf("Size of character: %zu bytes\n", sizeof(char));

    printf("Size of Structure: %zu bytes\n", sizeof(StructData));
    printf("Size of Union: %zu bytes\n", sizeof(UnionData));

    printf("Size of TaggedValue: %zu bytes\n", sizeof(TaggedValue));

    // Memory addresses
    printf("\n----- MEMORY ADDRESSES -----\n");

    printf("Structure address: %p\n", (void*)&s);
    printf("Integer address: %p\n", (void*)&s.integer);
    printf("Float address: %p\n", (void*)&s.decimal);
    printf("Character address: %p\n", (void*)&s.character);

    printf("\nUnion address: %p\n", (void*)&u);
    printf("Integer address: %p\n", (void*)&u.integer);
    printf("Float address: %p\n", (void*)&u.decimal);
    printf("Character address: %p\n", (void*)&u.character);

    // Member offsets
    printf("\n----- MEMBER OFFSETS -----\n");

    printf("Structure integer offset: %zu\n",
           offsetof(StructData, integer));
    printf("Structure float offset: %zu\n",
           offsetof(StructData, decimal));
    printf("Structure character offset: %zu\n",
           offsetof(StructData, character));

    // Tagged union
    printf("\n----- TAGGED UNION -----\n");

    set_value(&value, INTEGER);
    display_union(value.data, value.type);

    set_value(&value, DECIMAL);
    display_union(value.data, value.type);

    set_value(&value, CHARACTER);
    display_union(value.data, value.type);

    return 0;
}
