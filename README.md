# SecretSharing

Distribuzione di una parte del segreto a n persone, ne saranno necessarie k per ricostruirlo
Basato suaritmetica modulare
* S : segreto
* n : num partecipanti
* k : partecipanti necessari a ricostruire il segreto
* p : modulo, p>S
### Schema (n,n):
Sono necessari tutti i partecipanti per ricostruire il segreto
- scegli n-1 valori 0<a[i]<p
- l'ultimo valore è il segreto meno la somma di tutti gli altri
    - a[n-1] = (S - a[0] - ... - a[n-2]) mod p
- a ogni partecipante viene fornito a[i] e p
- Per ricostruire il segreto somma tutti i valori di a mod p
    - S = (a[0] + a[1] + ... + a[n-1]) mod p
### Schema (k,n):
Sono necessari k partecipanti per ricostruire il segreto
- scegli k-1 valori 0<a[i]<p
- per ogni utente i-esimo calcola il suo valore
    - y[i] = a[0]*i^0 + a[1]*i^1 + ... + a[k-2]*i^(k-1)
- a ogni partecipante viene fornito il valore "y[i]" e l'ID utente "i"
- Per ricostruire il segreto è necessario risolvere un sistema lineare di k equazioni in cui S e a[] sono le incognite
    - y[i] = S + a[0]*i^0 + a[1]*i^1 + ... + a[k-2]*i^(k-1)

______________________________________________________________________________________________________________________

Distribution of a slice of the secret to n people, k people will be necessary to recreate the secret
Based on modular arithmetic
* S : secret
* n : num participants
* k : participants needed to recreate the secret
* p : modulus, p>S

### (n,n) schema:
All participants needed to recreate the secret
- choose n-1 values 0<a[i]<p
- last value is the secret value minus the sum of the others
	- a[n-1] = (S - a[0] - ... - a[n-2]) mod p
- every i-th participant gets a[i] and p
- To recreate the secret you need to sum every a value mod p
	- S = (a[0] + a[1] + ... + a[n-1]) mod p

### (k,n) schema:
k participants needed to recreate the secret
- choose k-1 values 0<a[i]<p
- for each i-th participant calculate his value
	- y[i] = a[0]*i^0 + a[1]*i^1 + ... + a[k-2]*i^(k-1)
- every i-th participant gets y[i], his "ID"(i) and p
- To recreate the secret you need to solve a linear system of k equations in which S and a[] are the unknown quantity
	- y[i] = S + a[0]*i^0 + a[1]*i^1 + ... + a[k-2]*i^(k-1)
