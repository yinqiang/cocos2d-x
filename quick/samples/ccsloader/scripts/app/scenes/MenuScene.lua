
local MenuScene = class("MenuScene", function()
    return display.newScene("MenuScene")
end)

function MenuScene:ctor()
	local node = cc.uiloader:load("Test_1.ExportJson")
	self:addChild(node)

	dumpUITree(node)
end

function MenuScene:onEnter()
end


depth = 1
function dumpUITree(node)
	if not node then
		return
	end

	printLine(string.format("Name:%s", node.name))
	printLine(string.format("Position:(%d, %d)", node:getPositionX(), node:getPositionY()))
	local size = node:getContentSize()
	printLine(string.format("Size:(%d, %d)", size.width, size.height))
	printLine(string.format("Scale:(%f, %f)", node:getScaleX(), node:getScaleY()))
	local anchor = node:getAnchorPoint()
	printLine(string.format("Anchor:(%f, %f)", anchor.x, anchor.y))
	printLine(string.format("ChildCount:%d", node:getChildrenCount()))

	depth = depth + 1
	for i,v in ipairs(node:getChildren()) do
		dumpUITree(v)
	end
	depth = depth - 1
end

function printLine(str)
	local t = {"+"}
	for i=1,depth do
		table.insert(t, "----")
	end
	table.insert(t, str)
	print(table.concat(t))
end

return MenuScene
