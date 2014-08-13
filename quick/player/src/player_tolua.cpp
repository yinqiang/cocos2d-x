/*
** Lua binding: player_luabinding
** Generated automatically by tolua++-1.0.92 on Tue Aug 12 11:26:58 2014.
*/

#include "player_tolua.h"
#include "CCLuaEngine.h"

using namespace cocos2d;


/* Exported function */
TOLUA_API int  tolua_player_luabinding_open (lua_State* tolua_S);

#include <string>
#include <vector>
#include "PlayerProtocol.h"
#include "tolua++.h"
#include "tolua_fix.h"
using namespace std;
using namespace player;
#define CLASS_HASH_CODE(x) x.hash_code()

/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_PlayerSettings (lua_State* tolua_S)
{
 PlayerSettings* self = (PlayerSettings*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_std__vector_std__string_ (lua_State* tolua_S)
{
 std::vector<std::string>* self = (std::vector<std::string>*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}
#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"cocos2d::Ref");
 tolua_usertype(tolua_S,"PlayerSettings");
 tolua_usertype(tolua_S,"PlayerServiceProtocol");
 tolua_usertype(tolua_S,"PlayerMenuItem");
 tolua_usertype(tolua_S,"PlayerEditBoxServiceProtocol");
 tolua_usertype(tolua_S,"PlayerMenuServiceProtocol");
 tolua_usertype(tolua_S,"PlayerFileDialogServiceProtocol");
 tolua_usertype(tolua_S,"PlayerProtocol");
 tolua_usertype(tolua_S,"PlayerMessageBoxServiceProtocol");
 tolua_usertype(tolua_S,"std::vector<std::string>");
}

/* method: new of class  PlayerSettings */
#ifndef TOLUA_DISABLE_tolua_player_luabinding_PlayerSettings_new00
static int tolua_player_luabinding_PlayerSettings_new00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"PlayerSettings",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   PlayerSettings* tolua_ret = (PlayerSettings*)  Mtolua_new((PlayerSettings)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"PlayerSettings");
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  PlayerSettings */
#ifndef TOLUA_DISABLE_tolua_player_luabinding_PlayerSettings_new00_local
static int tolua_player_luabinding_PlayerSettings_new00_local(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"PlayerSettings",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   PlayerSettings* tolua_ret = (PlayerSettings*)  Mtolua_new((PlayerSettings)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"PlayerSettings");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: openLastProject of class  PlayerSettings */
#ifndef TOLUA_DISABLE_tolua_get_PlayerSettings_openLastProject
static int tolua_get_PlayerSettings_openLastProject(lua_State* tolua_S)
{
  PlayerSettings* self = (PlayerSettings*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'openLastProject'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->openLastProject);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: openLastProject of class  PlayerSettings */
#ifndef TOLUA_DISABLE_tolua_set_PlayerSettings_openLastProject
static int tolua_set_PlayerSettings_openLastProject(lua_State* tolua_S)
{
  PlayerSettings* self = (PlayerSettings*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'openLastProject'",NULL);
  if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->openLastProject = ((bool)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: offsetX of class  PlayerSettings */
#ifndef TOLUA_DISABLE_tolua_get_PlayerSettings_offsetX
static int tolua_get_PlayerSettings_offsetX(lua_State* tolua_S)
{
  PlayerSettings* self = (PlayerSettings*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'offsetX'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->offsetX);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: offsetX of class  PlayerSettings */
#ifndef TOLUA_DISABLE_tolua_set_PlayerSettings_offsetX
static int tolua_set_PlayerSettings_offsetX(lua_State* tolua_S)
{
  PlayerSettings* self = (PlayerSettings*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'offsetX'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->offsetX = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: offsetY of class  PlayerSettings */
#ifndef TOLUA_DISABLE_tolua_get_PlayerSettings_offsetY
static int tolua_get_PlayerSettings_offsetY(lua_State* tolua_S)
{
  PlayerSettings* self = (PlayerSettings*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'offsetY'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->offsetY);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: offsetY of class  PlayerSettings */
#ifndef TOLUA_DISABLE_tolua_set_PlayerSettings_offsetY
static int tolua_set_PlayerSettings_offsetY(lua_State* tolua_S)
{
  PlayerSettings* self = (PlayerSettings*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'offsetY'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->offsetY = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: getInstance of class  PlayerProtocol */
#ifndef TOLUA_DISABLE_tolua_player_luabinding_PlayerProtocol_getInstance00
static int tolua_player_luabinding_PlayerProtocol_getInstance00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"PlayerProtocol",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   PlayerProtocol* tolua_ret = (PlayerProtocol*)  PlayerProtocol::getInstance();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"PlayerProtocol");
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getInstance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: purgeInstance of class  PlayerProtocol */
#ifndef TOLUA_DISABLE_tolua_player_luabinding_PlayerProtocol_purgeInstance00
static int tolua_player_luabinding_PlayerProtocol_purgeInstance00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"PlayerProtocol",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   PlayerProtocol::purgeInstance();
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'purgeInstance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setPlayerSettings of class  PlayerProtocol */
#ifndef TOLUA_DISABLE_tolua_player_luabinding_PlayerProtocol_setPlayerSettings00
static int tolua_player_luabinding_PlayerProtocol_setPlayerSettings00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PlayerProtocol",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const PlayerSettings",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PlayerProtocol* self = (PlayerProtocol*)  tolua_tousertype(tolua_S,1,0);
  const PlayerSettings* settings = ((const PlayerSettings*)  tolua_tousertype(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setPlayerSettings'", NULL);
#endif
  {
   self->setPlayerSettings(*settings);
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setPlayerSettings'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getPlayerSettings of class  PlayerProtocol */
#ifndef TOLUA_DISABLE_tolua_player_luabinding_PlayerProtocol_getPlayerSettings00
static int tolua_player_luabinding_PlayerProtocol_getPlayerSettings00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const PlayerProtocol",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const PlayerProtocol* self = (const PlayerProtocol*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getPlayerSettings'", NULL);
#endif
  {
   PlayerSettings tolua_ret = (PlayerSettings)  self->getPlayerSettings();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((PlayerSettings)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"PlayerSettings");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(PlayerSettings));
     tolua_pushusertype(tolua_S,tolua_obj,"PlayerSettings");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getPlayerSettings'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getFileDialogService of class  PlayerProtocol */
#ifndef TOLUA_DISABLE_tolua_player_luabinding_PlayerProtocol_getFileDialogService00
static int tolua_player_luabinding_PlayerProtocol_getFileDialogService00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PlayerProtocol",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PlayerProtocol* self = (PlayerProtocol*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getFileDialogService'", NULL);
#endif
  {
   PlayerFileDialogServiceProtocol* tolua_ret = (PlayerFileDialogServiceProtocol*)  self->getFileDialogService();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"PlayerFileDialogServiceProtocol");
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getFileDialogService'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getMessageBoxService of class  PlayerProtocol */
#ifndef TOLUA_DISABLE_tolua_player_luabinding_PlayerProtocol_getMessageBoxService00
static int tolua_player_luabinding_PlayerProtocol_getMessageBoxService00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PlayerProtocol",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PlayerProtocol* self = (PlayerProtocol*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getMessageBoxService'", NULL);
#endif
  {
   PlayerMessageBoxServiceProtocol* tolua_ret = (PlayerMessageBoxServiceProtocol*)  self->getMessageBoxService();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"PlayerMessageBoxServiceProtocol");
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getMessageBoxService'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getMenuService of class  PlayerProtocol */
#ifndef TOLUA_DISABLE_tolua_player_luabinding_PlayerProtocol_getMenuService00
static int tolua_player_luabinding_PlayerProtocol_getMenuService00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PlayerProtocol",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PlayerProtocol* self = (PlayerProtocol*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getMenuService'", NULL);
#endif
  {
   PlayerMenuServiceProtocol* tolua_ret = (PlayerMenuServiceProtocol*)  self->getMenuService();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"PlayerMenuServiceProtocol");
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getMenuService'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getEditBoxService of class  PlayerProtocol */
#ifndef TOLUA_DISABLE_tolua_player_luabinding_PlayerProtocol_getEditBoxService00
static int tolua_player_luabinding_PlayerProtocol_getEditBoxService00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PlayerProtocol",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PlayerProtocol* self = (PlayerProtocol*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getEditBoxService'", NULL);
#endif
  {
   PlayerEditBoxServiceProtocol* tolua_ret = (PlayerEditBoxServiceProtocol*)  self->getEditBoxService();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"PlayerEditBoxServiceProtocol");
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getEditBoxService'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: openFile of class  PlayerFileDialogServiceProtocol */
#ifndef TOLUA_DISABLE_tolua_player_luabinding_PlayerFileDialogServiceProtocol_openFile00
static int tolua_player_luabinding_PlayerFileDialogServiceProtocol_openFile00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PlayerFileDialogServiceProtocol",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PlayerFileDialogServiceProtocol* self = (PlayerFileDialogServiceProtocol*)  tolua_tousertype(tolua_S,1,0);
  const std::string title = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  const std::string directory = ((const std::string)  tolua_tocppstring(tolua_S,3,0));
  const std::string extensions = ((const std::string)  tolua_tocppstring(tolua_S,4,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'openFile'", NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->openFile(title,directory,extensions);
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
   tolua_pushcppstring(tolua_S,(const char*)title);
   tolua_pushcppstring(tolua_S,(const char*)directory);
   tolua_pushcppstring(tolua_S,(const char*)extensions);
  }
 }
 return 4;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'openFile'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: openMultiple of class  PlayerFileDialogServiceProtocol */
#ifndef TOLUA_DISABLE_tolua_player_luabinding_PlayerFileDialogServiceProtocol_openMultiple00
static int tolua_player_luabinding_PlayerFileDialogServiceProtocol_openMultiple00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const PlayerFileDialogServiceProtocol",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const PlayerFileDialogServiceProtocol* self = (const PlayerFileDialogServiceProtocol*)  tolua_tousertype(tolua_S,1,0);
  const std::string title = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  const std::string directory = ((const std::string)  tolua_tocppstring(tolua_S,3,0));
  const std::string extensions = ((const std::string)  tolua_tocppstring(tolua_S,4,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'openMultiple'", NULL);
#endif
  {
   std::vector<std::string> tolua_ret = (std::vector<std::string>)  self->openMultiple(title,directory,extensions);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((std::vector<std::string>)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"std::vector<std::string>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(std::vector<std::string>));
     tolua_pushusertype(tolua_S,tolua_obj,"std::vector<std::string>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
   tolua_pushcppstring(tolua_S,(const char*)title);
   tolua_pushcppstring(tolua_S,(const char*)directory);
   tolua_pushcppstring(tolua_S,(const char*)extensions);
  }
 }
 return 4;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'openMultiple'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: saveFile of class  PlayerFileDialogServiceProtocol */
#ifndef TOLUA_DISABLE_tolua_player_luabinding_PlayerFileDialogServiceProtocol_saveFile00
static int tolua_player_luabinding_PlayerFileDialogServiceProtocol_saveFile00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PlayerFileDialogServiceProtocol",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PlayerFileDialogServiceProtocol* self = (PlayerFileDialogServiceProtocol*)  tolua_tousertype(tolua_S,1,0);
  const std::string title = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  const std::string path = ((const std::string)  tolua_tocppstring(tolua_S,3,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'saveFile'", NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->saveFile(title,path);
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
   tolua_pushcppstring(tolua_S,(const char*)title);
   tolua_pushcppstring(tolua_S,(const char*)path);
  }
 }
 return 3;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'saveFile'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: openDirectory of class  PlayerFileDialogServiceProtocol */
#ifndef TOLUA_DISABLE_tolua_player_luabinding_PlayerFileDialogServiceProtocol_openDirectory00
static int tolua_player_luabinding_PlayerFileDialogServiceProtocol_openDirectory00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PlayerFileDialogServiceProtocol",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PlayerFileDialogServiceProtocol* self = (PlayerFileDialogServiceProtocol*)  tolua_tousertype(tolua_S,1,0);
  const std::string title = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  const std::string directory = ((const std::string)  tolua_tocppstring(tolua_S,3,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'openDirectory'", NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->openDirectory(title,directory);
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
   tolua_pushcppstring(tolua_S,(const char*)title);
   tolua_pushcppstring(tolua_S,(const char*)directory);
  }
 }
 return 3;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'openDirectory'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getMenuId of class  PlayerMenuItem */
#ifndef TOLUA_DISABLE_tolua_player_luabinding_PlayerMenuItem_getMenuId00
static int tolua_player_luabinding_PlayerMenuItem_getMenuId00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const PlayerMenuItem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const PlayerMenuItem* self = (const PlayerMenuItem*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getMenuId'", NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->getMenuId();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getMenuId'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getTitle of class  PlayerMenuItem */
#ifndef TOLUA_DISABLE_tolua_player_luabinding_PlayerMenuItem_getTitle00
static int tolua_player_luabinding_PlayerMenuItem_getTitle00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const PlayerMenuItem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const PlayerMenuItem* self = (const PlayerMenuItem*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getTitle'", NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->getTitle();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getTitle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getOrder of class  PlayerMenuItem */
#ifndef TOLUA_DISABLE_tolua_player_luabinding_PlayerMenuItem_getOrder00
static int tolua_player_luabinding_PlayerMenuItem_getOrder00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const PlayerMenuItem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const PlayerMenuItem* self = (const PlayerMenuItem*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getOrder'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getOrder();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getOrder'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isGroup of class  PlayerMenuItem */
#ifndef TOLUA_DISABLE_tolua_player_luabinding_PlayerMenuItem_isGroup00
static int tolua_player_luabinding_PlayerMenuItem_isGroup00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const PlayerMenuItem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const PlayerMenuItem* self = (const PlayerMenuItem*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isGroup'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isGroup();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isGroup'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isEnabled of class  PlayerMenuItem */
#ifndef TOLUA_DISABLE_tolua_player_luabinding_PlayerMenuItem_isEnabled00
static int tolua_player_luabinding_PlayerMenuItem_isEnabled00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const PlayerMenuItem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const PlayerMenuItem* self = (const PlayerMenuItem*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isEnabled'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isEnabled();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isEnabled'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isChecked of class  PlayerMenuItem */
#ifndef TOLUA_DISABLE_tolua_player_luabinding_PlayerMenuItem_isChecked00
static int tolua_player_luabinding_PlayerMenuItem_isChecked00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const PlayerMenuItem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const PlayerMenuItem* self = (const PlayerMenuItem*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isChecked'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isChecked();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isChecked'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getShortcut of class  PlayerMenuItem */
#ifndef TOLUA_DISABLE_tolua_player_luabinding_PlayerMenuItem_getShortcut00
static int tolua_player_luabinding_PlayerMenuItem_getShortcut00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const PlayerMenuItem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const PlayerMenuItem* self = (const PlayerMenuItem*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getShortcut'", NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->getShortcut();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getShortcut'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setTitle of class  PlayerMenuItem */
#ifndef TOLUA_DISABLE_tolua_player_luabinding_PlayerMenuItem_setTitle00
static int tolua_player_luabinding_PlayerMenuItem_setTitle00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PlayerMenuItem",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PlayerMenuItem* self = (PlayerMenuItem*)  tolua_tousertype(tolua_S,1,0);
  const std::string title = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setTitle'", NULL);
#endif
  {
   self->setTitle(title);
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setTitle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setEnabled of class  PlayerMenuItem */
#ifndef TOLUA_DISABLE_tolua_player_luabinding_PlayerMenuItem_setEnabled00
static int tolua_player_luabinding_PlayerMenuItem_setEnabled00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PlayerMenuItem",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PlayerMenuItem* self = (PlayerMenuItem*)  tolua_tousertype(tolua_S,1,0);
  bool enabled = ((bool)  tolua_toboolean(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setEnabled'", NULL);
#endif
  {
   self->setEnabled(enabled);
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setEnabled'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setChecked of class  PlayerMenuItem */
#ifndef TOLUA_DISABLE_tolua_player_luabinding_PlayerMenuItem_setChecked00
static int tolua_player_luabinding_PlayerMenuItem_setChecked00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PlayerMenuItem",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PlayerMenuItem* self = (PlayerMenuItem*)  tolua_tousertype(tolua_S,1,0);
  bool checked = ((bool)  tolua_toboolean(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setChecked'", NULL);
#endif
  {
   self->setChecked(checked);
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setChecked'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setShortcut of class  PlayerMenuItem */
#ifndef TOLUA_DISABLE_tolua_player_luabinding_PlayerMenuItem_setShortcut00
static int tolua_player_luabinding_PlayerMenuItem_setShortcut00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PlayerMenuItem",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PlayerMenuItem* self = (PlayerMenuItem*)  tolua_tousertype(tolua_S,1,0);
  const std::string shortcut = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setShortcut'", NULL);
#endif
  {
   self->setShortcut(shortcut);
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setShortcut'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addItem of class  PlayerMenuServiceProtocol */
#ifndef TOLUA_DISABLE_tolua_player_luabinding_PlayerMenuServiceProtocol_addItem00
static int tolua_player_luabinding_PlayerMenuServiceProtocol_addItem00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PlayerMenuServiceProtocol",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PlayerMenuServiceProtocol* self = (PlayerMenuServiceProtocol*)  tolua_tousertype(tolua_S,1,0);
  const std::string menuId = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  const std::string title = ((const std::string)  tolua_tocppstring(tolua_S,3,0));
  const std::string parentId = ((const std::string)  tolua_tocppstring(tolua_S,4,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addItem'", NULL);
#endif
  {
   PlayerMenuItem* tolua_ret = (PlayerMenuItem*)  self->addItem(menuId,title,parentId);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"PlayerMenuItem");
   tolua_pushcppstring(tolua_S,(const char*)menuId);
   tolua_pushcppstring(tolua_S,(const char*)title);
   tolua_pushcppstring(tolua_S,(const char*)parentId);
  }
 }
 return 4;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addItem'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addItem of class  PlayerMenuServiceProtocol */
#ifndef TOLUA_DISABLE_tolua_player_luabinding_PlayerMenuServiceProtocol_addItem01
static int tolua_player_luabinding_PlayerMenuServiceProtocol_addItem01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PlayerMenuServiceProtocol",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  PlayerMenuServiceProtocol* self = (PlayerMenuServiceProtocol*)  tolua_tousertype(tolua_S,1,0);
  const std::string menuId = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  const std::string title = ((const std::string)  tolua_tocppstring(tolua_S,3,0));
  const std::string parentId = ((const std::string)  tolua_tocppstring(tolua_S,4,0));
  int order = ((int)  tolua_tonumber(tolua_S,5,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addItem'", NULL);
#endif
  {
   PlayerMenuItem* tolua_ret = (PlayerMenuItem*)  self->addItem(menuId,title,parentId,order);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"PlayerMenuItem");
   tolua_pushcppstring(tolua_S,(const char*)menuId);
   tolua_pushcppstring(tolua_S,(const char*)title);
   tolua_pushcppstring(tolua_S,(const char*)parentId);
  }
 }
 return 4;
tolua_lerror:
 return tolua_player_luabinding_PlayerMenuServiceProtocol_addItem00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: addItem of class  PlayerMenuServiceProtocol */
#ifndef TOLUA_DISABLE_tolua_player_luabinding_PlayerMenuServiceProtocol_addItem02
static int tolua_player_luabinding_PlayerMenuServiceProtocol_addItem02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PlayerMenuServiceProtocol",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  PlayerMenuServiceProtocol* self = (PlayerMenuServiceProtocol*)  tolua_tousertype(tolua_S,1,0);
  const std::string menuId = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  const std::string title = ((const std::string)  tolua_tocppstring(tolua_S,3,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addItem'", NULL);
#endif
  {
   PlayerMenuItem* tolua_ret = (PlayerMenuItem*)  self->addItem(menuId,title);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"PlayerMenuItem");
   tolua_pushcppstring(tolua_S,(const char*)menuId);
   tolua_pushcppstring(tolua_S,(const char*)title);
  }
 }
 return 3;
tolua_lerror:
 return tolua_player_luabinding_PlayerMenuServiceProtocol_addItem01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: getItem of class  PlayerMenuServiceProtocol */
#ifndef TOLUA_DISABLE_tolua_player_luabinding_PlayerMenuServiceProtocol_getItem00
static int tolua_player_luabinding_PlayerMenuServiceProtocol_getItem00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PlayerMenuServiceProtocol",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PlayerMenuServiceProtocol* self = (PlayerMenuServiceProtocol*)  tolua_tousertype(tolua_S,1,0);
  const std::string menuId = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getItem'", NULL);
#endif
  {
   PlayerMenuItem* tolua_ret = (PlayerMenuItem*)  self->getItem(menuId);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"PlayerMenuItem");
   tolua_pushcppstring(tolua_S,(const char*)menuId);
  }
 }
 return 2;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getItem'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeItem of class  PlayerMenuServiceProtocol */
#ifndef TOLUA_DISABLE_tolua_player_luabinding_PlayerMenuServiceProtocol_removeItem00
static int tolua_player_luabinding_PlayerMenuServiceProtocol_removeItem00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PlayerMenuServiceProtocol",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PlayerMenuServiceProtocol* self = (PlayerMenuServiceProtocol*)  tolua_tousertype(tolua_S,1,0);
  const std::string menuId = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeItem'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->removeItem(menuId);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
   tolua_pushcppstring(tolua_S,(const char*)menuId);
  }
 }
 return 2;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeItem'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: showMessageBox of class  PlayerMessageBoxServiceProtocol */
#ifndef TOLUA_DISABLE_tolua_player_luabinding_PlayerMessageBoxServiceProtocol_showMessageBox00
static int tolua_player_luabinding_PlayerMessageBoxServiceProtocol_showMessageBox00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PlayerMessageBoxServiceProtocol",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PlayerMessageBoxServiceProtocol* self = (PlayerMessageBoxServiceProtocol*)  tolua_tousertype(tolua_S,1,0);
  const std::string title = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  const std::string message = ((const std::string)  tolua_tocppstring(tolua_S,3,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'showMessageBox'", NULL);
#endif
  {
   int tolua_ret = (int)  self->showMessageBox(title,message);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
   tolua_pushcppstring(tolua_S,(const char*)title);
   tolua_pushcppstring(tolua_S,(const char*)message);
  }
 }
 return 3;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'showMessageBox'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: showMessageBox of class  PlayerMessageBoxServiceProtocol */
#ifndef TOLUA_DISABLE_tolua_player_luabinding_PlayerMessageBoxServiceProtocol_showMessageBox01
static int tolua_player_luabinding_PlayerMessageBoxServiceProtocol_showMessageBox01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PlayerMessageBoxServiceProtocol",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  PlayerMessageBoxServiceProtocol* self = (PlayerMessageBoxServiceProtocol*)  tolua_tousertype(tolua_S,1,0);
  const std::string title = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  const std::string message = ((const std::string)  tolua_tocppstring(tolua_S,3,0));
  int buttonsType = ((int)  tolua_tonumber(tolua_S,4,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'showMessageBox'", NULL);
#endif
  {
   int tolua_ret = (int)  self->showMessageBox(title,message,buttonsType);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
   tolua_pushcppstring(tolua_S,(const char*)title);
   tolua_pushcppstring(tolua_S,(const char*)message);
  }
 }
 return 3;
tolua_lerror:
 return tolua_player_luabinding_PlayerMessageBoxServiceProtocol_showMessageBox00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_player_luabinding_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"PlayerSettings","PlayerSettings","",tolua_collect_PlayerSettings);
  #else
  tolua_cclass(tolua_S,"PlayerSettings","PlayerSettings","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"PlayerSettings");
   tolua_function(tolua_S,"new",tolua_player_luabinding_PlayerSettings_new00);
   tolua_function(tolua_S,"new_local",tolua_player_luabinding_PlayerSettings_new00_local);
   tolua_function(tolua_S,".call",tolua_player_luabinding_PlayerSettings_new00_local);
   tolua_variable(tolua_S,"openLastProject",tolua_get_PlayerSettings_openLastProject,tolua_set_PlayerSettings_openLastProject);
   tolua_variable(tolua_S,"offsetX",tolua_get_PlayerSettings_offsetX,tolua_set_PlayerSettings_offsetX);
   tolua_variable(tolua_S,"offsetY",tolua_get_PlayerSettings_offsetY,tolua_set_PlayerSettings_offsetY);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"PlayerProtocol","PlayerProtocol","",NULL);
  tolua_beginmodule(tolua_S,"PlayerProtocol");
   tolua_function(tolua_S,"getInstance",tolua_player_luabinding_PlayerProtocol_getInstance00);
   tolua_function(tolua_S,"purgeInstance",tolua_player_luabinding_PlayerProtocol_purgeInstance00);
   tolua_function(tolua_S,"setPlayerSettings",tolua_player_luabinding_PlayerProtocol_setPlayerSettings00);
   tolua_function(tolua_S,"getPlayerSettings",tolua_player_luabinding_PlayerProtocol_getPlayerSettings00);
   tolua_function(tolua_S,"getFileDialogService",tolua_player_luabinding_PlayerProtocol_getFileDialogService00);
   tolua_function(tolua_S,"getMessageBoxService",tolua_player_luabinding_PlayerProtocol_getMessageBoxService00);
   tolua_function(tolua_S,"getMenuService",tolua_player_luabinding_PlayerProtocol_getMenuService00);
   tolua_function(tolua_S,"getEditBoxService",tolua_player_luabinding_PlayerProtocol_getEditBoxService00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"PlayerFileDialogServiceProtocol","PlayerFileDialogServiceProtocol","PlayerServiceProtocol",NULL);
  tolua_beginmodule(tolua_S,"PlayerFileDialogServiceProtocol");
   tolua_function(tolua_S,"openFile",tolua_player_luabinding_PlayerFileDialogServiceProtocol_openFile00);
   tolua_function(tolua_S,"openMultiple",tolua_player_luabinding_PlayerFileDialogServiceProtocol_openMultiple00);
   tolua_function(tolua_S,"saveFile",tolua_player_luabinding_PlayerFileDialogServiceProtocol_saveFile00);
   tolua_function(tolua_S,"openDirectory",tolua_player_luabinding_PlayerFileDialogServiceProtocol_openDirectory00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"PlayerMenuItem","PlayerMenuItem","cocos2d::Ref",NULL);
  tolua_beginmodule(tolua_S,"PlayerMenuItem");
   tolua_function(tolua_S,"getMenuId",tolua_player_luabinding_PlayerMenuItem_getMenuId00);
   tolua_function(tolua_S,"getTitle",tolua_player_luabinding_PlayerMenuItem_getTitle00);
   tolua_function(tolua_S,"getOrder",tolua_player_luabinding_PlayerMenuItem_getOrder00);
   tolua_function(tolua_S,"isGroup",tolua_player_luabinding_PlayerMenuItem_isGroup00);
   tolua_function(tolua_S,"isEnabled",tolua_player_luabinding_PlayerMenuItem_isEnabled00);
   tolua_function(tolua_S,"isChecked",tolua_player_luabinding_PlayerMenuItem_isChecked00);
   tolua_function(tolua_S,"getShortcut",tolua_player_luabinding_PlayerMenuItem_getShortcut00);
   tolua_function(tolua_S,"setTitle",tolua_player_luabinding_PlayerMenuItem_setTitle00);
   tolua_function(tolua_S,"setEnabled",tolua_player_luabinding_PlayerMenuItem_setEnabled00);
   tolua_function(tolua_S,"setChecked",tolua_player_luabinding_PlayerMenuItem_setChecked00);
   tolua_function(tolua_S,"setShortcut",tolua_player_luabinding_PlayerMenuItem_setShortcut00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"PlayerMenuServiceProtocol","PlayerMenuServiceProtocol","",NULL);
  tolua_beginmodule(tolua_S,"PlayerMenuServiceProtocol");
   tolua_function(tolua_S,"addItem",tolua_player_luabinding_PlayerMenuServiceProtocol_addItem00);
   tolua_function(tolua_S,"addItem",tolua_player_luabinding_PlayerMenuServiceProtocol_addItem01);
   tolua_function(tolua_S,"addItem",tolua_player_luabinding_PlayerMenuServiceProtocol_addItem02);
   tolua_function(tolua_S,"getItem",tolua_player_luabinding_PlayerMenuServiceProtocol_getItem00);
   tolua_function(tolua_S,"removeItem",tolua_player_luabinding_PlayerMenuServiceProtocol_removeItem00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"PlayerMessageBoxServiceProtocol","PlayerMessageBoxServiceProtocol","PlayerServiceProtocol",NULL);
  tolua_beginmodule(tolua_S,"PlayerMessageBoxServiceProtocol");
   tolua_function(tolua_S,"showMessageBox",tolua_player_luabinding_PlayerMessageBoxServiceProtocol_showMessageBox00);
   tolua_function(tolua_S,"showMessageBox",tolua_player_luabinding_PlayerMessageBoxServiceProtocol_showMessageBox01);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_player_luabinding (lua_State* tolua_S) {
 return tolua_player_luabinding_open(tolua_S);
};
#endif

