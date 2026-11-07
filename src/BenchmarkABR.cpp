// Benchmark de l'arbre binaire de recherche : effet de l'ordre d'insertion
//   ./bin/BenchmarkABR        (tableau lisible)
//   ./bin/BenchmarkABR csv    (format CSV)
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <chrono>
#include <random>
#include <numeric>
#include <algorithm>
#include "ArbreBinaireRecherche.h"
using namespace std;
using namespace std::chrono;

double ns(steady_clock::time_point t0) { return duration<double, nano>(steady_clock::now() - t0).count(); }

struct Mesure { double inserer, rechercher, supprimer; int hauteur; };

// Construit l'arbre avec les cles dans l'ordre donne, puis mesure les 3 operations (ns par operation)
Mesure mesurer(const vector<int>& cles)
{
    int N = cles.size();
    vector<int> requetes = cles;                         // recherches et suppressions dans un ordre aleatoire
    shuffle(requetes.begin(), requetes.end(), mt19937(7));
    Mesure m;
    ABR a;
    auto t0 = steady_clock::now();
    for (int x : cles) a.inserer(x);
    m.inserer = ns(t0) / N;
    m.hauteur = a.hauteur();

    long long trouves = 0;
    t0 = steady_clock::now();
    for (int x : requetes) trouves += a.rechercher(x);
    m.rechercher = ns(t0) / N;
    if (trouves != N) cout << "ERREUR : recherche\n";

    t0 = steady_clock::now();
    for (int x : requetes) a.supprimer(x);
    m.supprimer = ns(t0) / N;
    if (!a.vide()) cout << "ERREUR : suppression\n";
    return m;
}

int main(int argc, char* argv[])
{
    bool csv = argc > 1 && string(argv[1]) == "csv";
    if (csv) cout << "ordre;N;hauteur;inserer_ns;rechercher_ns;supprimer_ns\n";
    else {
        cout << "ARBRE BINAIRE DE RECHERCHE : EFFET DE L'ORDRE D'INSERTION\n";
        cout << "(temps moyen par operation, en nanosecondes ; '-' = non mesure, trop long)\n\n";
        cout << left << setw(12) << "Ordre" << right << setw(10) << "N" << setw(10) << "Hauteur"
             << setw(13) << "Insertion" << setw(13) << "Recherche" << setw(14) << "Suppression" << "\n";
        cout << string(72, '-') << "\n";
    }
    for (string ordre : {"croissant", "aleatoire"}) {
        for (int N : {1000, 2000, 5000, 10000, 20000, 50000, 100000, 1000000}) {
            if (ordre == "croissant" && N > 20000) continue;   // O(N^2) : trop long au-dela
            vector<int> cles(N);
            iota(cles.begin(), cles.end(), 0);                  // 0, 1, 2, ..., N-1
            if (ordre == "aleatoire") shuffle(cles.begin(), cles.end(), mt19937(42));
            // meilleur de 3 essais
            Mesure best = mesurer(cles);
            for (int r = 1; r < 3; r++) {
                Mesure m = mesurer(cles);
                best.inserer = min(best.inserer, m.inserer);
                best.rechercher = min(best.rechercher, m.rechercher);
                best.supprimer = min(best.supprimer, m.supprimer);
            }
            if (csv)
                cout << ordre << ";" << N << ";" << best.hauteur << ";" << best.inserer << ";"
                     << best.rechercher << ";" << best.supprimer << "\n";
            else
                cout << left << setw(12) << ordre << right << setw(10) << N << setw(10) << best.hauteur
                     << fixed << setprecision(1)
                     << setw(13) << best.inserer << setw(13) << best.rechercher << setw(14) << best.supprimer << "\n";
            cout.flush();
        }
    }
    return 0;
}
