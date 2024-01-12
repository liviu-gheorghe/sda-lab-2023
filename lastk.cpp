#include <bits/stdc++.h>
using namespace std;

int main()
{

    // Se foloseste un min heap pentru a stoca numerele din sirul generat
    priority_queue<long long, vector<long long>, greater<long long>> pq;

    long long n, k, A, B, C, D, prev;

    cin >> n >> k >> A >> B >> C >> D;

    for (int i = 1; i <= n; i++)
    {

        long long x;

        // Se genereaza elementul curent din sir
        if (i == 1)
        {
            x = A;
        }
        else
        {
            x = (B * prev + C) % D;
        }

        // Introducem in min heap primele k elemente
        if (i <= k)
        {
            pq.push(x);
        }
        else
        {

            // Altfel, le introducem doar daca sunt mai mari decat minimul din heap (caz in care in scoatem
            // si il inlocuim cu numarul adaugat)

            long long minHeapVal = pq.top();

            if (minHeapVal < x)
            {
                pq.pop();
                pq.push(x);
            }
        }

        prev = x;
    }

    // Afisam cele mai mari k elemente in ordine crescatoare
    for (int i = 1; i <= k; i++)
    {
        if (!pq.empty())
        {
            cout << pq.top() << " ";
            pq.pop();
        }
    }
}