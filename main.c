#include <stdio.h>
#include <string.h>

#define MAX_PRODUCTS 50
#define NAME_LEN 100

typedef struct {
    char name[NAME_LEN];
    float price;
    int quantity;
} Product;

Product warehouse[MAX_PRODUCTS];
int productCount = 0;


void defProducts() {
    strcpy(warehouse[0].name, "Macbook");
    warehouse[0].price = 799.99;
    warehouse[0].quantity = 5;

    strcpy(warehouse[1].name, "Logitech Mouse");
    warehouse[1].price = 29.50;
    warehouse[1].quantity = 20;

    strcpy(warehouse[2].name, "Steelseries Keyboard");
    warehouse[2].price = 89.00;
    warehouse[2].quantity = 15;

    strcpy(warehouse[3].name, "Acer Monitor");
    warehouse[3].price = 299.00;
    warehouse[3].quantity = 8;

    strcpy(warehouse[4].name, "USB Flash Drive");
    warehouse[4].price = 15.99;
    warehouse[4].quantity = 50;

    productCount = 5;
}

void listProducts() {
    if (productCount == 0) {
        printf("Sklad je prázdný.\n");
        return;
    }

    printf("\nIndex | Název | Cena | Kusy\n");
    for (int i = 0; i < productCount; i++) {
        printf("%d | %s | %.2f | %d\n",
               i,
               warehouse[i].name,
               warehouse[i].price,
               warehouse[i].quantity);
    }
}

int main() {
    defProducts();
    listProducts();
    return 0;
}