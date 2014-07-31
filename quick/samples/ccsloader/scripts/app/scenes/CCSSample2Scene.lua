
local CCSSample2Scene = class("CCSSample2Scene", function()
    return display.newScene("CCSSample2Scene")
end)

function CCSSample2Scene:ctor()
	app:createTitle(self, "CCS Sample2")
	app:createNextButton(self)

	local node = cc.uiloader:load("DemoLogin.ExportJson")
	if node then
		self:addChild(node)
	end
end

return CCSSample2Scene
