#include <bits/stdc++.h>
using namespace std;

// Se da o matrice cu N linii si M coloane plina cu 0 si 1.
// Se cere sa se afle cate dreptunghiuri maximale exista.
// Un dreptunghi maximal este o submatrice a matricii date care este plina cu 0 si are proprietatea ca nu se mai poate extinde.
// O submatrice se poate extinde daca cel putin una din laturile ei are ca vecini doar casute cu 0.

ifstream fin("dreptunghiuri5.in");
ofstream fout("dreptunghiuri5.out");

int N, M;

int main()
{

    fin >> N >> M;

    vector<vector<int>> a(N + 1, vector<int>(M + 1, 1));

    // Citim elementele matricei
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            fin >> a[i][j];
        }
    }

    int nrDreptunghiuriMaximale = 0;

    // Pentru fiecare coloana, nrZeroDeasupra[i] o sa retina cate zerouri sunt deasupra liniei curente (inclusiv linia curenta)
    // inainte de a aparea un 1
    // Deci prin intermediu acestui vector putem sa ne dam seama cat de mult ne putem extinde cum submatricea pe verticala

    // Daca nrZeroDeasupra[i] = 5, atunci inseamna ca putem forma o submatrice cu inaltimea maxim 5 avand ca ultima linie i
    // si ca prima linie i-4
    vector<int> nrZeroDeasupra(M + 1, 0);

    // Parcurgem fiecare linie in parte
    for (int i = 0; i < N; i++)
    {

        // Calculam nrZerouriDeasupra pentru fiecare coloana in parte
        // Vectorul este initializat o singura data in afara loop-ului de parcurgere a liniilor deoarece
        // la fiecare linie se aduna 1 sau se revine la 0 (in functie de valoarea gasita in matrice)
        for (int j = 0; j < M; j++)
        {
            if (a[i][j] == 1)
            {
                // Daca apare un 1, resetam numarul de zerouri care se afla deasupra liniei curente
                nrZeroDeasupra[j] = 0;
            }
            else
            {
                // Altfel crestem numarul de zerouri
                nrZeroDeasupra[j]++;
            }
        }

        // O stiva in care vom retine, pentru linia curenta, toate coloanele pe care le vom procesa
        // pentru a vedea pana unde ne putem "extinde" cu submatricea curenta de zerouri pe orizontala

        // Informatia legata de cat de mult ne putem extinde pe verticala (avand ca linie de finish linia curenta) o avem
        // deja pentru fiecare coloana in parte in vectorul nrZeroDeasupra
        stack<int> st;

        // Indicele coloanei unde ne oprim
        int jOprire = -1;

        // Parcurgem fiecare coloana in parte, si mergem cu j pana la nr_coloane + 1 pentru a acoperi
        // si cazul special in care submatricea maximala de zerouri se intinde pe orizontala pana la ultima
        // coloana
        for (int j = 0; j <= M; j++)
        {

            // Scoatem din stiva toate coloanele deja existente pentru care exista un numar
            // de zerouri desupra mai mare decat numarul de zerouri de deasupra coloanei curente
            while (st.size() && nrZeroDeasupra[st.top()] > nrZeroDeasupra[j])
            {

                // Pentru fiecare element pe care il scoatem, verificam daca acesta contribuie la
                // formarea unei submatrice maximale

                st.pop();
                int lastok;
                if (st.size())
                {
                    lastok = st.top();
                }
                else
                {
                    lastok = -1;
                }

                // Daca lastok e mai mic jOprire incrementam numarul de submatrice maximale
                if (lastok < jOprire)
                {
                    nrDreptunghiuriMaximale++;
                }
            }

            // Scoatem din stiva toate coloanele deja existente pentru care exista un numar
            // de zerouri desupra egal cu numarul de zerouri de deasupra coloanei curente
            while (st.size() && nrZeroDeasupra[st.top()] == nrZeroDeasupra[j])
            {
                st.pop();
            }

            // Introducem in stiva coloana curenta

            st.push(j);

            if (a[i + 1][j] == 1)
            {

                // Daca dedesubt avem un i, jOprire va fi setat la j nu mai putem avansa deoarece (nu putem construi o submatrice mai mare)
                jOprire = j;
            }
        }
    }

    fout << nrDreptunghiuriMaximale;
}