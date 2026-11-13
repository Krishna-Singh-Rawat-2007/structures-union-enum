// Structures - 2
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define TOLERANCE 0.001 // Am using this for checking if the rectangle is a square

typedef struct {
    int ID;
    float width;
    float height;
    float area;
    float perimeter;
} Rectangle;

// Calculation for area and perimeter
int calculate_geometry(Rectangle *r) {

    float area = r->width * r->height;
    float perimeter = 2 * (r->width + r->height);

    if (!isfinite(area) || !isfinite(perimeter)) {
        printf("The Values for Area or Perimeter is invalid\n");
        return 0;
    }

    r->area = area;
    r->perimeter = perimeter;
    return 1 ;
}

void square_check(Rectangle r){
    if ((r.width - r.height)<TOLERANCE && (r.height- r.width)<TOLERANCE){
        printf("is a sqaure\n");

    }
    else{
        printf("is a rectangle\n");
    }
}


Rectangle* create_rectangle_array(int size) {
    if(size>1000 || size <=0){
        prinft("Ivalid number of recatangles\n");
        return NULL;
    }

    Rectangle *rectangles = malloc(size * sizeof(Rectangle));

    if (rectangles == NULL){
        printf("Memory allocation failed\n");
        return NULL;
    }

    return rectangles;
}

void add_rectangle(Rectangle *rectangles, int index, int ID, float width, float height, int *count, int capacity) {
    if ((*count) >= capacity){
        printf("memory is completely full ");
        return;
    }
    if(!(isfinite(height)) || !isfinite(width) || height <=0 || width<= 0 || ID <=0){
        printf("Invalid inputs");
        return;
    }
    for(int i=0; i <(*count);i++){
        if (rectangles[i].ID == ID){
            printf("ID already exists");
            return;
        }

    }
    if (index < 0 || index >= capacity) {
        printf("Invalid index.\n");
            return;
    }
    rectangles[index].ID = ID;
    rectangles[index].width = width;
    rectangles[index].height = height;
    
    if (!calculate_geometry(&rectangles[index])) {
        return;
    }
    (*count)++;
}


void display_rectangles(Rectangle *rectangles, int size) {
    for (int i = 0; i < size; i++) {
        printf("Rectangle ID %d: Width = %.2f, Height = %.2f, Area = %.2f\n, Perimeter = %.2f\n", rectangles[i].ID, rectangles[i].width, rectangles[i].height, rectangles[i].area, rectangles[i].perimeter);
        square_check(rectangles[i]);
    }
}

void search_rectangles(Rectangle *rectangles, int size, int ID){
      for (int i = 0; i < size; i++) {
        if (rectangles[i].ID == ID) {
            printf("\nRectangle found!\n");
            printf("ID: %d\n", rectangles[i].ID);
            printf("Width: %.2f\n", rectangles[i].width);
            printf("Height: %.2f\n", rectangles[i].height);
            printf("Area: %.2f\n", rectangles[i].area);
            printf("Perimeter: %.2f\n", rectangles[i].perimeter);
            return;
        }
    }

    printf("Rectangle with ID %d not found.\n", ID);


}

void update_rectangles(Rectangle *rectangles, int size, int ID){
    for (int i = 0; i < size; i++) {
        if (rectangles[i].ID == ID) {
            float new_height, new_width;
            printf("Enter new width: ");
            scanf("%f", &new_width);

            printf("Enter new height: ");
            scanf("%f", &new_height);

            if(!(isfinite(new_height)) || !isfinite(new_width) || new_height <=0 || new_width<= 0){
                printf("Invalid inputs, Update is stopped");
                return;
            } 
            Rectangle temp = rectangles[i];

            temp.height = new_height;
            temp.width = new_width;

            if (!calculate_geometry(&temp)) {
                printf("Update failed.\n");
                return;
            }

            rectangles[i] = temp;
            printf("update was successfull");
            return;
        }
       
    }
    printf("ID not found");


}

void delete_rectangle(Rectangle *rectangles, int *count, int ID) {
    for (int i = 0; i < *count; i++) {
        if (rectangles[i].ID == ID) {

            for (int j = i; j < *count - 1; j++) {
                rectangles[j] = rectangles[j + 1];
            }

            (*count)--;

            printf("Rectangle deleted successfully!\n");
            return;
        }
    }

    printf("Rectangle with ID %d not found.\n", ID);
}

