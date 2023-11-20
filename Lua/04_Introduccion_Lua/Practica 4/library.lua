creatures = {}
creatures.grunt = { image = "grunt.png", dimX = 64, dimY = 64}
creatures.mage = { image = "mago.png", dimX = 24, dimY = 24}
creatures.griphon = { image = "grifo.png", dimX = 128, dimY = 128}
creatures.dragon = { image = "dragon.png", dimX = 64, dimY = 64}
creatures.health_bar = {image = "health_bar.png", dimX = 256, dimY = 119}
creatures.wow = {image = "wow.png", dimX = 1024, dimY = 768}
creatures.blue_pin = {image = "blue_pin.png", dimX = 64, dimY = 113}
creatures.red_pin = {image = "red_pin.png", dimX = 64, dimY = 113}
creatures.green_pin = {image = "green_pin.png", dimX = 64, dimY = 113}
creatures.yellow_pin = {image = "yellow_pin.png", dimX = 64, dimY = 113}

function drawCreature(the_layer, name, posX, posY)
    posX = posX or 0
    posY = posY or 0
    gfxQuad = MOAIGfxQuad2D.new()
    
    texture_name = creatures[name].image
  
    gfxQuad:setTexture(texture_name)
    gfxQuad:setRect(0, 0, creatures[name].dimX, creatures[name].dimY)
    gfxQuad:setUVRect(0, 0, 1, 1)
  
    prop = MOAIProp2D.new()
    prop:setDeck(gfxQuad)
    prop:setLoc(posX, posY)
    layer:insertProp(prop)
    return prop
end

function drawPoint(x, y)
    r, g, b, a = 1, 1, 0, 1
    MOAIGfxDevice.setPenColor (r, g, b, a)
    MOAIDraw.drawPoints(x, y)
end

function drawBackground(the_layer, name)
    return drawCreature(the_layer, name)
end

function getPropPosition(prop)
    return prop:getLoc()
end
    
function setPropPosition(prop, x, y)
    prop:setLoc(x, y)
end

function getCreatureSize(name)
    return creatures[name].dimX, creatures[name].dimY
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