-- Escribe codigo
require "library"
prepareWindow()

pointA_X = 10
pointA_Y = 10
pointB_X = 10
pointB_Y = 10

dirX = 0
dirY = 0

dirNormalX = 0
dirNormalY = 0

size = 0

creature = drawCreature(layer, "griphon", 256, 256)
pointA = drawCreature(layer, "blue_pin", pointA_X, pointA_Y)
pointB = drawCreature(layer, "green_pin", pointB_X, pointB_Y)

mousePositionX = nil
mousePositionY = nil

function onUpdate(seconds)
    creaturePositionX, creaturePositionY = getPropPosition(creature)
    -- Empieza tu código
    
    dirX = pointB_X - pointA_X
    dirY = pointB_Y - pointA_Y
    
    size = math.sqrt((dirX*dirX) + (dirY*dirY))
    
    if size ~= 0 then
       dirNormalX = dirX / size
       dirNormalY = dirY / size
       creaturePositionX = creaturePositionX + (dirNormalX * 50) * seconds
       creaturePositionY = creaturePositionY + (dirNormalY * 50) * seconds
    end 
    
    -- Termina tu código
    setPropPosition(creature, creaturePositionX, creaturePositionY)
    setPropPosition(pointA, pointA_X, pointA_Y)
    setPropPosition(pointB, pointB_X, pointB_Y)
end

function onClickLeft(down)
    print("Clicked Left")
    if down then
        -- Escribe tu código para el botón izquierdo
        
        pointA_X = mousePositionX
        pointA_Y = mousePositionY
        
        -- Termina tu código
        setPropPosition(creature, pointA_X, pointA_Y)
    end
end

function onClickRight(down)
    print("Clicked Right")
    if down then
        -- Escribe tu código para el botón derecho
        
        pointB_X = mousePositionX
        pointB_Y = mousePositionY
        
        -- Termina tu código
        setPropPosition(creature, pointA_X, pointA_Y)
    end
end

function onMouseMove(posX, posY)
    mousePositionX = posX
    mousePositionY = posY
    --print("Mouse Moved to " .. posX .. ","..posY)
end

function onKeyPress(key, down)
    print("Key pressed: "..key)
end



callbackConfiguration(onClickLeft, onClickRight, onMouseMove, onKeyPress)
mainLoop()

