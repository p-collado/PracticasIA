function drawPoint(x, y)
    r, g, b, a = 1, 1, 0, 1
    MOAIGfxDevice.setPenColor (r, g, b, a)
    MOAIDraw.drawPoints(x, y)
end

function getPropPosition(prop)
    return prop:getLoc()
end
    
function setPropPosition(prop, x, y)
    prop:setLoc(x, y)
end

function addImage(texture, posX, posY, sizeX, sizeY)
    posX = posX or 0
    posY = posY or 0
    gfxQuad = MOAIGfxQuad2D.new()
    
    gfxQuad:setTexture(texture)
    gfxQuad:setRect(0, 0, sizeX, sizeY)
    gfxQuad:setUVRect(0, 0, 1, 1)
  
    prop = MOAIProp2D.new()
    prop:setDeck(gfxQuad)
    prop:setLoc(posX, posY)
    layer:insertProp(prop)
    return prop
end

function removeImage(image)
    layer:removeProp(image)
end

function prepareWindow(onDraw)
    MOAISim.openWindow("test", 1024, 768)

    viewport = MOAIViewport.new()
    viewport:setSize(1024, 768)
    viewport:setScale(1024, -768)
    viewport:setOffset(-1, 1)

    layer = MOAILayer2D.new()
    layer:setViewport(viewport)
    MOAISim.pushRenderPass(layer)
 
    return layer
end

-- Configuration --
function pointerCallback(x, y)
    mouseX, mouseY = layer:wndToWorld(x, y)
    onMouseMove(mouseX, mouseY)
end

function callbackConfiguration(onClickLeft, onClickRight, pointerCallback, onKeyPress, onDraw, layer)
    -- callbacks configuration
    MOAIInputMgr.device.mouseLeft:setCallback(onClickLeft)
    MOAIInputMgr.device.mouseRight:setCallback(onClickRight)
    MOAIInputMgr.device.pointer:setCallback(pointerCallback)
    if (MOAIInputMgr.device.keyboard) then
        MOAIInputMgr.device.keyboard:setCallback(onKeyPress)
    end
    
    if (onDraw and layer) then
        scriptDeck = MOAIScriptDeck.new ()
        scriptDeck:setRect (0, 0, 1, 1)
        scriptDeck:setDrawCallback (onDraw)

        prop = MOAIProp2D.new()
        prop:setDeck(scriptDeck)
        layer:insertProp(prop)
    end
end

function addCreature(creature_name, positionX, positionY)
    return drawCreature(layer, creature_name, positionX, positionY)
end

function removeCreature(creature)
    layer:removeProp(creature)
end

function mainLoop()
    mainThread = MOAIThread.new()
    mainThread:run(
      function ()
        timer0 = os.clock()
        while true do
            timer1 = os.clock()
            time_elapsed = math.min(timer1-timer0, 1/30)
            onUpdate(time_elapsed)
            timer0 = timer1
            coroutine.yield()
        end
      end
    )
end