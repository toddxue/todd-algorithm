/*
 * draw.h --
 *
 * draw data structures and misc routines
 *
 * 2010/01/12: initial release by Todd Xue
 */

#ifndef _draw_h
#define _draw_h

#include <stdio.h>
#include <string.h>
#include <math.h>

struct Draw {
    char str[30][81];
    char fill;
    Draw() {
        memset(str, ' ', sizeof(str));
        for (int yy = 0; yy < 30; ++yy)
            str[yy][80] = '\n';
        fill = '.';
    }

    int x;
    int y;

    void move_to(int x2, int y2) {
        x = x2;
        y = y2;
    }

    /*
     *-------------------------------------------------------------------------
     *
     * line_to --
     *
     *-------------------------------------------------------------------------
     */
    void line_to(int x2, int y2) {
        double ratio = 10.0/80.0;
        if (x2 > x) {
            double k = (y2-y)*1.0 / (x2-x);
            if (fabs(k) > ratio) line_to_y(x2, y2);
            else
            for (int xx = x; xx <= x2; ++xx) {
                int yy = int(round(y + k * (xx-x)));
                str[yy][xx] = fill;
            }
        }
        else if (x2 < x) {
            double k = (y2-y)*1.0 / (x2-x);
            if (fabs(k) > ratio) line_to_y(x2, y2);
            else
            for (int xx = x; xx >= x2; --xx) {
                int yy = int(round(y + k * (xx-x)));
                str[yy][xx] = fill;
            }
        }
        else {  // x2 == x
            if (y < y2) 
                for (int yy = y; yy <= y2; ++yy)
                    str[yy][x] = fill;
            else if (y > y2) 
                    for (int yy = y; yy >= y2; --yy)
                        str[yy][x] = fill;
            else
                str[y][x] = fill;
        }
        
        move_to(x2, y2);
    }

    void line_to_y(int x2, int y2) {
        if (y2 > y) {
            double k = (x2-x)*1.0 / (y2-y);
            for (int yy = y; yy <= y2; ++yy) {
                int xx = int(round(x + k * (yy-y)));
                str[yy][xx] = fill;
            }
        }
        else if (y2 < y) {
            double k = (x2-x)*1.0 / (y2-y);
            for (int yy = y; yy >= y2; --yy) {
                int xx = int(round(x + k * (yy-y)));
                str[yy][xx] = fill;
            }
        }
    }

    
    char& point(int xx, int yy) {
        return str[yy][xx];
    }

    void print() {
        printf("%.*s", sizeof(str), str);
    }

};

#endif
