#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int prime[] = {2,3,5,7,11,13,17,19,23,29,1,2};

void *test(void *k)
{	
	int i =0;
	int sum =0;
	int *aka=malloc(sizeof(int));
	int j = 0;
	i = *(int*)k;
	
	if (i == 1)
	{
		
		while (j <= (sizeof(prime) / 4) / 2)
		{
			sum+=prime[j];
			j++;
		}
		
	}
	else
	{
		j = (sizeof(prime) / 4) / 2;
		j++;
		while(j < (sizeof(prime) / 4))
		{
			sum+=prime[j];
			j++;
		}
	}
	
	*aka = sum;
	return (void*) aka;
}
int main()
{
	pthread_t th;
	pthread_t tb;
	int *i =0;
	int sum = 0;
	int number1 = 1 ;
	int number2 = 2;
	
	int *k;
	pthread_create(&th,NULL,&test,&number1);
	pthread_create(&tb,NULL,&test,&number2);
	pthread_join(th,(void **) &i);
	
	sum += *i;
	free(i);
	pthread_join(tb, (void **) &i);
	sum += *i;
	printf("%d",sum);
	
}