
local ccsloader = class("ccsloader")

function ccsloader:load(jsonFile)
	local fileUtil = cc.FileUtils:getInstance()
	local fullPath = fileUtil:fullPathForFilename(jsonFile)
	print("fullPath:" .. fullPath)
	local jsonStr = fileUtil:getStringFromFile(fullPath)
	print("jsonStr:" .. jsonStr)
	local jsonVal = json.decode(jsonStr)

	for i,v in ipairs(jsonVal.textures) do
		display.addSpriteFrames(v, jsonVal.texturesPng[i])
	end

	return self:parserJson(jsonVal)
end

function ccsloader:parserJson(jsonVal)
	local root = jsonVal.nodeTree
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

	dump(options, "options:")
	uiNode.name = options.name or "unknow node"

	if options.fileName then
		uiNode:setSpriteFrame(options.fileName)
	end

	if options.flipX then
		uiNode:setFlippedX(options.flipX)
	end
	if options.flipY then
		uiNode:setFlippedY(options.flipY)
	end
	uiNode:setRotation(options.rotation or 0)

	uiNode:setPositionX(options.x or 0)
	uiNode:setPositionY(options.y or 0)
	print("htl scale x:", options.scaleX)
	uiNode:setScaleX(options.scaleX or 1)
	print("htl scale y:", options.scaleY)
	uiNode:setScaleY(options.scaleY or 1)
	uiNode:setVisible(options.visible or true)
	uiNode:setLocalZOrder(options.ZOrder or 0)
	if 0 ~= options.width and 0 ~= options.height then
		print("htl set content size")
		uiNode:setContentSize(cc.size(options.width, options.height))
	end
	uiNode:setTag(options.tag or 0)
	uiNode:setAnchorPoint(
		cc.p(options.anchorPointX or 0.5, options.anchorPointY or 0.5))

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

	printInfo("create node:" .. clsName)
	if clsName == "Node" then
		node = cc.Node:create()
	elseif clsName == "Sprite" or clsName == "Scale9Sprite" then
		node = cc.Sprite:create()
	else
		printError("ccsloader not support node:" .. clsName)
	end

	return node
end

return ccsloader
