#include <stdio.h>
#include <stdlib.h>

struct Comanda{
int pret,cantitate;
char data[30];
char produs[50];
}comanda[100];

int nrComenzi;
//Functie de citire comanda in fisiere
void citireComanda(){
    FILE* fp = fopen("Comenzi.txt", "r");
    fscanf(fp, "%d", &nrComenzi);
    fgetc(fp);

    for(int i = 0; i < nrComenzi; i++){
        fgets(comanda[i].produs, 50, fp);
        comanda[i].produs[strlen(comanda[i].produs) - 1] = '\0';
        fgets(comanda[i].data, 30, fp);
        comanda[i].data[strlen(comanda[i].data) - 1] = '\0';
        fscanf(fp, "%d", &comanda[i].cantitate);
        fscanf(fp, "%d", &comanda[i].pret);
        fgetc(fp);
    }
}
//Functie de afisare comanda
void afisareComanda(){
    printf("-= Afisare Comanda (total comenzi: %d) =-\n", nrComenzi);

    for(int i =0; i < nrComenzi; i++){
        printf("Nume produs: %s\n", comanda[i].produs);
        printf("Cantitate produs: %d\n", comanda[i].cantitate);
        printf("Pret produs: %d RON\n", comanda[i].pret);
        printf("Data: %s\n", comanda[i].data);
        printf("\n");
    }
}
//Functie de introducere comanda in fisier
void introducereComandaInFisier(){
    FILE *fp = fopen("Comenzi.txt", "w");

    fprintf(fp, "%d\n", nrComenzi);

    for(int i = 0; i < nrComenzi; ++i){
        fprintf(fp, "%s\n", comanda[i].produs);
        fprintf(fp, "%d\n", comanda[i].cantitate);
        fprintf(fp, "%d\n", comanda[i].pret);
        fprintf(fp, "%s\n", comanda[i].data);
    }
    fclose(fp);
}
//Functie de a adauga comanda in fisier
void adaugaComandaInFisier(){
    FILE *fp = fopen("Comenzi.txt", "w");

    fprintf(fp, "%d\n", nrComenzi);

    for(int i = 0; i < nrComenzi; i++){
        fprintf(fp, "%s\n", comanda[i].produs);
        fprintf(fp, "%d\n", comanda[i].cantitate);
        fprintf(fp, "%d\n", comanda[i].pret);
        fprintf(fp, "%s\n", comanda[i].data);
    }
    fclose(fp);
}
//functie de a afisa istoricul vanzarilor pentru o zi anume
void afisareVanzariZiua(char data[30]) {
    int totalBaniZi = 0;
    int totalProduseZi = 0;
    int gasit = 0;


    printf("-= Vanzari pentru data de %s =-\n", data);
    printf("Produs | Cantitate | Pret\n");
    for (int i = 0; i < nrComenzi; i++) {
        if (strcmp(comanda[i].data, data) == 0) {
            printf("%s | %d | %d RON\n", comanda[i].produs, comanda[i].cantitate, comanda[i].pret);
            totalBaniZi += comanda[i].cantitate * comanda[i].pret;
            totalProduseZi += comanda[i].cantitate;
            gasit = 1;
        }

    }
    if(gasit == 0){
        printf("Nu au fost gasite vanzari pentru data %s\n", data);
    }
    else{
        printf("\n");
        printf("Bani castigati in ziua %s sunt: %d RON\n", data, totalBaniZi);
        if(totalProduseZi > 1){
            printf("In ziua de %s au fost comandate %d produse\n", data, totalProduseZi);
        }
        else{
        printf("In ziua de %s a fost comandat %d produs\n", data, totalProduseZi);
        }
    }
}

// Functie pentru a afisa la sfarsitul zilei istoricul vanzarilor si cantitatea de bani castigata
void afisareIstoricVanzari() {
    int totalBani = 0;
    int totalProduse = 0;


    printf("-= Istoric vanzari =-\n");
    printf("Produs | Cantitate | Pret | Data\n");
    for (int i = 0; i < nrComenzi; i++) {
        printf("%s | %d | %d RON | %s\n", comanda[i].produs, comanda[i].cantitate, comanda[i].pret, comanda[i].data);
        totalBani += (comanda[i].pret*comanda[i].cantitate);
        totalProduse += comanda[i].cantitate;
    }
    printf("\nTotal bani castigati: %d RON", totalBani);
    printf("\nTotal produse vandute: %d Produse\n", totalProduse);
}

