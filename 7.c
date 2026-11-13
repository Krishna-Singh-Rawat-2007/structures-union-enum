
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    CMD_ADD,
    CMD_DELETE,
    CMD_VIEW,
    CMD_UPDATE,
    CMD_COMPLETE,
    CMD_FIND,
    CMD_HELP,
    CMD_EXIT,
    CMD_UNKNOWN
} CommandType;

typedef enum {
    PENDING,
    DONE
} TaskStatus;

typedef struct {
    int ID;
    char description[200];
    TaskStatus status;
} Task;

int read_line(char *input, int size) {
    if (fgets(input, size, stdin) == NULL) {
        return 0;
    }

    int length = strlen(input);

    if (length > 0 && input[length - 1] == '\n') {
        input[length - 1] = '\0';
    }
    else {
        int ch = getchar();

        if (ch != '\n' && ch != EOF) {
            while (ch != '\n' && ch != EOF) {
                ch = getchar();
            }

            return -1;
        }
    }

    return 1;
}

CommandType get_command_type(char *command) {

    for (int i = 0; command[i] != '\0'; i++) {
        if (command[i] >= 'a' && command[i] <= 'z') {
            command[i] = command[i] - 32;
        }
    }

    if (strcmp(command, "ADD") == 0) return CMD_ADD;
    if (strcmp(command, "DELETE") == 0) return CMD_DELETE;
    if (strcmp(command, "VIEW") == 0) return CMD_VIEW;
    if (strcmp(command, "UPDATE") == 0) return CMD_UPDATE;
    if (strcmp(command, "COMPLETE") == 0) return CMD_COMPLETE;
    if (strcmp(command, "FIND") == 0) return CMD_FIND;
    if (strcmp(command, "HELP") == 0) return CMD_HELP;
    if (strcmp(command, "EXIT") == 0) return CMD_EXIT;

    return CMD_UNKNOWN;
}

int read_task_id(int *ID) {

    char input[50];

    printf("Enter task ID: ");

    int result = read_line(input, sizeof(input));

    if (result != 1) {
        if (result == -1) {
            printf("Invalid ID input.\n");
        }
        return 0;
    }

    if (input[0] == '\0') {
        printf("Task ID cannot be empty.\n");
        return 0;
    }

    int number = 0;

    for (int i = 0; input[i] != '\0'; i++) {

        if (input[i] < '0' || input[i] > '9') {
            printf("Invalid task ID.\n");
            return 0;
        }

        int digit = input[i] - '0';

        if (number > (2147483647 - digit) / 10) {
            printf("Task ID is too large.\n");
            return 0;
        }

        number = number * 10 + digit;
    }

    if (number <= 0) {
        printf("Task ID must be positive.\n");
        return 0;
    }

    *ID = number;
    return 1;
}

int find_task_index(Task *tasks, int count, int ID) {

    for (int i = 0; i < count; i++) {
        if (tasks[i].ID == ID) {
            return i;
        }
    }

    return -1;
}

void add_task(Task **tasks, int *count, int *capacity) {

    int ID;

    if (!read_task_id(&ID)) {
        return;
    }

    if (find_task_index(*tasks, *count, ID) != -1) {
        printf("Task ID already exists.\n");
        return;
    }

    char description[200];

    printf("Enter task description: ");

    int result = read_line(description, sizeof(description));

    if (result != 1) {
        printf("Invalid description input.\n");
        return;
    }

    if (description[0] == '\0') {
        printf("Description cannot be empty.\n");
        return;
    }

    if (*count == *capacity) {

        int new_capacity;

        if (*capacity == 0) {
            new_capacity = 2;
        }
        else {
            new_capacity = 2 * (*capacity);
        }

        Task *new_tasks = realloc(*tasks, new_capacity * sizeof(Task));

        if (new_tasks == NULL) {
            printf("Memory reallocation failed.\n");
            return;
        }

        *tasks = new_tasks;
        *capacity = new_capacity;
    }

    (*tasks)[*count].ID = ID;
    strcpy((*tasks)[*count].description, description);
    (*tasks)[*count].status = PENDING;

    (*count)++;

    printf("Task %d added successfully.\n", ID);
}

