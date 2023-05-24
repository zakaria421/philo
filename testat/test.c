# include <sys/time.h>
# include <stdio.h>
# include <unistd.h>

time_t	get_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
}


int main()
{
	// time_t start_time;
	// time_t current_time;

	// start_time = get_time();
	
	// printf("start_time: %ld\n", start_time);
	// //printf("current_time: %ld\n", current_time);
	// sleep(1);
	// current_time = get_time();
	// printf("current_time - start_time: %ld\n", current_time - start_time);
	// return (0);
	printf("zakaria\n");
	usleep(1000000);
	printf("mama\n");
}