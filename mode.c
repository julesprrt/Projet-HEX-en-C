#include "mode.h"
#include "basedujeu.h"
#include "macro.h"
#include <ctype.h>
#include <stdio.h>

void mode_standard_alea(int mode) {

  int taille = choix_taille();
  int plateau[taille][taille];
  int plateau_verif[taille][taille];
  int plateau_victoireJ1[taille][taille];
  int plateau_victoireJ2[taille][taille];
  generation_tableau_victoireJ1(taille, plateau_victoireJ1);
  generation_tableau_victoireJ2(taille, plateau_victoireJ2);
  generation_tableau_verif_modesp(
      taille, plateau_verif); // Plateau de verification des cases bloquées.
  if (mode == 1)              // Lancement du mode standard
  {
    generation_tableau(taille, plateau);
    affichage_du_tableau(taille, plateau);
  } else if (mode == 2) // Lancement du mode aleatoire
  {
    generation_tableau_alea(taille, plateau);
    affichage_du_tableau(taille, plateau);
  }
  int joueur1 = 0, joueur2 = 2;
  Jeux pion;
  int i = 1, k = 0;
  do {
    printf("\nTour de joueur %d :\n", joueur1 + i);
    regle();
    demande();
    scanf("%d", &pion.chiffre);

    while (pion.chiffre < 1 || pion.chiffre > taille) {
      printf("Veuillez saisir une valeur compatible avec le tableau (chiffre "
             "entre 1 et %d) :\n",
             taille);
      scanf("%d", &pion.chiffre);
    }

    printf("-\n");
    int verif = scanf(" %c", &pion.lettre);

    if (pion.lettre == 'x') {
      int gagnant;
      if (i == 1) {
        gagnant = 2;
      } else {
        gagnant = 1;
      }
      printf("Vous avez choisi d'abandonner, le joueur numero %d a gagne !\n",
             gagnant);
      return;
    }

    if (pion.lettre == 's') {
      sauvegarde(mode, i, taille, plateau, plateau_verif);
    }

    while (verif != 1) {
      erreur_lettre();
      verif = scanf(" %c", &pion.lettre);
    }
    if (pion.lettre == 's') {
      continue;
    }
    while (pion.lettre < 'a' || pion.lettre >= 'a' + taille) {
      printf("Veuillez saisir une valeur compatible avec le tableau (lettre "
             "entre 'a' et '%c') :\n",
             'a' + taille - 1);
      scanf(" %c", &pion.lettre);
      pion.lettre = tolower(pion.lettre);
    }

    printf("\nVous avez choisi de placer votre pion en %d-%c\n", pion.chiffre,
           pion.lettre);

    pion.lettre = tolower(pion.lettre);
    if (pion.lettre >= 'a' && pion.lettre <= 'z') {
      pion.chiffre_de_la_lettre = pion.lettre - 'a';
    }

    if (plateau[pion.chiffre - 1][pion.chiffre_de_la_lettre] == 1 ||
        plateau[pion.chiffre - 1][pion.chiffre_de_la_lettre] == 2 ||
        plateau[pion.chiffre - 1][pion.chiffre_de_la_lettre] == 9) {
      erreur_case();
      continue; // Demande au joueur de saisir une case valide
    }

    plateau[pion.chiffre - 1][pion.chiffre_de_la_lettre] = i;
    affichage_du_tableau(taille, plateau);

    if (i == 1) {
      victoireJ1(taille, plateau, plateau_victoireJ1); // Victoire J1
    } else if (i == 2) {
      victoireJ2(taille, plateau, plateau_victoireJ2); // Victoire J2
    }

    i++;
    if (i % 2 == 0) {
      i = 2;
    } else {
      i = 1;
    }
  } while (&victoireJ1 || &victoireJ2);
}

