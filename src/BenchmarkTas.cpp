// Benchmark du tas max : version ecrite a la main (tableau, sans conteneur)
//                        contre std::priority_queue<int> (tas max par defaut)
// On compare l'INSERTION de N valeurs et l'EXTRACTION de la racine (la plus grande valeur).
//   ./bin/BenchmarkTas        (tableau lisible)
//   ./bin/BenchmarkTas csv    (format CSV)
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <queue>
#include <chrono>
#include <random>
#include <algorithm>
#include "TasMax.h"
using namespace std;
using namespace std::chrono;

double ns(steady_clock::time_point t0) { return duration<double, nano>(steady_clock::now() - t0).count(); }
volatile long long puits = 0;           // empeche le compilateur de supprimer les calculs

vector<int> donnees(int N, const string& ordre)
{
    vector<int> v(N);
    mt19937 g(12345);
    for (int& x : v) x = g() % 1000000000;
    if (ordre == "croissant")   sort(v.begin(), v.end());
    if (ordre == "decroissant") sort(v.rbegin(), v.rend());
    return v;
}

// Verifie que les deux tas extraient exactement les memes valeurs, dans l'ordre decroissant
bool verifier()
{
    vector<int> v = donnees(100000, "aleatoire");
    TasMax t;
    priority_queue<int> pq;
    for (int x : v) { t.inserer(x); pq.push(x); }
    int precedent = 2000000000;
    while (!pq.empty()) {
        int a = t.extraireRacine(), b = pq.top(); pq.pop();
        if (a != b || a > precedent) return false;
        precedent = a;
    }
    return t.vide();
}

struct Temps { double insMain, insPQ, extMain, extPQ; };

Temps mesurer(const vector<int>& v)
{
    int N = v.size();
    Temps r;
    {   // tas ecrit a la main
        TasMax t;
        auto t0 = steady_clock::now();
        for (int x : v) t.inserer(x);
        r.insMain = ns(t0) / N;
        long long s = 0;
        t0 = steady_clock::now();
        while (!t.vide()) s += t.extraireRacine();
        r.extMain = ns(t0) / N;
        puits = puits + s;
    }
    {   // priority_queue
        priority_queue<int> pq;
        auto t0 = steady_clock::now();
        for (int x : v) pq.push(x);
        r.insPQ = ns(t0) / N;
        long long s = 0;
        t0 = steady_clock::now();
        while (!pq.empty()) { s += pq.top(); pq.pop(); }
        r.extPQ = ns(t0) / N;
        puits = puits + s;
    }
    return r;
}

int main(int argc, char* argv[])
{
    bool csv = argc > 1 && string(argv[1]) == "csv";
    if (!verifier()) { cout << "ERREUR : les deux tas ne donnent pas le meme resultat\n"; return 1; }

    if (csv) cout << "ordre;N;ins_main_ns;ins_pq_ns;ext_main_ns;ext_pq_ns\n";
    else {
        cout << "TAS MAX : ECRIT A LA MAIN (tableau) vs priority_queue\n";
        cout << "Verification : les deux tas extraient les memes valeurs, dans l'ordre decroissant -> OK\n";
        cout << "(temps moyen par operation, en nanosecondes ; meilleur de 5 essais)\n\n";
        cout << left << setw(13) << "Donnees" << right << setw(10) << "N"
             << setw(12) << "Ins. main" << setw(12) << "Ins. PQ"
             << setw(12) << "Ext. main" << setw(12) << "Ext. PQ" << "\n";
        cout << string(71, '-') << "\n";
    }
    for (string ordre : {"aleatoire", "croissant", "decroissant"}) {
        for (int N : {1000, 10000, 100000, 1000000, 10000000}) {
            vector<int> v = donnees(N, ordre);
            int reps = N >= 10000000 ? 3 : 5;
            Temps best = mesurer(v);
            for (int r = 1; r < reps; r++) {
                Temps m = mesurer(v);
                best.insMain = min(best.insMain, m.insMain);
                best.insPQ   = min(best.insPQ, m.insPQ);
                best.extMain = min(best.extMain, m.extMain);
                best.extPQ   = min(best.extPQ, m.extPQ);
            }
            if (csv)
                cout << ordre << ";" << N << ";" << best.insMain << ";" << best.insPQ << ";"
                     << best.extMain << ";" << best.extPQ << "\n";
            else
                cout << left << setw(13) << ordre << right << setw(10) << N << fixed << setprecision(1)
                     << setw(12) << best.insMain << setw(12) << best.insPQ
                     << setw(12) << best.extMain << setw(12) << best.extPQ << "\n";
            cout.flush();
        }
    }
    if (!csv) cout << "\nIns. = insertion ; Ext. = extraction de la racine ; main = tas ecrit a la main ; PQ = priority_queue\n";
    return 0;
}
