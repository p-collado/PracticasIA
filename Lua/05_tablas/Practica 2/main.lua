-- Escribe codigo
require "library"
prepareWindow()

mousePositionX = nil
mousePositionY = nil

-- Define tus variables globales

creatures = {}
creatures["grunt"]= { image = "creatures/grunt.png", dimX = 64, dimY = 64}
creatures["mago"] = { image = "creatures/mago.png", dimX = 24, dimY = 24}
creatures["grifo"] = { image = "creatures/grifo.png", dimX = 128, dimY = 128}
creatures["dragon"] = { image = "creatures/dragon.png", dimX = 64, dimY = 64}

-- Fin de tus variables globales

-- Define tus funciones y llamadas


function addCreature(nombre, positionX, positionY)
    addImage(creatures[nombre].image ,positionX, positionY, creatures[nombre].dimX,creatures[nombre].dimY)
end

-- Fin de tus funciones



function onUpdate(seconds)
end

function onClickLeft(down)
    print("Clicked Left")
    if not down then
        -- Escribe tu código para el botón izquierdo
        
        addCreature("dragon", mousePositionX,mousePositionY)
        
        -- Termina tu código
    end
end

function onClickRight(down)
    print("Clicked Right")
    if not down then
        -- Escribe tu código para el botón derecho
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

