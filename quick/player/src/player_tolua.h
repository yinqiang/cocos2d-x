
#ifndef __PLAYER_TOLUA_H_
#define __PLAYER_TOLUA_H_

extern "C" {
#include "lua.h"
#include "tolua++.h"
#include "tolua_fix.h"
}

TOLUA_API int luaopen_player_luabinding(lua_State* tolua_S);

#endif // __PLAYER_TOLUA_H_
