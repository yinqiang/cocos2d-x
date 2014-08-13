
local UILoaderUtilitys = {}

function UILoaderUtilitys.loadTexture(plist, png)
	if UILoaderUtilitys.isNil(plist) then
		return
	end

	local fullPath = fileUtil:fullPathForFilename(plist)
	cc.FileUtils:getInstance():addSearchPath(io.pathinfo(fullPath).dirname)
	local spCache = cc.SpriteFrameCache:getInstance()
	if png then
		spCache:addSpriteFrames(plist, png)
	else
		spCache:addSpriteFrames(plist)
	end
end

function UILoaderUtilitys.isNil(str)
	if not str or 0 == string.utf8len(str) then
		return true
	else
		return false
	end
end

return UILoaderUtilitys

