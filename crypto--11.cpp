#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

// Function to get the next prime number
mpz_t getNextPrime(char *ans) {
    mpz_t test;
    mpz_init_set_str(test, ans, 10);
    while (!mpz_probable_prime_p(test, 99)) {
        mpz_add_ui(test, test, 1);
    }
    return test;
}

// Function to find Q
mpz_t findQ(mpz_t n) {
    mpz_t start;
    mpz_init_set_ui(start, 2);
    while (!mpz_probable_prime_p(n, 99)) {
        while (mpz_mod_ui(n, n, start)!= 0) {
            mpz_add_ui(start, start, 1);
        }
        mpz_divexact(n, n, start);
    }
    return n;
}

// Function to get generator G
mpz_t getGen(mpz_t p, mpz_t q, gmp_randstate_t r) {
    mpz_t h;
    mpz_init(h);
    mpz_urandomb(h, r, mpz_sizeinbase(p, 2));
    mpz_mod(h, h, p);
    mpz_powm(h, h, mpz_sub_ui(p, 1), p);
    mpz_divexact(h, h, q);
    return h;
}

int main() {
    gmp_randstate_t randObj;
    gmp_randinit_default(randObj);
    mpz_t p, q, g, x, y, k, r, hashVal, kInv, s, w, u1, u2, v;

    // Initialize variables
    mpz_init(p);
    mpz_init(q);
    mpz_init(g);
    mpz_init(x);
    mpz_init(y);
    mpz_init(k);
    mpz_init(r);
    mpz_init(hashVal);
    mpz_init(kInv);
    mpz_init(s);
    mpz_init(w);
    mpz_init(u1);
    mpz_init(u2);
    mpz_init(v);

    // Get prime number p
    mpz_set_str(p, "10600", 10);
    p = getNextPrime(mpz_get_str(NULL, 10, p));

    // Get q
    mpz_sub_ui(q, p, 1);
    q = findQ(q);

    // Get generator g
    g = getGen(p, q, randObj);

    printf("\nSimulation of Digital Signature Algorithm\n");
    printf("\nGlobal public key components are:\n");
    printf("\np is: ");
    mpz_out_str(stdout, 10, p);
    printf("\n");
    printf("\nq is: ");
    mpz_out_str(stdout, 10, q);
    printf("\n");
    printf("\ng is: ");
    mpz_out_str(stdout, 10, g);
    printf("\n");

    // Get secret information
    mpz_urandomb(x, randObj, mpz_sizeinbase(q, 2));
    mpz_mod(x, x, q);
    mpz_powm(y, g, x, p);
    mpz_urandomb(k, randObj, mpz_sizeinbase(q, 2));
    mpz_mod(k, k, q);
    mpz_powm(r, g, k, p);
    mpz_mod(r, r, q);
    mpz_urandomb(hashVal, randObj, mpz_sizeinbase(p, 2));
    mpz_invert(kInv, k, q);
    mpz_mul(s, kInv, hashVal);
    mpz_addmul(s, kInv, x, r);
    mpz_mod(s, s, q);

    printf("\nSecret information are:\n");
    printf("x (private) is: ");
    mpz_out_str(stdout, 10, x);
    printf("\n");
    printf("k (secret) is: ");
    mpz_out_str(stdout, 10, k);
    printf("\n");
    printf("y (public) is: ");
    mpz_out_str(stdout, 10, y);
    printf("\n");
    printf("h (rndhash) is: ");
    mpz_out_str(stdout, 10, hashVal);
    printf("\n");

    printf("\nGenerating digital signature:\n");
    printf("r is: ");
    mpz_out_str(stdout, 10, r);
    printf("\n");
    printf("s is: ");
    mpz_out_str(stdout, 10, s);
    printf("\n");

    // Verify digital signature
    mpz_invert(w, s, q);
    mpz_mul(u1, hashVal, w);
    mpz_mod(u1, u1, q);
    mpz_mul(u2, r, w);
    mpz_mod(u2, u2, q);
    mpz_powm(v, g, u1, p);
    mpz_mul(v, v, y);
    mpz_powm(v, v, u2, p);
    mpz_mod(v, v, q);

    if