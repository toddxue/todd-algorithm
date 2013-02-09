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
    
    enum {
        eX_MAX = 100,
        eY_MAX = 30,
    };
    
    char str[eY_MAX+1][eX_MAX+2];
    char fill_x, fill_y, fill_backslash;
    Draw(bool boundary=true, char fill_x = '.', char fill_y = '.', char fill_backslash = '\\') 
        : fill_x(fill_x)
        , fill_y(fill_y)
        , fill_backslash(fill_backslash)
    {
        memset(str, ' ', sizeof(str));

        for (int yy = 0; yy <= eY_MAX; ++yy)
            str[yy][eX_MAX+1] = '\n';

        if (boundary) {
            for (int yy = 0; yy <= eY_MAX; ++yy) {
                str[yy][0] = '|';
                str[yy][eX_MAX] = '|';
                str[yy][eX_MAX+1] = '\n';
            }
            for (int xx = 1; xx < eX_MAX; ++xx) {
                str[0][xx] = '-';
                str[eY_MAX][xx] = '-';
            }

            const char corner = 'o';
            str[0][0]   = corner;
            str[0][eX_MAX]  = corner;
            str[eY_MAX][eX_MAX] = corner;
            str[eY_MAX][0]  = corner;
        }
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
        double ratio = eY_MAX/eX_MAX*1.0;
        if (x2 > x) {
            double k = (y2-y)*1.0 / (x2-x);
            if (fabs(k) > ratio) line_to_y(x2, y2);
            else
            for (int xx = x; xx <= x2; ++xx) {
                int yy = int(round(y + k * (xx-x)));
                str[yy][xx] = fill_x;
            }
        }
        else if (x2 < x) {
            double k = (y2-y)*1.0 / (x2-x);
            if (fabs(k) > ratio) line_to_y(x2, y2);
            else
            for (int xx = x; xx >= x2; --xx) {
                int yy = int(round(y + k * (xx-x)));
                str[yy][xx] = fill_x;
            }
        }
        else {  // x2 == x
            if (y < y2) 
                for (int yy = y; yy <= y2; ++yy)
                    str[yy][x] = fill_y;
            else if (y > y2) 
                    for (int yy = y; yy >= y2; --yy)
                        str[yy][x] = fill_y;
            else
                str[y][x] = '.';
        }
        
        move_to(x2, y2);
    }

    void line_to_y(int x2, int y2) {
        if (y2 > y) {
            double k = (x2-x)*1.0 / (y2-y);
            for (int yy = y; yy <= y2; ++yy) {
                int xx = int(round(x + k * (yy-y)));
                str[yy][xx] = fill_backslash;
            }
        }
        else if (y2 < y) {
            double k = (x2-x)*1.0 / (y2-y);
            for (int yy = y; yy >= y2; --yy) {
                int xx = int(round(x + k * (yy-y)));
                str[yy][xx] = fill_y;
            }
        }
    }

    char& point(int xx, int yy) {
        return str[yy][xx];
    }

    void out(int xx, int yy, char const* text) {
        for (int i = xx; i < eX_MAX && *text; ++i) 
            str[yy][i] = *text++;
    }

    void out(int xx, int yy, int n) {
        char str[16];
        sprintf(str, "%d", n);
        out(xx, yy, str);
    }

    void out(int xx, int yy, char c) {
        str[yy][xx] = c;
    }

    void print() {
        printf("%.*s", int(sizeof(str)), (char const*)str);
    }

};

#endif
