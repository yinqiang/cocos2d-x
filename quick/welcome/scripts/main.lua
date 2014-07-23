

cc.FileUtils:getInstance():addSearchPath("res/")

local winsize = cc.Director:getInstance():getWinSize()
local scene = cc.Scene:create()
local sprite = cc.Sprite:create("logo.png")
sprite:setScale(0.5)
sprite:setPosition(winsize.width / 2, winsize.height / 2)
scene:addChild(sprite)
cc.Director:getInstance():runWithScene(scene)