//Functie pentru a afisa cea mai profitabila zi
void ceaMaiProfitabilaZi(){
    int totalBaniZi = 0;
    int totalProduzeZi = 0;
    int maxBaniZi = 0;
    char dataMax[30];
    for(int i = 0; i < nrComenzi; i++){
        totalBaniZi += comanda[i].cantitate * comanda[i].pret;
        totalProduzeZi += comanda[i].cantitate;
        if(i == nrComenzi - 1 || strcmp((comanda[i].data), comanda[i + 1].data) != 0 ){
            if(totalBaniZi > maxBaniZi){
                maxBaniZi = totalBaniZi;
                strcpy(dataMax, comanda[i].data);
            }
            totalBaniZi = 0;
            totalProduzeZi = 0;
        }

    }
    printf("Cea mai profitabila zi este %s, cu venituri de %d RON.\n", dataMax, maxBaniZi);
}


// Functie pentru a determina cel mai bine vandut produs
void celMaiBineVandutProdus() {
    int maxVanzari = 0;
    char produs[50];
    for (int i = 0; i < nrComenzi; i++) {
        int vanzari = 0;
        for (int j = 0; j < nrComenzi; j++) {
            if (strcmp(comanda[i].produs, comanda[j].produs) == 0) {
                vanzari += comanda[j].cantitate;
            }
        }
        if (vanzari > maxVanzari) {
            maxVanzari = vanzari;
            strcpy(produs, comanda[i].produs);
        }
    }
    printf("Cel mai bine vandut produs este: %s, cu un total de %d vanzari.\n", produs, maxVanzari);
}


// Functie pentru a determina media cantitatilor fiecarui produs in parte
void medieProdus(){
    char produs[50];
    printf("Introduceti numele produsului dorit: ");
    scanf("%s", produs);
    int numarComenzi = 0;
    int totalCantitate = 0;
    float media;
    for(int i = 0; i < nrComenzi; i++){
        if(strcmp(comanda[i].produs, produs) == 0){
            numarComenzi++;
            totalCantitate += comanda[i].cantitate;
        }
    }
    media = (float) totalCantitate / numarComenzi;
    printf("Medie cantitate pentru produsul %s este: %.2f\n", produs, media);
}



int main() {
    citireComanda();

    while(1 == 1){
        system("cls");
        printf("-= MENIU PRINCIPAL =-\n");
        printf("1. Afisare comanda\n");
        printf("2. Introducere comanda\n");
        printf("3. Istoricul vanzarilor efectuate si cantitatea de bani castigata\n");
        printf("4. Istoric zi anume\n");
        printf("5. Cea mai profitabila zi\n");
        printf("6. Cel mai bine vandut produs\n");
        printf("7. Media cantitatilor comandate pentru fiecare produs in parte\n");
        printf("8. Iesire\n");

        int choice;
        do {
            printf("Optiunea dorita: ");
            scanf("%d", &choice);
        } while(choice < 1 || choice > 8);

        system("cls");

        if(choice == 1){
            afisareComanda();
            system("pause");
        }
        if(choice == 2){
            printf("Nume produs: "); scanf("%s", &comanda[nrComenzi].produs);
            printf("Cantitate produs: "); scanf("%d", &comanda[nrComenzi].cantitate);
            printf("Pret produs: "); scanf("%d", &comanda[nrComenzi].pret);
            printf("Data: "); scanf("%s", &comanda[nrComenzi].data);
            printf("Comanda adaugata cu succes!\n");
            nrComenzi++;
            introducereComandaInFisier();
            system("pause");
        }
        if(choice == 3){
            afisareIstoricVanzari();
            system("pause");
        }
        if(choice == 4){
            printf("-= Istoric zi anume =-\n");
            printf("\n");
            char data[30];
            printf("Introduceti data pentru care doriti sa afisati istoricul vanzarilor: ");
            scanf("%s", &data);
            printf("\n");
            afisareVanzariZiua(data);
            system("pause");
        }
        if(choice == 5){
            printf("-= Cea mai profitabila zi =-\n");
            ceaMaiProfitabilaZi();
            system("pause");
        }
        if(choice == 6){
            printf("-= Cel mai bine vandut produs =-\n");
            celMaiBineVandutProdus();
            system("pause");
        }
        if(choice == 7){
            printf("-= Media cantitatilor comandate pentru fiecare produs in parte =-\n");
            medieProdus();
            system("pause");
        }
        if(choice == 8){
            return 0;
        }

    }

}
