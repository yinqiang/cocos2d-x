/****************************************************************************
 Copyright (c) 2013-2014 Chukong Technologies Inc.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/
#include "lua_cocos2dx_deprecated.h"
#include "cocos2d.h"
#include "tolua_fix.h"
#include "LuaBasicConversions.h"
#include "LuaScriptHandlerMgr.h"
#include "CCLuaValue.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

#define deprecatedClassTip(className) CCLOG("%s will be not binded in lua,please use the lua's table instead",className)
#define deprecatedFunctionTip(oldFun,newFun) CCLOG("%s was deprecated please use %s instead ",oldFun, newFun)
static int tolua_Cocos2d_CCPoint_new00(lua_State* tolua_S)
{
    deprecatedClassTip("CCPoint");
    
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertable(tolua_S,1,"CCPoint",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        Point tolua_ret;
        point_to_luaval(tolua_S, tolua_ret);
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
    return 0;
#endif
}


static int tolua_Cocos2d_CCPoint_new00_local(lua_State* tolua_S)
{
    deprecatedClassTip("CCPoint");
    
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertable(tolua_S,1,"CCPoint",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        Point tolua_ret;
        point_to_luaval(tolua_S, tolua_ret);
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
    return 0;
#endif
}


static int tolua_Cocos2d_CCPoint_new01(lua_State* tolua_S)
{
    deprecatedClassTip("CCPoint");
    
    tolua_Error tolua_err;
    if (
        !tolua_isusertable(tolua_S,1,"CCPoint",0,&tolua_err) ||
        !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
        !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,4,&tolua_err)
        )
        goto tolua_lerror;
    else
    {
        float x = ((float)  tolua_tonumber(tolua_S,2,0));
        float y = ((float)  tolua_tonumber(tolua_S,3,0));
        Point tolua_ret(x,y);
        point_to_luaval(tolua_S, tolua_ret);
    }
    return 1;
tolua_lerror:
    return tolua_Cocos2d_CCPoint_new00(tolua_S);
}


static int tolua_Cocos2d_CCPoint_new01_local(lua_State* tolua_S)
{
    deprecatedClassTip("CCPoint");
    
    tolua_Error tolua_err;
    if (
        !tolua_isusertable(tolua_S,1,"CCPoint",0,&tolua_err) ||
        !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
        !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,4,&tolua_err)
        )
        goto tolua_lerror;
    else
    {
        float x = ((float)  tolua_tonumber(tolua_S,2,0));
        float y = ((float)  tolua_tonumber(tolua_S,3,0));
        Point tolua_ret(x,y);
        point_to_luaval(tolua_S, tolua_ret);
    }
    return 1;
tolua_lerror:
    return tolua_Cocos2d_CCPoint_new00_local(tolua_S);
}

static int tolua_collect_CCPoint (lua_State* tolua_S)
{
    Point* self = (Point*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int register_cocos2dx_deprecated_Point(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"CCPoint");
#ifdef __cplusplus
    tolua_cclass(tolua_S,"CCPoint","CCPoint","",tolua_collect_CCPoint);
#else
    tolua_cclass(tolua_S,"CCPoint","CCPoint","",NULL);
#endif
    tolua_beginmodule(tolua_S,"CCPoint");
        tolua_function(tolua_S,"new",tolua_Cocos2d_CCPoint_new00);
        tolua_function(tolua_S,"new_local",tolua_Cocos2d_CCPoint_new00_local);
        tolua_function(tolua_S,".call",tolua_Cocos2d_CCPoint_new00_local);
        tolua_function(tolua_S,"new",tolua_Cocos2d_CCPoint_new01);
        tolua_function(tolua_S,"new_local",tolua_Cocos2d_CCPoint_new01_local);
        tolua_function(tolua_S,".call",tolua_Cocos2d_CCPoint_new01_local);
    tolua_endmodule(tolua_S);
    
    return 1;
}

static int tolua_Cocos2d_CCRect_new00(lua_State* tolua_S)
{
    deprecatedClassTip("CCRect");
    
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertable(tolua_S,1,"CCRect",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        Rect tolua_ret;
        rect_to_luaval(tolua_S, tolua_ret);
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
    return 0;
#endif
}


static int tolua_Cocos2d_CCRect_new00_local(lua_State* tolua_S)
{
    deprecatedClassTip("CCRect");
    
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertable(tolua_S,1,"CCRect",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        Rect tolua_ret;
        rect_to_luaval(tolua_S, tolua_ret);
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
    return 0;
#endif
}

static int tolua_Cocos2d_CCRect_new01(lua_State* tolua_S)
{
    deprecatedClassTip("CCRect");
    
    tolua_Error tolua_err;
    if (
        !tolua_isusertable(tolua_S,1,"CCRect",0,&tolua_err) ||
        !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
        !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
        !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
        !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,6,&tolua_err)
        )
        goto tolua_lerror;
    else
    {
        float x = ((float)  tolua_tonumber(tolua_S,2,0));
        float y = ((float)  tolua_tonumber(tolua_S,3,0));
        float width = ((float)  tolua_tonumber(tolua_S,4,0));
        float height = ((float)  tolua_tonumber(tolua_S,5,0));
        Rect tolua_ret(x, y, width, height);
        rect_to_luaval(tolua_S, tolua_ret);
    }
    return 1;
tolua_lerror:
    return tolua_Cocos2d_CCRect_new00(tolua_S);
}


static int tolua_Cocos2d_CCRect_new01_local(lua_State* tolua_S)
{
    deprecatedClassTip("CCRect");
    
    tolua_Error tolua_err;
    if (
        !tolua_isusertable(tolua_S,1,"CCRect",0,&tolua_err) ||
        !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
        !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
        !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
        !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,6,&tolua_err)
        )
        goto tolua_lerror;
    else
    {
        float x = ((float)  tolua_tonumber(tolua_S,2,0));
        float y = ((float)  tolua_tonumber(tolua_S,3,0));
        float width = ((float)  tolua_tonumber(tolua_S,4,0));
        float height = ((float)  tolua_tonumber(tolua_S,5,0));
        Rect tolua_ret(x, y, width, height);
        rect_to_luaval(tolua_S, tolua_ret);
    }
    return 1;
tolua_lerror:
    return tolua_Cocos2d_CCRect_new00_local(tolua_S);
}

static int register_cocos2dx_deprecated_Rect(lua_State* tolua_S)
{
    
    tolua_usertype(tolua_S,"CCRect");
    tolua_cclass(tolua_S,"CCRect","CCRect","",NULL);
    tolua_beginmodule(tolua_S,"CCRect");
        tolua_function(tolua_S,"new",tolua_Cocos2d_CCRect_new00);
        tolua_function(tolua_S,"new_local",tolua_Cocos2d_CCRect_new00_local);
        tolua_function(tolua_S,".call",tolua_Cocos2d_CCRect_new00_local);
        tolua_function(tolua_S,"new",tolua_Cocos2d_CCRect_new01);
        tolua_function(tolua_S,"new_local",tolua_Cocos2d_CCRect_new01_local);
        tolua_function(tolua_S,".call",tolua_Cocos2d_CCRect_new01_local);
    tolua_endmodule(tolua_S);
    
    return 1;
}

static int tolua_Cocos2d_CCSize_new00(lua_State* tolua_S)
{
    deprecatedClassTip("CCSize");
    
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertable(tolua_S,1,"CCSize",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        Size tolua_ret;
        size_to_luaval(tolua_S, tolua_ret);
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
    return 0;
#endif
}


static int tolua_Cocos2d_CCSize_new00_local(lua_State* tolua_S)
{
    deprecatedClassTip("CCSize");
    
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertable(tolua_S,1,"CCSize",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        Size tolua_ret;
        size_to_luaval(tolua_S, tolua_ret);
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
    return 0;
#endif
}


static int tolua_Cocos2d_CCSize_new01(lua_State* tolua_S)
{
    deprecatedClassTip("CCSize");
    
    tolua_Error tolua_err;
    if (
        !tolua_isusertable(tolua_S,1,"CCSize",0,&tolua_err) ||
        !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
        !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,4,&tolua_err)
        )
        goto tolua_lerror;
    else
    {
        float width = ((float)  tolua_tonumber(tolua_S,2,0));
        float height = ((float)  tolua_tonumber(tolua_S,3,0));
        Size tolua_ret(width, height);
        size_to_luaval(tolua_S, tolua_ret);
    }
    return 1;
tolua_lerror:
    return tolua_Cocos2d_CCSize_new00(tolua_S);
}



static int tolua_Cocos2d_CCSize_new01_local(lua_State* tolua_S)
{
    
    deprecatedClassTip("CCSize");
    
    tolua_Error tolua_err;
    if (
        !tolua_isusertable(tolua_S,1,"CCSize",0,&tolua_err) ||
        !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
        !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,4,&tolua_err)
        )
        goto tolua_lerror;
    else
    {
        float width = ((float)  tolua_tonumber(tolua_S,2,0));
        float height = ((float)  tolua_tonumber(tolua_S,3,0));
        Size tolua_ret(width, height);
        size_to_luaval(tolua_S, tolua_ret);
    }
    return 1;
tolua_lerror:
    return tolua_Cocos2d_CCSize_new00_local(tolua_S);
}


static int register_cocos2dx_deprecated_Size(lua_State* tolua_S)
{
    
    tolua_usertype(tolua_S,"CCSize");
    tolua_cclass(tolua_S,"CCSize","CCSize","",NULL);
    tolua_beginmodule(tolua_S,"CCSize");
        tolua_function(tolua_S,"new",tolua_Cocos2d_CCSize_new00);
        tolua_function(tolua_S,"new_local",tolua_Cocos2d_CCSize_new00_local);
        tolua_function(tolua_S,".call",tolua_Cocos2d_CCSize_new00_local);
        tolua_function(tolua_S,"new",tolua_Cocos2d_CCSize_new01);
        tolua_function(tolua_S,"new_local",tolua_Cocos2d_CCSize_new01_local);
        tolua_function(tolua_S,".call",tolua_Cocos2d_CCSize_new01_local);
    tolua_endmodule(tolua_S);
    
    return 1;
}

#if 0
static int tolua_cocos2d_kmGLPushMatrix00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnoobj(tolua_S,1,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        glPushMatrix();
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'kmGLPushMatrix'.",&tolua_err);
    return 0;
#endif
}

static int tolua_cocos2d_kmGLTranslatef00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
        !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
        !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,4,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        float x = ((float)  tolua_tonumber(tolua_S,1,0));
        float y = ((float)  tolua_tonumber(tolua_S,2,0));
        float z = ((float)  tolua_tonumber(tolua_S,3,0));
        {
            glTranslatef(x,y,z);
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'kmGLTranslatef'.",&tolua_err);
    return 0;
#endif
}

static int tolua_cocos2d_kmGLPopMatrix00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnoobj(tolua_S,1,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        {
           glPopMatrix();
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'kmGLPopMatrix'.",&tolua_err);
    return 0;
#endif
}

static int tolua_cocos2d_kmGLLoadMatrix00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!tolua_istable(tolua_S, 1, 0, &tolua_err)||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        Mat4 mat4;
        size_t len = lua_objlen(tolua_S, 1);
        for (int i = 0; i < len; i++)
        {
            lua_pushnumber(tolua_S,i + 1);
            lua_gettable(tolua_S,1);
#ifndef TOLUA_RELEASE
            if (!tolua_isnumber(tolua_S, -1, 0, &tolua_err))
            {
                lua_pop(tolua_S, 1);
                goto tolua_lerror;
            }
            else
#endif
            {
                mat4.m[i] = tolua_tonumber(tolua_S, -1, 0);
                lua_pop(tolua_S, 1);
            }
        }
        kmGLLoadMatrix(&mat4);
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'kmGLLoadMatrix'.",&tolua_err);
    return 0;
#endif
}
#endif //0

int register_all_cocos2dx_deprecated(lua_State* tolua_S)
{
    tolua_open(tolua_S);
    
    tolua_module(tolua_S,NULL,0);
    tolua_beginmodule(tolua_S,NULL);
    register_cocos2dx_deprecated_Point(tolua_S);
    register_cocos2dx_deprecated_Rect(tolua_S);
    register_cocos2dx_deprecated_Size(tolua_S);
//    register_cocos2dx_deprecated_String(tolua_S);
//    tolua_function(tolua_S,"kmGLPushMatrix",tolua_cocos2d_kmGLPushMatrix00);
//    tolua_function(tolua_S,"kmGLTranslatef",tolua_cocos2d_kmGLTranslatef00);
//    tolua_function(tolua_S,"kmGLPopMatrix",tolua_cocos2d_kmGLPopMatrix00);
//    tolua_function(tolua_S,"kmGLLoadMatrix",tolua_cocos2d_kmGLLoadMatrix00);
    tolua_endmodule(tolua_S);
    
    return 0;
}

extern int lua_cocos2dx_Animation_createWithSpriteFrames(lua_State* tolua_S);

static int tolua_cocos2d_Animation_createWithSpriteFrames_deprecated00(lua_State* tolua_S)
{
    tolua_Error tolua_err;
    if (
        !tolua_isusertable(tolua_S,1,"Animation",0,&tolua_err) ||
        !tolua_istable(tolua_S,2,0,&tolua_err) ||
        !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,4,&tolua_err)
        )
        goto tolua_lerror;
    else
    {
        Vector<SpriteFrame*> vec;
        luaval_to_ccvector(tolua_S, 2, &vec);
        float delay = ((float)  tolua_tonumber(tolua_S,3,0));
        cocos2d::Animation* tolua_ret = (cocos2d::Animation*)  cocos2d::Animation::createWithSpriteFrames(vec,delay);
        int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
        int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
        toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"cc.Animation");
    
    }
    return 1;
tolua_lerror:
    return lua_cocos2dx_Animation_createWithSpriteFrames(tolua_S);
}

static int tolua_cocos2d_Animation_createWithSpriteFrames_deprecated01(lua_State* tolua_S)
{
    tolua_Error tolua_err;
    if (
        !tolua_isusertable(tolua_S,1,"Animation",0,&tolua_err) ||
        !tolua_istable(tolua_S,2,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
    {
        Vector<SpriteFrame*> vec;
        luaval_to_ccvector(tolua_S, 2, &vec);
        cocos2d::Animation* tolua_ret = (cocos2d::Animation*)  cocos2d::Animation::createWithSpriteFrames(vec);
        int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
        int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
        toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"cc.Animation");
        
    }
    return 1;
tolua_lerror:
    return tolua_cocos2d_Animation_createWithSpriteFrames_deprecated00(tolua_S);
}

static void extendAnimationDeprecated(lua_State* tolua_S)
{
    lua_pushstring(tolua_S,"Animation");
    lua_rawget(tolua_S,LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        lua_pushstring(tolua_S,"createWithSpriteFrames");
        lua_pushcfunction(tolua_S,tolua_cocos2d_Animation_createWithSpriteFrames_deprecated00);
        lua_rawset(tolua_S,-3);
        lua_pushstring(tolua_S,"createWithSpriteFrames");
        lua_pushcfunction(tolua_S,tolua_cocos2d_Animation_createWithSpriteFrames_deprecated01);
        lua_rawset(tolua_S,-3);
    }
    lua_pop(tolua_S, 1);
}

static int tolua_cocos2d_Sequence_createWithTwoActions(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertable(tolua_S,1,"Sequence",0,&tolua_err) ||
        !tolua_isusertype(tolua_S,2,"FiniteTimeAction",0,&tolua_err) ||
        !tolua_isusertype(tolua_S,3,"FiniteTimeAction",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,4,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        FiniteTimeAction* pActionOne = ((FiniteTimeAction*)  tolua_tousertype(tolua_S,2,0));
        FiniteTimeAction* pActionTwo = ((FiniteTimeAction*)  tolua_tousertype(tolua_S,3,0));
        {
            Sequence* tolua_ret = (Sequence*)  Sequence::createWithTwoActions(pActionOne,pActionTwo);
            int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
            int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
            toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"cc.Sequence");
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'createWithTwoActions'.",&tolua_err);
    return 0;
#endif
}

extern int tolua_cocos2d_Sequence_create(lua_State* tolua_S);
static int tolua_Cocos2d_Sequence_create_deprecated00(lua_State* tolua_S)
{
    tolua_Error tolua_err;
    if (
        !tolua_isusertable(tolua_S,1,"Sequence",0,&tolua_err) ||
        !tolua_istable(tolua_S,2,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
    {
        Vector<FiniteTimeAction*> vec;
        luaval_to_ccvector(tolua_S, 2, &vec);
        Sequence* tolua_ret = (Sequence*)  Sequence::create(vec);
        int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
        int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
        toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"cc.Sequence");
    }
    return 1;
tolua_lerror:
    return tolua_cocos2d_Sequence_create(tolua_S);
}

static int extendSequenceDeprecated(lua_State* tolua_S)
{
    lua_pushstring(tolua_S,"Sequence");
    lua_rawget(tolua_S,LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        tolua_function(tolua_S, "createWithTwoActions",tolua_cocos2d_Sequence_createWithTwoActions);
        tolua_function(tolua_S, "create", tolua_Cocos2d_Sequence_create_deprecated00);
    }
    lua_pop(tolua_S, 1);
    
    return 1;
}

#ifdef __cplusplus
extern "C" {
#endif
extern int tolua_bnd_cast(lua_State* tolua_S);
#ifdef __cplusplus
}
#endif

static int tolua_bnd_cast_deprecated00(lua_State* tolua_S)
{
    void* v = nullptr;
    std::string strValue = "";
    strValue = tolua_tostring(tolua_S,2,NULL);
    size_t pos = strValue.find("CC");
    if (pos == 0 &&
        std::string::npos == strValue.find("CCBAnimationManager") &&
        std::string::npos == strValue.find("CCString") &&
        std::string::npos == strValue.find("CCPoint") &&
        std::string::npos == strValue.find("CCRect") &&
        std::string::npos == strValue.find("CCSize") &&
        std::string::npos == strValue.find("CCArray"))
    {
        strValue = strValue.substr(2);
        if (lua_islightuserdata(tolua_S, 1)) {
            v = tolua_touserdata(tolua_S, 1, NULL);
        } else {
            v = tolua_tousertype(tolua_S, 1, 0);
        };
        if (v && !strValue.empty())
            tolua_pushusertype(tolua_S,v,strValue.c_str());
        else
            lua_pushnil(tolua_S);
        return 1;        
    }
    else
    {
        std::string castName = tolua_tostring(tolua_S,2,NULL);
        auto iter = g_typeCast.find(castName);
        if (iter != g_typeCast.end() )
        {
            CCLOG("Cast name %s doesn't include modular name which it belongs to,please add the modular name",iter->first.c_str());
            tolua_pushstring(tolua_S, iter->second.c_str());
            lua_insert(tolua_S, 2);
            lua_pop(tolua_S, 1);
        }
        return tolua_bnd_cast(tolua_S);
    }
}

static int extendToluaDeprecated(lua_State* tolua_S)
{
    lua_getglobal(tolua_S, "_G");
    if (lua_istable(tolua_S,-1))//stack:...,_G,
    {
        lua_pushstring(tolua_S,"tolua");//stack:_G,keyValue
        lua_gettable(tolua_S, -2);//stack:_G,toluaModule
        if (lua_istable(tolua_S,-1))
        {
            tolua_function(tolua_S, "cast", tolua_bnd_cast_deprecated00);
        }
        lua_pop(tolua_S, 1);//statck:_G
    }
    lua_pop(tolua_S, 1);//statck:...
    
    return 1;
}

static int tolua_cocos2d_Spawn_createWithTwoActions_deprcated00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertable(tolua_S,1,"Spawn",0,&tolua_err) ||
        !tolua_isusertype(tolua_S,2,"FiniteTimeAction",0,&tolua_err) ||
        !tolua_isusertype(tolua_S,3,"FiniteTimeAction",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,4,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        FiniteTimeAction* pAction1 = ((FiniteTimeAction*)  tolua_tousertype(tolua_S,2,0));
        FiniteTimeAction* pAction2 = ((FiniteTimeAction*)  tolua_tousertype(tolua_S,3,0));
        {
            Spawn* tolua_ret = (Spawn*)  Spawn::createWithTwoActions(pAction1,pAction2);
            int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
            int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
            toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"cc.Spawn");
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'createWithTwoActions'.",&tolua_err);
    return 0;
#endif
}

static int extendSpawnDeprecated(lua_State* tolua_S)
{
    lua_pushstring(tolua_S,"Spawn");
    lua_rawget(tolua_S,LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        tolua_function(tolua_S, "createWithTwoActions", tolua_cocos2d_Spawn_createWithTwoActions_deprcated00);
    }
    lua_pop(tolua_S, 1);
    return 1;
}


static int tolua_cocos2d_Menu_createWithArray00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertable(tolua_S,1,"Menu",0,&tolua_err) ||
        !tolua_istable(tolua_S,2,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        Vector<MenuItem*> vec;
        luaval_to_ccvector(tolua_S, 2, &vec);
        Menu* tolua_ret = (Menu*)  Menu::createWithArray(vec);
        int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
        int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
        toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"cc.Menu");
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'createWithArray'.",&tolua_err);
    return 0;
#endif
}

static int tolua_cocos2d_Menu_alignItemsInColumnsWithArray00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"Menu",0,&tolua_err) ||
        !tolua_istable(tolua_S,2,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        Menu* self = (Menu*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'alignItemsInColumnsWithArray'", NULL);
#endif
        ValueVector valueVector;
        luaval_to_ccvaluevector(tolua_S, 2, &valueVector);
        self->alignItemsInColumnsWithArray(valueVector);
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'alignItemsInColumnsWithArray'.",&tolua_err);
    return 0;
#endif
}


static int tolua_cocos2d_Menu_alignItemsInRowsWithArray00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"Menu",0,&tolua_err) ||
        !tolua_istable(tolua_S,2,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        Menu* self = (Menu*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'alignItemsInRowsWithArray'", NULL);
#endif
        ValueVector valueVector;
        luaval_to_ccvaluevector(tolua_S, 2, &valueVector);
        self->alignItemsInRowsWithArray(valueVector);
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'alignItemsInRowsWithArray'.",&tolua_err);
    return 0;
#endif
}

static int extendMenuDeprecated(lua_State* tolua_S)
{
    lua_pushstring(tolua_S,"Menu");
    lua_rawget(tolua_S,LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        tolua_function(tolua_S, "createWithArray", tolua_cocos2d_Menu_createWithArray00);
        tolua_function(tolua_S, "alignItemsInColumnsWithArray", tolua_cocos2d_Menu_alignItemsInColumnsWithArray00);
        tolua_function(tolua_S, "alignItemsInRowsWithArray", tolua_cocos2d_Menu_alignItemsInRowsWithArray00);
    }
    lua_pop(tolua_S, 1);
    return 1;
}

static int tolua_cocos2d_LayerMultiplex_createWithArray00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertable(tolua_S,1,"LayerMultiplex",0,&tolua_err) ||
        !tolua_istable(tolua_S,2,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        Vector<Layer*> vec;
        luaval_to_ccvector(tolua_S, 2, &vec);
        LayerMultiplex* tolua_ret = (LayerMultiplex*)  LayerMultiplex::createWithArray(vec);
        int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
        int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
        toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"cc.LayerMultiplex");
        
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'createWithArray'.",&tolua_err);
    return 0;
#endif
}

static int extendLayerMultiplexDeprecated(lua_State* tolua_S)
{
    lua_pushstring(tolua_S,"LayerMultiplex");
    lua_rawget(tolua_S,LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        tolua_function(tolua_S, "createWithArray", tolua_cocos2d_LayerMultiplex_createWithArray00);
    }
    lua_pop(tolua_S, 1);
    return 1;
}


int register_all_cocos2dx_manual_deprecated(lua_State* tolua_S)
{
    if (NULL == tolua_S)
        return 0;
    
    extendAnimationDeprecated(tolua_S);
    extendSequenceDeprecated(tolua_S);
    extendToluaDeprecated(tolua_S);
    extendMenuDeprecated(tolua_S);
    extendLayerMultiplexDeprecated(tolua_S);
    return 0;
}
