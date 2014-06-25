
local MenuScene = class("MenuScene", function()
    return display.newScene("MenuScene")
end)

function MenuScene:ctor()
	cc.uiloader:load("Test_1.ExportJson")
end

function MenuScene:onEnter()
end

return MenuScene
