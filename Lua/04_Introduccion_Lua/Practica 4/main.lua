-- Escribe codigo
require "library"
prepareWindow()

mousePositionX = nil
mousePositionY = nil

-- Define tus variables globales

arraycriaturas = {}
arrayVida = {}

-- Termina tu definicion de variables

function onUpdate(seconds)

    if(seconds%6==0)then
       for index, elemento in ipairs(arraycriaturas) do
            randomX = math.random(70, 1024)
            randomY = math.random(70, 768)
            setPropPosition(elemento, randomX, randomY)             
       end
    end
end

function onClickLeft(down)
    print("Clicked Left")
    creatureSizeX, creatureSizeY = getCreatureSize("griphon")
    if not down then
        -- Escribe tu código para el botón izquierdo
        if #arraycriaturas ~= 0 then
        table.insert(arraycriaturas, #arraycriaturas + 1,  addCreature("griphon", mousePositionX - (creatureSizeX/2)  , mousePositionY - (creatureSizeY/2)))
        table.insert(arrayVida, #arrayVida + 1, 25)
        else 
            table.insert(arraycriaturas, 1,  addCreature("griphon", mousePositionX - (creatureSizeX/2)  , mousePositionY - (creatureSizeY/2)))
            table.insert(arrayVida, 1, 25)
        end
        -- Termina tu código
    end
end

function onClickRight(down)
    print("Clicked Right")
    creatureSizeX, creatureSizeY = getCreatureSize("griphon")
    creaturePositionX, creaturePositionY = nil
    elementoin = nil
    if not down then
        -- Escribe tu código para el botón derecho
        index = 1
        for index, elemento in ipairs(arraycriaturas) do
              creaturePositionX, creaturePositionY = getPropPosition(elemento)
            if (mousePositionX >= creaturePositionX and mousePositionX <= creaturePositionX + creatureSizeX) and
               (mousePositionY >= creaturePositionY and mousePositionY <= creaturePositionY + creatureSizeY) then
                arrayVida[index] = arrayVida[index] - 5
                print(index, elemento)
                print(index, arrayVida[index])
            end
            if(arrayVida[index] <= 0) then
                removeCreature(elemento)
                table.remove(arraycriaturas,index)
                table.remove(arrayVida, index)
            end
        end
        -- Termina tu código
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

