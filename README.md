# c_logger
A Lightweight Logger Implemented with C

# Main features
- Easy to use, You can adjust it through macro parameters
- Can output Debug, INFO, WARN, ERROR, and FATAL level logs
- Can limit the size of log file(Unit : MB)
- Can limit the number of log files
- The naming of log files can be set with a fixed prefix
- Thread safety
  
# Output
```c
May 21 2024 23:45:01 [1661][1663] [./test.c print_log:19] [ERROR] this an error thread 2 54246
May 21 2024 23:45:01 [1661][1663] [./test.c print_log:20] [ERROR] this an error thread 2 54246
May 21 2024 23:45:01 [1661][1663] [./test.c print_log:13] [INFO] this an info thread 2 54247
May 21 2024 23:45:01 [1661][1663] [./test.c print_log:14] [INFO] this an info thread 2 54247
May 21 2024 23:45:01 [1661][1663] [./test.c print_log:16] [WARN] this an warn thread 2 54247
May 21 2024 23:45:01 [1661][1662] [./test.c print_log:13] [INFO] this an info thread 1 59045
May 21 2024 23:45:01 [1661][1662] [./test.c print_log:14] [INFO] this an info thread 1 59045
May 21 2024 23:45:01 [1661][1662] [./test.c print_log:16] [WARN] this an warn thread 1 59045
May 21 2024 23:45:01 [1661][1662] [./test.c print_log:17] [WARN] this an warn thread 1 59045
May 21 2024 23:45:01 [1661][1662] [./test.c print_log:19] [ERROR] this an error thread 1 59045
May 21 2024 23:45:01 [1661][1662] [./test.c print_log:20] [ERROR] this an error thread 1 59045
```

# Example
```c
#include <unistd.h>
#include <pthread.h>
#include "./logger.h"

void *print_log(void *arg)
{
	char *str = (char *)arg;
	for ( int i = 0; i < 100000; i++ )
	{
		logger_level_printf(LOGGER_DEBUG_LEVEL, "this an debug %s %d", str, 525 + i);
		logger_level_printf(LOGGER_INFO_LEVEL, "this an info %s %d", str, 525 + i);
		logger_level_printf(LOGGER_WARN_LEVEL, "this an warn %s %d", str, 525 + i);
		logger_level_printf(LOGGER_ERROR_LEVEL, "this an error %s %d", str, 525 + i);
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
```
