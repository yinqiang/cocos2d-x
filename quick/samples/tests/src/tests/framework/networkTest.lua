
local NetworkTestScene = game.createSceneClass("NetworkTestScene")

function NetworkTestScene:ctor()
    self.requestCount = 0

    self:prepare({
        description = "Please check console output"
    })

    local items = {
        "createHTTPRequest",
        "createHTTPRequestBadDomain",
        "send data to server",
    }
    self:addChild(game.createMenu(items, handler(self, self.runTest)))
end

function NetworkTestScene:onResponse(event, index, dumpResponse)
    local request = event.request
    printf("REQUEST %d - event.name = %s", index, event.name)
    if event.name == "completed" then
        printf("REQUEST %d - getResponseStatusCode() = %d", index, request:getResponseStatusCode())
        printf("REQUEST %d - getResponseHeadersString() =\n%s", index, request:getResponseHeadersString())

        if request:getResponseStatusCode() ~= 200 then
        else
            printf("REQUEST %d - getResponseDataLength() = %d", index, request:getResponseDataLength())
            if dumpResponse then
                printf("REQUEST %d - getResponseString() =\n%s", index, request:getResponseString())
            end
        end
    elseif event.name == "progress" then
        printf("REQUEST %d - total:%d, have download:%d, this circle download:%d", index, event.total, event.dltotal, event.dlnow)
    else
        printf("REQUEST %d - getErrorCode() = %d, getErrorMessage() = %s", index, request:getErrorCode(), request:getErrorMessage())
    end

    print("----------------------------------------")
end

function NetworkTestScene:createHTTPRequestTest()
    self.requestCount = self.requestCount + 1
    local index = self.requestCount
    local url
    -- url = "http://b.zol-img.com.cn/desk/bizhi/image/5/1920x1080/1403231389216.jpg"
    url = "http://quick-x.com/feed/"
    local request = network.createHTTPRequest(function(event)
        if tolua.isnull(self) then
            printf("REQUEST %d COMPLETED, BUT SCENE HAS QUIT", index)
            return
        end
        self:onResponse(event, index)
    end, url, "GET")
    printf("REQUEST START %d", index)
    request:start()
end

function NetworkTestScene:createHTTPRequestBadDomainTest()
    self.requestCount = self.requestCount + 1
    local index = self.requestCount
    local request = network.createHTTPRequest(function(event)
        if tolua.isnull(self) then
            printf("REQUEST %d COMPLETED, BUT SCENE HAS QUIT", index)
            return
        end
        self:onResponse(event, index)
    end, "http://quick-x.com.x.y.z.not/", "GET")
    printf("REQUEST START %d", index)
    request:start()
end



function NetworkTestScene:send_data_to_serverTest()
    self.requestCount = self.requestCount + 1
    local index = self.requestCount
    local request = network.createHTTPRequest(function(event)
        if tolua.isnull(self) then
            printf("REQUEST %d COMPLETED, BUT SCENE HAS QUIT", index)
            return
        end
        self:onResponse(event, index, true)
        local cookiesStr = event.request:getCookieString()
        local cookie = network.parseCookie(cookiesStr)
        dump(cookie, "GET COOKIE FROM SERVER")
    end, "http://quick-x.com/tests/http_request_tests.php", "POST")
    request:addPOSTValue("username", "dualface")
    request:setCookieString(network.makeCookieString({C1 = "V1", C2 = "V2"}))
    printf("REQUEST START %d", index)
    request:start()
end

return NetworkTestScene
