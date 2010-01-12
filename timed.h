#ifndef _timed_h
#define _timed_h

#include <stdio.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>
#include <limits.h>

extern size_t* g_xmem_pmalloced_size;

struct ToddTime {

    float utime;
    float stime;
    float TIMED_MS(struct timeval& r) { return r.tv_sec*1000 + r.tv_usec/1000.0; }

    size_t xmem_malloced_size;

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
            xmem_malloced_size = *g_xmem_pmalloced_size;

            level() += 3;
        }
        else { // useless of this, only to disable coverity warning
            utime = stime = 0;
            xmem_malloced_size = 0;
        }
    }

    ~ToddTime() {
        if (enable) {
            level() -= 3;
            struct rusage ru;
            ::getrusage(RUSAGE_SELF, &ru);
            utime = TIMED_MS(ru.ru_utime) - utime;
            stime = TIMED_MS(ru.ru_stime) - stime;

            char* curr = (char*)::sbrk(0);
            FILE* stream = output == 1 ? stdout : stderr;
            ::fprintf(stream, 
                      "%.*s[%-20s] %10.5gms/user %10.5gms/sys %10u bytes/mem\n", 
                      level(), 
                      spaces(), 
                      prompt, 
                      utime, 
                      stime, 
                      (*g_xmem_pmalloced_size-xmem_malloced_size)
                );
        }
    }
};

struct ToddTimeClock {

    char const* prompt;
    int output; // 1 means stdout, 2 means stderr
    bool enable;
    clock_t ticks;
    size_t xmem_malloced_size;

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
    ToddTimeClock(char const* prompt, int output, bool enable) 
        : prompt(prompt)
        , output(output)
        , enable(enable && (output == 1 || output == 2)) {
        
        if (enable) {
            if (output == 0)
                printf("%.*s~~Enter %s:\n", level(), spaces(), prompt);
            level() += 3;
            xmem_malloced_size = *g_xmem_pmalloced_size;
            ticks = clock();
        }
    }

    ~ToddTimeClock() {
        if (enable) {
            ticks = clock() - ticks;
            level() -= 3;
            FILE* stream = output == 1 ? stdout : stderr;
            ::fprintf(stream, 
                      "%.*s[%-20s] %g ms/clock %du bytes/mem\n",
                      level(), 
                      spaces(), 
                      prompt,
                      double(ticks)*1000/CLOCKS_PER_SEC,
                      (*g_xmem_pmalloced_size-xmem_malloced_size)
                );
        }
    }
};

#if defined(__CYGWIN__)

#define TIMED_BLOCK_STDOUT(block, enable) ToddTimeClock toddtime_##block(#block, 1, enable);
#define TIMED_BLOCK_STDERR(block, enable) ToddTimeClock toddtime_##block(#block, 2, enable);

#else

#define TIMED_BLOCK_STDOUT(block, enable) ToddTime toddtime_##block(#block, 1, enable);
#define TIMED_BLOCK_STDERR(block, enable) ToddTime toddtime_##block(#block, 2, enable);

#endif

#endif
