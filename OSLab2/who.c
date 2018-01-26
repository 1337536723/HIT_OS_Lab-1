#include<errno.h>
#include<asm/segment.h>

char kName[24] = "";

int sys_whoami(char* name, unsigned int size)
{
	int charCount = 0;	
	while(charCount <= 23)
	{
		/* if(name[charCount] == '\0')*/
		if(kName[charCount] == '\0')
		{
			break;
		}
		else
		{
			charCount++;
		}
	}
	
	int needSize = charCount + 1;
	
	if (size < needSize)
	{
		/*errno = EINVAL;*/
		return -EINVAL;
	}	
	
	int i;
	for (i = 0; i < charCount; i++)
	{
		put_fs_byte(kName[i], name + i);
	}
	put_fs_byte('\0',name + i);
	return charCount;
}

int sys_iam(const char * name)
{

/*get chars number of name[]*/
	int charCount = 0;
	while(charCount <= 23)
	{
		/* if(name[charCount] == '\0')*/
		if((char)get_fs_byte(name + charCount) == '\0')
		{
			break;
		}
		else
		{
			charCount++;
		}
	}
	
	if (charCount > 23)
	{
		/*errno = EINVAL;*/
		return -EINVAL;
	}
	
	int i = 0;
	for(;i < charCount; i++)
	{
		kName[i] = (char)get_fs_byte(name + i);
	}
	kName[i] = '\0';	


	/*	printk("kName in whoami:%s\n",kName);*/

	//printk("whoami function\n");
	return charCount;

/*	char * p = name;
	char *i = kName;		
	while((char)get_fs_byte(p)!='\0' )
	{
		*i = (char)get_fs_byte(p);
		++p;
		++i;
	}
	*i = '\0';*/
	/**kName = (char)get_fs_byte(name);
	kName[1] = '\0';
	printk("iam function\n");
	printk("kName:%s\n",kName);
	return (4);*/
}

