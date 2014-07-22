
local MainScene = class("MainScene", function()
    return display.newScene("MainScene")
end)

MainScene.TAG_SHARDER_NODE = 1111

MainScene._FILTERS = {
    {name = "bloom", filter = display.filters.BLOOM},
    {name = "blur", filter = display.filters.BLUR, param = {10, 5}},
    {name = "outline", filter = display.filters.OUTLINE},
    {name = "noise", filter = display.filters.NOISE},
    {name = "edgedetedt", filter = display.filters.EDGEDETEDT},
    {name = "greyscale", filter = display.filters.GREYSCALE},
    {name = "sepia", filter = display.filters.SEPIA},
    {name = "celshading", filter = display.filters.CELSHADING},
    {name = "lensflare", filter = display.filters.LENSFLARE}
}

function MainScene:ctor()
	self:_addUI()
	self:_createFilters()
	self:_showFilter()
end

function MainScene:onEnter()
end

function MainScene:onExit()
end

function MainScene:_addUI()
    self.sp = display.newFilteredSprite("helloworld.png")
        :pos(display.cx, display.cy)
        :addTo(self)

	cc.ui.UIPushButton.new("close.png")
		:align(display.RIGHT_BOTTOM, display.width, display.bottom)
		:addTo(self, 0)
		:onButtonClicked(handler(self, self._onClose))
	
	self._prevBtn = cc.ui.UIPushButton.new({normal="b1.png",pressed="b2.png"})
		:align(display.BOTTOM_CENTER, display.cx-100, display.bottom)
		:addTo(self, 0)
		:onButtonClicked(handler(self, self._onPrev))
	self._resetBtn = cc.ui.UIPushButton.new({normal="r1.png",pressed="r2.png"})
		:align(display.BOTTOM_CENTER, display.cx, display.bottom)
		:addTo(self, 0)
		:onButtonClicked(handler(self, self._onReset))
	self._nextBtn = cc.ui.UIPushButton.new({normal="f1.png",pressed="f2.png"})
		:align(display.BOTTOM_CENTER, display.cx+100, display.bottom)
		:addTo(self, 0)
		:onButtonClicked(handler(self, self._onNext))


	self._title = ui.newTTFLabel({text="-- Shader test --"})
		:align(display.CENTER, display.cx, display.top - 20)
		:addTo(self, 10)
    self._subTitle = ui.newTTFLabel({text=self._FILTERS[1].name})
        :align(display.CENTER, display.cx, display.top - 40)
        :addTo(self, 10)
end

function MainScene:_createFilters()
	self._curFilter = 1
	self._filterCount = #self._FILTERS
end

function MainScene:_showFilter()
    local filter = self._FILTERS[self._curFilter]
    self._subTitle:setString(filter.name)
    if filter.filter then
        if filter.param then
            self.sp:setEffectByName(filter.filter, unpack(filter.param))
        else
            self.sp:setEffectByName(filter.filter)
        end
    end
end

function MainScene:_onPrev()
	self._curFilter = self._curFilter - 1
	if self._curFilter <= 0 then
		self._curFilter = self._filterCount
	end
	self:_showFilter()
end

function MainScene:_onReset()
	self:_showFilter()
end

function MainScene:_onNext()
	self._curFilter = self._curFilter + 1
	if self._curFilter > self._filterCount then
		self._curFilter = 1
	end
	self:_showFilter()
end

function MainScene:_onClearFilter()
	print("onCliearFilter")
	if self._filterSprite then
		self._filterSprite:clearFilter()
	end
end

function MainScene:_onClose()
	game.exit()
end

function MainScene:_resetSharderNode()
	local node = self:getChildByTag(self.TAG_SHARDER_NODE)
	if node then
		self:removeChild(node, true)
	end

	node = display.newNode()
	node:setTag(self.TAG_SHARDER_NODE)
	self:addChild(node)

	return node
end

function MainScene:_showRetroEffect()
	local node = self:_resetSharderNode()

	local accum = 0
    self._label = cc.Label:createWithBMFont("fonts/west_england-64.fnt", "RETRO EFFECT")
    self._label:setAnchorPoint(0.5, 0.5)
    self._label:setPosition(display.cx, display.cy)
    node:addChild(self._label)

	local program = cc.GLProgram:create("Shaders/example_ColorBars.vsh", "Shaders/example_ColorBars.fsh")
    program:bindAttribLocation(cc.ATTRIBUTE_NAME_POSITION, cc.VERTEX_ATTRIB_POSITION) 
    program:bindAttribLocation(cc.ATTRIBUTE_NAME_TEX_COORD, cc.VERTEX_ATTRIB_TEX_COORD)
    program:link()
    program:updateUniforms()
    self._label:setGLProgram(program)

    local function updateRetroEffect(fTime)
        if nil == self._label then
            return
        end
        accum = accum + fTime
        local letterCount = self._label:getStringLength()
        local i = 0
        for i= 0 ,letterCount - 1 do
            local sprite = self._label:getLetter(i)
            local oldPosX,oldPosY = sprite:getPosition()
            sprite:setPosition(oldPosX, math.sin(accum * 2 + i / 2.0) * 20)
            local scaleY = math.sin(accum * 2 + i / 2.0 + 0.707)
            sprite:setScaleY(scaleY)
        end
    end

    node:addNodeEventListener(cc.NODE_ENTER_FRAME_EVENT, updateRetroEffect)
