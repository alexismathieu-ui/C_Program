#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <unistd.h>

/* Annuaire : fonctions découpées (chaque fonction <= 20 lignes) */

static void trim_newline(char *s) {
    size_t i = strlen(s);
    if (i && s[i - 1] == '\n')
        s[i - 1] = '\0';
}

static void pause_stdin(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

static FILE *ouvrir_annuaire(const char *mode) {
    return fopen("annuaire.txt", mode);
}

void afficher_annuaire(void) {
    FILE *f = ouvrir_annuaire("r");
    if (!f) {
        printf("Aucun annuaire trouvé (fichier introuvable).\n");
        return;
    }
    char ligne[256];
    int n = 0;
    while (fgets(ligne, sizeof(ligne), f)) {
        trim_newline(ligne);
        if (*ligne)
            printf("%2d: %s\n", ++n, ligne);
    }
    if (n == 0)
        printf("L'annuaire est vide.\n");
    fclose(f);
}

int lire_input(const char *prompt, char *buf, size_t sz) {
    printf("%s", prompt);
    if (!fgets(buf, sz, stdin))
        return 0;
    trim_newline(buf);
    return buf[0] != '\0';
}

void ajouter_nom_annuaire(void) {
    char prenom[100] = {0}, nom[100] = {0};
    if (!lire_input("Entrez le prénom: ", prenom, sizeof(prenom))) {
        printf("Prénom vide, annulation.\n");
        return;
    }
    if (!lire_input("Entrez le nom: ", nom, sizeof(nom))) {
        printf("Nom vide, annulation.\n");
        return;
    }
    FILE *f = ouvrir_annuaire("a");
    if (!f) {
        perror("Erreur d'ouverture du fichier pour ajout");
        return;
    }
    fprintf(f, "%s %s\n", prenom, nom);
    fclose(f);
    printf("Entrée ajoutée: %s %s\n", prenom, nom);
}

int ligne_est_nom_cible(const char *ligne, const char *cible) {
    char prenom[128] = {0}, nom[128] = {0};
    if (sscanf(ligne, "%127s %127s", prenom, nom) >= 2)
        return strcmp(nom, cible) == 0;
    return 0;
}

void supprimer_par_nom(void) {
    char cible[100] = {0};
    if (!lire_input("Entrez le nom (famille) à supprimer: ", cible,
                    sizeof(cible))) {
        printf("Nom vide, annulation.\n");
        return;
    }
    FILE *f = ouvrir_annuaire("r");
    if (!f) {
        printf("Aucun annuaire trouvé.\n");
        return;
    }
    FILE *tmp = fopen("annuaire.tmp", "w");
    if (!tmp) {
        perror("Erreur lors de la création du fichier temporaire");
        fclose(f);
        return;
    }
    char ligne[256];
    int sup = 0;
    while (fgets(ligne, sizeof(ligne), f)) {
        if (ligne_est_nom_cible(ligne, cible)) {
            sup++;
            continue;
        }
        fputs(ligne, tmp);
    }
    fclose(f);
    fclose(tmp);
    if (sup > 0) {
        if (remove("annuaire.txt") != 0) {
            perror("Erreur lors de la suppression de l'ancien fichier");
            return;
        }
        if (rename("annuaire.tmp", "annuaire.txt") != 0) {
            perror("Erreur lors du renommage du fichier temporaire");
            return;
        }
        printf("%d entrée(s) supprimée(s) avec le nom '%s'.\n", sup, cible);
    } else {
        remove("annuaire.tmp");
        printf("Aucune entrée trouvée avec le nom '%s'.\n", cible);
    }
}

void run_annuaire_menu(void) {
    for (;;) {
        printf("\n=== Menu Annuaire ===\n");
        printf("1) Voir l'annuaire\n");
        printf("2) Ajouter un nom\n");
        printf("3) Supprimer par nom (famille)\n");
        printf("4) Quitter\n");
        printf("Choix: ");
        int choix = 0;
        if (scanf("%d", &choix) != 1) {
            printf("Entrée invalide.\n");
            pause_stdin();
            continue;
        }
        pause_stdin();
        switch (choix) {
        case 1:
            afficher_annuaire();
            break;
        case 2:
            ajouter_nom_annuaire();
            break;
        case 3:
            supprimer_par_nom();
            break;
        case 4:
            printf("Au revoir.\n");
            return;
        default:
            printf("Choix inconnu.\n");
        }
    }
}



int main() {
    run_annuaire_menu();
    return 0;
}
