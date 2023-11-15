#include "basedujeu.h"
#include "macro.h"
#include "mode.h"
#include "reprise_mode.h"
#include "time.h"
#include <stdio.h>
#include <stdlib.h>

int menuinitial() {
  int choix = 0;
  choix_initial(); // Affichage du menu
  scanf("%d", &choix);
  while (choix < 1 || choix > 3){ // Contrôle de la valeur de choix
    printf("Choisissez une valeure compatible :\n");
    scanf("%d", &choix);
  }
  if (choix == 1) {
    mode();
  } else if (choix == 2) {
    printf("Reprise de la derniere partie....\n");
    reprise_sauvegarde();
  } else if (choix == 3) {
    exit (0);
  }
  return 0;
}

/**
 *
 * @return mode de jeu
 */
int mode() {
  int rep_mode;
  choix_mode(); // Affichage des modes
  scanf("%d", &rep_mode);
  while (rep_mode < 1 || rep_mode > 3) { // Contôle de la valeur de rep_mode
    printf("Entrez une valeur correspondante a un des mode :\n");
    scanf("%d", &rep_mode);
  }
  if (rep_mode == 1) {
    mode_standard_alea(rep_mode); // Lancement du mode standard aléa
  } else if (rep_mode == 2) {
    mode_standard_alea(rep_mode);
  } else if (rep_mode == 3) { 
    mode_special(); // Lancement du mode standard aléa
  }
  return 0;
}

/**
 *
 * @return dimension du plateau
 */
int choix_taille() {
  int taille;
  printf("Quelle dimensions de tableau souhaitez vous ? :\n");
  scanf("%d", &taille);
  while (taille < TAILLE_MINI || taille > TAILLE_MAXI) {
    printf("Le tableau doit etre de taille >= 9x9 ou <= 14x14:\n");
    scanf("%d", &taille);
  }
  return taille;
}

/**
 * @param taille
 * @param plateau
 * saisie la taille et le plateau et genere un tableau rempli de 0 sans
 * l'afficher. Est utilisé dans les fonctions des modes.
 */
void generation_tableau(int taille,int plateau[][taille]) {

  // GENERATION DU TABLEAU
  for (int i = 0; i < taille; i++) {
    for (int j = 0; j < taille; j++) {
      plateau[i][j] = 0; // On remplit le tableau de 0.
    }
  }
}
void generation_tableau_verif_modesp(int taille,int plateau[][taille]) {

  // GENERATION DU TABLEAU
  for (int i = 0; i < taille; i++) {
    for (int j = 0; j < taille; j++) {
      plateau[i][j] = 0; // On remplit le tableau de 0.
    }
  }
}
void generation_tableau_victoireJ1(int taille,int plateau_victoireJ1[][taille]) {
  // GENERATION DU TABLEAU
  for (int i = 0; i < taille; i++) {
    for (int j = 0; j < taille; j++) {
      plateau_victoireJ1[i][j] = 100; // On remplit le tableau de 100.
    }
  }
}
void generation_tableau_victoireJ2(int taille,int plateau_victoireJ2[][taille]) {
  // GENERATION DU TABLEAU
  for (int i = 0; i < taille; i++) {
    for (int j = 0; j < taille; j++) {
      plateau_victoireJ2[i][j] = 100; // On remplit le tableau de 100.
    }
  }
}

/**
 * @param taille
 * @param plateau
 * saisie la taille et le plateau et genere un tableau avec N cases préremplie 
 * pour les deux joueurs sans
 * l'afficher. Est utilisé dans les fonctions des modes.
 */
