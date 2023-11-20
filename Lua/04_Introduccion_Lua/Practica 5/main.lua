-- Escribe codigo
require "library"
prepareWindow()

creature = drawCreature(layer, "griphon", 256, 256)
mousePositionX = 0
mousePositionY = 0

movement = 1

randomX = 0
randomY = 0

function onUpdate(seconds)
    creaturePositionX, creaturePositionY = getPropPosition(creature)
    -- Empieza tu c�digo para mover a la criatura
    

    creaturePositionX = creaturePositionX + (randomX * 40) * seconds
    creaturePositionY = creaturePositionY + (randomY * 40) * seconds
    

    -- Termina tu c�digo
    setPropPosition(creature, creaturePositionX, creaturePositionY)
end

function onClickLeft(down)
    print("Clicked Left")
end

function onClickRight(down)
    print("Clicked Right")
end

function onMouseMove(posX, posY)
    mousePositionX = posX
    mousePositionY = posY
    creatureSizeX, creatureSizeY = getCreatureSize("griphon")
    creaturePositionX, creaturePositionY = getPropPosition(creature)
    -- Escribe tu c�digo aqui para el movimiento del rat�n
    if((mousePositionX >= creaturePositionX and mousePositionX <= creaturePositionX + creatureSizeX) and 
       (mousePositionY >= creaturePositionY and mousePositionY <= creaturePositionY + creatureSizeY)) then
       
       if(movement == 1) then 
            randomX = math.random(-1,1)
            randomY = math.random(-1,1)
            movement = 0
       end
    end
    
      if((mousePositionX < creaturePositionX or mousePositionX > creaturePositionX + creatureSizeX) and 
           (mousePositionY < creaturePositionY or mousePositionY > creaturePositionY + creatureSizeY)) then
            movement = 1
       end
    -- Termina tu c�digo
end

function onKeyPress(key, down)
    print("Key pressed: "..key)
end



callbackConfiguration(onClickLeft, onClickRight, onMouseMove, onKeyPress)
mainLoop()

