#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char ean[14];
    char name[50];
    float purchase_price;
    float sale_price;
    int quantity;
    int dph;
} Product;

Product *warehouse = NULL;
int product_count = 0;

// Vrati cenu vcetne DPH
float priceWithDPH(float price, int dph) {
    return price * (1.0f + dph / 100.0f);
}

// Vypise zkraceny vypis produktu do seznamu
void printRow(int i) {
    printf("ID: %d | EAN: %s | Nazev: %-20s | Prod. cena: %.2f Kc | Ks: %d\n",
        i,
        warehouse[i].ean,
        warehouse[i].name,
        warehouse[i].sale_price,
        warehouse[i].quantity);
}

// Vypise vsechny produkty (zkraceny seznam)
void listProducts() {
    if (product_count == 0) {
        printf("Sklad je prazdny.\n");
        return;
    }
    printf("\nSeznam produktu:\n");
    for (int i = 0; i < product_count; i++) {
        printRow(i);
    }
}

// Vypise cely detail produktu
void printDetail(int i) {
    printf("\n--- DETAIL PRODUKTU ---\n");
    printf("ID:                  %d\n",    i);
    printf("EAN:                 %s\n",    warehouse[i].ean);
    printf("Nazev:               %s\n",    warehouse[i].name);
    printf("Nakupni cena:        %.2f Kc (bez DPH)\n", warehouse[i].purchase_price);
    printf("                     %.2f Kc (s DPH %d%%)\n",
        priceWithDPH(warehouse[i].purchase_price, warehouse[i].dph), warehouse[i].dph);
    printf("Prodejni cena:       %.2f Kc (bez DPH)\n", warehouse[i].sale_price);
    printf("                     %.2f Kc (s DPH %d%%)\n",
        priceWithDPH(warehouse[i].sale_price, warehouse[i].dph), warehouse[i].dph);
    printf("Pocet kusu:          %d\n",    warehouse[i].quantity);
    printf("Hodnota skladu:      %.2f Kc (s DPH)\n",
        priceWithDPH(warehouse[i].sale_price, warehouse[i].dph) * warehouse[i].quantity);
    printf("-----------------------\n");
}

// Prida novy produkt
void addProduct() {
    warehouse = realloc(warehouse, (product_count + 1) * sizeof(Product));
    if (warehouse == NULL) {
        printf("Chyba: nedostatek pameti!\n");
        exit(1);
    }

    Product *p = &warehouse[product_count];

    printf("EAN (13 cislic): ");
    scanf("%13s", p->ean);
    int c; while ((c = getchar()) != '\n' && c != EOF);

    printf("Nazev: ");
    scanf(" %49[^\n]", p->name);

    printf("Nakupni cena (bez DPH): ");
    scanf("%f", &p->purchase_price);

    printf("Prodejni cena (bez DPH): ");
    scanf("%f", &p->sale_price);

    printf("Pocet kusu: ");
    scanf("%d", &p->quantity);

    printf("DPH sazba (0 / 12 / 21): ");
    scanf("%d", &p->dph);
    if (p->dph != 0 && p->dph != 12 && p->dph != 21) {
        printf("Neplatna sazba, nastavuji 21%%.\n");
        p->dph = 21;
    }

    product_count++;
    printf("Produkt pridan.\n");
}

// Vyhledani podle nazvu
void searchByName() {
    char query[50];
    printf("Hledany nazev (nebo cast): ");
    scanf(" %49[^\n]", query);

    int found = 0;
    for (int i = 0; i < product_count; i++) {
        if (strstr(warehouse[i].name, query) != NULL) {
            printDetail(i);
            found = 1;
        }
    }
    if (!found) printf("Zadny produkt nebyl nalezen.\n");
}

// Vyhledani podle cenoveho rozsahu
void searchByPrice() {
    float min, max;
    printf("Cena od (bez DPH): ");
    scanf("%f", &min);
    printf("Cena do (bez DPH): ");
    scanf("%f", &max);

    int found = 0;
    for (int i = 0; i < product_count; i++) {
        if (warehouse[i].sale_price >= min && warehouse[i].sale_price <= max) {
            printDetail(i);
            found = 1;
        }
    }
    if (!found) printf("V teto cenove relaci nic nemame.\n");
}

