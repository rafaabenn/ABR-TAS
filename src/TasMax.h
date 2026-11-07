// Tas max ecrit a la main, SANS conteneur de la STL : un simple tableau dynamique (new / delete).
// Regle : chaque parent est plus grand que ses enfants -> le maximum est a la racine (indice 0).
// Pour l'element d'indice i : parent (i-1)/2, enfant gauche 2i+1, enfant droit 2i+2.
#pragma once
#include <iostream>
using namespace std;

class TasMax {
private:
    int* t;              // le tableau
    int capacite;        // nombre de cases reservees
    int n = 0;           // nombre d'elements dans le tas

    static int parent(int i) { return (i - 1) / 2; }
    static int gauche(int i) { return 2 * i + 1; }
    static int droite(int i) { return 2 * i + 2; }

    // Agrandir le tableau quand il est plein (on double sa taille)
    void agrandir()
    {
        int* nouveau = new int[2 * capacite];
        for (int i = 0; i < n; i++) nouveau[i] = t[i];
        delete[] t;
        t = nouveau;
        capacite *= 2;
    }

    // Faire monter l'element i tant qu'il est plus grand que son parent
    void monter(int i)
    {
        while (i > 0 && t[i] > t[parent(i)]) {
            swap(t[i], t[parent(i)]);
            i = parent(i);
        }
    }

    // Faire descendre l'element i vers le plus grand de ses enfants
    void descendre(int i)
    {
        while (true) {
            int plusGrand = i;
            int g = gauche(i), d = droite(i);
            if (g < n && t[g] > t[plusGrand]) plusGrand = g;
            if (d < n && t[d] > t[plusGrand]) plusGrand = d;
            if (plusGrand == i) break;            // les deux enfants sont plus petits : fini
            swap(t[i], t[plusGrand]);
            i = plusGrand;
        }
    }

public:
    TasMax(int capaciteInitiale = 16) : t(new int[capaciteInitiale]), capacite(capaciteInitiale) {}
    ~TasMax() { delete[] t; }
    TasMax(const TasMax&) = delete;              // pas de copie (le tableau serait partage)
    TasMax& operator=(const TasMax&) = delete;

    // Insertion : on ajoute a la fin, puis on fait monter -> O(log n)
    void inserer(int v)
    {
        if (n == capacite) agrandir();
        t[n] = v;
        monter(n);
        n++;
    }

    // Lire la racine (le maximum) -> O(1)
    int racine() const { return t[0]; }

    // Extraire la racine : le dernier element prend sa place, puis on le fait descendre -> O(log n)
    int extraireRacine()
    {
        int max = t[0];
        t[0] = t[n - 1];
        n--;
        descendre(0);
        return max;
    }

    bool vide() const { return n == 0; }
    int taille() const { return n; }

    void afficherTableau() const
    {
        for (int i = 0; i < n; i++) cout << t[i] << " ";
        cout << "\n";
    }
    // Dessin de l'arbre : racine a gauche, enfant droit en haut
    void dessiner(int i = 0, int espace = 0) const
    {
        if (i >= n) return;
        dessiner(droite(i), espace + 6);
        cout << string(espace, ' ') << t[i] << "\n";
        dessiner(gauche(i), espace + 6);
    }
};
