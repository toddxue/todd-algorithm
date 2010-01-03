#ifndef _timed_h
#define _timed_h

#include <stdio.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>
#include <limits.h>

struct ToddTime {

    float utime;
    float stime;
    float TIMED_MS(struct timeval& r) { return r.tv_sec*1000 + r.tv_usec/1000.0; }

    char* memory;

    char const* prompt;
    int output; // 1 means stdout, 2 means stderr
    bool enable;

    int& level() {
        static int _level = 0;
        return _level;
    }
    
    char* spaces() {
        static char _spaces[] = 
            "                                            "
            "                                            "
            "                                            "
            "                                            "
            "                                            "
            "                                            "
            "                                            "
            "                                            "
            "                                            "
            "                                            "
            "                                            "
            "                                            "
            "                                            "
            "                                            "
            ;
        return _spaces;
    }
    
    ToddTime(char const* prompt, int output, bool enable) 
        : prompt(prompt)
        , output(output)
        , enable(enable && (output == 1 || output == 2)) {
        
        if (enable) {
            if (output == 0)
                printf("%.*s~~Enter %s:\n", level(), spaces(), prompt);

            struct rusage ru;
            ::getrusage(RUSAGE_SELF, &ru);
            utime = TIMED_MS(ru.ru_utime);
            stime = TIMED_MS(ru.ru_stime);
            memory = (char*)::sbrk(0);

            level() += 3;
        }
        else { // useless of this, only to disable coverity warning
            utime = stime = 0;
            memory = 0; 
        }
    }

    ~ToddTime() {
        if (enable) {
            level() -= 3;

            struct rusage ru;
            ::getrusage(RUSAGE_SELF, &ru);
            utime = TIMED_MS(ru.ru_utime) - utime;
            stime = TIMED_MS(ru.ru_stime) - stime;

            FILE* stream = output == 1 ? stdout : stderr;
            ::fprintf(stream, 
                      "%.*s[%-20s] /user %10.5gms /sys %10.5gms /mem %10.5gM\n", 
                      level(), 
                      spaces(), 
                      prompt, 
                      utime, 
                      stime, double((char*)sbrk(0)-memory)/1000000
                );
        }
    }
};

#define TIMED_BLOCK_STDOUT(block, enable) ToddTime toddtime_##block(#block, 1, enable);
#define TIMED_BLOCK_STDERR(block, enable) ToddTime toddtime_##block(#block, 2, enable);

#endif