// Smazani produktu
void deleteProduct() {
    listProducts();
    if (product_count == 0) return;

    int id;
    printf("ID ke smazani: ");
    scanf("%d", &id);
    if (id < 0 || id >= product_count) {
        printf("Neplatne ID.\n");
        return;
    }

    for (int i = id; i < product_count - 1; i++) {
        warehouse[i] = warehouse[i + 1];
    }
    product_count--;

    warehouse = realloc(warehouse, product_count * sizeof(Product));
    printf("Produkt smazan.\n");
}

// Uprava produktu
void editProduct() {
    listProducts();
    if (product_count == 0) return;

    int id;
    printf("ID k uprave: ");
    scanf("%d", &id);
    if (id < 0 || id >= product_count) {
        printf("Neplatne ID.\n");
        return;
    }

    Product *p = &warehouse[id];
    char volba;

    do {
        printf("\nUprava: %s\n", p->name);
        printf("1 - Nazev\n");
        printf("2 - Nakupni cena\n");
        printf("3 - Prodejni cena\n");
        printf("4 - Pocet kusu\n");
        printf("5 - DPH sazba\n");
        printf("Z - Zpet\n");
        printf("Volba: ");
        scanf(" %c", &volba);

        switch (volba) {
            case '1': printf("Novy nazev: ");         scanf(" %49[^\n]", p->name);    break;
            case '2': printf("Nova nakupni cena: ");  scanf("%f", &p->purchase_price); break;
            case '3': printf("Nova prodejni cena: "); scanf("%f", &p->sale_price);     break;
            case '4': printf("Novy pocet kusu: ");    scanf("%d", &p->quantity);       break;
            case '5': printf("Nova DPH sazba: ");     scanf("%d", &p->dph);            break;
            case 'Z':
            case 'z': break;
            default: printf("Neplatna volba.\n");
        }
    } while (volba != 'Z' && volba != 'z');

    printf("Produkt upraven.\n");
}

// Hlavni menu
void menu() {
    printf("\n=== SKLADOVY SYSTEM ===\n");
    printf("1 - Zobrazit vse\n");
    printf("2 - Detail podle ID\n");
    printf("3 - Hledat podle nazvu\n");
    printf("4 - Hledat podle ceny\n");
    printf("5 - Pridat produkt\n");
    printf("6 - Smazat produkt\n");
    printf("7 - Upravit produkt\n");
    printf("X - Konec\n");
    printf("Volba: ");
}

int main() {
    warehouse = realloc(warehouse, (product_count + 1) * sizeof(Product));
    warehouse[product_count++] = (Product){"1234567890123", "Macbook Air",    650.00f, 799.99f, 5,  21};

    warehouse = realloc(warehouse, (product_count + 1) * sizeof(Product));
    warehouse[product_count++] = (Product){"2345678901234", "Logitech Mouse",  18.00f,  29.50f, 20, 21};

    warehouse = realloc(warehouse, (product_count + 1) * sizeof(Product));
    warehouse[product_count++] = (Product){"3456789012345", "Steelseries KB",  55.00f,  89.00f, 15, 21};

    char volba;
    while (1) {
        menu();
        scanf(" %c", &volba);

        switch (volba) {
            case '1': listProducts(); break;
            case '2': {
                listProducts();
                int id;
                printf("ID: ");
                scanf("%d", &id);
                if (id >= 0 && id < product_count) printDetail(id);
                else printf("Neplatne ID.\n");
                break;
            }
            case '3': searchByName();  break;
            case '4': searchByPrice(); break;
            case '5': addProduct();    break;
            case '6': deleteProduct(); break;
            case '7': editProduct();   break;
            case 'X':
            case 'x':
                printf("Konec programu.\n");
                free(warehouse);
                return 0;
            default:
                printf("Neplatna volba.\n");
        }
    }
}