void generation_tableau_alea(int taille, int plateau[][taille]) {

  // GENERATION DU TABLEAU NORMAL REMPLI DE 0

  for (int i = 0; i < taille; i++) {
    for (int j = 0; j < taille; j++) {
      plateau[i][j] = 0; // On remplit le tableau de 0.
    }
  }

  int nombre = (taille - 1) / 2; // Création de N.
  srand(time(NULL));

  // ATTRIBUTION J1
  for (int i = 0; i < nombre; i++) {
    int ligne_alea, colonne_alea;
    do {
      ligne_alea = rand() % taille;   // Tirage aléatoire ligne.
      colonne_alea = rand() % taille; // Tirage aléatoire colonne.
    } while (plateau[ligne_alea][colonne_alea] != 0); // VERIF que case prise est pas prise.
    plateau[ligne_alea][colonne_alea] = 1; // Pion 1 pour le joueur 1 placer
  }
  // ATTRIBUTION J2
  for (int i = 0; i < nombre; i++) {
    int ligne_alea, colonne_alea;
    do {
      ligne_alea = rand() % taille;   // Tirage aléatoire ligne.
      colonne_alea = rand() % taille; // Tirage aléatoire colonne.
    } while (plateau[ligne_alea][colonne_alea] != 0); // VERIF que case prise est pas prise.
    plateau[ligne_alea][colonne_alea] = 2; // Pion 1 pour le joueur 1 placer
  }
}

/**
 * @param taille
 * @param plateau
 * permet d'afficher le tableau de HEX avec le bon décalage des cases ainsi que     
 * les bonnes valeurs de celles-ci.
 */
void affichage_du_tableau(int taille, int plateau[][taille]) {

  // AFFICHAGE DU TAB
  int lettre;
  for (lettre = 0; lettre < taille; lettre++) {
    printf(rouge "  %c " reset, 'a' + lettre);
  }             // Affichage de la première ligne avec les lettres.
  printf("\n"); // Retour à la ligne afin de bien distinguer les contours du
                // plateau.
  for (int chiffre_colonne = 0; chiffre_colonne < taille; chiffre_colonne++) {
    for (int k = 0; k < chiffre_colonne; k++) {
      printf("  "); // Ce décalage permet de créer le plateau en incliné. Cette
                    // disposition est nécessaire pour le jeu HEX car une case
                    // doit toucher 6 autres.
    }
    if (chiffre_colonne < 9){
      printf(bleu "%d   " reset, chiffre_colonne + 1); // Ajout des chiffres en colonnes afin d'avoir les contours du plateau.
    }
    else if (chiffre_colonne >= 9){
      printf(bleu "%d  " reset, chiffre_colonne + 1); // Ajout des chiffres en colonnes afin d'avoir les contours du plateau avec un espace en moins pour l'alignement.
    }
    for (int j = 0; j < taille; j++) {
      if (plateau[chiffre_colonne][j] == 0) {
        printf(
            "%d   ",
            plateau[chiffre_colonne][j]); // On affiche les valeurs du plateau
      } else if (plateau[chiffre_colonne][j] == 1) {
        printf(
            jaune "%d   " reset,
            plateau[chiffre_colonne][j]); // On affiche les valeurs du plateau
      } else if (plateau[chiffre_colonne][j] == 2) {
        printf(
            vert "%d   " reset,
            plateau[chiffre_colonne][j]); // On affiche les valeurs du plateau
      } else if (plateau[chiffre_colonne][j] == 9) {
        printf(
            violet "%d   " reset,
            plateau[chiffre_colonne][j]); // On affiche les valeurs du plateau
      }
    }
    printf(bleu "%d" reset,
           chiffre_colonne +
               1); // Affichage du chiffre de colonne à côté des valeurs.
    if (chiffre_colonne == taille - 1) {
      printf("\n");
      for (int k = 0; k < taille + 1; k++) {
        printf("  "); // Ce décalage permet de créer le plateau en incliné.
                      // Cette disposition est nécessaire pour le jeu HEX car
                      // une case doit toucher 6 autres.
      }
      for (lettre = 0; lettre < taille; lettre++) {
        printf(rouge "  %c " reset,
               'a' +
                   lettre); // Affichage de la dernière ligne avec les lettres.
      }
    }
    printf("\n");
  }
}

/**
 *
 * @param mode
 * @param i
 * @param taille
 * @param plateau
 * permet de sauvegarder le mode, le tour du joueur, la taille, et le plateau
 * afin de pouvoir les réutillisez pour la fonction suivante
 */
