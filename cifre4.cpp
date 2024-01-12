#include <bits/stdc++.h>
using namespace std;

ifstream fin("cifre4.in");
ofstream fout("cifre4.out");

int cifre[] = {2, 3, 5, 7};

long long solve(int n, int p)
{

    // Vector de frecventa de lungime P-1 ce retine daca restul r a fost gasit
    // pana in momentul de fata

    vector<bool> frecv(5000000, false);

    // Coada in care se introduc numere de "candideaza" pt rezultat

    queue<long long> q;

    // Initial in coada vom introduce 0

    q.push(0);
    while (!q.empty())
    {
        long long x = q.front();
        q.pop();

        // Daca acelasi rest a mai fost obtinut anterior nu mai are sens
        // sa continuam pentru ca avem deja un numar mai mic care a obtinut acelasi rest

        // Daca acesta ar fi fost N, atunci am fi iesit deja din functie
        if (!frecv[x % p])
        {

            // Marcam acest rest ca fiind obtinut
            frecv[x % p] = true;

            // Daca am obtinut restul n returnam rezultatul
            if (x % p == n)
            {
                return x;
            }

            // Construim noii candidati pe care ii adaugam in coada, adugand la candidatul curent
            // ca si sufix fiecare dintre cifrele eligibile, in ordine crescatoare

            for (int i = 0; i < 4; i++)
            {
                q.push(x * 10 + cifre[i]);
            }
        }
    }
    return -1;
}

int main()
{
    int T, N, P;
    fin >> T;
    for (int i = 0; i < T; i++)
    {
        fin >> N >> P;
        fout << solve(N, P) << "\n";
    }
    return 0;
}