end

function MainScene:_showShaderMajori()
    local node = self:_resetSharderNode()

    local fileUtiles = cc.FileUtils:getInstance()

    local vertSource = vertDefaultSource
    local fragSource = fileUtiles:getStringFromFile("Shaders/example_Monjori.fsh")
    local glProgam = cc.GLProgram:createWithByteArrays(vertSource, fragSource)
    local glprogramstate = cc.GLProgramState:getOrCreateWithGLProgram(glProgam)
    local resolution = cc.p(256, 256)

    local glNode  = gl.glNodeCreate()
    glNode:setContentSize(cc.size(256, 256))
    glNode:setAnchorPoint(cc.p(0.5, 0.5))
    glNode:setGLProgramState(glprogramstate)
    glNode:getGLProgramState():setUniformVec2("resolution", resolution)

    local function updateMajori(fTime)
        time = time + fTime
    end

    local function majoriDraw(transform, transformUpdated)
        local w = 256
        local h = 256

        local vertices ={ 0,0, w,0, w,h, 0,0, 0,h, w,h }
        local glProgramState = glNode:getGLProgramState()
        glProgramState:setVertexAttribPointer("a_position", 2, gl.FLOAT, false, 0, vertices, #vertices)
        glProgramState:apply(transform)
        gl.drawArrays(gl.TRIANGLES, 0, 6)
    end

    node:scheduleUpdateWithPriorityLua(updateMajori,0)
    glNode:registerScriptDrawHandler(majoriDraw)
    time = 0
    node:addChild(glNode,-10)
    glNode:setPosition( size.width/2, size.height/2)
    local center = cc.p( size.width / 2 * scaleFactor, size.height / 2 * scaleFactor)
    glNode:getGLProgramState():setUniformVec2("center", center)
end

function MainScene:_showShaderMandelbrot()
    local node = self:_resetSharderNode()

    local fileUtiles = cc.FileUtils:getInstance()
    local vertSource = vertDefaultSource
    local fragSource = fileUtiles:getStringFromFile("Shaders/example_Mandelbrot.fsh")
    local glProgam = cc.GLProgram:createWithByteArrays(vertSource, fragSource)
    local glprogramstate = cc.GLProgramState:getOrCreateWithGLProgram(glProgam)
    local resolution = cc.p(256, 256)

    local glNode  = gl.glNodeCreate()
    glNode:setContentSize(cc.size(256, 256))
    glNode:setAnchorPoint(cc.p(0.5, 0.5))
    glNode:setGLProgramState(glprogramstate)
    glNode:getGLProgramState():setUniformVec2("resolution", resolution)

    local function updateMandelbrot(fTime)
        time = time + fTime
    end

    local function mandelbrotDraw(transform, transformUpdated)
        local w = 256
        local h = 256

        local vertices ={ 0,0, w,0, w,h, 0,0, 0,h, w,h }
        local glProgramState = glNode:getGLProgramState()
        glProgramState:setVertexAttribPointer("a_position", 2, gl.FLOAT, false, 0, vertices, #vertices)
        glProgramState:apply(transform)
        gl.drawArrays(gl.TRIANGLES, 0, 6)
    end

    node:scheduleUpdateWithPriorityLua(updateMandelbrot,0)
    glNode:registerScriptDrawHandler(mandelbrotDraw)
    time = 0
    node:addChild(glNode,-10)
    glNode:setPosition( size.width/2, size.height/2)
    local center = cc.p( size.width / 2 * scaleFactor, size.height / 2 * scaleFactor)
    glNode:getGLProgramState():setUniformVec2("center", center)
    return node
end

function MainScene:_showShaderHeart()
    local node = self:_resetSharderNode()

    local fileUtiles = cc.FileUtils:getInstance()
    local vertSource = vertDefaultSource
    local fragSource = fileUtiles:getStringFromFile("Shaders/example_Heart.fsh")
    local glProgam = cc.GLProgram:createWithByteArrays(vertSource, fragSource)
    local glprogramstate = cc.GLProgramState:getOrCreateWithGLProgram(glProgam)
    local resolution = cc.p(256, 256)

    local glNode  = gl.glNodeCreate()
    glNode:setContentSize(cc.size(256, 256))
    glNode:setAnchorPoint(cc.p(0.5, 0.5))
    glNode:setGLProgramState(glprogramstate)
    glNode:getGLProgramState():setUniformVec2("resolution", resolution)

    local function updateHeart(fTime)
        time = time + fTime
    end

    local function heartDraw(transform, transformUpdated)
        local w = 256
        local h = 256

        local vertices ={ 0,0, w,0, w,h, 0,0, 0,h, w,h }
        local glProgramState = glNode:getGLProgramState()
        glProgramState:setVertexAttribPointer("a_position", 2, gl.FLOAT, false, 0, vertices, #vertices)
        glProgramState:apply(transform)
        gl.drawArrays(gl.TRIANGLES, 0, 6)
    end

    node:scheduleUpdateWithPriorityLua(updateHeart,0)
    glNode:registerScriptDrawHandler(heartDraw)
    time = 0
    node:addChild(glNode,-10)
    glNode:setPosition( size.width/2, size.height/2)
    local center = cc.p( size.width / 2 * scaleFactor, size.height / 2 * scaleFactor)
    glNode:getGLProgramState():setUniformVec2("center", center)
    return node
end

function MainScene:_showShaderPlasma()
    local node = self:_resetSharderNode()

    local fileUtiles = cc.FileUtils:getInstance()
    local vertSource = vertDefaultSource
    local fragSource = fileUtiles:getStringFromFile("Shaders/example_Plasma.fsh")
    local glProgam = cc.GLProgram:createWithByteArrays(vertSource, fragSource)
    local glprogramstate = cc.GLProgramState:getOrCreateWithGLProgram(glProgam)
    local resolution = cc.p(256, 256)

    local glNode  = gl.glNodeCreate()
    glNode:setContentSize(cc.size(256, 256))
    glNode:setAnchorPoint(cc.p(0.5, 0.5))
    glNode:setGLProgramState(glprogramstate)
    glNode:getGLProgramState():setUniformVec2("resolution", resolution)


    local function updatePlasma(fTime)
        time = time + fTime
    end

    local function plasmaDraw(transform, transformUpdated)
        local w = 256
        local h = 256

        local vertices ={ 0,0, w,0, w,h, 0,0, 0,h, w,h }
        local glProgramState = glNode:getGLProgramState()
        glProgramState:setVertexAttribPointer("a_position", 2, gl.FLOAT, false, 0, vertices, #vertices)
        glProgramState:apply(transform)
        gl.drawArrays(gl.TRIANGLES, 0, 6)
    end

    node:scheduleUpdateWithPriorityLua(updatePlasma,0)
    glNode:registerScriptDrawHandler(plasmaDraw)
    time = 0
    node:addChild(glNode,-10)
    glNode:setPosition( size.width/2, size.height/2)
    local center = cc.p( size.width / 2 * scaleFactor, size.height / 2 * scaleFactor)
    glNode:getGLProgramState():setUniformVec2("center", center)
    return node
end

function MainScene:_showShaderFlower()
    local node = self:_resetSharderNode()

    local fileUtiles = cc.FileUtils:getInstance()
    local vertSource = vertDefaultSource
    local fragSource = fileUtiles:getStringFromFile("Shaders/example_Flower.fsh")
    local glProgam = cc.GLProgram:createWithByteArrays(vertSource, fragSource)
    local glprogramstate = cc.GLProgramState:getOrCreateWithGLProgram(glProgam)
    local resolution = cc.p(256, 256)

    local glNode  = gl.glNodeCreate()
    glNode:setContentSize(cc.size(256, 256))
    glNode:setAnchorPoint(cc.p(0.5, 0.5))
    glNode:setGLProgramState(glprogramstate)
    glNode:getGLProgramState():setUniformVec2("resolution", resolution)

    local function updateFlower(fTime)
        time = time + fTime
    end

    local function flowerDraw(transform, transformUpdated)
        local w = 256
        local h = 256

        local vertices ={ 0,0, w,0, w,h, 0,0, 0,h, w,h }
        local glProgramState = glNode:getGLProgramState()
        glProgramState:setVertexAttribPointer("a_position", 2, gl.FLOAT, false, 0, vertices, #vertices)
        glProgramState:apply(transform)
        gl.drawArrays(gl.TRIANGLES, 0, 6)
    end

    node:scheduleUpdateWithPriorityLua(updateFlower,0)
    glNode:registerScriptDrawHandler(flowerDraw)
    time = 0
    node:addChild(glNode,-10)
    glNode:setPosition( size.width/2, size.height/2)
    local center = cc.p( size.width / 2 * scaleFactor, size.height / 2 * scaleFactor)
    glNode:getGLProgramState():setUniformVec2("center", center)
    return node
end

function MainScene:_showShaderJulia()
    local node = self:_resetSharderNode()

    local fileUtiles = cc.FileUtils:getInstance()
    local vertSource = vertDefaultSource
    local fragSource = fileUtiles:getStringFromFile("Shaders/example_Julia.fsh")
    local glProgam = cc.GLProgram:createWithByteArrays(vertSource, fragSource)
    local glprogramstate = cc.GLProgramState:getOrCreateWithGLProgram(glProgam)
    local resolution = cc.p(256, 256)

    local glNode  = gl.glNodeCreate()
    glNode:setContentSize(cc.size(256, 256))
    glNode:setAnchorPoint(cc.p(0.5, 0.5))
    glNode:setGLProgramState(glprogramstate)
    glNode:getGLProgramState():setUniformVec2("resolution", resolution)

    local function updateJulia(fTime)
        time = time + fTime
    end

    local function juliaDraw(transform, transformUpdated)
        local w = 256
        local h = 256

        local vertices ={ 0,0, w,0, w,h, 0,0, 0,h, w,h }
        local glProgramState = glNode:getGLProgramState()
        glProgramState:setVertexAttribPointer("a_position", 2, gl.FLOAT, false, 0, vertices, #vertices)
        glProgramState:apply(transform)
        gl.drawArrays(gl.TRIANGLES, 0, 6)
    end

    node:scheduleUpdateWithPriorityLua(updateJulia,0)
    glNode:registerScriptDrawHandler(juliaDraw)
    time = 0
    node:addChild(glNode,-10)
    glNode:setPosition( size.width/2, size.height/2)
    local center = cc.p( size.width / 2 * scaleFactor, size.height / 2 * scaleFactor)
    glNode:getGLProgramState():setUniformVec2("center", center)
    return node
end

function MainScene:_showGLGetActive()
    local node = self:_resetSharderNode()

    local sprite = cc.Sprite:create("Images/grossini.png")
    sprite:setPosition( size.width/2, size.height/2)
    node:addChild(sprite)
    local glNode = gl.glNodeCreate()
    node:addChild(glNode,-10)
    local scheduler = cc.Director:getInstance():getScheduler()

    local function getCurrentResult()
        local var = {}
        local glProgam = sprite:getGLProgram()
        if nil ~= glProgam then
            local p = glProgam:getProgram()
            local aaSize,aaType,aaName = gl.getActiveAttrib(p,0)
            local strFmt = "size:"..aaSize.." type:"..aaType.." name:"..aaName
            print(strFmt)
            local auSize,auType,auName = gl.getActiveUniform(p,0)
            strFmt = "size:"..auSize.." type:"..auType.." name:"..auName
            print(strFmt)
            local shadersTable         = gl.getAttachedShaders(p)
            if type(shadersTable) == "table" then
                local count = table.getn(shadersTable)
                local i = 1
                strFmt = ""
                for i=1, count do
                    strFmt = strFmt..shadersTable[i].." "
                end
                print(strFmt)
            end 

            if nil ~= schedulEntry then
                scheduler:unscheduleScriptEntry(schedulEntry)
            end
        end
    end
    
    if nil ~= schedulEntry then
        scheduler:unscheduleScriptEntry(schedulEntry)
    end
    schedulEntry = scheduler:scheduleScriptFunc(getCurrentResult, 0.5, false)

    return node
end

    --Have problem
function MainScene:_shwoTexImage2D()
    local texture = {}
    local squareVertexPositionBuffer = {}
    local squareVertexTextureBuffer  = {}
    local node = self:_resetSharderNode()

    local glNode   = gl.glNodeCreate()
    node:addChild(glNode, 10)
    glNode:setPosition(size.width/2, size.height/2)
    glNode:setContentSize(cc.size(128,128))
    glNode:setAnchorPoint(cc.p(0.5,0.5))
    local shaderCache = cc.ShaderCache:getInstance()
    local shader = shaderCache:getProgram("ShaderPositionTexture")

    local function initGL()
        texture.texture_id  = gl.createTexture()
        gl.bindTexture(gl.TEXTURE_2D,texture.texture_id )
        local pixels = {}
        local i = 1
        while i <= 4096 do
            pixels[i] = math.floor(i / 4)
            i = i + 1
            pixels[i] = math.floor(i / 16)
            i = i + 1
            pixels[i] = math.floor(i / 8)
            i = i + 1
            pixels[i] = 255
            i = i + 1
        end

        gl._texImage2D(gl.TEXTURE_2D, 0, gl.RGBA, 32, 32, 0, gl.RGBA, gl.UNSIGNED_BYTE, table.getn(pixels),pixels)
        gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, gl.NEAREST)
        gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.NEAREST)
        gl.bindTexture(gl.TEXTURE_2D, 0)

        --Square
        squareVertexPositionBuffer.buffer_id = gl.createBuffer()
        gl.bindBuffer(gl.ARRAY_BUFFER, squareVertexPositionBuffer.buffer_id)
        local vertices = { 128, 128, 0, 128, 128, 0, 0, 0 }
        gl.bufferData(gl.ARRAY_BUFFER,table.getn(vertices),vertices,gl.STATIC_DRAW)

        squareVertexTextureBuffer.buffer_id = gl.createBuffer()
        gl.bindBuffer(gl.ARRAY_BUFFER, squareVertexTextureBuffer.buffer_id)
        local texcoords = { 1, 1, 0, 1, 1, 0, 0, 0 }
        gl.bufferData(gl.ARRAY_BUFFER,table.getn(texcoords),texcoords,gl.STATIC_DRAW)
        gl.bindBuffer(gl.ARRAY_BUFFER,0)
    end

    local function TexImage2DDraw(transform, transformUpdated)
        if nil ~= shader then
            shader:use()
            shader:setUniformsForBuiltins(transform)

            gl.bindTexture(gl.TEXTURE_2D, texture.texture_id)
            gl.glEnableVertexAttribs(bit._or(cc.VERTEX_ATTRIB_FLAG_TEX_COORDS, cc.VERTEX_ATTRIB_FLAG_POSITION))

            gl.bindBuffer(gl.ARRAY_BUFFER, squareVertexPositionBuffer.buffer_id)
            gl.vertexAttribPointer(cc.VERTEX_ATTRIB_POSITION,2,gl.FLOAT,false,0,0)


            gl.bindBuffer(gl.ARRAY_BUFFER, squareVertexTextureBuffer.buffer_id)
            gl.vertexAttribPointer(cc.VERTEX_ATTRIB_TEX_COORD,2,gl.FLOAT,false,0,0)

            gl.drawArrays(gl.TRIANGLE_STRIP,0,4)

            gl.bindTexture(gl.TEXTURE_2D,0)
            gl.bindBuffer(gl.ARRAY_BUFFER,0)
        end
    end

    initGL()
    glNode:registerScriptDrawHandler(TexImage2DDraw)
    return node
end

function MainScene:_showSupportedExtensionsLayer()
    local node = self:_resetSharderNode()

    local glNode = gl.glNodeCreate()
    node:addChild(glNode,-10)
    local supportExtensions = gl.getSupportedExtensions()
    if type(supportExtensions) ~= "table" then
        print("error:return value not table")
        return
    end
    local count = table.getn(supportExtensions)
    local i = 1
    for i=1,count do
        print(supportExtensions[i])
    end

    return node
end

function MainScene:_showReadPixels()
    local node = self:_resetSharderNode()

    local glNode = gl.glNodeCreate()
    node:addChild(glNode,-10)

    local x = size.width
    local y = size.height

    local blue = cc.LayerColor:create(cc.c4b(0, 0, 255, 255))
    local red = cc.LayerColor:create(cc.c4b(255, 0, 0, 255))
    local green = cc.LayerColor:create(cc.c4b(0, 255, 0, 255))
    local white = cc.LayerColor:create(cc.c4b(255, 255, 255, 255))

    blue:setScale(0.5)
    blue:setPosition(-x / 4, -y / 4)

    red:setScale(0.5)
    red:setPosition(x / 4, -y / 4)

    green:setScale(0.5)
    green:setPosition(-x / 4, y / 4)

    white:setScale(0.5)
    white:setPosition(x / 4, y / 4)

    node:addChild(blue,10)
    node:addChild(white,11)
    node:addChild(green,12)
    node:addChild(red,13)

    local scheduler = cc.Director:getInstance():getScheduler()

    local function getCurrentResult()
        local x = size.width
        local y = size.height

        local pixelCount = 4
        local i = 1
        local strFmt = ""
        --blue
        local bPixels = gl.readPixels(0,   0,   1, 1, gl.RGBA, gl.UNSIGNED_BYTE, pixelCount)
        for i=1,pixelCount do
            local strTmp = string.format("%d:%d ",i,bPixels[i])
            strFmt = strFmt .. strTmp
        end
        print(strFmt)
        strFmt = ""
        --red
        local rPixels = gl.readPixels(x-1, 0,   1, 1, gl.RGBA, gl.UNSIGNED_BYTE, pixelCount)
        for i=1,pixelCount do
            local strTmp = string.format("%d:%d ",i,rPixels[i])
            strFmt = strFmt .. strTmp
        end
        print(strFmt)
        strFmt = ""
        --green
        local gPixels = gl.readPixels(0,   y-1, 1, 1, gl.RGBA, gl.UNSIGNED_BYTE, pixelCount)
        for i=1,pixelCount do
            local strTmp = string.format("%d:%d ",i,gPixels[i])
            strFmt = strFmt .. strTmp
        end
        print(strFmt)
        strFmt = ""
        --white
        local wPixels = gl.readPixels(x-1, y-1, 1, 1, gl.RGBA, gl.UNSIGNED_BYTE, pixelCount)
        for i=1,pixelCount do
            local strTmp = string.format("%d:%d ",i,wPixels[i])
            strFmt = strFmt .. strTmp
        end
        print(strFmt)

        if nil ~= schedulEntry then
            scheduler:unscheduleScriptEntry(schedulEntry)
        end
    end
    
    if nil ~= schedulEntry then
        scheduler:unscheduleScriptEntry(schedulEntry)
    end

    schedulEntry = scheduler:scheduleScriptFunc(getCurrentResult, 0.5, false)

    return node
end

function MainScene:_showClear()
    local node = self:_resetSharderNode()

    local blue = cc.LayerColor:create(cc.c4b(0, 0, 255, 255))
    node:addChild( blue, 1 )

    local glNode = gl.glNodeCreate()
    node:addChild(glNode,10)
    --gl.init()
    local scheduler = cc.Director:getInstance():getScheduler()

    local function clearDraw()
        gl.clear(gl.COLOR_BUFFER_BIT)
    end

    local function getCurrentResult()

        local pixels = gl.readPixels(math.floor(size.width/2), math.floor(size.height/2), 1, 1, gl.RGBA, gl.UNSIGNED_BYTE, 4)
        local strFmt = ""
        for i=1,4 do
            local strTmp = string.format("%d:%d ",i,pixels[i])
            strFmt = strFmt .. strTmp
        end
        print(strFmt)
        if nil ~= schedulEntry then
            scheduler:unscheduleScriptEntry(schedulEntry)
        end
    end
    glNode:setPosition( size.width/2, size.height/2 )
    glNode:registerScriptDrawHandler(clearDraw)

    if nil ~= schedulEntry then
        scheduler:unscheduleScriptEntry(schedulEntry)
    end

    schedulEntry = scheduler:scheduleScriptFunc(getCurrentResult, 0.5, false)
    return node
end

function MainScene:_showNodeWebGLAPI()
    local node = self:_resetSharderNode()

    local glNode = gl.glNodeCreate()
    node:addChild(glNode,10)
    local shaderProgram = {}
    local triangleVertexPositionBuffer = {}
    local triangleVertexColorBuffer = {}
    local squareVertexPositionBuffer = {}
    local squareVertexColorBuffer = {}
    local pMatrix = {1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1}
    local mvMatrix = {1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1}

    local vsh =  "\n".."attribute vec3 aVertexPosition;\n".."attribute vec4 aVertexColor;\n"..
                 "uniform mat4 uMVMatrix;\n".."uniform mat4 uPMatrix;\n".."varying vec4 vColor;\n"..
                 "void main(void) {\n".." gl_Position = uPMatrix * uMVMatrix * vec4(aVertexPosition, 1.0);\n".." vColor = aVertexColor;\n"..
                 "}\n"

    local fsh = "\n"..
                "#ifdef GL_ES\n"..
                "precision mediump float;\n"..
                "#endif\n"..
                "varying vec4 vColor;\n"..
                "void main(void) {\n"..
                " gl_FragColor = vColor;\n"..
                "}\n"

    local function compileShader(source,type)
        local shader
        if type == "fragment" then
            shader = gl.createShader(gl.FRAGMENT_SHADER)
        else
            shader = gl.createShader(gl.VERTEX_SHADER)
        end
        gl.shaderSource(shader,source)
        gl.compileShader(shader)
        local ret = gl.getShaderParameter(shader,gl.COMPILE_STATUS)
        if not ret then
            --throw
            print("Could not compile "..type.." shader")
        end
        return shader
    end

    local function initBuffers()
        triangleVertexPositionBuffer.buffer_id = gl.createBuffer()
        gl.bindBuffer(gl.ARRAY_BUFFER, triangleVertexPositionBuffer.buffer_id)
        local vertices = {
         0.0,  1.0,  0.0,
        -1.0, -1.0,  0.0,
         1.0, -1.0,  0.0
        }
        gl.bufferData(gl.ARRAY_BUFFER, 9, vertices,gl.STATIC_DRAW)
        triangleVertexPositionBuffer.itemSize = 3
        triangleVertexPositionBuffer.numItems = 3

        triangleVertexColorBuffer.buffer_id = gl.createBuffer()
        gl.bindBuffer(gl.ARRAY_BUFFER, triangleVertexColorBuffer.buffer_id)
        local colors = {
        1.0, 0.0, 0.0, 1.0,
        1.0, 0.0, 0.0, 1.0,
        1.0, 0.0, 0.0, 1.0
        }
        gl.bufferData(gl.ARRAY_BUFFER, 12, colors , gl.STATIC_DRAW)
        triangleVertexColorBuffer.itemSize = 4
        triangleVertexColorBuffer.numItems = 3

        squareVertexPositionBuffer.buffer_id = gl.createBuffer()
        gl.bindBuffer(gl.ARRAY_BUFFER, squareVertexPositionBuffer.buffer_id)
        vertices = {
         1.0,  1.0,  0.0,
        -1.0,  1.0,  0.0,
         1.0, -1.0,  0.0,
        -1.0, -1.0,  0.0
        }
        gl.bufferData(gl.ARRAY_BUFFER, 12, vertices,gl.STATIC_DRAW)
        squareVertexPositionBuffer.itemSize = 3
        squareVertexPositionBuffer.numItems = 4

        squareVertexColorBuffer.buffer_id = gl.createBuffer()
        gl.bindBuffer(gl.ARRAY_BUFFER, squareVertexColorBuffer.buffer_id)
        colors = {
            0.0, 0.0, 1.0, 1.0,
            0.0, 0.0, 1.0, 1.0,
            0.0, 0.0, 1.0, 1.0,
            0.0, 0.0, 1.0, 1.0
        }
        gl.bufferData(gl.ARRAY_BUFFER, 16,colors, gl.STATIC_DRAW)
        squareVertexColorBuffer.itemSize = 4
        squareVertexColorBuffer.numItems = 4

        gl.bindBuffer(gl.ARRAY_BUFFER, 0)
    end

    local function setMatrixUniforms()
        gl.uniformMatrix4fv(shaderProgram.pMatrixUniform,false,table.getn(pMatrix), pMatrix)
        gl.uniformMatrix4fv(shaderProgram.mvMatrixUniform,false,table.getn(mvMatrix),mvMatrix)
    end

    local function nodeWebGLDraw()
        gl.useProgram(shaderProgram.program_id)
        gl.uniformMatrix4fv(shaderProgram.pMatrixUniform,false,table.getn(pMatrix),pMatrix)
        gl.uniformMatrix4fv(shaderProgram.mvMatrixUniform,false,table.getn(mvMatrix),mvMatrix)

        gl.enableVertexAttribArray(shaderProgram.vertexPositionAttribute)
        gl.enableVertexAttribArray(shaderProgram.vertexColorAttribute)

        --Draw
        gl.bindBuffer(gl.ARRAY_BUFFER, squareVertexPositionBuffer.buffer_id)
        gl.vertexAttribPointer(shaderProgram.vertexPositionAttribute, squareVertexPositionBuffer.itemSize, gl.FLOAT, false, 0, 0)

        gl.bindBuffer(gl.ARRAY_BUFFER, squareVertexColorBuffer.buffer_id)
        gl.vertexAttribPointer(shaderProgram.vertexColorAttribute, squareVertexColorBuffer.itemSize, gl.FLOAT, false, 0, 0)

        setMatrixUniforms()

        gl.drawArrays(gl.TRIANGLE_STRIP, 0, squareVertexPositionBuffer.numItems)

        --DrawArray
        gl.bindBuffer(gl.ARRAY_BUFFER, triangleVertexPositionBuffer.buffer_id)
        gl.vertexAttribPointer(shaderProgram.vertexPositionAttribute, triangleVertexPositionBuffer.itemSize, gl.FLOAT, false, 0, 0)

        gl.bindBuffer(gl.ARRAY_BUFFER, triangleVertexColorBuffer.buffer_id)
        gl.vertexAttribPointer(shaderProgram.vertexColorAttribute, triangleVertexColorBuffer.itemSize, gl.FLOAT, false, 0, 0)

        gl.drawArrays(gl.TRIANGLES, 0, triangleVertexPositionBuffer.numItems)

        gl.bindBuffer(gl.ARRAY_BUFFER, 0)          
    end

    local fshader = compileShader(fsh, 'fragment')
    local vshader = compileShader(vsh, 'vertex')
    shaderProgram.program_id = gl.createProgram()
    gl.attachShader(shaderProgram.program_id,vshader)
    gl.attachShader(shaderProgram.program_id,fshader)
    gl.linkProgram(shaderProgram.program_id)
    if not gl.getProgramParameter(shaderProgram.program_id, gl.LINK_STATUS) then
        --throw
        print("Could not initialise shaders")
    end
    gl.useProgram(shaderProgram.program_id)

    shaderProgram.vertexPositionAttribute = gl.getAttribLocation(shaderProgram.program_id,"aVertexPosition")
    gl.enableVertexAttribArray(shaderProgram.vertexPositionAttribute)

    shaderProgram.vertexColorAttribute = gl.getAttribLocation(shaderProgram.program_id,"aVertexColor")
    gl.enableVertexAttribArray(shaderProgram.vertexColorAttribute)

    shaderProgram.pMatrixUniform = gl.getUniformLocation(shaderProgram.program_id, "uPMatrix")
    shaderProgram.mvMatrixUniform = gl.getUniformLocation(shaderProgram.program_id, "uMVMatrix")

    initBuffers()

    glNode:registerScriptDrawHandler(nodeWebGLDraw)

    return node
end

function MainScene:_showGLNodeCCAPI()
    local node = self:_resetSharderNode()

    local glNode = gl.glNodeCreate()
    node:addChild(glNode,10)
    local shader = cc.ShaderCache:getInstance():getProgram("ShaderPositionColor")
    local triangleVertexPositionBuffer = {}
    local triangleVertexColorBuffer = {}
    local squareVertexPositionBuffer = {}
    local squareVertexColorBuffer    = {}

    local function initBuffers()
        triangleVertexPositionBuffer.buffer_id = gl.createBuffer()
        gl.bindBuffer(gl.ARRAY_BUFFER, triangleVertexPositionBuffer.buffer_id)  
        local vertices = {
         size.width / 2,   size.height,
         0,                 0,
         size.width,     0
        }
        gl.bufferData(gl.ARRAY_BUFFER, table.getn(vertices), vertices, gl.STATIC_DRAW)

        triangleVertexColorBuffer.buffer_id = gl.createBuffer()
        gl.bindBuffer(gl.ARRAY_BUFFER, triangleVertexColorBuffer.buffer_id) 
        local colors = {
        1.0, 0.0, 0.0, 1.0,
        1.0, 0.0, 0.0, 1.0,
        1.0, 0.0, 0.0, 1.0
        }
        gl.bufferData(gl.ARRAY_BUFFER, table.getn(colors),colors, gl.STATIC_DRAW)

        --Square
        squareVertexPositionBuffer.buffer_id = gl.createBuffer()
        gl.bindBuffer(gl.ARRAY_BUFFER, squareVertexPositionBuffer.buffer_id)
        vertices = {
            size.width,  size.height,
            0,           size.height,
            size.width,  0,
            0,           0
        }
        gl.bufferData(gl.ARRAY_BUFFER, table.getn(vertices), vertices, gl.STATIC_DRAW)
        
        squareVertexColorBuffer.buffer_id = gl.createBuffer()
        gl.bindBuffer(gl.ARRAY_BUFFER, squareVertexColorBuffer.buffer_id)
        colors = {
        0.0, 0.0, 1.0, 1.0,
        0.0, 0.0, 1.0, 1.0,
        0.0, 0.0, 1.0, 1.0,
        0.0, 0.0, 1.0, 1.0
        };
        gl.bufferData(gl.ARRAY_BUFFER, table.getn(colors), colors, gl.STATIC_DRAW)
        gl.bindBuffer(gl.ARRAY_BUFFER, 0)
    end

    local function GLNodeCCAPIDraw(transform, transformUpdated)
        shader:use()
        shader:setUniformsForBuiltins(transform)
        gl.glEnableVertexAttribs(cc.VERTEX_ATTRIB_FLAG_COLOR or cc.VERTEX_ATTRIB_FLAG_POSITION)

        --
        gl.bindBuffer(gl.ARRAY_BUFFER, squareVertexPositionBuffer.buffer_id)
        gl.vertexAttribPointer(cc.VERTEX_ATTRIB_POSITION, 2, gl.FLOAT, false, 0, 0)

        gl.bindBuffer(gl.ARRAY_BUFFER, squareVertexColorBuffer.buffer_id)
        gl.vertexAttribPointer(cc.VERTEX_ATTRIB_COLOR, 4, gl.FLOAT, false, 0, 0)

        gl.drawArrays(gl.TRIANGLE_STRIP, 0, 4)

        gl.bindBuffer(gl.ARRAY_BUFFER, triangleVertexPositionBuffer.buffer_id)
        gl.vertexAttribPointer(cc.VERTEX_ATTRIB_POSITION, 2, gl.FLOAT, false, 0, 0)

        gl.bindBuffer(gl.ARRAY_BUFFER, triangleVertexColorBuffer.buffer_id)
        gl.vertexAttribPointer(cc.VERTEX_ATTRIB_COLOR, 4, gl.FLOAT, false, 0, 0)

        gl.drawArrays(gl.TRIANGLE_STRIP, 0, 3)

        gl.bindBuffer(gl.ARRAY_BUFFER, 0)

    end

    initBuffers()
    glNode:registerScriptDrawHandler(GLNodeCCAPIDraw)

    return node
end

function MainScene:_showGLTexParamter()
    local node = self:_resetSharderNode()

    local glNode  = gl.glNodeCreate()
    node:addChild(glNode,10)
    local function getTexValues()
        gl.bindTexture(gl.TEXTURE_2D, 0)
        gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, gl.NEAREST)
        gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.NEAREST)
        gl.texParameteri( gl.TEXTURE_2D, gl.TEXTURE_WRAP_S, gl.CLAMP_TO_EDGE )
        gl.texParameteri( gl.TEXTURE_2D, gl.TEXTURE_WRAP_S, gl.CLAMP_TO_EDGE )

        local mag = gl.getTexParameter(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER)
        local min = gl.getTexParameter(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER)
        local w_s = gl.getTexParameter(gl.TEXTURE_2D, gl.TEXTURE_WRAP_S)
        local w_t = gl.getTexParameter(gl.TEXTURE_2D, gl.TEXTURE_WRAP_S)
        local strFmt = string.format("%d %d %d %d",mag,min,w_s,w_t)
        print(strFmt)
    end
    getTexValues()
    return node
end

function MainScene:_showGetUniform()
    local node = self:_resetSharderNode()

    local glNode  = gl.glNodeCreate()
    node:addChild(glNode,10)
    local pMatrix = {1,2,3,4, 4,3,2,1, 1,2,4,8, 1.1,1.2,1.3,1.4}

    local function runTest()
        local shader = cc.ShaderCache:getInstance():getProgram("ShaderPositionTextureColor")
        local program = shader:getProgram()

        shader:use()

        local loc = gl.getUniformLocation( program, "CC_MVPMatrix")

        gl.uniformMatrix4fv(loc, false, table.getn(pMatrix), pMatrix)

        local uniformTable = gl.getUniform( program, loc )
        local count = table.getn(uniformTable)
        local strFmt = ""
        for i=1,count do
            local  strTmp = string.format("%d: %.16f ",i - 1, uniformTable[i])
            strFmt = strFmt..strTmp
        end
        print(strFmt)
    end

    runTest()

    return node
end

return MainScene