void area_summary(Rectangle *rectangle, int size){
    if( size<=0){
        printf("There are no rectangles ");
        return;

    }
    float total=0, average ;
    int largest_index=0, smallest_index=0;
    for(int i =0; i<size; i++){
        total= total + rectangle[i].area;
        if (rectangle[largest_index].area < rectangle[i].area){
            largest_index = i;
        }
         if (rectangle[smallest_index].area > rectangle[i].area){
            smallest_index = i;
        }

        
    }
    average = total / size;

    printf("\n--- Rectangle Statistics ---\n");

    printf("Largest Rectangle:\n");
    printf("ID: %d\n", rectangle[largest_index].ID);
    printf("Area: %.2f\n", rectangle[largest_index].area);

    printf("\nSmallest Rectangle:\n");
    printf("ID: %d\n", rectangle[smallest_index].ID);
    printf("Area: %.2f\n", rectangle[smallest_index].area);

    printf("\nTotal Area: %.2f\n", total);
    printf("Average Area: %.2f\n", average);
}
void sort_rectangles(Rectangle *rectangles, int size) {

    if (size <= 0) {
        printf("There are no rectangles.\n");
        return;
    }

    // Sorting rectangles by area and then by ID
    for (int i = 0; i < size - 1; i++) {

        for (int j = 0; j < size - i - 1; j++) {

            if (rectangles[j].area > rectangles[j + 1].area ||
               (rectangles[j].area == rectangles[j + 1].area &&
                rectangles[j].ID > rectangles[j + 1].ID)) {

                Rectangle temp = rectangles[j];
                rectangles[j] = rectangles[j + 1];
                rectangles[j + 1] = temp;
            }
        }
    }
}
void display_filtered_rectangles(Rectangle *rectangles, int size) {

    if (size <= 0) {
        printf("There are no rectangles.\n");
        return;
    }
    float threshold =0;
    printf("Enter the threshold to which the areas exceed");
    if (scanf("%f", &threshold) != 1 || !isfinite(threshold)) {
    printf("Invalid threshold.\n");
    return;
}

    int found = 0;

    printf("\n--- Filtered Rectangles ---\n");

    for (int i = 0; i < size; i++) {

        if (rectangles[i].area > threshold) {

            printf("\nID: %d\n", rectangles[i].ID);
            printf("Width: %.2f\n", rectangles[i].width);
            printf("Height: %.2f\n", rectangles[i].height);
            printf("Area: %.2f\n", rectangles[i].area);

            found = 1;
        }
    }

    if (found == 0) {
        printf("No rectangles found above the given threshold.\n");
    }
}

void free_rectangle_array(Rectangle *rectangles) {
    free(rectangles);
}


int main() {

    int capacity, count = 0;
    int choice, ID;
    float width, height;

    printf("Enter the initial number of rectangles (1-1000): ");

    if (scanf("%d", &capacity) != 1) {
        printf("Invalid input.\n");
        return 1;
    }

    Rectangle *rectangles = create_rectangle_array(capacity);

    if (rectangles == NULL) {
        return 1;
    }

    // Taking initial rectangle details
    while (count < capacity) {

        printf("\nEnter details for Rectangle %d\n", count + 1);

        printf("Enter ID: ");
        if (scanf("%d", &ID) != 1) {
            printf("Invalid input.\n");
            free_rectangle_array(rectangles);
            return 1;
        }

        printf("Enter width: ");
        if (scanf("%f", &width) != 1) {
            printf("Invalid input.\n");
            free_rectangle_array(rectangles);
            return 1;
        }

        printf("Enter height: ");
        if (scanf("%f", &height) != 1) {
            printf("Invalid input.\n");
            free_rectangle_array(rectangles);
            return 1;
        }

        int previous_count = count;

        add_rectangle(rectangles, count, ID, width, height,
                      &count, capacity);

        if (count == previous_count) {
            printf("Please enter the details again.\n");
        }
    }

    // Main menu
    while (1) {

        printf("\n========== RECTANGLE INVENTORY SYSTEM ==========\n");
        printf("1. Add Rectangle\n");
        printf("2. Display All Rectangles\n");
        printf("3. Search Rectangle\n");
        printf("4. Update Rectangle\n");
        printf("5. Delete Rectangle\n");
        printf("6. Area Statistics\n");
        printf("7. Sort Rectangles\n");
        printf("8. Filter Rectangles by Area\n");
        printf("9. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input.\n");
            free_rectangle_array(rectangles);
            return 1;
        }

        if (choice == 1) {

            if (count >= capacity) {
                printf("Memory is completely full.\n");
            }
            else {
                printf("Enter Rectangle ID: ");
                scanf("%d", &ID);

                printf("Enter width: ");
                scanf("%f", &width);

                printf("Enter height: ");
                scanf("%f", &height);

                add_rectangle(rectangles, count, ID, width, height,
                              &count, capacity);
            }
        }

        else if (choice == 2) {
            display_rectangles(rectangles, count);
        }

        else if (choice == 3) {
            printf("Enter the ID to search: ");
            scanf("%d", &ID);

            search_rectangles(rectangles, count, ID);
        }

        else if (choice == 4) {
            printf("Enter the ID to update: ");
            scanf("%d", &ID);

            update_rectangles(rectangles, count, ID);
        }

        else if (choice == 5) {
            printf("Enter the ID to delete: ");
            scanf("%d", &ID);

            delete_rectangle(rectangles, &count, ID);
        }

        else if (choice == 6) {
            area_summary(rectangles, count);
        }

        else if (choice == 7) {
            sort_rectangles(rectangles, count);
            printf("Rectangles sorted successfully.\n");
            display_rectangles(rectangles, count);
        }

        else if (choice == 8) {
            display_filtered_rectangles(rectangles, count);
        }

        else if (choice == 9) {
            printf("Exiting Rectangle Inventory System.\n");
            break;
        }

        else {
            printf("Invalid choice. Please try again.\n");
        }
    }

    free_rectangle_array(rectangles);

    return 0;
}

