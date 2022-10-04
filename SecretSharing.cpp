/*

 Secret Sharing:
Distribuzione di una parte del segreto a n persone, ne saranno necessarie k per ricostruirlo
Basato suaritmetica modulare
S : segreto
n : num partecipanti
k : partecipanti necessari a ricostruire il segreto
p : modulo, p>S

 Schema (n,n):
Sono necessari tutti i partecipanti per ricostruire il segreto
- scegli n-1 valori 0<a[i]<p
- l'ultimo valore è il segreto meno la somma di tutti gli altri
    a[n-1] = (S - a[0] - ... - a[n-2]) mod p
- a ogni partecipante viene fornito a[i] e p
Per ricostruire il segreto somma tutti i valori di a mod p
    S = (a[0] + a[1] + ... + a[n-1]) mod p

 Schema (k,n):
Sono necessari k partecipanti per ricostruire il segreto
- scegli k-1 valori 0<a[i]<p
- per ogni utente i-esimo calcola il suo valore
    y[i] = a[0]*i^0 + a[1]*i^1 + ... + a[k-2]*i^(k-1)
- a ogni partecipante viene fornito il valore "y[i]" e l'ID utente "i"
Per ricostruire il segreto è necessario risolvere un sistema lineare di k equazioni
    y[i] = S + a[0]*i^0 + a[1]*i^1 + ... + a[k-2]*i^(k-1)
in cui S e a[] sono le incognite

*/

#include <iostream>
#include <stdio.h>
#include <time.h>
#include <cmath>
#define MAX_DIM 100
using namespace std;

bool primo(int n);
int gauss(double coef_mat[][MAX_DIM], double term_noti[], double sol[], int dim);
int pivot(int dim, int j, double matr[][MAX_DIM], double tn[]);
int mcd(int a, int b);
int modFrazioni(int x, int y, int m);

