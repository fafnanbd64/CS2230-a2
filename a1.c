#include <stdio.h>
#include <stdlib.h>
#include <math.h>
// TODO: what are function prototypes?
void other_base(unsigned, unsigned);
void power2_base(unsigned, unsigned);
void base_256(unsigned, unsigned);
// this will not change, so we can declare it constant
const char *ascii = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz+/";
// this _will_ change, however
char buffer[32];
int i =31; //Here, I initialized a pointer to keep track of the buffer.
// every C program must implement the `main()` function
int main(int argc, char *argv[]) {
	// TODO: error check
	//Here, I check the number of arguments in the terminal. If the number of arguments is anything but 2
	// the output is an error message that prints the usage. 
	if (argc != 3) {                
	    printf("Usage: ./a1 <decimal> <base>");
		return -1;
	} 
	// properly NULL terminate the buffer
	buffer[31] = '\0';
	// use `atoi()` function to translate characters to numbers
	unsigned decimal = atoi(argv[1]);
	unsigned base    = atoi(argv[2]);
    //Here, I used a bunch of if else if control statements to check my base. If the base is equal to 256, I pass the decimal and base to base_256 function. If the base is a power of 2, then the arguments are passed to power2_base function. Similarly i also checked my base again if it falls under the range. If its less than 2 or greater than 64 and not 256, an error message is printed. 
	if (base == 256) {
	    base_256(decimal, base);
	    
	}
	else if (base == 2 || base == 4 || base == 8 || base==16 || base ==32 || base ==64) {
	    power2_base(decimal, base);
	}
	else if (base <= 1 || base >= 65 && base != 256) {
	    fputs("INVALID BASE\n", stderr);
        exit(EXIT_FAILURE);
	}
	else{
	    other_base(decimal, base);
	}
	//To check my argv[1] inputs, I used a pointer and a for loop to check if there's anything other than
	//digits that fall from 0 to 9. if any of the input is anything except the numbers, it prints an error. As you described in the asssignment to use fprintf to print the error message, I tried but failed to print the error so I used the printf function. 
	char *num = argv[1];
	for (int a=0; num[a] != 0; a++) {
	    if (num[a] > '9' && num[a] < '0') {
	        printf("INVALID NUMBER\n");
            return -1;
	    }
	}
	printf("%s\n", &buffer[i+1]);
	return 0;
}
void other_base(unsigned decimal, unsigned base) {
	//for the other bases, i used the divide and modulo function to calculate the result and the buffer was filled from the end. Here, we find the quotient first and then the remainder. the remainder is stored in the buffer and keep dividing the dividend untill we get zero.
    int dv = decimal;
    int dr = base;
    int q = '\0';
    int r;
    for ( i; dv > 0 ; i-- ) {
        
        q=( dv / dr );
        r= dv % dr;
        buffer[i] = ascii[r];
        dv = ( dv / dr);
        }
	return;
}
void power2_base(unsigned decimal, unsigned base) {

	// TODO: for bases that are a power of 2 but still not 256
	//In ths function we use mask and shift where we and the mask with the dividend and put in the buffer and keep shifting the value until we get zero. 
    int dv = decimal;
    int q = '\0';
	int mask = base - 1;
	int shift = (int)log2(base);
	
    for ( i; dv > 0 ; i--) {
        q=(dv & mask);
        buffer[i] = ascii[q];
        dv = dv >> shift;
    }
    
    //printf("pow 2 base");
	return;
}
void base_256(unsigned decimal, unsigned base) {
   
	// TODO: for base 256 only
	// In this function, we integrated both the algorithms. in the first while function, we mask the dividend and then check with an if and else function. Since the number is too large for the ascii storage, we divide and modulus the number with 10 to break it down.  
	int mask = ( base -1 );

	while  ( decimal > 0 ) {
	    int q = decimal & mask;
	    if ( q == 0 ) { 
	        buffer[i--] = ascii[q]; 
	} else {
	    for( i; q > 0 ; i-- ) {
	        buffer [i] = ascii [ q % 10 ];
	        q = q/10;
	    }
	}
	buffer[ i-- ] = '.'; //to store the period. 
	decimal = decimal >> (int)log2(base); //decimal was changed to rotate the calculation again and keep doing it untill the shifting becomes zero. the replacement of division. 
	}
	i++;
	return;
}