#include <stdio.h>

struct Output_Set
{
    int Code;
    char* p;
    char ASCII_char;
}Out;

int main(void)
{
    FILE *fptr;
    // use appropriate location if you are using MacOS or Linux
    fptr = fopen("ProgramTwo.out","w");
    if(fptr == NULL)
    {
       printf("Error!");
       exit(1);
    }
    int Input[]={66,114,117,99,101,32,83,97,121,115,32,72,105,33,7,9,50,48,49,57};
    struct Output_Set Output_table[128];
    for(int i = 0;i < 128;i++)
    {
        Output_table[i].Code = i;
        if((i>=0 && i<=32) || i==127)
            Output_table[i].p = "white space";
        else if((i>=33 && i<=47) || (i>=58 && i<=64) || (i>=91 && i<=95)||(i>=123 && i<=126))
            Output_table[i].p = "Special character";
        else if((i>=48 && i<=57))
            Output_table[i].p = "digit";
        else if(i>=65 && i<=90)
            Output_table[i].p = "Upper Case";
        else
            Output_table[i].p = "Lower Case";
        if ((i>=0 && i<=32) || i==127)
            Output_table[i].ASCII_char = ' ';
        else
            Output_table[i].ASCII_char = i;
    }
    char* b ="string";
    char c = 57;
    printf("char c %c",c);
    printf("string %s\n",Output_table[0].p);
    for(int i=0;i<20;i++)
        fprintf(fptr,"Code: %-3d    type: %20s     ASCII_CHAR: %10c \n",Output_table[Input[i]].Code,Output_table[Input[i]].p,Output_table[Input[i]].ASCII_char);
    fclose(fptr);
    return 0;
}

