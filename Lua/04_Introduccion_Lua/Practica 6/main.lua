-- Escribe codigo
require "library"
prepareWindow()

creature = drawCreature(layer, "griphon", 256, 256)
mousePositionX = 0
mousePositionY = 0

gameOver = false

randomX = 0
randomY = 0

function onUpdate(seconds)
    creaturePositionX, creaturePositionY = getPropPosition(creature)
    creatureSizeX, creatureSizeY = getCreatureSize("griphon")
    -- Empieza tu código para mover a la criatura

    if(creaturePositionX < -(creatureSizeX/2) or creaturePositionX > 1024 + (creatureSizeX/2) and creaturePositionY < -(creatureSizeY/2) or creaturePositionY > 768 + (creatureSizeY/2)) then
           
        gameOver = true
           
    end
    
    if(gameOver) then
    
        creaturePositionX = (1024 / 2) - (creatureSizeX/2)
        creaturePositionY = (768 / 2) - (creatureSizeY/2)
        
    else
    
    creaturePositionX = creaturePositionX + randomX * 350 * seconds
    creaturePositionY = creaturePositionY + randomY * 350 * seconds

    end
    -- Termina tu código
    setPropPosition(creature, creaturePositionX, creaturePositionY)
end

function onClickLeft(down)
    print("Clicked Left")
        -- Escribe tu c?digo aqui para bot?n izquierdo rat?n
        
    creatureSizeX, creatureSizeY = getCreatureSize("griphon")
    creaturePositionX, creaturePositionY = getPropPosition(creature)
 
 if(down) then
    if((mousePositionX >= creaturePositionX and mousePositionX <= creaturePositionX + creatureSizeX) and 
       (mousePositionY >= creaturePositionY and mousePositionY <= creaturePositionY + creatureSizeY)) then
       
            randomX = math.random(-1,1)
            randomY = math.random(-1,1)

    end
 end
            -- Termina tu c?digo
end

function onClickRight(down)
    print("Clicked Right")
end

function onMouseMove(posX, posY)
    mousePositionX = posX
    mousePositionY = posY
    
end

function onKeyPress(key, down)
    print("Key pressed: "..key)
end



callbackConfiguration(onClickLeft, onClickRight, onMouseMove, onKeyPress)
mainLoop()

