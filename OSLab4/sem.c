#include<asm/segment.h>
#include<asm/system.h>
#define SEM_NUM		16
#define SNAME_MAX_LEN	30

struct sem_t
{
	char name[SNAME_MAX_LEN];
	int value;
	int wakable;
	struct task_struct * p;
};


struct sem_t sems[SEM_NUM];

struct sem_t *getSemByName(const char * name);
struct sem_t *getFreeSemSpace();

struct sem_t * sys_sem_open(const char *name, unsigned int value)
{
	
//	strcpy(name, sems[0].name);
	char nameBuf[SNAME_MAX_LEN];
	char c;
	int i = 0;
	while((c = get_fs_byte(name + i)) != '\0')
	{
		nameBuf[i] = c;
		++i;
	}
	
	nameBuf[i] = '\0';
	//printk("sem_open\n");	
	struct sem_t *q = getSemByName(nameBuf);
	if (q != 0)
	{
		return q;
	}
	else
	{
		struct sem_t *t = getFreeSemSpace();
		if (t == 0)
		{
			return 0;
		}
		strcpy(t->name, nameBuf);
		t->value = value;
		t->wakable = 0;
		t->p = 0;
		return t;
	}
}

int sys_sem_wait(struct sem_t *sem)
{
	//printk("sem_wait\n");
	if (sem == 0)
	{
		return -1;
	}	
	cli();
	sem->value--;
	if (sem->value < 0)
	{
		sleep_on(&(sem->p));//unc;
		while(sem->wakable <= 0){
			sleep_on(&(sem->p));//unc;
		}
		sem->wakable--;
	}
	sti();

	return 0;
}

int sys_sem_post(struct sem_t *sem)
{
	//printk("sem_post\n");
	if (sem == 0)
	{
		return -1;
	}
	cli();
	sem->value++;
	if (sem->value <= 0)
	{
		wake_up(&(sem->p));
		sem->wakable++;
	}
	sti();
	
	return 0;
}

int sys_sem_unlink(const char *name)
{
	char nameBuf[SNAME_MAX_LEN];
	int i = 0;
	char c;	
	while((c = get_fs_byte(name + i)) != '\0')
	{
		nameBuf[i] = c;
		++i;
	}

	nameBuf[i] = '\0';
	
	struct sem_t *p = getSemByName(nameBuf);
	if (p == 0)
	{
		return -1;
	}
	else
	{
		strcpy(p->name, "");
		p->value = 0;
		p->wakable = 0;
		p->p = 0;
	//	printk("sem_unlink succ\n");
		return 0;
	}
}

struct sem_t *getSemByName(const char * name)
{
	int i = 0;
	for(i = 0; i < SEM_NUM; ++i)
	{
		if (strcmp(name, sems[i].name) == 0)
		{
			return &sems[i];
		}
	}
	return 0;
}

struct sem_t *getFreeSemSpace()
{
	int i = 0;
	for (i = 0; i < SEM_NUM; ++i)
	{
		if (strcmp(sems[i].name, "") == 0)
		{
			return &sems[i];
		}
	}
	return 0;
}

