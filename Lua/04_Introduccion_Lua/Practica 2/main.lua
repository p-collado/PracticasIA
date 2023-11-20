-- Escribe codigo
require "library"
prepareWindow()

creature = drawCreature(layer, "griphon", 256, 256)
mousePositionX = 0
mousePositionY = 0

dirX = 1
dirY = 0

function onUpdate(seconds)
    creaturePositionX, creaturePositionY = getPropPosition(creature)
    -- Empieza tu código para mover a la criatura
    
    creaturePositionX = creaturePositionX + (20 * dirX) * seconds
    creaturePositionY = creaturePositionY + (20 * dirY) * seconds
    
    -- Termina tu código
    setPropPosition(creature, creaturePositionX, creaturePositionY)
end

function onClickLeft(down)
    if down then
        print("Clicked Left")
        creatureSizeX, creatureSizeY = getCreatureSize("griphon")
        creaturePositionX, creaturePositionY = getPropPosition(creature)
        -- Escribe tu código aqui para botón izquierdo ratón
        if dirX == 1 and dirY == 0 then
            dirX = -1
            return
        end
        
        if dirX == -1 and dirY == 0 then
            dirX = 0
            dirY = -1
            return
        end
        
        if dirX == 0 and dirY == -1 then
            dirX= 0
            dirY = 1
            return
        end
        
        if dirX == 0 and dirY == 1 then
            dirX = 1
            dirY = 0
            return         
        end 
        -- Termina tu código
    end
end

function onClickRight(down)
    print("Clicked Right")
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

