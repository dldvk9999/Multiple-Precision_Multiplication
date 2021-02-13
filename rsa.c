#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
//#include <gmp.h>
#include <assert.h>
#include <unistd.h>
#define  MAX 1024
/*
typedef long long unsigned int number;

void rsa_keys(mpz_t n, mpz_t d, const mpz_t p, const mpz_t q, const mpz_t e) {
    mpz_mul(n, p, q);

    mpz_t p_1, q_1, lambda, gcd, mul, mod;
    mpz_inits(p_1, q_1, lambda, gcd, mul, mod, NULL);
    mpz_sub_ui(p_1, p, 1);
    mpz_sub_ui(q_1, q, 1);
    mpz_lcm(lambda, p_1, q_1);

    printf("lambda = %s\n", mpz_get_str(NULL, 0, lambda));
    // e must be bigger than 1
    assert(mpz_cmp_ui(e, 1) > 0);

    // e must be smaller than lambda
    assert(mpz_cmp(lambda, e) > 0);

    // GCD(e, lambda) must be 1
    mpz_gcd(gcd, e, lambda);
    assert(mpz_cmp_ui(gcd, 1) == 0);

    mpz_invert(d, e, lambda);

    // e * d MOD lambda must be 1
    mpz_mul(mul, e, d);
    mpz_mod(mod, mul, lambda);
    assert(mpz_cmp_ui(mod, 1) == 0);

    mpz_clears(gcd, p_1, q_1, mul, mod, lambda, NULL);
}

// RSA encryption
void encrypt(mpz_t encrypted, const mpz_t message, const mpz_t e,  const mpz_t n) {
    mpz_powm(encrypted, message, e, n);
}

// RSA decryption
void decrypt(mpz_t original, const mpz_t encrypted, const mpz_t d, const mpz_t n) {
    mpz_powm(original, encrypted, d, n);
}

void display_gmp(const mpz_t message, const mpz_t n, const mpz_t e, const mpz_t d) {
    mpz_t encrypted, decrypted;
    mpz_inits(encrypted, decrypted, NULL);
    encrypt(encrypted, message, e, n);
    decrypt(decrypted, encrypted, d, n);

    // The decrypted message must be equal to the original
    assert(mpz_cmp(message, decrypted) == 0);

    printf("Public key = (e: %s, n: %s)\n", mpz_get_str(NULL, 0, e), mpz_get_str(NULL, 0, n));
    printf("Private key = (d: %s, n: %s)\n", mpz_get_str(NULL, 0, d), mpz_get_str(NULL, 0, n));
    printf("Original message: %s\n", mpz_get_str(NULL, 0, message));
    printf("Encrypted message: %s\n", mpz_get_str(NULL, 0, encrypted));
    printf("Decrypted message: %s\n", mpz_get_str(NULL, 0, decrypted));
    printf("\n");

    mpz_clears(encrypted, decrypted, NULL);
}

void display_num(const number msg, const number pi, const number qi, const number ei) {
    printf("Initializing with p = %llu, q = %llu, e = %llu\n", pi, qi, ei);
    mpz_t n, d, p, q, e, original;
    mpz_init_set_ui(p, pi);
    mpz_init_set_ui(q, qi);
    mpz_init_set_ui(e, ei);
    mpz_init_set_ui(original, msg);
    mpz_inits(n, d, NULL);
    rsa_keys(n, d, p, q, e);

    display_gmp(original, n, e, d);

    mpz_clears(n, d, e, p, q, original, NULL);
}

void display_str(const char *msg, const char *pi, const char *qi, const char *ei) {
    printf("Initializing with p = %s, q = %s, e = %s\n", pi, qi, ei);

    mpz_t n, d, p, q, e, original;
    mpz_init_set_str(p, pi, 10);
    mpz_init_set_str(q, qi, 10);
    mpz_init_set_str(e, ei, 10);
    mpz_init_set_str(original, msg, 10);
    mpz_inits(n, d, NULL);
    rsa_keys(n, d, p, q, e);

    display_gmp(original, n, e, d);
    mpz_clears(n, d, e, p, q, original, NULL);
}
*/

