#include "lua_cocos2dx_extension_filter_auto.hpp"
#include "cocos2dFilters.h"
#include "tolua_fix.h"
#include "LuaBasicConversions.h"



int lua_cocos2dx_extension_filter_Filter_draw(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::Filter* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Filter",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::Filter*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_filter_Filter_draw'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->draw();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "draw",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_filter_Filter_draw'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_filter_Filter_initSprite(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::Filter* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Filter",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::Filter*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_filter_Filter_initSprite'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::extension::FilteredSprite* arg0;

        ok &= luaval_to_object<cocos2d::extension::FilteredSprite>(tolua_S, 2, "cc.FilteredSprite",&arg0);
        if(!ok)
            return 0;
        cobj->initSprite(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "initSprite",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_filter_Filter_initSprite'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_filter_Filter_getProgram(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::Filter* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Filter",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::Filter*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_filter_Filter_getProgram'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cocos2d::GLProgram* ret = cobj->getProgram();
        object_to_luaval<cocos2d::GLProgram>(tolua_S, "cc.GLProgram",(cocos2d::GLProgram*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getProgram",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_filter_Filter_getProgram'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_filter_Filter_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::Filter* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj = new cocos2d::extension::Filter();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.Filter");
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "Filter",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_filter_Filter_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_extension_filter_Filter_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (Filter)");
    return 0;
}

int lua_register_cocos2dx_extension_filter_Filter(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.Filter");
    tolua_cclass(tolua_S,"Filter","cc.Filter","cc.Ref",nullptr);

    tolua_beginmodule(tolua_S,"Filter");
        tolua_function(tolua_S,"new",lua_cocos2dx_extension_filter_Filter_constructor);
        tolua_function(tolua_S,"draw",lua_cocos2dx_extension_filter_Filter_draw);
        tolua_function(tolua_S,"initSprite",lua_cocos2dx_extension_filter_Filter_initSprite);
        tolua_function(tolua_S,"getProgram",lua_cocos2dx_extension_filter_Filter_getProgram);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::extension::Filter).name();
    g_luaType[typeName] = "cc.Filter";
    g_typeCast["Filter"] = "cc.Filter";
    return 1;
}
TOLUA_API int register_all_cocos2dx_extension_filter(lua_State* tolua_S)
{
	tolua_open(tolua_S);
	
	tolua_module(tolua_S,"cc",0);
	tolua_beginmodule(tolua_S,"cc");

	lua_register_cocos2dx_extension_filter_Filter(tolua_S);

	tolua_endmodule(tolua_S);
	return 1;
}

