#include <stdio.h>
#include <math.h>
struct Input_Set
{
    int Value;
    int Radix;
    int Operand_Size;
};

struct Output_Format
{
    unsigned long Value;
    unsigned long  Maximum;
    unsigned long Minimum;
};

struct Output_Set
{

    struct Output_Format Binary;
    struct Output_Format Octal;
    struct Output_Format Decimal;
    struct Output_Format Hexadecimal;
    struct Output_Format Signed_One;
    struct Output_Format Signed_Two;
    struct Output_Format Sign_Mag;
}Ouput;

unsigned long into_binary(long long num)
{
    if(num == 0)
        return 0;
    else
        return (num%2)+10*into_binary(num/2);
}

unsigned long into_sign_binary(long num,int operand_size)
{
    if (operand_size != 4 && operand_size != 8 && operand_size != 16)
        return 0;
    if (num >= -pow(2,operand_size-1) && num <= pow(2,operand_size-1))
    {
        if (num < 0)
            return into_binary(abs(num))+pow(10,operand_size-1);
        else
            return into_binary(abs(num));
    }
    else
        return 0;
}
unsigned long into_one_complement(long num,int operand_size)
{

    if (operand_size != 4 && operand_size != 8 && operand_size != 16)
        return 0;
    if (num >= -pow(2,operand_size-1) && num <= pow(2,operand_size-1))
    {
        if(num > 0)
            return into_binary(num);
        else
            return into_binary(pow(2,operand_size)-abs(num)-1);
    }
    else
        return 0;
}

unsigned long into_two_complement(long num,int operand_size)
{
    if (operand_size != 4 && operand_size != 8 && operand_size != 16)
        return 0;
    if (num >= -pow(2,operand_size-1) && num <= pow(2,operand_size-1))
    {
        if(num > 0)
            return into_binary(num);
        else
            return into_binary(pow(2,operand_size)-abs(num));
    }
    else
        return 0;
}

