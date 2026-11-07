// Demonstration du tas max et du tas min ecrits a la main (sans conteneur)
#include <iostream>
#include "TasMax.h"
#include "TasMin.h"
using namespace std;

int main()
{
    int valeurs[] = {7, 9, 67, 1, 28, 8, 10, 29, 2, 57, 40, 6};

    // ---------- Tas max ----------
    TasMax tmax;
    for (int v : valeurs) tmax.inserer(v);
    cout << "===== TAS MAX =====\n";
    cout << "Tableau : "; tmax.afficherTableau();
    cout << "Arbre (racine a gauche) :\n"; tmax.dessiner();
    cout << "Racine (maximum) : " << tmax.racine() << "\n";
    cout << "Extractions successives : ";
    while (!tmax.vide()) cout << tmax.extraireRacine() << " ";
    cout << "\n";

    // ---------- Tas min ----------
    TasMin tmin;
    for (int v : valeurs) tmin.inserer(v);
    cout << "\n===== TAS MIN =====\n";
    cout << "Tableau : "; tmin.afficherTableau();
    cout << "Arbre (racine a gauche) :\n"; tmin.dessiner();
    cout << "Racine (minimum) : " << tmin.racine() << "\n";
    cout << "Extractions successives : ";
    while (!tmin.vide()) cout << tmin.extraireRacine() << " ";
    cout << "\n";
    return 0;
}
