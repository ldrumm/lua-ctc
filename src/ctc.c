#include <lua.h>
#include <lauxlib.h>
#include <stdlib.h>


static int constant_time_memeq(const void *s1, const void *s2, size_t len)
{
    // If x == y i.e. pointer aliases, then there maybe additional timing
    // issues introduced due to the effects of cache locality. We don't guard against
    // that case;  Crypto is hard.
    const unsigned char *x = s1;
    const unsigned char *y = s2;
    int result = 0;
    for(size_t i = 0; i < len; i++)
        result |= x[i] ^ y[i];
    return result == 0;
}

static int lconstant_time_memeq(lua_State *L)
{
    size_t len_x;
    size_t len_y;
    if(lua_gettop(L) != 2){
        return luaL_error("ctc requires exactly two arguments");
    }
    const char * x = lua_tolstring(L, 1, &len_x);
    const char * y = lua_tolstring(L, 2, &len_y);

    int len_neq = (len_x != len_y);
    size_t min = len_y ^ ((len_x ^ len_y) & -(len_x < len_y));

    lua_pushboolean(L, !(constant_time_memeq(x, y, min) | len_neq));
    return 1;
}


LUA_API int luaopen_ctc(lua_State *L)
{
    lua_pushcfunction(L, lconstant_time_memeq);
    return 1;
}
