--[[
    file: player.lua

    player 的 lua 核心
]]

--
-- 返回 table 的字符串
--

local function table_print (tt, indent, done)
  done = done or {}
  indent = indent or 0
  if type(tt) == "table" then
    local sb = {}
    for key, value in pairs (tt) do
      table.insert(sb, string.rep (" ", indent)) -- indent it
      if type (value) == "table" and not done [value] then
        done [value] = true

        if "string" == type(key) then
            table.insert(sb, string.format("%s ={\n", tostring(key)));
        else
            table.insert(sb, "{\n");    
        end

        table.insert(sb, table_print (value, indent + 2, done))
        table.insert(sb, string.rep (" ", indent)) -- indent it
        table.insert(sb, "},\n");
      elseif type(value) == "function" then

      elseif "number" == type(key) then
        table.insert(sb, string.format("\"%s\",\n", tostring(value)))
      elseif type (value) == "number" then
                table.insert(sb, string.format(
            "%s = %s,\n", tostring (key), tostring(value)))

      elseif type (value) == "string" then
                table.insert(sb, string.format(
            "%s = \"%s\",\n", tostring (key), tostring(value)))

      elseif type (value) == "boolean" then
                table.insert(sb, string.format(
            "%s = %s,\n", tostring (key), tostring(value)))
      -- else
      --   table.insert(sb, string.format(
      --       "%s = \"%s\",\n", tostring (key), tostring(value)))
       end
    end
    return table.concat(sb)
  else
    return tt .. "\n"
  end
end

local function to_string( tbl )
    if  "nil"       == type( tbl ) then
        return tostring(nil)
    elseif  "table" == type( tbl ) then
        return table_print(tbl)
    elseif  "string" == type( tbl ) then
        return tbl
    else
        return tostring(tbl)
    end
end

--
-- save player setting to ~/.quick_player.lua
--
local player = {}

function player:saveSetting(fileName)
    fileName = fileName or player.configFilePath
    local file, err = io.open(fileName, "wb")
    if err then return err end

    local ret = to_string(self.settings)
    file:write(ret)
    file:close()
end

function player:loadSetting(fileName)
    local file, err = io.open(fileName, "rb")
    if err then return err end

    local data = file:read("*all")
    local func = loadstring("local settings = {" .. data .. "} return settings")
    self.settings = func()
end

function player:setQuickRootPath()
    local fileName = self.userHomeDir .. ".QUICK_V3_ROOT"
    local file, err = io.open(fileName, "rb")
    if err then return err end


    self.quickRootPath = file:read("*l") .. "/"
end

function player:restorDefaultSettings()
    local func = loadstring("local settings = {" .. self.defaultSettings .. "} return settings")
    self.settings = func()
    self:saveSetting()
end

--
-- title: string
-- args : table
--
function player:openProject( title, args )

    local welcomeTitle = self.quickRootPath .. "quick/welcom/"
    if title == welcomeTitle then return end

    local recents = self.settings.PLAYER_OPEN_RECENTS
    if recents then
        local index = #recents
        while index > 0 do
            local v = recents[index]
            if v.title == title then table.remove(recents, index) end
            index = index - 1
        end
        table.insert(recents, 1, {title=title, args=args})
        self:saveSetting()
    end
end

function player:clearMenu()
    self.settings.PLAYER_OPEN_RECENTS = {}
    self:saveSetting()
end

function player:buildUI()
    local menuBar = PlayerProtocol:getInstance():getMenuService()

    -- FILE
    local fileMenu = menuBar:addItem("FILE_MENU", "&File")
    -- menuBar:addItem("QUIT_MENU", "New Project...", "FILE_MENU")
    -- menuBar:addItem("OPEN_MENU", "Open", "FILE_MENU")
    -- menuBar:addItem("SAVE_MENU", "Save", "FILE_MENU")

    -- menuBar:addItem("WELCOME_MENU_SEP", "-", "FILE_MENU")
    menuBar:addItem("WELCOME_MENU", "Welcome", "FILE_MENU")
        :setShortcut("super+w")

    -- menuBar:addItem("CLOSE_SEP", "-", "FILE_MENU")
    -- menuBar:addItem("CLOSE_MENU", "Close", "FILE_MENU")
        -- :setShortcut("super+w")

    -- VIEW
    local viewMenu = menuBar:addItem("VIEW_MENU", "&View")
    menuBar:addItem("RELAUNCH_MENU", "Relaunch", "VIEW_MENU")
        :setShortcut("super+r")