void sauvegarde(int mode, int i, int taille, int plateau[][taille],int plateau_verif[][taille]) {
  FILE *fichier =
      fopen("sauvegardeHEX.txt", "w"); // Ouverture du fichier en mode ecriture.
  if (fichier == NULL) {
    printf("Erreur lors de l'ouverture du fichier.\n"); // Erreur si le fichier
                                                        // ne s'ouvre pas.
    return;
  }
  fprintf(fichier, "%d\n",
          mode); // La premiere ligne est le mode de la partie sauvegarde.
  fprintf(fichier, "%d\n",
          i); // La deuxieme ligne est le joueur qui doit jouer.
  fprintf(fichier, "%d\n",
          taille); // La troisieme ligne correspond a la taille du plateau.

  for (int i = 0; i < taille; i++) {
    for (int j = 0; j < taille; j++) {
      fprintf(fichier, "%d ", plateau[i][j]); // On ecrit les valeurs
    }
    fprintf(fichier, "\n");
  }
  fprintf(fichier, "\n");
  for (int i = 0; i < taille; i++) {
    for (int j = 0; j < taille; j++) {
      fprintf(fichier, "%d ", plateau_verif[i][j]); // On ecrit les valeurs
    }
    fprintf(fichier, "\n");
  }
  fclose(fichier); // Fermeture du fichier text.
  printf("La partie a ete sauvegardee.\n");
}

/**
 * permet de recuperer les parametres dans le fichier "SauvegardeHEX.text".
 * Recopie les valeurs des paramètres dans les variables.
 * Recopie les valeurs du plateau dans un tableau.
 * En fonction du mode recupere, lance le mode avec la fonction associée.
 */
void reprise_sauvegarde() {
  FILE *fichier;
  int i;
  int taille, mode;
  printf("Chargement de la partie...\n");

  // Ouvrir le fichier en mode lecture
  fichier = fopen("sauvegardeHEX.txt", "r");

  if (fichier == NULL) {
    printf("Erreur lors de l'ouverture du fichier de sauvegarde.\n");
    return;
  }

  fscanf(fichier, "%d", &mode);
  fgetc(fichier);
  fscanf(fichier, "%d", &i);
  fgetc(fichier);
  fscanf(fichier, "%d", &taille);
  fgetc(fichier);

  int plateau[taille][taille];
  int plateau_verif[taille][taille];
  // Lire les valeurs du plateau depuis le fichier
  for (int x = 0; x < taille; x++) {
    for (int j = 0; j < taille; j++) {
      fscanf(fichier, "%d", &plateau[x][j]);
    }
    fgetc(fichier); // Lire l'espace ou le caractère de nouvelle ligne
  }
  fgetc(fichier);
  for (int x = 0; x < taille; x++) {
    for (int j = 0; j < taille; j++) {
      fscanf(fichier, "%d", &plateau_verif[x][j]);
    }
    fgetc(fichier); // Lire l'espace ou le caractère de nouvelle ligne
  }
  // Fermer le fichier
  fclose(fichier);
  affichage_du_tableau(taille, plateau);
  printf("La partie a ete charge.\n");
  if (mode == 1 || mode == 2) {
    reprise_mode_sa(mode, i, taille, plateau);
  } else if (mode == 3) {
    reprise_mode_special(i, taille, plateau, plateau_verif);
  }
}

/**
 * @param taille
 * @param plateau
 * @param plateau_victoire
 * determine si le joueur à gagner en regardant si les pions de celui-ci forment    
 * un chemin à la fois sur le plateau de jeu ainsi que sur le plateau_victoire      
 * associé au joueur.
 */