void mode_special() {
  int mode = 3; // Designe le mode spécial pour la sauvegarde.
  int taille = choix_taille();
  int plateau[taille][taille];
  int plateau_verif[taille][taille];
  int plateau_victoireJ1[taille][taille];
  int plateau_victoireJ2[taille][taille];
  int joueur1 = 0, joueur2 = 2;
  Jeux pion; // Definition du pion a l'aide de la structure.
  int i = 1, k = 0, s = 0;
  generation_tableau_victoireJ1(
      taille, plateau_victoireJ1); // Plateau victoire du joueur 1
  generation_tableau_victoireJ2(
      taille, plateau_victoireJ2); // Plateau victoire du joueur 2
  generation_tableau_verif_modesp(
      taille, plateau_verif);          // Plateau pour cases bloquées.
  generation_tableau(taille, plateau); // Plateau de jeu.
  affichage_du_tableau(taille, plateau);

  // DEBUT DU JEU
  do {
    s--; // Décrémenter la variable afin de fare
    if (s == 0) {
      if (i == 1){
        printf("\nLe joueur %d doit passe son tour.",i);
          i = 2;
      }
      else if (i == 2){
      printf("\nLe joueur %d doit passe son tour.",i);
        i = 1;
      }
    }
    // Mise à jour du nombre de tours restants pour les cases inutilisables
    for (int x = 0; x < taille; x++) {
      for (int y = 0; y < taille; y++) {
        if (plateau_verif[x][y] > 0) {
          plateau_verif[x][y]++; // Incrémenter le nombre de tours restants
        }
        if (plateau_verif[x][y] > 4) {
          plateau[x][y] = 0; // Debloquer la case
          plateau_verif[x][y] = 0; // On remet à 0 notre case dans plateau_verif
          printf("\nLa case %d-%c n'est plus bloquee ! Voici le plateau mit a jour.\n\n", x + 1, 'a' + y);
          affichage_du_tableau(taille, plateau);
        }
      }
    }

    int choix_special = 0;
    printf("\nTour de joueur %d : \n", joueur1 + i);
    menu_mode_special();
    scanf("%d", &choix_special);

    // MODE SPECIAL CHOIX 1
    if (choix_special == 1) {
      demande();
      regle();
      scanf("%d", &pion.chiffre);

      while (pion.chiffre < 1 || pion.chiffre > taille) {
        printf("Veuillez saisir une valeur compatible avec le tableau (chiffre "
               "entre 1 et %d) :\n",
               taille);
        scanf(" %d", &pion.chiffre);
      }

      printf("-\n");
      int verif = scanf(" %c", &pion.lettre);

      if (pion.lettre == 'x') {
        int gagnant;
        if (i == 1) {
          gagnant = 2;
        } else {
          gagnant = 1;
        }
        printf("Vous avez choisi d'abandonner, le joueur numero %d a gagne !\n",
               gagnant);
        return;
      }

      if (pion.lettre == 's') {
        sauvegarde(mode, i, taille, plateau, plateau_verif);
      }

      while (verif != 1) {
        erreur_lettre();
        verif = scanf(" %c", &pion.lettre);
      }
      if (pion.lettre == 's') {
        continue;
      }
      while (pion.lettre < 'a' || pion.lettre >= 'a' + taille) {
        printf("Veuillez saisir une valeur compatible avec le tableau (lettre "
               "entre 'a' et '%c') :\n",
               'a' + taille - 1);
        scanf(" %c", &pion.lettre);
        pion.lettre = tolower(pion.lettre);
      }

      printf("\nVous avez choisi de placer votre pion en %d-%c\n", pion.chiffre,
             pion.lettre);

      pion.lettre = tolower(pion.lettre);
      if (pion.lettre >= 'a' && pion.lettre <= 'z') {
        pion.chiffre_de_la_lettre = pion.lettre - 'a';
      }

      if (plateau[pion.chiffre - 1][pion.chiffre_de_la_lettre] == 1 ||
          plateau[pion.chiffre - 1][pion.chiffre_de_la_lettre] == 2 ||
          plateau[pion.chiffre - 1][pion.chiffre_de_la_lettre] == 9) {
        erreur_case();
        continue; // Demande au joueur de saisir une case valide
      }

      plateau[pion.chiffre - 1][pion.chiffre_de_la_lettre] = i;
      affichage_du_tableau(taille, plateau);

      i++;
      if (i % 2 == 0) {
        i = 2;
      } else {
        i = 1;
      }
    }
    // MODE SPECIAL CHOIX 2
    if (choix_special == 2) {

      Jeux pion_a_retirer;
      printf("Quel pion souhaitez vous retirez : (CHIFFRE-LETTRE)\n");
      scanf("%d", &pion_a_retirer.chiffre);
      while (pion_a_retirer.chiffre < 1 || pion_a_retirer.chiffre > taille) {
        printf("Veuillez saisir une valeur compatible avec le tableau (chiffre "
               "entre 1 et %d) :\n",
               taille);
        scanf("%d", &pion_a_retirer.chiffre);
      }
      printf("-\n");
      int verif = scanf(" %c", &pion_a_retirer.lettre);
      while (verif != 1) {
        erreur_lettre();
        verif = scanf(" %c", &pion_a_retirer.lettre);
      }
      while (pion_a_retirer.lettre < 'a' ||
             pion_a_retirer.lettre >= 'a' + taille) {
        printf("Veuillez saisir une valeur compatible avec le tableau (lettre "
               "entre 'a' et '%c') :\n",
               'a' + taille - 1);
        scanf(" %c", &pion_a_retirer.lettre);
        pion_a_retirer.lettre = tolower(pion_a_retirer.lettre);
      }
      pion_a_retirer.lettre = tolower(
          pion_a_retirer.lettre); // Convertion en minuscule du caractere pour
      // utiliser le CODE ASCII.
      if (pion_a_retirer.lettre >= 'a' && pion_a_retirer.lettre <= 'z') {
        pion_a_retirer.chiffre_de_la_lettre =
            pion_a_retirer.lettre -
            'a'; // On soustrait le code ASCII de la lettre 'a'.
      }
      int bloque = 9;
      plateau[pion_a_retirer.chiffre - 1][pion_a_retirer.chiffre_de_la_lettre] =
          bloque;
      plateau_verif[pion_a_retirer.chiffre - 1]
                   [pion_a_retirer.chiffre_de_la_lettre] = 1;
      affichage_du_tableau(taille, plateau);
      printf("\nVous avez choisi de retirer le pion en %d-%c, cette case "
             "devient donc inutilisable pour 3 tours.\n",
             pion_a_retirer.chiffre, pion_a_retirer.lettre);
      printf("\n");
      k++;
      i++;
      if (i % 2 == 0) {
        i = 2; // Condition IF pour que les tours alternent juste en 1 et 2 et
               // que i ne prennent pas d'autres valeurs.
      } else {
        i = 1;
      }
    }

    // MODE SPECIAL CHOIX 3

    if (choix_special == 3) {
      s = 2;
      demande();
      printf("Premiere position :\n");
      scanf("%d", &pion.chiffre);
      while (pion.chiffre < 1 || pion.chiffre > taille) {
        printf("Veuillez saisir une valeur compatible avec le tableau (chiffre "
               "entre 1 et %d) :\n",
               taille);
        scanf("%d", &pion.chiffre);
      }
      printf("- \n");
      int verif = scanf(" %c", &pion.lettre);
      if (pion.lettre == 'x') {
        int gagnant;
        if (i == 1) {
          gagnant = 2;
        } else {
          gagnant = 1;
        }
        printf("Vous avez choisi d'abandonner, le joueur numero %d a gagne !\n",
               gagnant);
        return;
      }
      if (pion.lettre == 's') {
        sauvegarde(mode, i, taille, plateau, plateau_verif);
      }
      while (verif != 1) {
        erreur_lettre();
        verif = scanf(" %c", &pion.lettre);
      }
      if (pion.lettre == 's') {
        continue;
      }
      while (pion.lettre < 'a' || pion.lettre >= 'a' + taille) {
        printf("Veuillez saisir une valeur compatible avec le tableau (lettre "
               "entre 'a' et '%c') :\n",
               'a' + taille - 1);
        scanf(" %c", &pion.lettre);
        pion.lettre = tolower(pion.lettre);
      }

      printf("\nVous avez choisi de placer votre pion en %d-%c \n",
             pion.chiffre, pion.lettre);

      // Conversion de la lettre en chiffre pour l'afficher dans le tableau.

      pion.lettre =
          tolower(pion.lettre); // Convertion en minuscule du caractère pour
      // utiliser le CODE ASCII.
      if (pion.lettre >= 'a' && pion.lettre <= 'z') {
        pion.chiffre_de_la_lettre =
            pion.lettre - 'a'; // On soustrait le code ASCII de la lettre 'a'.
      }

      // Vérification que la case du tableau n'est pas prise.
      if (plateau[pion.chiffre - 1][pion.chiffre_de_la_lettre] == 1 ||
          plateau[pion.chiffre - 1][pion.chiffre_de_la_lettre] == 2 ||
          plateau[pion.chiffre - 1][pion.chiffre_de_la_lettre] == 9) {
        erreur_case();
        continue;

        // Conversion de la lettre en chiffre pour l'afficher dans le tableau.

        pion.lettre =
            tolower(pion.lettre); // Convertion en minuscule du caractère pour
        // utiliser le CODE ASCII.
        if (pion.lettre >= 'a' && pion.lettre <= 'z') {
          pion.chiffre_de_la_lettre =
              pion.lettre - 'a'; // On soustrait le code ASCII de la lettre 'a'.
        }
      }

      plateau[pion.chiffre - 1][pion.chiffre_de_la_lettre] =
          i; // Affectation dans le tableau du point du joueur.
      int ligneP1 =
          pion.chiffre - 1; // On retient le placement du pion tout juste joué
      int colonneP1 = pion.chiffre_de_la_lettre; // pour pouvoir le réutiliser
                                                 // pour la deuxième position
      affichage_du_tableau(taille, plateau);

      printf("Deuxieme position :\n");
      scanf("%d", &pion.chiffre);
      while (pion.chiffre < 1 || pion.chiffre > taille) {
        printf("Veuillez saisir une valeur compatible avec le tableau (chiffre "
               "entre 1 et %d) :\n",
               taille);
        scanf("%d", &pion.chiffre);
      }
      printf("- \n");
      verif = scanf(" %c", &pion.lettre);
      if (pion.lettre == 'x') {
        int gagnant;
        if (i == 1) {
          gagnant = 2;
        } else {
          gagnant = 1;
        }
        printf("Vous avez choisi d'abandonner, le joueur numero %d a gagne !\n",
               gagnant);
        return;
      }
      if (pion.lettre == 's') {
        sauvegarde(mode, i, taille, plateau, plateau_verif);
      }
      while (verif != 1) {
        erreur_lettre();
        verif = scanf(" %c", &pion.lettre);
      }
      if (pion.lettre == 's') {
        continue; // SI demande de sauvegarde, passe au tour suivant directement
      }
      while (pion.lettre < 'a' || pion.lettre >= 'a' + taille) {
        printf("Veuillez saisir une valeur compatible avec le tableau (lettre "
               "entre 'a' et '%c') :\n",
               'a' + taille - 1);
        scanf(" %c", &pion.lettre);
        pion.lettre = tolower(pion.lettre);
      }

      printf("\nVous avez choisi de placer votre pion en %d-%c \n",
             pion.chiffre, pion.lettre);

      // Conversion de la lettre en chiffre pour l'afficher dans le tableau.

      pion.lettre =
          tolower(pion.lettre); // Convertion en minuscule du caractère pour
      // utiliser le CODE ASCII.

      if (pion.lettre >= 'a' && pion.lettre <= 'z') {
        pion.chiffre_de_la_lettre =
            pion.lettre - 'a'; // On soustrait le code ASCII de la lettre 'a'.
      }
      // Vérification que les deux cases ne sont pas adjacentes.
      int chiffre_reel = pion.chiffre - 1;
      if (plateau[chiffre_reel + 1][pion.chiffre_de_la_lettre] == i &&
              chiffre_reel < taille - 1 ||
          plateau[chiffre_reel - 1][pion.chiffre_de_la_lettre] == i &&
              chiffre_reel > 0 ||
          plateau[chiffre_reel][pion.chiffre_de_la_lettre - 1] == i &&
              pion.chiffre_de_la_lettre > 0 ||
          plateau[chiffre_reel][pion.chiffre_de_la_lettre + 1] == i &&
              pion.chiffre_de_la_lettre < taille - 1 ||
          plateau[chiffre_reel + 1][pion.chiffre_de_la_lettre - 1] == i &&
              chiffre_reel < taille - 1 && pion.chiffre_de_la_lettre > 0 ||
          plateau[chiffre_reel - 1][pion.chiffre_de_la_lettre + 1] == i &&
              chiffre_reel > 0 && pion.chiffre_de_la_lettre < taille - 1) {
        erreur_adjacence();
        plateau[ligneP1][colonneP1] =
            0; // On réaffecte la valeur 0 à la case précédemment joué
        affichage_du_tableau(taille, plateau);
        continue;
      }

      // Vérification que la case du tableau n'est pas prise.
      if (plateau[pion.chiffre - 1][pion.chiffre_de_la_lettre] == 1 ||
          plateau[pion.chiffre - 1][pion.chiffre_de_la_lettre] == 2 ||
          plateau[pion.chiffre - 1][pion.chiffre_de_la_lettre] == 9) {
        erreur_case();
        plateau[ligneP1][colonneP1] =
            0; // On réaffecte la valeur 0 à la case précédemment joué
        affichage_du_tableau(taille, plateau);
        continue;
      }

      plateau[pion.chiffre - 1][pion.chiffre_de_la_lettre] =
          i; // Affectation dans le tableau du point du joueur.
      affichage_du_tableau(taille, plateau);

      if (i == 1) {
        victoireJ1(taille, plateau, plateau_victoireJ1); // Tour du joueur 1 donc victoireJ1 
      } else if (i == 2) {
        victoireJ2(taille, plateau, plateau_victoireJ2); // Tour du joueur 2 donc victoireJ2
      }

      i++;
      k++; // Passe au tour suivant
      if (i % 2 == 0) {
        i = 2; // Condition IF pour que les tours alternent juste en 1 et 2 et
               // que i ne prenne pas d'autres valeurs.
      } else {
        i = 1;
      }
    }
  } while (&victoireJ1 || &victoireJ2);
}
