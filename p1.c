/* 
Alex Beall 
Project 1
10/11/2015
section 0101

This Code will encrypt a file by reading from an input file, 
shifting each character by the amount specified by a seperate encryption file, 
then write the encrypted message into a new file. 
This code can then also decrypt the encrypted message.

Setup
*/

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
//File setup

FILE *input1, *input2, *output;

input1 = fopen(argv[1], "r");
input2 = fopen(argv[2], "r");
output = fopen(argv[3], "w");

if (input1 == NULL)
{printf("FIle %s cannot open!\n", argv[1]);
}
if (input2 == NULL)
{printf("FIle %s cannot open!\n", argv[2]);
}
if (output == NULL)
{printf("FIle %s cannot open!\n", argv[3]);
}


//Variables
int BlockSize = 100, key[BlockSize], x = 0, shift, type;	
char ot, opmode, result;								//ot=original text
char special[17] = "!@#$%^&*()/.,? \n";
int index =0;

//determine if Encrypt or Decrypt
	fscanf(input2, "%c", &opmode);						
		if (opmode == 'e')
		{
			type = 1;
		}
		if (opmode == 'd')
		{
			type = 2;
		}
		
// Find block size and add values to key
	fscanf(input2, "%*s %d", &BlockSize);
	for (x =0; x < BlockSize; x++)
	{
		fscanf(input2, "%d", &key[x]);											
	}
	x=0;

// Use key to encrypt original text character by character
if (type == 1)
{
// loop until end of file is reached
while (fscanf(input1, "%c", &ot)!= EOF)
	{
//Uppercase
	if((ot >= 65) && (ot <= 90))			
	{
		if (ot + key[x] > 90)
		{
			result = (((ot + key[x])%90)%26 + 64);
			fprintf(output, "%c", result);
		}
		else
		{
			result = (ot + key[x]);
			fprintf(output, "%c", result);
		}	
	}
	
//lowercase
	else if((ot >= 97) && (ot <= 122))			
	{
		if (ot + key[x] > 122)
		{
			result = (((ot + key[x])%122)%26 + 96);
			fprintf(output, "%c", result);
		}
		else
		{
			result = ot + key[x];
			fprintf(output, "%c", result);
		}
	}
	
//Number
	else if((ot >= 48) && (ot <= 57))	
	{
		if (ot + key[x] > 57)
		{
			result = (((ot + key[x])%57)%10 + 47);
			fprintf(output, "%c", result);
		}
		else
		{
		result = ot + key[x];
		fprintf(output, "%c", result);
		}
	}
//Special characters
	else
	{
		switch(ot)
		{
		case '!' : index = 0; break; 
		case '@' : index = 1; break;
		case '#' : index = 2; break;
		case '$' : index = 3; break;
		case '%' : index = 4; break;
		case '^' : index = 5; break;
		case '&' : index = 6; break;
		case '*' : index = 7; break;
		case '(' : index = 8; break;
		case ')' : index = 9; break;
		case '/' : index = 10; break;
		case '.' : index = 11; break;
		case ',' : index = 12; break;
		case '?' : index = 13; break;
		case ' ' : index = 14; break;
		case '\n': index = 15; break;
		}
		if (index + key[x]%16 > 15)
		{
			result = special[(index + key[x])%16];
			fprintf(output, "%c", result);
		}
		else
		{
			result = special[index + key[x]];
			fprintf(output, "%c", result);
		}
	}
// move to next value in key array
		x++;
		x = x%BlockSize;
	}
}

// Use key to decrypt the encrypted message
if (type == 2)
{
// loop until end of file is reached
	while (fscanf(input1, "%c", &ot)!= EOF)
	{
//Uppercase
	if((ot >= 65) && (ot <= 90))			
	{
		if (ot - key[x] < 65)
		{
			result = (91 - (65%(ot - key[x]))%26);
			fprintf(output, "%c", result);
		}
		else
		{
			result = (ot - key[x]);
			fprintf(output, "%c", result);
		}	
	}
//lowercase
	else if((ot >= 97) && (ot <= 122))			
	{
		if (ot - key[x] < 97)
		{
			result = (123 - (97%(ot - key[x]))%26);
			fprintf(output, "%c", result);
		}
		else
		{
			result = ot - key[x];
			fprintf(output, "%c", result);
		}
	}
//Number
	else if((ot >= 48) && (ot <= 57))	
	{
		if (ot - key[x]%10 < 48)
		{
			result = (58 - (48%(ot - key[x]))%10);
			fprintf(output, "%c", result);
		}
		else
		{
		result = ot - key[x]%10;
		fprintf(output, "%c", result);
		}
	}
//Special character
	else
	{
		switch(ot)
		{
		case '!' : index = 0; break; 
		case '@' : index = 1; break;
		case '#' : index = 2; break;
		case '$' : index = 3; break;
		case '%' : index = 4; break;
		case '^' : index = 5; break;
		case '&' : index = 6; break;
		case '*' : index = 7; break;
		case '(' : index = 8; break;
		case ')' : index = 9; break;
		case '/' : index = 10; break;
		case '.' : index = 11; break;
		case ',' : index = 12; break;
		case '?' : index = 13; break;
		case ' ' : index = 14; break;
		case '\n': index = 15; break;
		}
		if (index - key[x]%16 < 0)
		{
			result = special[16 + (index - key[x])%16];
			fprintf(output, "%c", result);
		}
		else
		{
			result = special[index - key[x]];
			fprintf(output, "%c", result);
		}
	}
//move to next value in key array
		x++;
		x = x%BlockSize;
	}
}
	fclose(input1);
	fclose(input2);
	fclose(output);
	
	return 0;
}