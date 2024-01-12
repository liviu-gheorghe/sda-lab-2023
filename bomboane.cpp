#include <bits/stdc++.h>
using namespace std;

int main()
{

    ifstream fin("bomboane.in");
    ofstream fout("bomboane.out");

    int n, x, suma = 0;

    // Min heap pentru minime
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> minime;

    // Min heap pentru minime
    priority_queue<pair<int, int>, vector<pair<int, int>>, less<pair<int, int>>> maxime;

    // Citim datele din fisier si in acelasi timp calculam nr total de bomboane si introducem datele in heap-uri

    fin >> n;

    for (int i = 1; i <= n; i++)
    {
        fin >> x;
        suma += x;
        minime.push(make_pair(x, i));
        maxime.push(make_pair(x, i));
    }

    // Daca suma nu e divizibila cu n atunci nu e posibil sa impartim uniform bomboanele

    if (suma % n)
    {
        fout << -1;
        return 0;
    }

    // Nr mediu de bomboane, la final fiecare cutie va contine acest numar de bomboane
    int nr_mediu = suma / n;

    vector<vector<int>> mutari = vector<vector<int>>();

    while (!(maxime.empty()))
    {

        pair<int, int> maxim_curent = maxime.top();

        pair<int, int> minim_curent = minime.top();

        maxime.pop();
        minime.pop();

        // Efectuam operatia doar daca au mai ramas cutii cu nr de bomboane mai mare decat media, altfel ne oprim

        // cout << maxim_curent.first << " " << minim_curent.first << "\n";

        if (maxim_curent.first <= nr_mediu || minim_curent.first >= nr_mediu)
        {

            // cout << "BREAK";
            break;
        }

        // Calculam de cate bomboane mai are nevoie minimul curent

        int nr_bomboane_necesare_minim_curent = nr_mediu - minim_curent.first;

        // Calcuam si cate bomboane mai putem sa mai luam de la maxim, pentru ca nu putem / nu ar fi eficient sa scadem sub
        // nr_mediu_bomboane

        int nr_bomboane_valabile_din_maxim_curent = maxim_curent.first - nr_mediu;

        // Aici distingem 3 cazuri

        // 1. Exista mai multe bomboane decat e suficient, caz in care reintroducem in heap doar maximul cu nr
        // de bomboane actualizat

        if (nr_bomboane_valabile_din_maxim_curent > nr_bomboane_necesare_minim_curent)
        {
            mutari.push_back({maxim_curent.second, minim_curent.second, nr_bomboane_necesare_minim_curent});
            maxime.push(make_pair(nr_mediu + (nr_bomboane_valabile_din_maxim_curent - nr_bomboane_necesare_minim_curent), maxim_curent.second));
        }
        else if (nr_bomboane_valabile_din_maxim_curent == nr_bomboane_necesare_minim_curent)
        {
            // 2. Exista bomboane fix atat cat ar fi nevoie (maximul si minimul curent sunt egal departate de medie)
            // In acest caz nu mai reintroducem nimic in heap
            mutari.push_back({maxim_curent.second, minim_curent.second, nr_bomboane_necesare_minim_curent});
        }
        else
        {
            // 3. In maxim exista un numar de bomboane mai mic decat este necesar, prin urmare trebuie sa
            // reintroducem in heap minimul
            mutari.push_back({maxim_curent.second, minim_curent.second, nr_bomboane_valabile_din_maxim_curent});
            minime.push(make_pair(minim_curent.first + nr_bomboane_valabile_din_maxim_curent, minim_curent.second));
        }
    }

    fout << mutari.size() << "\n";

    for (int i = 0; i < mutari.size(); i++)
    {
        fout << mutari[i][0] << " " << mutari[i][1] << " " << mutari[i][2] << "\n";
    }

    fin.close();
    fout.close();

    return 0;
}