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

int main() {
    printf("Skladové hospodářství\n");
    return 0;
}