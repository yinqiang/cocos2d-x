
local ccsloader = class("ccsloader")

function ccsloader:load(jsonFile)
	local jsonStr = cc.FileUtils:getInstance():getStringFromFile(jsonFile)
	local json = json.decode()

	dump(json, "demo head ui:")
end

return ccsloader
