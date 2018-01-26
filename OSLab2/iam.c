#define __LIBRARY__
#include <unistd.h>
#include<string.h>

_syscall1(int, iam, const char*, name);

int main(int argc,char *argv[])
{
	char inputBuff[24] = "";
	int strNum = argc - 1;
	int i;
	if (argc == 1)
	{
		return 0;
	}
	else
	{
		for (i = 1; i <= strNum; i++)
		{
			if (i != 1)
			{
				if (strlen(inputBuff) + 1 > 23)
				{
					return -1;
				}
				else
				{
					strcat(inputBuff," ");
				}
			}
			
			if (strlen(inputBuff) + strlen(argv[i]) > 23)
			{
				return -1;
			}
			else
			{
				strcat(inputBuff,argv[i]);
			}
		}	
		return iam(inputBuff);
	}


	return 0;
}

