typedef enum {INFO. WARNING, FATAL} Levels;

int log_event(Levels I, const char *fmt, ...);

int set_logfile(const char *logfile_name);

void close_logfile(void);