int atoi_c(char c) {
    int value = 0;
    if (c == '\0') return 0;
    if (c >= '0' && c <= '9')  value = value * 10 + c - '0';
    return value;
}

int SizeArr(int *arr) { 
	char *array = malloc(sizeof(char) * MAX);
	for (int i = 0; i < MAX; i++) array[i] = (char)arr[i];
	int result = strlen(array);
	free(array);
	return result;
}

int* MPM(int *a, int *b, int lx, int ly) {
	int c = 0, res = 0;
	int *x = malloc(sizeof(int) * MAX);
	int *y = malloc(sizeof(int) * MAX);
	//printf("a : ");
	//for (int i = 0; i < lx; i++) printf("%d", a[i]); printf("\n");
	//printf("b : ");
	//for (int i = 0; i < ly; i++) printf("%d", b[i]); printf("\n");
	
	if (lx >= ly) {
		for (int i = 0; i < lx; i++) x[i] = a[i];
		for (int i = 0; i < ly; i++) y[i] = b[i];
	}
	else {
		for (int i = 0; i < ly; i++) x[i] = b[i];
		for (int i = 0; i < lx; i++) y[i] = a[i];
		int tmp = lx;
		lx = ly;
		ly = tmp;
	}
	
	//printf("x : ");
	//for (int i = 0; i < lx; i++) printf("%d", x[i]); printf("\n");
	//printf("y : ");
	//for (int i = 0; i < ly; i++) printf("%d", y[i]); printf("\n");
	
	int *result = malloc(sizeof(int) * MAX);
	for (int i = 0; i < lx + ly + 1; i++) result[i] = 0;
	for (int i = ly; i >= 0; i--) {
		c = 0;
		for (int j = lx; j >= 0; j--) {
			res = result[i+j] + x[j]*y[i] + c;
			result[i+j] = res % 10;
			c = res / 10;
			//printf("%d %d\n", c, result[i+j]);
		}
		if (i == 0 && (res / 10) >= 1) {
			for (int k = MAX; k > 0; k--) result[k] = result[k-1];
			result[i] = c;
			ly++;
		}
		else result[i-1] = c;
	}
	//for (int i = 0; i < lx + ly - 1; i++) printf("%d", result[i]);
	//printf("\n");
	free(result);
	return result;
}

int* MINUS(int *a, int *b, int alen, int blen) {		// a - b
	int c = 0;
	int count = 0;
	int la = alen-1;
	int lb = blen-1;
	int *result = malloc(sizeof(int) * MAX);
	
	//for (int i = 0; i < la+1; i++) printf("%d", a[i]); printf(" - ");
	//for (int i = 0; i < lb+1; i++) printf("%d", b[i]); printf(" = ");
	
	for (int i = 0; i < la; i++) result[i] = a[i];
	for (int i = la > lb ? la-1 : la; i >= 0; i--) {
		//printf("(%d,%d) ", a[la], b[i]);
		if (a[la] > b[i]) result[la] = a[la] - b[i];
		else if (a[la] == b[i]) { result[la] = a[la] - b[i]; count++; }
		else {
			a[la-1]--;
			result[la] = 10 - b[i] + a[la];
		}
		if (result[0] == 0)
			for (int j = 0; j < MAX; j++)
				if (result[j] != 0) {
					for (int k = 0; k < MAX; k++)
						result[k] = result[k+j];
					count = count - j;
					break;
				}
		//for (int j = 0; j < SizeArr(result) + count; j++)
		//	printf("%d", result[j]); printf("\n");
		la--;
	}
	return result;
}

