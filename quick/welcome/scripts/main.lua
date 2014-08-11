
-- 0 - disable debug info, 1 - less debug info, 2 - verbose debug info
DEBUG = 1

-- display FPS stats on screen
DEBUG_FPS = true

-- dump memory info every 10 seconds
DEBUG_MEM = false

-- screen orientation
CONFIG_SCREEN_ORIENTATION = "landscape"

-- auto scale mode
CONFIG_SCREEN_AUTOSCALE = "FILL_ALL"

require("framework.init")

-- if display.screenScale > 1 then
--     cc.FileUtils:getInstance():addSearchPath("res/hd2x/")
-- else
    cc.FileUtils:getInstance():addSearchPath("res/hd/")
-- end

local scene = display.newScene("main")

display.newSprite("bg.png")
    :pos(display.cx, display.cy)
    :addTo(scene)

display.newSprite("logo.png")
    :pos(display.cx, display.cy)
    :addTo(scene)

display.replaceScene(scene)
