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

void addProduct() {
    if (productCount >= MAX_PRODUCTS) {
        printf("Sklad je plný.\n");
        return;
    }

    printf("Název: ");
    scanf(" %[^\n]", warehouse[productCount].name);

    printf("Cena: ");
    scanf("%f", &warehouse[productCount].price);

    printf("Počet kusů: ");
    scanf("%d", &warehouse[productCount].quantity);

    productCount++;
    printf("Produkt přidán.\n");
}

void searchByName() {
    char name[NAME_LEN];
    printf("Zadej celý název: ");
    scanf(" %[^\n]", name);

    for (int i = 0; i < productCount; i++) {
        if (strcmp(warehouse[i].name, name) == 0) {
            printf("%d | %s | %.2f | %d\n",
                   i,
                   warehouse[i].name,
                   warehouse[i].price,
                   warehouse[i].quantity);
            return;
        }
    }

    printf("Produkt nebyl nalezen.\n");
}

void searchByPrice() {
    float min, max;

    printf("Cena od: ");
    scanf("%f", &min);
    printf("Cena do: ");
    scanf("%f", &max);

    int found = 0;
    for (int i = 0; i < productCount; i++) {
        if (warehouse[i].price >= min && warehouse[i].price <= max) {
            printf("%d | %s | %.2f | %d\n",
                   i,
                   warehouse[i].name,
                   warehouse[i].price,
                   warehouse[i].quantity);
            found = 1;
        }
    }

    if (!found) {
        printf("Nic nebylo nalezeno.\n");
    }
}

void productDetail() {
    int index;
    listProducts();

    printf("Zadej index produktu: ");
    scanf("%d", &index);

    if (index < 0 || index >= productCount) {
        printf("Neplatný index.\n");
        return;
    }

    printf("\nNázev: %s\n", warehouse[index].name);
    printf("Cena: %.2f\n", warehouse[index].price);
    printf("Počet kusů: %d\n", warehouse[index].quantity);
}

void removeProduct() {
    int index;
    listProducts();

    printf("Index ke smazání: ");
    scanf("%d", &index);

    if (index < 0 || index >= productCount) {
        printf("Neplatný index.\n");
        return;
    }

    for (int i = index; i < productCount - 1; i++) {
        warehouse[i] = warehouse[i + 1];
    }

    productCount--;
    printf("Produkt odstraněn.\n");
}

void editProduct() {
    int index;
    listProducts();

    printf("Index k úpravě: ");
    scanf("%d", &index);

    if (index < 0 || index >= productCount) {
        printf("Neplatný index.\n");
        return;
    }

    printf("Nový název: ");
    scanf(" %[^\n]", warehouse[index].name);

    printf("Nová cena: ");
    scanf("%f", &warehouse[index].price);

    printf("Nový počet kusů: ");
    scanf("%d", &warehouse[index].quantity);

    printf("Produkt upraven.\n");
}

void menu() {
    printf("\n--- SKLADOVÉ HOSPODÁŘSTVÍ ---\n");
    printf("1 - Výpis produktů\n");
    printf("2 - Přidat produkt\n");
    printf("3 - Vyhledat podle názvu\n");
    printf("4 - Vyhledat podle ceny\n");
    printf("5 - Detail produktu\n");
    printf("6 - Odstranit produkt\n");
    printf("7 - Upravit produkt\n");
    printf("X - Konec\n");
    printf("Volba: ");
}

int main() {
    char choice;
    defProducts();

    while (1) {
        menu();
        scanf(" %c", &choice);

        switch (choice) {
            case '1': listProducts(); break;
            case '2': addProduct(); break;
            case '3': searchByName(); break;
            case '4': searchByPrice(); break;
            case '5': productDetail(); break;
            case '6': removeProduct(); break;
            case '7': editProduct(); break;
            case 'X':
            case 'x':
                printf("Konec programu.\n");
                return 0;
            default:
                printf("Neplatná volba.\n");
        }
    }
}