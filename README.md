# Arbre binaire de recherche et tas (C++)

TP de C++ — ILISI 2e année — BENNOUR RAFAA

- **ABR** : insertion, recherche, minimum/maximum, suppression (feuille, un enfant, deux enfants), parcours préfixe, infixe, suffixe et en largeur.
- **Tas max** et **tas min** écrits à la main, **sans conteneur** (tableau `new`/`delete`).
- **Benchmark** : tas max à la main contre `std::priority_queue<int>`, sur l'insertion et l'extraction de la racine (la plus grande valeur).

## Organisation

```
src/
  ArbreBinaireRecherche.h   classe ABR
  TasMax.h, TasMin.h        tas écrits à la main
  DemoABR.cpp, DemoTas.cpp  démonstrations
  BenchmarkABR.cpp          ABR : ordre croissant vs aléatoire
  BenchmarkTas.cpp          tas max : à la main vs priority_queue
resultats/                  sorties des démos et mesures (CSV)
rapport/                    rapport LaTeX + PDF
```

## Compiler et lancer

```
make          # compile tout dans bin/   (Windows : mingw32-make)
make demo     # démonstrations ABR et tas
make bench    # benchmarks (quelques minutes)
```

Sans make :

```
g++ -O2 -std=c++17 src/BenchmarkTas.cpp -o BenchmarkTas
./BenchmarkTas          # tableau lisible
./BenchmarkTas csv      # format CSV
```

## Résultats principaux

| | Tas à la main | priority_queue |
|---|---|---|
| Insertion | plus rapide dans 9 cas sur 15 (7 à 24 %) | |
| Extraction de la racine | | plus rapide dans 14 cas sur 15 |
| Extraction, N = 10 millions, aléatoire | plus rapide | |

Mesures faites sur un Intel Core i7-8550U, 8 Go de RAM, Windows 11, g++ 15.2 (`-O2`).

ABR : avec des clés insérées dans l'ordre croissant, l'arbre devient une liste (hauteur = N) et devient 145 fois plus lent à N = 20 000.

Le rapport complet est dans `rapport/rapport_abr_tas.pdf`.