int victoireJ1(int taille, int plateau[][taille],int plateau_victoireJ1[][taille]) {
  int ligne, p, i, j, Xmin;
  for (ligne = 0; ligne < taille;
       ligne++) { // On remplie la première colonne du tableau victoire du J1
    if (plateau[ligne][0] == 1) {
      plateau_victoireJ1[ligne][0] = 1;
    }
  }
  for (i = 1; i < taille; i++) {
    for (j = 0; j < taille; j++) {
      if (plateau[j][i] == 1 &&
          (plateau[j + 1][i] == 1 || plateau[j - 1][i] == 1 ||
           plateau[j][i - 1] == 1 || plateau[j][i + 1] == 1 ||
           plateau[j + 1][i - 1] == 1 || plateau[j - 1][i + 1] == 1)) {
        Xmin = 100;
        if (Xmin > plateau_victoireJ1[j - 1][i] && j > 0) {
          Xmin = plateau_victoireJ1[j - 1][i];
        }
        if (Xmin > plateau_victoireJ1[j + 1][i] && j < taille - 1) {
          Xmin = plateau_victoireJ1[j + 1][i];
        }
        if (Xmin > plateau_victoireJ1[j][i - 1] && i > 0) {
          Xmin = plateau_victoireJ1[j][i - 1];
        }
        if (Xmin > plateau_victoireJ1[j][i + 1] && i < taille - 1) {
          Xmin = plateau_victoireJ1[j][i + 1];
        }
        if (Xmin > plateau_victoireJ1[j + 1][i - 1] && j < taille - 1 &&
            i > 0) {
          Xmin = plateau_victoireJ1[j + 1][i - 1];
        }
        if (Xmin > plateau_victoireJ1[j - 1][i + 1] && i < taille - 1 &&
            j > 0) {
          Xmin = plateau_victoireJ1[j - 1][i + 1];
        }
        if (Xmin == 101) {
          Xmin = 100;
        }
        if (Xmin != 100) {
          plateau_victoireJ1[j][i] = Xmin + 1;
        }
      }
    }
  }

  for (p = 0; p < taille; p++) {
    if (plateau_victoireJ1[p][taille - 1] >= taille &&
        plateau_victoireJ1[p][taille - 1] < 100) {
      printf("\n\nIl existe un chemin, le joueur 1 gagne !\n");
      exit(0);
      return 1;
    }
  }
}
int victoireJ2(int taille, int plateau[][taille],int plateau_victoireJ2[][taille]) {
  int colonne, p, i, j, Xmin;
  for (colonne = 0; colonne < taille;
       colonne++) { // On remplie la première colonne du tableau victoire du J2
    if (plateau[0][colonne] == 2) {
      plateau_victoireJ2[0][colonne] = 1;
    }
  }

  for (i = 1; i < taille; i++) {
    for (j = 0; j < taille; j++) {
      if (plateau[i][j] == 2 &&
          (plateau[i + 1][j] == 2 || plateau[i - 1][j] == 2 ||
           plateau[i][j - 1] == 2 || plateau[i][j + 1] == 2 ||
           plateau[i + 1][j - 1] == 2 || plateau[i - 1][j + 1] == 2)) {
        Xmin = 100;
        if (Xmin > plateau_victoireJ2[i - 1][j] && i > 0) {
          Xmin = plateau_victoireJ2[i - 1][j];
        }
        if (Xmin > plateau_victoireJ2[i + 1][j] && i < taille - 1) {
          Xmin = plateau_victoireJ2[i + 1][j];
        }
        if (Xmin > plateau_victoireJ2[i][j - 1] && j > 0) {
          Xmin = plateau_victoireJ2[j][i - 1];
        }
        if (Xmin > plateau_victoireJ2[i][j + 1] && j < taille - 1) {
          Xmin = plateau_victoireJ2[i][j + 1];
        }
        if (Xmin > plateau_victoireJ2[i + 1][j - 1] && i < taille - 1 &&
            j > 0) {
          Xmin = plateau_victoireJ2[i + 1][j - 1];
        }
        if (Xmin > plateau_victoireJ2[i - 1][j + 1] && j < taille - 1 &&
            i > 0) {
          Xmin = plateau_victoireJ2[i - 1][j + 1];
        }
        if (Xmin == 101) {
          Xmin = 100;
        }
        if (Xmin != 100) {
          plateau_victoireJ2[i][j] = Xmin + 1;
        }
      }
    }
  }

  for (p = 0; p < taille; p++) {
    if (plateau_victoireJ2[taille - 1][p] >= taille &&
        plateau_victoireJ2[taille - 1][p] < 100) {
      printf("\n\nIl existe un chemin, le joueur 2 gagne !\n");
      exit(0);
      return 1;
    }
  }
}