int main()
{
    srand(time(NULL));

    int S, p, n, k;
    int continua;
    do
    {
        system("cls");
        cout << "1. Distribuzione segreto\n";
        cout << "2. Ricostruzione segreto(n,n)\n";
        cout << "3. Ricostruzione segreto(k,n)\n";
        cout << "4. Informazioni\n";
        cout << "0. Esci\n\n";
        cin >> continua;
        system("cls");

        if (continua == 1)
        {
            do
            {
                cout << "Inserire il numero di partecipanti (n>1): ";
                cin >> n;
            } while (n <= 1);

            do
            {
                cout << "Inserire il numero di partecipanti richiesti per ricreare il segreto (0<k<=n): ";
                cin >> k;
            } while (k < 1 || k > n);

            cout << "Inserire il segreto: ";
            cin >> S;

            do
            {
                cout << "Inserire il modulo (p>S o 0 per generalo casualmente): ";
                cin >> p;
            } while (p < S && p != 0);
            if (!p)
            {
                do
                {
                    p = rand();
                } while (!primo(p) || p < S);
                cout << "Valore del modulo: " << p << endl;
            }

            if (k == n)
            {
                int a[n];
                a[n - 1] = 0;
                for (int i = 0; i < n - 1; i++)
                {
                    a[i] = rand() % p;
                    a[n - 1] += a[i];
                }
                a[n - 1] -= S;
                a[n - 1] = a[n - 1] < 0 ? a[n - 1] * -1 : p - (a[n - 1] % p);

                cout << "Valori parziali: ";
                for (int i = 0; i < n; i++)
                    cout << a[i] << " ";
                cout << endl;
            }
            else
            {
                int a[k - 1];
                for (int i = 0; i < k - 1; i++)
                    a[i] = rand() % p;

                int b;
                cout << "Valori parziali:\n";
                for (int i = 0; i < n; i++)
                {
                    b = S;
                    for (int j = 0; j < k - 1; j++)
                        b += pow(i + 1, j + 1) * a[j];
                    b %= p;
                    cout << " ID partecipante " << i + 1 << ", valore: " << b << endl;
                }
            }
        }
        else if (continua == 2)
        {
            cout << "Inserire il numero di partecipanti: ";
            cin >> n;
            cout << "Inserire il valore del modulo: ";
            cin >> p;
            cout << "Inserire i valori: ";
            S = 0;
            int temp;
            for (int i = 0; i < n; i++)
            {
                cin >> temp;
                S += temp;
            }
            S %= p;
            cout << "Segreto: " << S << endl;
        }
        else if (continua == 3)
        {
            cout << "Inserire il numero di partecipanti: ";
            cin >> k;
            cout << "Inserire il valore del modulo: ";
            cin >> p;

            int pos[k];
            double B[k];
            for (int i = 0; i < k; i++)
            {
                cout << "Inserire ID partecipante: ";
                cin >> pos[i];
                cout << "Inserire valore partecipante " << pos[i] << ": ";
                cin >> B[i];
            }
            double A[k][MAX_DIM];
            for (int i = 0; i < k; i++)
                for (int j = 0; j < k; j++)
                    A[i][j] = pow(pos[i], j);
            double S[k];
            if (gauss(A, B, S, k) == 0)
            {
                int x, y = 1;
                while (S[0] - (int)S[0] != 0)
                {
                    S[0] *= 10;
                    y *= 10;
                }
                x = S[0];
                x = modFrazioni(x, y, p);
                cout << "Soluzione: " << x << endl;
            }
            else
                cout << "Errore nel calcolo\n";
        }
        else if (continua == 4)
        {
            cout << " Secret Sharing:\n";
            cout << "Distribuzione di una parte del segreto a n persone, ne saranno necessarie k per ricostruirlo\n";
            cout << "Basato sull'aritmetica modulare\n";
            cout << "S : segreto\n";
            cout << "n : num partecipanti\n";
            cout << "k : partecipanti necessari a ricostruire il segreto\n";
            cout << "p : modulo, p>S\n";
            cout << endl;
            cout << "Schema (n,n):\n";
            cout << "Sono necessari tutti i partecipanti per ricostruire il segreto\n";
            cout << "- scegli n-1 valori 0<a[i]<p\n";
            cout << "- ultimo valore = il segreto meno la somma di tutti gli altri\n";
            cout << "a[n-1] = (S - a[0] - ... - a[n-2]) mod p\n";
            cout << "- a ogni partecipante viene fornito a[i] e p\n";
            cout << "Per ricostruire il segreto somma tutti i valori di a mod p\n";
            cout << "S = (a[0] + a[1] + ... + a[n-1]) mod p\n";
            cout << endl;
            cout << "Schema (k,n):\n";
            cout << "Sono necessari k partecipanti per ricostruire il segreto\n";
            cout << "- scegli k-1 valori 0<a[i]<p\n";
            cout << "- per ogni utente i-esimo calcola il suo valore\n";
            cout << "y[i] = a[0]*i^0 + a[1]*i^1 + ... + a[k-2]*i^(k-1)\n";
            cout << "- a ogni partecipante viene fornito il valore 'y[i]' e l'ID utente 'i'\n";
            cout << "Per ricostruire il segreto risolveri un sistema lineare di k equazioni\n";
            cout << "y[i] = S + a[0]*i^0 + a[1]*i^1 + ... + a[k-2]*i^(k-1)\n";
            cout << "in cui S e a[] sono le incognite\n";
        }
        if (continua)
            system("pause");

    } while (continua);
}

bool primo(int n)
{
    if (n == 1 || n == 0)
        return false;
    for (int i = 2; i < n / 2; i++)
        if (n % i == 0)
            return false;
    return true;
}

