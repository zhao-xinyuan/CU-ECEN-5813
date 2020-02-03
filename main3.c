#include <stdio.h>
#define INT_BITS sizeof(unsigned int)-1
unsigned long long into_binary(long long num)
{
    if(num == 0)
        return 0;
    else
        return (num%2)+10*into_binary(num/2);
}

/* https://www.geeksforgeeks.org/reverse-actual-bits-given-number/
Reverse the Binary Order*/
unsigned int reverseBits(unsigned int n)
{
    unsigned int rev = 0;

    // traversing bits of 'n' from the right
    while (n > 0)
    {
        // bitwise left shift
        // 'rev' by 1
        rev <<= 1;

        // if current bit is '1'
        if (n & 1 == 1)
            rev ^= 1;

        // bitwise right shift
        // 'n' by 1
        n >>= 1;

    }

    // required number
    return rev;
}
// https://codeforwin.org/2017/12/c-program-rotate-number-bits.html
int rotateLeft(int num, unsigned int rotation)
{
    int DROPPED_MSB;

    // The effective rotation
    rotation %= INT_BITS;


    // Loop till rotation becomes 0
    while(rotation--)
    {
        // Get MSB of num before it gets dropped
        DROPPED_MSB = (num >> INT_BITS) & 1;

        // Left rotate num by 1 and
        // Set its dropped MSB as new LSB
        num = (num << 1) | DROPPED_MSB;
    }

    return num;
}

int rotateRight(int num, unsigned int rotation)
{
    int DROPPED_LSB;

    // The effective rotation
    rotation %= INT_BITS;


    // Loop till rotation becomes 0
    while(rotation--)
    {
        // Get LSB of num before it gets dropped
        DROPPED_LSB = num & 1;

        // Right shift num by 1 and
        // Clear its MSB
        num = (num >> 1) & (~(1 << INT_BITS));

        // Set its dropped LSB as new MSB
        num = num | (DROPPED_LSB << INT_BITS);
    }

    return num;
}

int test(long long num)
{
    int number = 0;
    unsigned long num1;
    num1 = into_binary(num);
    if (num1%10 == 1)
        number++;
    if((num1/10)%10 == 1)
        number++;
    if((num1/100)%10 == 1)
        number++;
    if((num1/1000)%10 == 1)
        number++;
    if(number >= 3)
        return 1;
    else
        return 0;
}

int main(void)
{
    FILE *fptr;
    // use appropriate location if you are using MacOS or Linux
    fptr = fopen("ProgramThree.out","w");
    if(fptr == NULL)
    {
       printf("Error!");
       exit(1);
    }
    long value = 0xFACE;
    printf("Initial Value:          %x\n",value);
    if(test(value))
        printf("Test:true           %lu\n",into_binary(value));
    else
        printf("Test:false          %lu\n",into_binary(value));
    printf("Test %x\n",reverseBits(value));
    if(test(reverseBits(value)))
        printf("Reverse:true        %lu\n",into_binary(reverseBits(value)));
    else
        printf("Reverse:false       %lu\n",into_binary(reverseBits(value)));
    printf("Rotate the value:       %x\n",rotateLeft(reverseBits(value),6));
    if(test(rotateLeft(reverseBits(value),6)))
        printf("Left by 6:true      %lu\n",into_binary(rotateLeft(reverseBits(value),6)));
    else
        printf("Left by 6:false     %lu\n",into_binary(rotateLeft(reverseBits(value),6)));
    printf("Rotate the value:%x\n",rotateRight(rotateLeft(reverseBits(value),6),4));
    if(rotateRight(rotateLeft(reverseBits(value),6),4))
        printf("Right by 4:true     %lu\n",into_binary(rotateRight(rotateLeft(reverseBits(value),6),4)));
    else
        printf("Right by 4:false    %lu\n",into_binary(rotateRight(rotateLeft(reverseBits(value),6),4)));


    fprintf(fptr,"Initial Value:          %x\n",value);
    if(test(value))
        fprintf(fptr,"Test:true           %lu\n",into_binary(value));
    else
        fprintf(fptr,"Test:false          %lu\n",into_binary(value));
    fprintf(fptr,"Test %x\n",reverseBits(value));
    if(test(reverseBits(value)))
        fprintf(fptr,"Reverse:true        %lu\n",into_binary(reverseBits(value)));
    else
        fprintf(fptr,"Reverse:false       %lu\n",into_binary(reverseBits(value)));
    fprintf(fptr,"Rotate the value:       %x\n",rotateLeft(reverseBits(value),6));
    if(test(rotateLeft(reverseBits(value),6)))
       fprintf(fptr,"Left by 6:true      %lu\n",into_binary(rotateLeft(reverseBits(value),6)));
    else
        fprintf(fptr,"Left by 6:false     %lu\n",into_binary(rotateLeft(reverseBits(value),6)));
    fprintf(fptr,"Rotate the value:%x\n",rotateRight(rotateLeft(reverseBits(value),6),4));
    if(rotateRight(rotateLeft(reverseBits(value),6),4))
       fprintf(fptr,"Right by 4:true     %lu\n",into_binary(rotateRight(rotateLeft(reverseBits(value),6),4)));
    else
        fprintf(fptr,"Right by 4:false    %lu\n",into_binary(rotateRight(rotateLeft(reverseBits(value),6),4)));
     return 0;
}

