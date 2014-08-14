
local MenuScene = class("MenuScene", function()
    return display.newScene("MenuScene")
end)

function MenuScene:ctor()
	app:createTitle(self, "CCS Sample1")
	-- app:createNextButton(self)

	cc.FileUtils:getInstance():addSearchPath("res/jy_mobile/")
	app:loadCCSJsonFile(self, "publish/31100.json")
end

function MenuScene:onEnter()
end

return MenuScene
