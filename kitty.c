#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

char case_T ( char *buf ) 
{
        char *ptr;
        int i;
	
	for (i=0; i<strlen(buf); ++i)
        {
                if((ptr = strchr(buf, '\t')))
                {
			*ptr = '^';
		}
        }

        return *buf;
}


char case_A( char *buf ) 
{
	char *ptr;
	int i;
	
	for (i=0; i<strlen(buf); ++i)
	{
                if((ptr = strchr(buf, '\n')))
                {
                        *ptr = '$';
                }
		case_T( buf );
	}
	printf("\n");	
	return *buf;

}
char case_E( char *buf ) 
{
        char *ptr;
        int i;

        for (i=0; i<strlen(buf); ++i)
        {
                if((ptr = strchr(buf, '\n')))
                {
                        *ptr = '$';
                }
        }
        return *buf;


}
char case_b( char *buf, int *counter_b, char *tmp ) 
{
	int i;
	
	if ( buf[0] != '\n')
	{
		sprintf( tmp, "%d", ++*counter_b);
		strcat(tmp, "\t");
	        strcat( tmp, buf );
	}
	else
	{
		return *buf;
	}
        for(i=0; i<strlen(buf); i++)
        {
                buf[i] = tmp[i];
        }
	return *buf;
}

char case_n( char *buf, int *counter_n, char *tmp ) 
{
	int i;

	sprintf( tmp, "%d ", ++*counter_n);
	strcat( tmp, buf );

	for(i=0; i<1500; i++)
	{
		buf[i] = tmp[i];	
	}
	return *buf;	
}
char case_s ( char *buf , int *counter_s, FILE * fptr) 
{

	if(feof(fptr))
	{
		exit(EXIT_SUCCESS);
	}
	
	if ( buf[0] == '\n')  
	{
		++*counter_s;

		if( *counter_s >= 2)
		{
			fgets(buf, 1500, fptr);
			case_s( buf, counter_s, fptr);
		}
	}
	else if ( buf[0] != '\n')
	{
		*counter_s = 0;
	}
	
	return *buf;
}

char case_v(char *buf, FILE * fptr) 
{

	if(*buf < -96) 
	{
		fprintf(fptr, "M-^%c",*buf+192);
	}
	else if(*buf < 0) 
	{
		fprintf(fptr, "M-%c",*buf+128);
	} 
	else if(*buf == 9 || *buf == 10) 
	{
		putc(*buf, fptr);
	} 
	else if(*buf < 32 ) 
	{
		fprintf(fptr, "^%c",*buf+64);
	} 
	else if(*buf < 127) 
	{
		putc(*buf, fptr);
	} 
	else 
	{
		fprintf(fptr, "^?");
	}
	return *buf;
}

char swap( char * argv[] , int *arglen)
{
	char temp[15];
	char ch;
	int i;
	
	for(i=0; i<*arglen; ++i)
	{
		temp[i] = argv[1][i];
	}

	for(i=0; i<*arglen; ++i)
	{
		if(temp[i] == 's')
		{
			ch = temp[i];
			temp[i] = temp[1];
			temp[1] = ch;	
		}
	}
	
	for(i=0;i<*arglen; ++i)
	{
		argv[1][i] = temp[i];
	}
	

	return **argv;
}

int main(int argc, char * argv[])
{	
	int buflen;
	int arglen, counter_b = 0, counter_s = 0, counter_n = 0;
	char choice;
	char buf[1500];
	char tmp[1500];
	FILE * fptr;
	extern int optind;

	arglen = strlen ( argv[1] );
	
	swap( argv , &arglen);

	if(argv[2] == 0)
	{
		fptr = fopen(argv[1], "r");
		while(fgets(buf, 1500, fptr) != NULL)
		{
			printf("%s", buf);
		}
		fclose(fptr);
		exit(EXIT_SUCCESS);
	}
	else if (argv[2] != 0)
	{
		fptr = fopen(argv[2], "r");
	}

	while( fgets(buf, 1500, fptr) != NULL)
	{
		buflen = strlen( buf);

		while((choice = getopt ( argc, argv, "AbeEnstTuv")) != -1)
		{
	
			switch(choice)
			{
				case 'A': 
				case_A( buf );
				break;

				case 'b': 
				case_b(buf, &counter_b, tmp);
				break;
	
				case 'e':
				case_v( buf , fptr );
				case_E( buf );
				printf("\n");
				break;
	
				case 'E': 
				case_E( buf );
				printf("\n");
				break;
	
				case 'n': 
				case_n( buf, &counter_n, tmp );
				break;
		
				case 's': 
				case_s( buf , &counter_s, fptr );
				break;
		
				case 't':
				case_v( buf, fptr );
				case_T( buf );
				break;
		
				case 'T':
				case_T( buf );
				break;

				case 'u': 
				break;
		
				case 'v':
				case_v( buf, fptr );
				break;

			}
		}
		optind = 1;
		printf("%s", buf);
	}
	printf("\n");
	fclose(fptr);
	return 0;
}