int gauss(double coef_mat[][MAX_DIM], double term_noti[], double sol[], int dim)
{
    int i, j, k, // indici di scansione della matrice
        check = 0;
    double piv, alfa, temp;
    for (j = 0; j < dim - 1; j++)
    {
        // scegli pivot;
        check = pivot(dim, j, coef_mat, term_noti);
        if (check == 0)
            piv = coef_mat[j][j];
        else
            return (-1);
        // combinazione lineare
        for (i = j + 1; i < dim; i++)
        {
            // calcolo del coefficente della combinazione lineare
            alfa = coef_mat[i][j] / piv;
            // sottrazione
            for (k = j; k < dim; k++)
                coef_mat[i][k] = coef_mat[i][k] - alfa * coef_mat[j][k];
            // termini noti
            term_noti[i] = term_noti[i] - alfa * term_noti[j];
        } // for su righe i da j+1 a n
    }     // for sui primi n-1 elemnti della diagonale a[j][j]
    // Check su determinante
    if (coef_mat[dim - 1][dim - 1] == 0)
    {
        // cout << "Righe linearmente dipendenti. Soluzioni infinite\n\n";
        return (1);
    }
    // Trovo ora la soluzione
    sol[dim] = term_noti[dim] / coef_mat[dim][dim];
    for (i = dim - 1; i >= 0; i--)
    {
        temp = term_noti[i];
        for (k = i + 1; k < dim; k++)
            temp = temp - coef_mat[i][k] * sol[k];
        sol[i] = temp / coef_mat[i][i];
    } // for sulle righe n-1,n-2, ..., 1
    return (0);
}

// Funzione di pivoting parziale;
// cerca il pivot per la colonna j-esima
// e se diverso da a[j][j] esegue lo scambio
int pivot(int dim, int j, double matr[][MAX_DIM], double tn[])
{
    int k, r;
    double temp;
    char cont;
    // for( k=j; matr[k,j]==0 & k<=dim; k++);
    // system("cls");
    // cout << " Pivoting: passo (" << j << ")\n";
    // stampa(matr, tn, dim);
    // system("PAUSE");
    // cerco il primo elemento non nullo
    k = j;
    while (k < dim && matr[k][j] == 0)
        ++k;
    /*if (k < dim) // esiste k tc matr[k,j]==0
        cout << "matr[j][j] non nullo per j=" << k + 1 << "\n";
    else
    {
        cout << "Pivot NULLO !!\n\n";
        return (-1);
    }*/
    if (k >= dim)
        return -1;
    if (k != j)
    {
        // cout << "Scambio Riga " << j << " con " << k << "\n";
        // scambio righe
        for (r = j; r < dim; r++)
        {
            temp = matr[j][r];
            matr[j][r] = matr[k][r];
            matr[k][r] = temp;
        }
        temp = tn[j];
        tn[j] = tn[k];
        tn[k] = temp;
    }
    return (0);
}

int mcd(int x, int y)
{
    while (y > 0)
    {
        int r = x % y;
        x = y;
        y = r;
    }
    return x;
}

/*
    Basata sul concetto che
    x mod m = (x + zm) mod m
    con z intero (in particolare z = -1)
    quindi ottengo una frazione e il suo inverso
    x/y e (x-m)/(y-m)
    e controllo se possibile semplificare un numeratore con un denominatore
    se possibile mantengo quella frazione e ripeto il ciclo
*/
int modFrazioni(int x, int y, int m)
{
    if (x == 0) // numeratore a 0
        return 0;
    if (y == 0) // divisione per 0
        return -1;
    if (y == m - 1) // se m - y == 1 -> y = -1, inverto segno numeratore e denominatore si annulla
    {
        x *= -1;
        y = 1;
    }

    x = (x + m) % m;
    y = (y + m) % m;
    int X[2], Y[2];
    int res;
    int i, j;

    while (y != 1) // finché non si annulla il denominatore
    {
        // frazione 1
        X[0] = x;
        Y[0] = y;
        // frazione 2
        X[1] = x > 0 ? x - m : x + m;
        Y[1] = y > 0 ? y - m : y + m;

        // cout << X[0] << " " << X[1] << endl;
        // cout << Y[0] << " " << Y[1] << endl;

        i = 0, j = 0;
        do
        {
            res = mcd(abs(X[i]), abs(Y[j]));
            if (res == 1) // se non possibile semplificare la coppia scelta
            {
                if (++i == 2)
                {
                    i = 0;
                    j++;
                }
                if (j == 2) // non è più possibile semplificare
                    return -1;
            }
        } while (j < 2 && res == 1);
        // cout << "res: " << res << endl;

        // semplifico
        x = X[i] / res;
        y = Y[j] / res;

        // se entrambi negativi, annullo il meno
        if (x < 0 && y < 0)
        {
            x *= -1;
            y *= -1;
        }
        // cout << "Nuova frazione: " << x << "/" << y << endl;
    }

    return x < 0 ? x + m : x;
}