
local ccsloader = class("ccsloader")

function ccsloader:load(jsonFile)
	local fileUtil = cc.FileUtils:getInstance()
	local fullPath = fileUtil:fullPathForFilename(jsonFile)
	local jsonStr = fileUtil:getStringFromFile(fullPath)
	local jsonVal = json.decode(jsonStr)

	self:loadTexture(jsonVal)
	-- for i,v in ipairs(jsonVal.textures) do
	-- 	display.addSpriteFrames(v, jsonVal.texturesPng[i])
	-- end

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
	local uiNode = self:createUINode(clsName, options)
	if not uiNode then
		return
	end

	-- dump(options, "options:")
	uiNode.name = options.name or "unknow node"

	print("ccsloader set node params:" .. uiNode.name)

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

	-- print("htl scale x:", options.scaleX)
	uiNode:setScaleX(options.scaleX or 1)
	-- print("htl scale y:", options.scaleY)
	uiNode:setScaleY(options.scaleY or 1)
	uiNode:setVisible(options.visible or true)
	uiNode:setLocalZOrder(options.ZOrder or 0)
	uiNode:setTag(options.tag or 0)

	if clsName == "Button" then
		if 0 ~= options.width and 0 ~= options.height then
			uiNode:setButtonSize(options.width, options.height)
		end
		uiNode:align(self:getAnchorType(options.anchorPointX, options.anchorPointY),
			options.x or 0, options.y or 0)
	else if clsName == "ImageView" then
	else
		if 0 ~= options.width and 0 ~= options.height then
			uiNode:setContentSize(cc.size(options.width, options.height))
		end
		uiNode:setPositionX(options.x or 0)
		uiNode:setPositionY(options.y or 0)
		uiNode:setAnchorPoint(
			cc.p(options.anchorPointX or 0.5, options.anchorPointY or 0.5))
	end

	local children = jsonNode.children
	for i,v in ipairs(children) do
		local childrenNode = self:generateUINode(v)
		uiNode:addChild(childrenNode)
	end

	return uiNode
end

function ccsloader:createUINode(clsName, options)
	if not clsName then
		return
	end

	local node

	printInfo("create node:" .. clsName)
	if clsName == "Node" then
		node = cc.Node:create()
	elseif clsName == "Sprite" or clsName == "Scale9Sprite" then
		node = cc.Sprite:create()
	elseif clsName == "ImageView" then
		node = cc.ui.UIImage.new(
			self:transResName(options.fileNameData.path),
			{scale9 = true})
	elseif clsName == "Button" then
		node = cc.ui.UIPushButton.new(self:getButtonStateImages(options),
			{scale9 = true})
	else
		printError("ccsloader not support node:" .. clsName)
	end

	return node
end

function ccsloader:getButtonStateImages(options)
	local images = {}
	if options.normalData and options.normalData.path then
		images.normal = self:transResName(options.normalData.path)
	end
	if options.pressedData and options.pressedData.path then
		images.pressed = self:transResName(options.pressedData.path)
	end
	if options.disabledData and options.disabledData.path then
		images.disabled = self:transResName(options.disabledData.path)
	end

	dump(images, "images:")

	return images
end

function ccsloader:getAnchorType(anchorX, anchorY)
	if 1 == anchorX then
		if 1 == anchorY then
			return display.RIGHT_TOP
		elseif 0.5 == anchorY then
			return display.RIGHT_CENTER
		else
			return display.RIGHT_BOTTOM
		end
	elseif 0.5 == anchorX then
		if 1 == anchorY then
			return display.CENTER_TOP
		elseif 0.5 == anchorY then
			return display.CENTER
		else
			return display.CENTER_BOTTOM
		end
	else
		if 1 == anchorY then
			return display.LEFT_TOP
		elseif 0.5 == anchorY then
			return display.LEFT_CENTER
		else
			return display.LEFT_BOTTOM
		end
	end
end

function ccsloader:loadTexture(json)
	-- cc.FileUtils:getInstance():addSearchPath("res/")

	for i,v in ipairs(json.textures) do
		self.bUseTexture = true
		display.addSpriteFrames(v, json.texturesPng[i])
	end

end

function ccsloader:transResName(name)
	if self.bUseTexture then
		return "#" .. name
	else
		return name
	end
end

return ccsloader
