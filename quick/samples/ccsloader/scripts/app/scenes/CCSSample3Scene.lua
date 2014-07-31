
local CCSSample3Scene = class("CCSSample3Scene", function()
    return display.newScene("CCSSample3Scene")
end)

function CCSSample3Scene:ctor()
	app:createTitle(self, "CCS Sample3")
	app:createNextButton(self)

	local node = cc.uiloader:load("DemoMap.ExportJson")
	if node then
		self:addChild(node)
	end
end

return CCSSample3Scene
