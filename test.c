#include <unistd.h>
#include <pthread.h>
#include "./logger.h"

void *print_log(void *arg)
{
	char *str = (char *)arg;
	for ( int i = 0; i < 100000; i++ )
	{
		logger_level_printf(LOGGER_DEBUG_LEVEL, "this an debug %s %d", str, 525 + i);
		log_debug("this an debug %s %d", str, 525 + i);
		
		logger_level_printf(LOGGER_INFO_LEVEL, "this an info %s %d", str, 525 + i);
		log_info("this an info %s %d", str, 525 + i);

		logger_level_printf(LOGGER_WARN_LEVEL, "this an warn %s %d", str, 525 + i);
		log_warn("this an warn %s %d", str, 525 + i);

		logger_level_printf(LOGGER_ERROR_LEVEL, "this an error %s %d", str, 525 + i);
		log_error("this an error %s %d", str, 525 + i);

		if ( i % 10000 == 0 )
		{
			sleep(1);
		}
	}
	return NULL;
}

int main(void)
{
	logger_init("./log");

	pthread_t tid1, tid2;
	pthread_create(&tid1, NULL, print_log, "thread 1");
	pthread_create(&tid2, NULL, print_log, "thread 2");

	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);

	logger_destroy();
	return 0;
}