int main()
{
    struct Input_Set Input_table [12] = {{-6,10,4},{-7,10,4},{-7,9,4},{-7,10,5},{-10,10,4},{236,10,8},
                                        {0354,8,8},{0xEB,16,8},{-125,10,8},{65400,10,8},{65400,10,16},{-32701,10,16}};
    struct Output_Set Output_table [12];
    for(int i = 0;i < 12;i++)
    {
        Output_table[i].Binary.Value = into_binary(abs(Input_table[i].Value));
        Output_table[i].Binary.Maximum = into_binary(pow(2,Input_table[i].Operand_Size)-1);
        Output_table[i].Binary.Minimum = 0;
        Output_table[i].Octal.Value = abs(Input_table[i].Value);
        Output_table[i].Octal.Maximum = pow(2,Input_table[i].Operand_Size)-1;
        Output_table[i].Octal.Minimum = 0;
        Output_table[i].Decimal.Value = abs(Input_table[i].Value);
        Output_table[i].Decimal.Maximum = pow(2,Input_table[i].Operand_Size)-1;
        Output_table[i].Decimal.Minimum = 0;
        Output_table[i].Hexadecimal.Value = abs(Input_table[i].Value);
        Output_table[i].Hexadecimal.Maximum = pow(2,Input_table[i].Operand_Size)-1;
        Output_table[i].Hexadecimal.Minimum = 0;
        Output_table[i].Signed_One.Value = into_one_complement(Input_table[i].Value,Input_table[i].Operand_Size);
        Output_table[i].Signed_One.Maximum = into_one_complement(pow(2,Input_table[i].Operand_Size-1)-1,Input_table[i].Operand_Size);
        Output_table[i].Signed_One.Minimum = into_one_complement(-(pow(2,Input_table[i].Operand_Size-1)-1),Input_table[i].Operand_Size);
        Output_table[i].Signed_Two.Value = into_two_complement(Input_table[i].Value,Input_table[i].Operand_Size);
        Output_table[i].Signed_Two.Maximum = into_two_complement(pow(2,Input_table[i].Operand_Size-1)-1,Input_table[i].Operand_Size);
        Output_table[i].Signed_Two.Minimum = into_two_complement(-(pow(2,Input_table[i].Operand_Size-1)-1),Input_table[i].Operand_Size);
        Output_table[i].Sign_Mag.Value = into_sign_binary(Input_table[i].Value,Input_table[i].Operand_Size);
        Output_table[i].Sign_Mag.Maximum = into_sign_binary(pow(2,Input_table[i].Operand_Size-1)-1,Input_table[i].Operand_Size);
        Output_table[i].Sign_Mag.Minimum = into_sign_binary(-(pow(2,Input_table[i].Operand_Size-1)-1),Input_table[i].Operand_Size);
    }
    FILE *fptr;
    // use appropriate location if you are using MacOS or Linux
    fptr = fopen("ProgramOne.out","w");
    if(fptr == NULL)
    {
       printf("Error!");
       exit(1);
    }
    for (int i = 0;i < 12;i++)
    {
        fprintf(fptr,"Input:  Value              %-20d         Radix %-20d     Operand %-20d\n",Input_table[i].Value,Input_table[i].Radix,Input_table[i].Operand_Size);
        fprintf(fptr,"Output:                    %-20s         %-20s           %-20s\n","value","Maximum","Minimum");
        fprintf(fptr,"Binary(abs)                0b%-20lu       0b%-20lu         0b%-20lu\n",Output_table[i].Binary.Value,
               Output_table[i].Binary.Maximum,Output_table[i].Binary.Minimum);
        fprintf(fptr,"Octal(abs)                 %-20o          %-20o            %-20o\n",Output_table[i].Octal.Value,
               Output_table[i].Octal.Maximum,Output_table[i].Octal.Minimum);
        fprintf(fptr,"Decimal(abs)               %-20lu          %-20lu            %-20lu\n",Output_table[i].Decimal.Value,
               Output_table[i].Decimal.Maximum,Output_table[i].Decimal.Minimum);
        fprintf(fptr,"Hexadecimal(abs)           %-20x          %-20x            %-20x\n",Output_table[i].Hexadecimal.Value,
               Output_table[i].Hexadecimal.Maximum,Output_table[i].Hexadecimal.Minimum);
        if(Input_table[i].Operand_Size != 4 && Input_table[i].Operand_Size != 8 && Input_table[i].Operand_Size != 16)
        {
            fprintf(fptr,"Signed One's Complement    %-20s         %-20s           %-20s\n","error",
                   "error","error");
            fprintf(fptr,"Signed two's Complement    %-20s         %-20s           %-20s\n","error",
               "error","error");
            fprintf(fptr,"Sign-Magnitude             %-20s         %-20s           %-20s\n","error",
               "error","error");
        }
        else{
            if(Output_table[i].Signed_One.Value == 0)
                fprintf(fptr,"Signed One's Complement    %-20s          %-20lu           %-20lu\n","error",
                       Output_table[i].Signed_One.Maximum,Output_table[i].Signed_One.Minimum);
            else
                fprintf(fptr,"Signed One's Complement    %-20lu         %-20lu           %-20lu\n",Output_table[i].Signed_One.Value,
                       Output_table[i].Signed_One.Maximum,Output_table[i].Signed_One.Minimum);
            if(Output_table[i].Signed_Two.Value == 0)
                fprintf(fptr,"Signed two's Complement    %-20s          %-20lu           %-20lu\n","error",
                       Output_table[i].Signed_Two.Maximum,Output_table[i].Signed_Two.Minimum);
            else
                fprintf(fptr,"Signed two's Complement    %-20lu         %-20lu           %-20lu\n",Output_table[i].Signed_Two.Value,
                       Output_table[i].Signed_Two.Maximum,Output_table[i].Signed_Two.Minimum);
            if(Output_table[i].Sign_Mag.Value == 0)
                fprintf(fptr,"Sign-Magnitude             %-20s          %-20lu           %-20lu\n","error",
                       Output_table[i].Sign_Mag.Maximum,Output_table[i].Sign_Mag.Minimum);
            else
                fprintf(fptr,"Sign-Magnitude             %-20lu         %-20lu           %-20lu\n",Output_table[i].Sign_Mag.Value,
                       Output_table[i].Sign_Mag.Maximum,Output_table[i].Sign_Mag.Minimum);
        }
        fprintf(fptr,"\n");
    }
    fclose(fptr);
    return 0;
}

