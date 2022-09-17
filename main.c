#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#define MAX 100

typedef struct {
    int code;
    char nom[20];
    int quantite;
    float prix;
    float prixTTC;
    int jour;
    int mois;
    int annee;
} produit;

produit tab[MAX];
produit produitVendu [MAX];
int nbProduit = 0;
int nbProduitVendu = 0;

void ajouterProduit() {
    printf("Ajouter un nouveau produit : \n");
    printf("Code : ");
    scanf("%d", &tab[nbProduit].code);
    printf("Nom : ");
    scanf("%s", tab[nbProduit].nom);
    printf("Quantite : ");
    scanf("%d", &tab[nbProduit].quantite);
    printf("Prix : ");
    scanf("%f", &tab[nbProduit].prix);
    tab[nbProduit].prixTTC = tab[nbProduit].prix + (tab[nbProduit].prix * 0.15);
    printf("Prix TTC : %f\n", tab[nbProduit].prixTTC);
    nbProduit++;
}

void ajouterPlusieursProduits() {
    int nb;
    printf("Ajouter plusieurs nouveaux produits : \n");
    printf("Nombre de produits : ");
    scanf("%d", &nb);
    for (int i = 0; i < nb; i++) {
        ajouterProduit();
    }
    printf(" %d produits ont ete ajoutes avec succes !\n", nb);
}

void afficherProduits() {
    printf("Liste des produits : \n");
    for (int i = 0; i < nbProduit; i++) {
        printf("Code : %d\n", tab[i].code);
        printf("Nom : %s\n", tab[i].nom);
        printf("Quantite : %d\n", tab[i].quantite);
        printf("Prix : %f\n", tab[i].prix);
        printf("Prix TTC : %f\n", tab[i].prixTTC);
    }


}

void afficherProduitsParOrdreAlphabetique() {
    printf("Liste des produits par ordre alphabetique : \n");
    for (int i = 0; i < nbProduit; i++) {
        for (int j = i + 1; j < nbProduit; j++) {
            if (strcmp(tab[i].nom, tab[j].nom) > 0) {
                produit temp = tab[i];
                tab[i] = tab[j];
                tab[j] = temp;
            }
        }
    }
    afficherProduits();
}


void afficherProduitsParOrdrePrix() {
    printf("Liste des produits par ordre de prix : \n");
    for (int i = 0; i < nbProduit; i++) {
        for (int j = i + 1; j < nbProduit; j++) {
            if (tab[i].prix > tab[j].prix) {
                produit temp = tab[i];
                tab[i] = tab[j];
                tab[j] = temp;
            }
        }
    }
    afficherProduits();
}

void acheterProduit() {
    int code;
    int quantite;
    printf("Acheter un produit : \n");
    printf("Code : ");
    scanf("%d", &code);
    printf("Quantite : ");
    scanf("%d", &quantite);

    for (int i = 0; i < nbProduit; i++) {
        if (tab[i].code == code) {
            if (tab[i].quantite >= quantite) {
                tab[i].quantite -= quantite;
                produitVendu[nbProduitVendu].code = tab[i].code;
                strcpy(produitVendu[nbProduitVendu].nom, tab[i].nom);
                produitVendu[nbProduitVendu].quantite = quantite;
                produitVendu[nbProduitVendu].prix = tab[i].prix;
                produitVendu[nbProduitVendu].prixTTC = tab[i].prixTTC;
                time_t t = time(NULL);
                struct tm tm = *localtime(&t);
                produitVendu[nbProduitVendu].jour = tm.tm_mday;
                produitVendu[nbProduitVendu].mois = tm.tm_mon + 1;
                produitVendu[nbProduitVendu].annee = tm.tm_year + 1900;
                nbProduitVendu++;
                printf("Produit achete avec succes !\n");
            } else {
                printf("Quantite insuffisante !\n");
            }
        }
    }

}


void rechercherProduitParCode() {
    int code;
    printf("Rechercher un produit par code : \n");
    printf("Code : ");
    scanf("%d", &code);
    for (int i = 0; i < nbProduit; i++) {
        if (tab[i].code == code) {
            printf("Nom : %s\n", tab[i].nom);
            printf("Quantite : %d\n", tab[i].quantite);
            printf("Prix : %f\n", tab[i].prix);
            printf("Prix TTC : %f\n", tab[i].prixTTC);
            break;
        }
    }
}

void afficherProduitsParQuantite() {
    int quantite;
    printf("Afficher les produits par quantite : \n");
    printf("Quantite : ");
    scanf("%d", &quantite);
    for (int i = 0; i < nbProduit; i++) {
        if (tab[i].quantite == quantite) {
            printf("Code : %d\n", tab[i].code);
            printf("Nom : %s\n", tab[i].nom);
            printf("Prix : %f\n", tab[i].prix);
            printf("Prix TTC : %f\n", tab[i].prixTTC);
            printf("Mois : %d\n", tab[i].mois);
            printf("Annee : %d\n", tab[i].annee);
        }
    }
}


