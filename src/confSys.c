/*
 *	Configuration system v1
 *	
 *	HOW TO USE:
 *	 In the file you want to use the configuration system in you need
 *	 a static array of the names that you want to read from the config
 *	 file in the order that you want to read them into memory, e.g.
 *
 *	 	char *names[3] = {'a', 'b', 'f'};
 *
 *	 This is to compliment an array of the corresponding variable
 *	 addresses, e.g.
 *
 *	 	int addresses[3] = {&a, &b, &flags};
 *
 *	 Then simply run the function:
 *	 	
 *	 	loadConfig("filename.txt", names, addresses, 3);
 *
 *	 And the corresponding variables will be set to the number in the
 *	 config file.
 *
 *	IMPORTANT NOTE:
 *	 This config system only supports loading integer values into
 *	 variables, anything else will not work and may crash the program.
 *	 This system also cannot handle loading integers that have more
 *	 than 100 digits.
 *
 *	CONFIG FILES:
 *	 Config files must have a strict format, all variable names in the 
 *	 file and in the name array must be exactly 1 char. The values in
 *	 the config file must have a space of exactly 3 characters from
 *	 their variable name and the line must end with a semi-colon, e.g.
 *
 *	 	a = 3;
 *	 	b = 152;
 *		f = 0;
*/

#include "confSys.h"

void loadConfig(char *fname, char *cfgName, int **cfgAddr, unsigned int size)
{
	FILE *conf = fopen(fname, "r");
	int c;
	int position = 0;
	int confsize = CONFIG_BUFFER_SIZE;
	char *buffer = malloc(confsize);
	
	while ((c = getc(conf)) != EOF)
	{
		buffer[position] = c;
		++position;

		if (position >= confsize)
		{
			confsize += CONFIG_BUFFER_SIZE;
			buffer = realloc(buffer, confsize);
			
			if (!buffer)
				exit(1);
		}
	}
	int y;
	for (y = position; y < confsize; ++y)
		buffer[y] = '\0';
	
	fclose(conf);

	int i;
	int j;
	int k = 3;
	char string[100] = {};
	for (i = 0; i < confsize; ++i)
	{
		for (j = 0; j < size; ++j)
		{
			if (buffer[i] == cfgName[j])
			{
				int x;
				for (x = 0; x < sizeof(string); ++x)
				{
					string[x] = '\0';
				}

				while (buffer[i+k] != ';')
				{
					if (i+k < confsize)
					{
						string[k-3] = buffer[i+k];
						++k;
					}
					else
					{	
						break;
						break;
						break;
						break;
					}
				}
				k = 0;
				
				string[k-2] = '\0';
				*cfgAddr[j] = strtol(string, (char **)NULL, 10);
			}
		}
	}
	free(buffer);
}
