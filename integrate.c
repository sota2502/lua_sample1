#include <stdio.h>
#include <stdlib.h>
#include "include/lualib.h"
#include "include/lauxlib.h"

#define DIVISION_COUNT   1000

int main (int argc, char* argv[]) {
    lua_State *L = luaL_newstate();
    if ( argc < 4 ) {
        printf("usage: integrate start end calc.lua\n");
        return 1;
    }

    double start      = atof(argv[1]);
    double end        = atof(argv[2]);
    if ( start >= end ) {
        printf("end should be larger than start");
        return 1;
    }

    char* lua_file = argv[3];
    double width   = (end - start) / (double)DIVISION_COUNT;
    double delta   = width / 2.0;

    printf("DIVISION_COUNT       : %d\n", DIVISION_COUNT);
    printf("integration interval : %f -> %f\n", start, end );
    printf("width                : %f\n", width);
    printf("delta                : %f\n", delta);
    printf("calc                 : %s\n", lua_file);

    luaL_openlibs(L);
    (void)luaL_dofile(L, lua_file);

    double sum;
    double x;
    for( x = start + delta; x < end; x += width ) {
        lua_getglobal(L, "calc");

        lua_pushnumber(L, x);
        lua_call(L, 1, 1);

        double y = lua_tonumber(L, -1);
        sum += y * width;
    }

    printf("%f\n", sum);

    lua_close(L);

    return 0;
}
