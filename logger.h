#ifndef SRC_LOGGER_H
#define SRC_LOGGER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdarg.h>
#include <dirent.h>
#include <time.h>
#include <pthread.h>
#include <sys/stat.h>  
#include <sys/types.h> 
#include <sys/syscall.h>

extern long syscall(long pid, ...);

/*
 * 常量定义
 * */
#define FAILURE -1
#define SUCCESS 0

#define boolean int
#define true 1
#define false 0

#define MAX_FILE_PATH_LEN 256
/*
日志级别定义，数值越小，级别越高
*/
#define LOGGER_FATAL_LEVEL			1 	//致命错误，不可恢复
#define LOGGER_ERROR_LEVEL			2	//一般错误，可恢复
#define LOGGER_WARN_LEVEL			3	//警告
#define LOGGER_INFO_LEVEL			4	//信息
#define LOGGER_DEBUG_LEVEL			5	//调试

/*
当前日志级别配置
*/
#define LOGGER_CFG_LEVEL LOGGER_DEBUG_LEVEL
/*
 * 日志文件前缀
 * */
#define LOG_NAME_PREFIX "log"
// 日志文件数量
#define DEFAULT_LOG_NUM_SET 10
// 日志文件大小 
#define DEFAULT_LOG_SIZE_SET 20
// 日志每行列数限制
#define LIMIT_LOG_LENGTH 4096

typedef struct _logger_cfg
{
    int level;
    // MB
    long log_size;
    int files_num;
    char *log_dir;

    long log_size_cur;
    long file_num_cur;
    char *log_name_cur;
    FILE *file_cur;
}logger_cfg;

void logger_init(char *log_path);
void logger_destroy();

void logger_set_level(int level);
void logger_set_log_size(long log_size);
void logger_set_file_num(int file_num);

void _log_debug(const char *file, const char *func, const int line, const char *format, ...);
void _log_info(const char *file, const char *func, const int line, const char *format, ...);
void _log_warn(const char *file, const char *func, const int line, const char *format, ...);
void _log_error(const char *file, const char *func, const int line, const char *format, ...);
void _log_fatal(const char *file, const char *func, const int line, const char *format, ...);

#define logger_level_printf(level, arg...)\
    do {\
        if (level <= LOGGER_CFG_LEVEL) {\
            if (level == LOGGER_FATAL_LEVEL) {\
                _log_fatal(__FILE__, __func__, __LINE__, ##arg);\
            }\
            if (level == LOGGER_ERROR_LEVEL) {\
                _log_error(__FILE__, __func__, __LINE__, ##arg);\
            }\
            if (level == LOGGER_WARN_LEVEL) {\
                _log_warn(__FILE__, __func__, __LINE__, ##arg);\
            }\
            if (level == LOGGER_INFO_LEVEL) {\
                _log_info(__FILE__, __func__, __LINE__, ##arg);\
            }\
            if (level == LOGGER_DEBUG_LEVEL) {\
                _log_debug(__FILE__, __func__, __LINE__, ##arg);\
            }\
        }\
    } while(0)

#define log_fatal(arg...)	logger_level_printf(LOGGER_FATAL_LEVEL, ##arg)
#define log_error(arg...)	logger_level_printf(LOGGER_ERROR_LEVEL, ##arg)
#define log_warn(arg...)	logger_level_printf(LOGGER_WARN_LEVEL, ##arg)
#define log_info(arg...)	logger_level_printf(LOGGER_INFO_LEVEL, ##arg)
#define log_debug(arg...)	logger_level_printf(LOGGER_DEBUG_LEVEL, ##arg)

#endif 