end

function player:registerEventHandler()
    -- for app event
    local eventDispatcher = cc.Director:getInstance():getEventDispatcher()
    local event = function(e)
        if self.json == nil then self.json = require('framework.json') end

        local data = self.json.decode(e:getDataString())
        if data == nil then return end

        if data.name == "close" then
            -- player.trackEvent("exit")
            eventDispatcher:dispatchEvent(cc.EventCustom:new("WELCOME_APP_HIDE"))
            cc.Director:getInstance():endToLua()
        elseif data.name == "resize" then
            -- <code here> t.w,t.h
        elseif data.name == "focusIn" then
            -- cc.Director:getInstance():resume()
        elseif data.name == "focusOut" then
            -- cc.Director:getInstance():pause()
        elseif data.name == "keyPress" then
            -- t.key = "tab"
            -- t.key = "return"
        elseif data.name == "menuClicked" then
            self:onMenuClicked(data)
        end

    end

    eventDispatcher:addEventListenerWithFixedPriority(cc.EventListenerCustom:create("APP.EVENT", event), 1)
end

function player:onMenuClicked(event)
    local data = event.data
    if data == "CLOSE_MENU" then
        PlayerProtocol:getInstance():quit()
    elseif data == "RELAUNCH_MENU" then
        PlayerProtocol:getInstance():relaunch()
    elseif data == "WELCOME_MENU" then
        local config = ProjectConfig:new()
        config:resetToWelcome()
        PlayerProtocol:getInstance():openProjectWithProjectConfig(config)
    end

end

function player:readSettings()
    self.userHomeDir = __USER_HOME__
    self.configFilePath = player.userHomeDir .. ".quick_player.lua"
    if not cc.FileUtils:getInstance():isFileExist(player.configFilePath) then 
        self:restorDefaultSettings()
    end
    self:loadSetting(player.configFilePath)
    
    -- get QUICK_V3_ROOT path
    self:setQuickRootPath()

    local s = PlayerSettings:new()
    s.offsetX = cc.player.settings.PLAYER_WINDOW_X
    s.offsetY = cc.player.settings.PLAYER_WINDOW_Y 
    s.windowWidth = cc.player.settings.PLAYER_WINDOW_WIDTH 
    s.windowHeight = cc.player.settings.PLAYER_WINDOW_HEIGHT 
    s.openLastProject = cc.player.settings.PLAYER_OPEN_LAST_PROJECT
    PlayerProtocol:getInstance():setPlayerSettings(s)
end

function player:trackEvent(eventName, ev)
    local url = 'http://www.google-analytics.com/collect'
    local request = cc.HTTPRequest:createWithUrl(function(event) 
                                                    local eventName = eventName
                                                    if eventName == "exit" then 
                                                        cc.Director:getInstance():endToLua() 
                                                    end 
                                                end,
                                                url, 
                                                cc.kCCHTTPRequestMethodPOST)

    request:addPOSTValue("v", "1")
    request:addPOSTValue("tid", "UA-52790340-1")
    request:addPOSTValue("cid", cc.Native:getOpenUDID())
    request:addPOSTValue("t", "event")

    request:addPOSTValue("an", "player")
    request:addPOSTValue("av", cc.cocos2dVersion())

    request:addPOSTValue("ec", device.platform)
    request:addPOSTValue("ea", eventName)
    -- request:addPOSTValue("el", "mac")

    if ev == nil then ev = "0" else ev = tostring(ev) end
    request:addPOSTValue("ev", ev)

    request:start()
end

-- call from host
function player:trackStartEvent()
    self:trackEvent("launch")
end

function player:init()
    self.defaultSettings = [[
        PLAYER_COCOACHINA_KEY = "USER_KEY",
        PLAYER_COCOACHINA_USER = "USER_NAME",
        PLAYER_WINDOW_X = 0,
        PLAYER_WINDOW_Y = 0,
        PLAYER_WINDOW_WIDTH = 960,
        PLAYER_WINDOW_HEIGHT = 640,
        PLAYER_OPEN_LAST_PROJECT = true,
        PLAYER_OPEN_RECENTS ={
        },

    ]]

    self:registerEventHandler()
    self:readSettings()
    self:buildUI()
end
-- load player settings


cc = cc or {}
cc.player = cc.player or player

cc.player:init()
