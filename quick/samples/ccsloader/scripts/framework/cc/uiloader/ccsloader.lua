
local ccsloader = class("ccsloader")

function ccsloader:load(jsonFile)
	local jsonStr = cc.FileUtils:getInstance():getStringFromFile(jsonFile)
	local json = json.decode(jsonStr)

	for i,v in ipairs(json.textures) do
		display.addSpriteFrames(v, json.texturesPng[i])
	end

	return self:parserJson(json)
end

function ccsloader:parserJson(json)
	local root = json.nodeTree
	local uiRoot = self:generateUINode(root)

	return uiRoot
end

-- generate a ui node and invoke self to generate child ui node
function ccsloader:generateUINode(jsonNode)
	local clsName = jsonNode.classname
	local options = jsonNode.options
	local uiNode = self:createUINode(clsName)
	if not uiNode then
		return
	end

	uiNode.name = jsonNode.name
	uiNode:setPositionX(jsonNode.x or 0)
	uiNode:setPositionY(jsonNode.y or 0)
	uiNode:setScaleX(jsonNode.scaleX or 1)
	uiNode:setScaleY(jsonNode.scaleY or 1)
	uiNode:setVisible(options.visible or true)
	uiNode:setLocalZOrder(jsonNode.ZOrder or 0)
	if 0 ~= options.width and 0 ~= options.height then
		uiNode:setContentSize(cc.size(options.width, options.height))
	end
	uiNode:setTag(jsonNode.tag or 0)
	uiNode:setAnchorPoint(
		cc.p(jsonNode.anchorPointX or 0.5, jsonNode.anchorPointY or 0.5))

	local children = jsonNode.children
	for i,v in ipairs(children) do
		local childrenNode = self:generateUINode(v)
		uiNode:addChild(childrenNode)
	end

	return uiNode
end

function ccsloader:createUINode(clsName)
	if not clsName then
		return
	end

	local node

	if clsName == "Node" then
		node = cc.Node:create()
	elseif clsName == "Sprite" or clsName == "Scale9Sprite" then
		node = cc.Scale9Sprite:create()
	else
		printError("ccsloader not support node:" .. clsName)
	end

	return node
end

return ccsloader
