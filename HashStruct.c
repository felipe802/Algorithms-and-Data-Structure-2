#include <stdio.h>
#include <stdlib.h>
#define SIZE 31

typedef struct {
    int day, month, year;
} Date;

typedef struct {
    char street[50];
    char neighb[50];
    char city[50];
    char country[50];
    int num, cep;
} Adress;

typedef struct {
    int code;
    Date dateSig; //signed contract date
    char position[50];
    float salary;
} Contract;

typedef struct {
    char name[50];
    int cpf;
    Date dateBorn;
    Adress adr;
    Contract cont;
} Person;

void displayDate(Date d) {
    printf("%d/%d/%d\n", d.day, d.month, d.year);
}

void displayAdr(Adress adr) {
    printf("Adress:\n");
    printf("Street: %s\n", adr.street);
    printf("Neighborhood: %s\n", adr.neighb);
    printf("City: %s\n", adr.city);
    printf("Country: %s\n", adr.country);
    printf("Number: %d\n", adr.num);
    printf("Cep: %d\n", adr.cep);
}

void displayCont(Contract c) {
    printf("Contract: %d\n", c.code);
    printf("Position: %s\n", c.position);
    printf("Salary: R$ %.2f\n", c.salary);
    printf("Contract date:\n");
    displayDate(c.dateSig);
}

void displayPerson(Person p) {
    printf("Name: %s\n", p.name);
    printf("CPF: %d\n", p.cpf);
    printf("Birth Date: ");
    displayDate(p.dateBorn);
    displayAdr(p.adr);
    displayCont(p.cont);
}

Date inputDate(){
    Date d;
    printf("Input the date as the format dd mm yyyy:");
    scanf("%d%d%d", &d.day, &d.month, &d.year);
    getchar();
    return d;
}

Adress inputAdr(){
    Adress adr;
    printf("Street: ");
    fgets(adr.street, 49, stdin);
    printf("Neighborhood: ");
    fgets(adr.neighb, 49, stdin);
    printf("City: ");
    fgets(adr.city, 49, stdin);
    printf("Country: ");
    fgets(adr.country, 49, stdin);
    printf("Num: ");
    scanf("%d", &adr.num);
    getchar();
    printf("CEP: ");
    scanf("%d", &adr.cep);
    getchar();
    return adr;
}

Contract inputCont(){
    Contract cont;
    printf("Code: \n");
    scanf("%d", &cont.code);
    printf("Signing date: ");
    cont.dateSig = inputDate();
    printf("Position: \n");
    fgets(cont.position, 49, stdin);
    printf("Salary: R$");
    scanf("%f", &cont.salary);
    getchar();
    return cont;
}

Person inputPerson() {
    Person p;
    printf("\nName: ");
    fgets(p.name, 49, stdin);
    printf("\nCPF: ");
    scanf("%d", &p.cpf);
    printf("\nBirth Date:\n");
    p.dateBorn = inputDate();
    printf("\nAdress:\n");
    p.adr = inputAdr();
    printf("\nContract: \n");
    p.cont = inputCont();
    return p;
}

//our tab is a people vector. the key is cpf
void initializeTab(Person t[]) {
    for (int i = 0; i < SIZE; i++)
        t[i].cpf = 0; //means empty position
}

int funcHash(int key) {
    return key % SIZE;
}

void insert(Person t[]) {
    Person p = inputPerson();
    int id = funcHash(p.cpf);
    while(t[id].cpf != 0) {
        id = funcHash(id + 1); // linear treatment
    }
    t[id] = p;
}

Person* search(Person t[], int key) {
    int id = funcHash(key); 
    int start = id;
    while(t[id].cpf != 0) {
        if (t[id].cpf == key) {
            printf("\nindexed: %d ", id);
            return &t[id];
        }
        id = funcHash(id + 1);
        if (id == start) break; //restart, not found
    }
    return NULL;
}

void displayTab(Person t[]) {
    for (int i = 0; i < SIZE; i++) {
        printf("%d\n", i);
        if (t[i].cpf != 0) displayPerson(t[i]);
        printf("\n-------------------\n");
    }
}


int main() {
    int op, value, output;
    Person* searchy, tab[SIZE];

    initializeTab(tab);

    do {
        printf("\n0-exit\n1-insert\n2-search\n3-display\n");
        scanf("%d", &op);
        getchar();

        switch(op) {
            case 1:
                insert(tab);
                break;
            case 2:
                printf("which cpf to search? ");
                scanf("%d", &value);
                searchy = search(tab, value);
                if (searchy) {
                    printf("found!\n");
                    displayPerson(*searchy);
                }
                else printf("\nnot found\n");
                break;
            case 3:
                displayTab(tab);
                break;
            default: 
                if (op != 0) printf("invalid option\n");
        }

    } while (op != 0);

    return 0;
}