void afficherProduitsParEtatStock() {
    printf("Afficher les produits par etat du stock : \n");
    for (int i = 0; i < nbProduit; i++) {
        if (tab[i].quantite < 3) {
            printf("Code : %d\n", tab[i].code);
            printf("Nom : %s\n", tab[i].nom);
            printf("Quantite : %d\n", tab[i].quantite);
            printf("Prix : %f\n", tab[i].prix);
            printf("Prix TTC : %f\n", tab[i].prixTTC);
        }
    }
}


void alimenterStock() {
    int code, quantite;
    printf("Alimenter le stock : \n");
    printf("Code : ");
    scanf("%d", &code);
    printf("Quantite : ");
    scanf("%d", &quantite);
    for (int i = 0; i < nbProduit; i++) {
        if (tab[i].code == code) {
            tab[i].quantite += quantite;
            break;
        }
    }
}


void supprimerProduitParCode() {
    int code;
    printf("Supprimer un produit par code : \n");
    printf("Code : ");
    scanf("%d", &code);
    for (int i = 0; i < nbProduit; i++) {
        if (tab[i].code == code) {
            for (int j = i; j < nbProduit - 1; j++) {
                tab[j] = tab[j + 1];
            }
            nbProduit--;
            break;
        }
    }
}



void statistiqueVenteJournee() {
    float totalPrix = 0, moyennePrix = 0, maxPrix = 0, minPrix = 0;
    int nbProduitVenduJournee = 0;
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    int jour = tm.tm_mday;

    for (int i = 0; i < nbProduitVendu; i++) {
        if (produitVendu[i].jour == jour ) {
            totalPrix += produitVendu[i].prixTTC;
            moyennePrix = totalPrix / nbProduitVenduJournee;
            if (produitVendu[i].prixTTC > maxPrix) {
                maxPrix = produitVendu[i].prixTTC;
            }
            if (produitVendu[i].prixTTC < minPrix) {
                minPrix = produitVendu[i].prixTTC;
            }
            nbProduitVenduJournee++;
        }
    }
    printf("Total des prix des produits vendus en journée courante : %f\n", totalPrix);
    printf("Moyenne des prix des produits vendus en journée courante : %f\n", moyennePrix);
    printf("Max des prix des produits vendus en journée courante : %f\n", maxPrix);
    printf("Min des prix des produits vendus en journée courante : %f\n", minPrix);




}

void afficherMenu() {
    printf("1. Ajouter un produit\n");
    printf("2. Ajouter plusieurs produits\n");
    printf("3. Afficher les produits\n");
    printf("4. Afficher les produits par ordre alphabetique\n");
    printf("5. Afficher les produits par ordre de prix\n");
    printf("6. Acheter un produit\n");
    printf("7. Rechercher un produit par code\n");
    printf("8. Afficher les produits par quantite\n");
    printf("9. Afficher les produits par etat du stock\n");
    printf("10. Alimenter le stock\n");
    printf("11. Supprimer un produit par code\n");
    printf("12. Statistique de vente\n");
    printf("13. Quitter\n");
}

void pause() {
    printf("Appuyez sur une touche pour continuer...\n");
    getchar();
}

int main() {
    system("cls");
    statistiqueVenteJournee();
    int choix;
    do {
        menu:
        afficherMenu();
        printf("Choix : ");
        scanf ("%*[^\n]");
        scanf("%d", &choix);
        switch (choix) {
            case 1:
                ajouterProduit();
                printf("Produit ajoute avec succes !\n");
                goto menu;
            case 2:
                ajouterPlusieursProduits();
                goto menu;
            case 3:
                afficherProduits();
                goto menu;
            case 4:
                afficherProduitsParOrdreAlphabetique();
                goto menu;
            case 5:
                afficherProduitsParOrdrePrix();
                goto menu;
            case 6:
                acheterProduit();
                printf("Produit achete avec succes !\n");
                goto menu;
            case 7:
                rechercherProduitParCode();
                goto menu;
            case 8:
                afficherProduitsParQuantite();
                goto menu;
            case 9:
                afficherProduitsParEtatStock();
                goto menu;
            case 10:
                alimenterStock();
                printf("Stock alimenter avec succes !\n");
                goto menu;
            case 11:
                supprimerProduitParCode();
                printf("Produit supprime avec succes !\n");
                goto menu;
            case 12:
                statistiqueVenteJournee();
                goto menu;
            case 13:
                printf("Au revoir !\n");
                exit(0);
            default:
                printf("\a");
                printf("Choix invalide !\n");
        }

    } while (choix != 12);


    return 0;
}