int* SAM(int *x, int H, int *n, int len) {
	int *result  = malloc(sizeof(int) * MAX);
	int *z		 = malloc(sizeof(int) * MAX);
	int *bin	 = malloc(sizeof(int) * MAX);
	char *tmp	 = malloc(sizeof(char) * MAX);
	int i = 0;
	int flag = 0;
	
	/* Converts H in Binary */
	int m = 0;
	while(1) {
		bin[m] = H % 2;
		H = H / 2;
		m++; i++;
		if (H == 0) break;
	}
	z[0] = 1;
	//printf("binary : ");
	//for (int j = 0; j < i; j++) printf("%d", bin[j]); 
	//printf("\t\n\ti : %d\n\tz : ", i);
	//for (int j = 0; j < SizeArr(z); j++) printf("%d", z[j]); 
	//printf("\n\tx : ");
	//for (int j = 0; j < SizeArr(x); j++) printf("%d", x[j]); 
	//printf("\n\tn : ");
	//for (int j = 0; j < len; j++) printf("%d", n[j]); 
	//printf(", SizeArr(n) : %d\n", len);
	
	while(i >= 0) {
		flag = 0;
		z = MPM(z, z, SizeArr(z), SizeArr(z));		// Square
		//printf("Square : ");
		//for (int j = 0; j < SizeArr(z); j++)
		//	printf("%d", z[j]); printf("\n");
		
		while(1) {
			if (SizeArr(z) < len) break;
			else if (SizeArr(z) == len) {
				for (int j = 0; j < len; j++)
					if (z[j] < n[j]) { flag = 1; break; }
			}
			else {
				z = MINUS(z, n, SizeArr(z), len);
			}
			if (flag) break;
		}
		flag = 0;
		//printf("Square_Modular : ");
		//for (int j = 0; j < SizeArr(z); j++)
		//	printf("%d", z[j]); printf("\n");
		
		if(bin[--i] == 1) {
			z = MPM(z, x, SizeArr(z), SizeArr(x));	// and Multiply
			//printf("Multiply : ");
			//for (int j = 0; j < SizeArr(z); j++) 
			//	printf("%d", z[j]); printf(", SizeArr(z) : %d, SizeArr(n) : %d\n", SizeArr(z), SizeArr(n));
			
			while(1) {
				if (SizeArr(z) < len) break;
				else if (SizeArr(z) == len) {
					for (int j = 0; j < len; j++) {
						if (z[j] >= n[j]) {
							z = MINUS(z, n, SizeArr(z), len);
						}
						else if (z[j] < n[j]) {
							flag = 1; break; 
						}
					}
				}
				else z = MINUS(z, n, SizeArr(z), len);
				//for (int j = 0; j < SizeArr(z); j++) 
				//	printf("%d", z[j]); printf("\n");
				if (flag) break;
			}
		}
		
	}
	
	
	return z;
}

int* Prime_1(int* arr, int len) {
	--arr[len - 1];
	return arr;
}

