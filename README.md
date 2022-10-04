# SecretSharing

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
