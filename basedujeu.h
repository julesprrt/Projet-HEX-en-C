#ifndef PROJETIF_F_H

// STRUCTURE BASE DU JEU
typedef struct Jeux Jeux;
struct Jeux
{
    int chiffre;
    char lettre;
    int chiffre_de_la_lettre;


};

// Voici les fonctions de "base_du_jeu"
int menuinitial();
int mode();
int choix_taille();
void generation_tableau(int taille, int plateau[][taille]);
void generation_tableau_verif_modesp(int taille, int plateau[][taille]);
void generation_tableau_alea(int taille, int plateau[][taille]);
void generation_tableau_victoireJ1(int taille, int plateau[][taille]);
void generation_tableau_victoireJ2(int taille, int plateau[][taille]);
void affichage_du_tableau(int taille, int plateau[][taille]);
void sauvegarde(int mode, int i , int taille, int plateau[][taille], int plateau_verif[][taille]);
void reprise_sauvegarde();
int victoireJ1(int taille, int plateau[][taille], int plateau_victoireJ1[][taille]);
int victoireJ2(int taille, int plateau[][taille], int plateau_victoireJ2[][taille]);

#define PROJETIF_F_H

#endif //PROJETIF_F_H