int main(void) {
	/*
    mpz_t msg, n, d, e;
	
    // Example taken from Wikipedia
    // https://en.wikipedia.org/wiki/RSA_(cryptosystem)#Key_generation
    display_num(65, 61, 53, 17);
	
    // Example from Twitter
    // https://twitter.com/kosamari/status/838738015010848769
    mpz_init_set_ui(msg, 123);
    mpz_init_set_ui(n, 323);
    mpz_init_set_ui(e, 5);
    mpz_init_set_ui(d, 29);
    display_gmp(msg, n, e, d);
	
    // Very small prime numbers
    display_num(123, 13, 19, 17);
	
    // With some prime numbers from
    // http://www.bigprimes.net/
    display_num(67890, 541, 461, 107);
    display_num(123456, 1181, 929, 173);
	
    // The PHP version takes around 10 seconds on a MacBook Air
    display_num(123456, 1181, 929, 1987);
	
    // The PHP takes around 40 seconds in a MacBook Air
    display_num(123456, 1181, 929, 17);
	
    // Very big numbers; using Mersenne primes,
    // something impossible in the PHP version
    display_str("1111119999999999911111111",
                "162259276829213363391578010288127",
                "618970019642690137449562111",
                "170141183460469231731687303715884105727");
    mpz_clears(n, d, e, msg, NULL);
	*/
	
	/*   use gmp.h multi
	mpz_t x, y, result; 
  	
   	mpz_init_set_str(x, "76120582547389457612058254738945761205825473894576120582547389457612058254738945761205825473894576120582547389457612058254738945", 10); 
   	mpz_init_set_str(y, "92635911284390819263591128439081926359112843908192635911284390819263591128439081926359112843908192635911284390819263591128439081", 10); 
   	mpz_init(result); 
  	
   	mpz_mul(result, x, y); 
   	gmp_printf("    %Zd\n"
   	           "*\n"
   	           "    %Zd\n"
   	           "--------------------\n"
   	           "%Zd\n", x, y, result); 
  	
   	mpz_clear(x); 
   	mpz_clear(y); 
   	mpz_clear(result); 
	*/
	
	
	/* Multiple-precision Miltiplication */
	int  *result 	= malloc(sizeof(int)  * MAX);
	int  *result_1 	= malloc(sizeof(int)  * MAX);
	int  *Encrypt 	= malloc(sizeof(int)  * MAX);
	int  *Decrypt 	= malloc(sizeof(int)  * MAX);
	int  *arrp   	= malloc(sizeof(int)  * MAX);
	int  *arrq   	= malloc(sizeof(int)  * MAX);
	int  *arrmsg   	= malloc(sizeof(int)  * MAX);
	char *arr1   	= malloc(sizeof(char) * MAX);
	char *arr2   	= malloc(sizeof(char) * MAX);
	char *arr5  	= malloc(sizeof(char) * MAX);
	int d = 0;
	int e = 0;
	
	/* Initializing */
	printf("Enter the message as an integer. : ");
	scanf("%s", arr5);
	for (int i = 0; i < strlen(arr5); i++)
		arrmsg[i] = atoi_c(arr5[i]);
	
	/* insert p */
	printf("Enter the Prime number p : ");
	scanf("%s", arr1);
	for (int i = 0; i < strlen(arr1); i++)
		arrp[i] = atoi_c(arr1[i]);
	
	/* insert q */
	printf("Enter the Prime number q : ");
	scanf("%s", arr2);
	for (int i = 0; i < strlen(arr2); i++)
		arrq[i] = atoi_c(arr2[i]);
	
	/* generate e */
	printf("Enter the e : ");
	scanf("%d", &e);
	
	/* generate d */
	printf("Enter the d : ");
	scanf("%d", &d);
	
	/*** RSA ***/
	
	/* length check */
	int len = 0;
	if (strlen(arr1) >= 32 && strlen(arr2) >= 32) len = strlen(arr1) + strlen(arr2) - 1;
	else if (atoi_c(arr1[0]) * atoi_c(arr2[0]) >= 10) len = strlen(arr1) + strlen(arr2);
	else len = strlen(arr1) + strlen(arr2) - 1;
	if (strlen(arr1) >= 32 || strlen(arr2) >= 32) len++;
	
	
	/* print */
	printf("\n\n*****************RSA Algorithm****************\n");
	printf("Your Prime Number : \n  <p>\t%s\n  <q>\t%s\n", arr1, arr2);
	
	result = MPM(arrp, arrq, strlen(arr1), strlen(arr2));
	printf("Calculate N : \n\t");
	for (int i = 0; i < len; i++) printf("%d", result[i]); printf("\n");
	
	printf("Chosen e : \n\t%d\n", e);
	printf("Chosen d : \n\t%d\n", d);
	printf("Your Original Message : \n\t");
	for (int i = 0; i < strlen(arr5); i++) printf("%d", arrmsg[i]); printf("\n");
	printf("Encryption Message : \n\t");
	Encrypt = SAM(arrmsg, e, result, len);
	int max;
	for (int i = strlen(arr1); i >= 0; i--) 
		if (Encrypt[i] != 0) { max = i; break; }
	for (int i = 0; i < max+1; i++) printf("%d", Encrypt[i]); printf("\n");
	printf("Decryption Message : \n\t");
	Decrypt = SAM(Encrypt, d, result, len);
	// Does not work.
	for (int i = 0; i < strlen(arr5); i++) printf("%d", arrmsg[i]); printf("\n");
	
	//result_1 = MPM(Prime_1(arrp, strlen(arr1)), Prime_1(arrq, strlen(arr2)), strlen(arr1), strlen(arr2));
	//printf("Calculate (p-1)(q-1) : \n\t");
	//for (int i = 0; i < len; i++) printf("%d", result_1[i]); printf("\n");
	
	
	free(arrp); free(arrq);
	free(arr1); free(arr2);
    return 0;
}