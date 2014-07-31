
local CCSSample1Scene = class("CCSSample1Scene", function()
    return display.newScene("CCSSample1Scene")
end)

function CCSSample1Scene:ctor()
	app:createTitle(self, "CCS Sample1")
	app:createNextButton(self)

	local node = cc.uiloader:load("DemoHead_UI.ExportJson")
	if node then
		self:addChild(node)
	end
end

return CCSSample1Scene
