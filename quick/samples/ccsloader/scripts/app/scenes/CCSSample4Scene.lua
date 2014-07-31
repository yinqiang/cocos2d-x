
local CCSSample4Scene = class("CCSSample4Scene", function()
    return display.newScene("CCSSample4Scene")
end)

function CCSSample4Scene:ctor()
	app:createTitle(self, "CCS Sample4")
	app:createNextButton(self)

	local node = cc.uiloader:load("DemoShop.ExportJson")
	if node then
		self:addChild(node)
	end
end

return CCSSample4Scene
