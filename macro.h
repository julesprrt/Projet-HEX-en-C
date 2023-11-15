#ifndef PROJETIF_MACRO_H
// Ici on définit toutes nos macros qui permettent d'alléger le code en enlevant du texte.

#define regle() printf("Voici les regles : Le joueur 1 doit relier le tableau de droite a gauche et le joueur 2 de haut en bas.\n");

#define demande() printf("Quelle position souhaitez vous jouez ? (CHIFFRE-LETTRE) - SAISIR 'x' en miniscule  POUR ABANDON ET 's' en miniscule POUR SAUVEGARDER DANS LETTRE:\n");

#define erreur_lettre() printf("Erreur : La valeur que vous avez renseigne nest pas une lettre.\n");

#define erreur_case() printf("Cette case du plateau est prise ou bloque. Veuillez jouer un autre coup.\n");

#define erreur_adjacence() printf("Les deux pions sont adjacents. Veuillez jouer un autre coup.\n");

#define menu_mode_special() printf("1. Jouer normalement un pion :\n"); \
                            printf("2. Retirer un pion adverse. ATTENTION! Cette case deviendra inutilisable pendant trois tours\n") ;\
                            printf("3. Doubler un coup. ATTENTION! Les deux pions ne doivent pas etre adjacents. Vous serrez oblige de passer votre tour au coup suivant.\n");

#define choix_initial() printf("Bienvenue sur le jeu de HEX\n"); \
                        printf("1) Demarrer une partie\n"); \
                        printf("2) Reprendre une partie\n"); \
                        printf("3) Quitter\n");

#define choix_mode()    printf("1) Mode classique\n"); \
                        printf("2) Mode aletoire\n"); \
                        printf("3) Mode special\n");

// Ici on définit les codes de nos couleurs qui seront attribuées à chaque pion. Nous les utilisons dans les printf afin de distinguer les differents pions.
#define rouge     "\x1b[31m" 
#define reset   "\x1b[0m" // Permet de remettre la couleur du texte en blanc
#define violet   "\x1b[35m"
#define jaune "\x1b[33m"
#define bleu    "\x1b[34m"
#define vert  "\x1b[32m"

// Ici on définit la taille MAX et MIN de notre tableau principal.
#define TAILLE_MINI 9
#define TAILLE_MAXI 14

#define PROJETIF_MACRO_H

#endif //PROJETIF_MACRO_H
