// Demonstration de l'arbre binaire de recherche
#include <iostream>
#include <vector>
#include "ArbreBinaireRecherche.h"
using namespace std;

void afficher(const string& titre, const vector<int>& v)
{
    cout << titre;
    for (int x : v) cout << x << " ";
    cout << "\n";
}

int main()
{
    ABR arbre;
    for (int v : {50, 30, 70, 20, 40, 60, 80, 35, 45, 65})
        arbre.inserer(v);

    cout << "Arbre (racine a gauche, sous-arbre droit en haut) :\n";
    arbre.dessiner();

    cout << "\nNombre de noeuds : " << arbre.taille() << "\n";
    cout << "Hauteur          : " << arbre.hauteur() << "\n";
    cout << "Minimum          : " << arbre.minimum() << "\n";
    cout << "Maximum          : " << arbre.maximum() << "\n";

    afficher("\nParcours prefixe (racine, gauche, droite) : ", arbre.parcoursPrefixe());
    afficher("Parcours infixe  (gauche, racine, droite) : ", arbre.parcoursInfixe());
    afficher("Parcours suffixe (gauche, droite, racine) : ", arbre.parcoursSuffixe());
    afficher("Parcours en largeur (niveau par niveau)   : ", arbre.parcoursLargeur());

    cout << "\nRecherche de 45 : " << (arbre.rechercher(45) ? "trouve" : "absent") << "\n";
    cout << "Recherche de 55 : " << (arbre.rechercher(55) ? "trouve" : "absent") << "\n";
    cout << "Insertion de 40 (deja present) : " << (arbre.inserer(40) ? "ajoute" : "refuse") << "\n";

    cout << "\nSuppression de 20 (feuille) :\n";
    arbre.supprimer(20);
    afficher("  infixe : ", arbre.parcoursInfixe());
    cout << "Suppression de 60 (un seul enfant, 65) :\n";
    arbre.supprimer(60);
    afficher("  infixe : ", arbre.parcoursInfixe());
    cout << "Suppression de 50, la racine (deux enfants : remplacee par 65, le minimum a droite) :\n";
    arbre.supprimer(50);
    afficher("  infixe : ", arbre.parcoursInfixe());

    cout << "\nArbre apres les suppressions :\n";
    arbre.dessiner();
    return 0;
}
