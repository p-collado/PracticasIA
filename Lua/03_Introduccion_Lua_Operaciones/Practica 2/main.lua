-- Escribe codigo
require "library"
prepareWindow()

creature = drawCreature(layer, "griphon", 256, 256)

function onUpdate(seconds)
    creaturePositionX, creaturePositionY = getPropPosition(creature)
    -- Empieza tu código
    
    creaturePositionX = creaturePositionX - (10 * seconds)
    
    -- Termina tu código
    setPropPosition(creature, creaturePositionX, creaturePositionY)
end

function onClickLeft(down)
    print("Clicked Left")
end

function onClickRight(down)
    print("Clicked Right")
end

function onMouseMove(posX, posY)
    --print("Mouse Moved to " .. posX .. ","..posY)
end

function onKeyPress(key, down)
    print("Key pressed: "..key)
end



callbackConfiguration(onClickLeft, onClickRight, onMouseMove, onKeyPress)
mainLoop()