void delete_task(Task *tasks, int *count) {

    int ID;

    if (!read_task_id(&ID)) {
        return;
    }

    int index = find_task_index(tasks, *count, ID);

    if (index == -1) {
        printf("Task not found.\n");
        return;
    }

    for (int i = index; i < *count - 1; i++) {
        tasks[i] = tasks[i + 1];
    }

    (*count)--;

    printf("Task %d deleted successfully.\n", ID);
}

void view_tasks(Task *tasks, int count) {

    if (count == 0) {
        printf("No tasks available.\n");
        return;
    }

    printf("\n----- TASK LIST -----\n");

    for (int i = 0; i < count; i++) {

        printf("\nTask ID: %d\n", tasks[i].ID);
        printf("Description: %s\n", tasks[i].description);

        if (tasks[i].status == PENDING) {
            printf("Status: PENDING\n");
        }
        else {
            printf("Status: DONE\n");
        }
    }

    printf("\n---------------------\n");
}

void update_task(Task *tasks, int count) {

    int ID;

    if (!read_task_id(&ID)) {
        return;
    }

    int index = find_task_index(tasks, count, ID);

    if (index == -1) {
        printf("Task not found.\n");
        return;
    }

    char description[200];

    printf("Enter new description: ");

    int result = read_line(description, sizeof(description));

    if (result != 1) {
        printf("Invalid description input.\n");
        return;
    }

    if (description[0] == '\0') {
        printf("Description cannot be empty.\n");
        return;
    }

    strcpy(tasks[index].description, description);

    printf("Task %d updated successfully.\n", ID);
}

void complete_task(Task *tasks, int count) {

    int ID;

    if (!read_task_id(&ID)) {
        return;
    }

    int index = find_task_index(tasks, count, ID);

    if (index == -1) {
        printf("Task not found.\n");
        return;
    }

    tasks[index].status = DONE;

    printf("Task %d marked as DONE.\n", ID);
}

void find_task(Task *tasks, int count) {

    int ID;

    if (!read_task_id(&ID)) {
        return;
    }

    int index = find_task_index(tasks, count, ID);

    if (index == -1) {
        printf("Task not found.\n");
        return;
    }

    printf("\nTask ID: %d\n", tasks[index].ID);
    printf("Description: %s\n", tasks[index].description);

    if (tasks[index].status == PENDING) {
        printf("Status: PENDING\n");
    }
    else {
        printf("Status: DONE\n");
    }
}

void help() {

    printf("\n----- AVAILABLE COMMANDS -----\n");
    printf("ADD       - Add a new task\n");
    printf("DELETE    - Delete a task by ID\n");
    printf("VIEW      - Display all tasks\n");
    printf("UPDATE    - Update task description\n");
    printf("COMPLETE  - Mark a task as DONE\n");
    printf("FIND      - Find a task by ID\n");
    printf("HELP      - Display available commands\n");
    printf("EXIT      - Exit the program\n");
    printf("------------------------------\n");
}

int main() {

    Task *tasks = NULL;

    int count = 0;
    int capacity = 0;

    char input[100];

    CommandType cmd;

    while (1) {

        printf("\nEnter command (ADD, DELETE, VIEW, UPDATE, COMPLETE, FIND, HELP, EXIT): ");

        int result = read_line(input, sizeof(input));

        if (result == 0) {
            printf("\nInput terminated.\n");
            break;
        }

        if (result == -1) {
            printf("Command is too long.\n");
            continue;
        }

        cmd = get_command_type(input);

        if (cmd == CMD_ADD) {
            add_task(&tasks, &count, &capacity);
        }
        else if (cmd == CMD_DELETE) {
            delete_task(tasks, &count);
        }
        else if (cmd == CMD_VIEW) {
            view_tasks(tasks, count);
        }
        else if (cmd == CMD_UPDATE) {
            update_task(tasks, count);
        }
        else if (cmd == CMD_COMPLETE) {
            complete_task(tasks, count);
        }
        else if (cmd == CMD_FIND) {
            find_task(tasks, count);
        }
        else if (cmd == CMD_HELP) {
            help();
        }
        else if (cmd == CMD_EXIT) {
            printf("Exiting program.\n");
            break;
        }
        else {
            printf("Unknown command.\n");
        }
    }

    free(tasks);

    return 0;
}
