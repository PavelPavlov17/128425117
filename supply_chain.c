#define _CRT_SECURE_NO_WARNINGS
// Включваме стандартната библиотека за вход/изход
#include <stdio.h>

int main() {

    // Брой доставчици
    int suppliers;

    // Общо търсене (нужди) на фабриката
    int demand;

    // Запазваме оригиналното търсене за финалната справка
    int initialDemand;

    // Масив с цена на единица суровина за всеки доставчик
    int price[10];

    // Масив с налично количество суровина за всеки доставчик
    int quantity[10];

    // Масив с оригиналния номер (ID) на доставчика
    int supplierId[10];

    // Масив, който пази колко количество е взето от всеки доставчик
    int used[10];

    // Променливи за цикли
    int i, j;

    // Въвеждане на броя доставчици
    printf("Enter number of suppliers: ");
    scanf("%d", &suppliers);

    // Въвеждане на данни за всеки доставчик
    for (i = 0; i < suppliers; i++) {

        // Запазваме оригиналния номер на доставчика
        supplierId[i] = i + 1;

        // Първоначално не сме взели нищо
        used[i] = 0;

        // Въвеждане на цена за текущия доставчик
        printf("Supplier %d price per unit: ", i + 1);
        scanf("%d", &price[i]);

        // Въвеждане на налично количество
        printf("Supplier %d available quantity: ", i + 1);
        scanf("%d", &quantity[i]);
    }

    // Въвеждане на общото търсене на фабриката
    printf("Enter factory demand: ");
    scanf("%d", &demand);

    // Запазваме първоначалното търсене
    initialDemand = demand;

    // Сортиране на доставчиците по цена (възходящо)
    for (i = 0; i < suppliers - 1; i++) {
        for (j = i + 1; j < suppliers; j++) {

            if (price[i] > price[j]) {

                int temp;

                temp = price[i];
                price[i] = price[j];
                price[j] = temp;

                temp = quantity[i];
                quantity[i] = quantity[j];
                quantity[j] = temp;

                temp = supplierId[i];
                supplierId[i] = supplierId[j];
                supplierId[j] = temp;

                temp = used[i];
                used[i] = used[j];
                used[j] = temp;
            }
        }
    }

    // Променлива за крайната цена
    int totalCost = 0;

    // Оптимизация – купуваме първо от най-евтините доставчици
    for (i = 0; i < suppliers && demand > 0; i++) {

        int taken = (quantity[i] <= demand) ? quantity[i] : demand;

        used[i] = taken;
        totalCost += taken * price[i];
        demand -= taken;
    }

    // Финална оптимизационна справка
    printf("\nFINAL OPTIMIZATION SUMMARY\n");
    printf("------------------------------------------------------------\n");
    printf("| %-10s | %-10s | %-10s | %-10s |\n",
        "Supplier", "Price", "Used", "Cost");
    printf("------------------------------------------------------------\n");

    for (i = 0; i < suppliers; i++) {
        if (used[i] > 0) {
            printf("| %-10d | %-10d | %-10d | %-10d |\n",
                supplierId[i],
                price[i],
                used[i],
                used[i] * price[i]);
        }
    }

    printf("------------------------------------------------------------\n");

    // Проверка дали пазарът е могъл да покрие търсенето
    if (demand > 0) {
        printf("WARNING: Market supply is insufficient!\n");
        printf("Requested: %d units\n", initialDemand);
        printf("Supplied:  %d units\n", initialDemand - demand);
    }
    else {
        printf("All demand has been successfully covered.\n");
    }

    // Крайна цена
    printf("Total optimized cost: %d\n", totalCost);

    // Край на програмата
    return 0;
}
