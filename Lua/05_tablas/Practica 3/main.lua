-- Escribe codigo
require "library"
prepareWindow()

mousePositionX = nil
mousePositionY = nil

-- Define tus variables globales

creatures = {}
creatures.grunt = { image = "creatures//grunt.png", dimX = 64, dimY = 64} 
creatures.mage = { image = "creatures//mage.png", dimX = 24, dimY = 24} 
creatures.griphon = { image = "creatures/gryphon.png", dimX = 128, dimY = 128} 
creatures.dragon = { image = "creatures//dragon.png", dimX = 64, dimY = 64} 
creatures.peon = { image = "creatures//peon.png", dimX = 64, dimY = 64}


mapa = {
    {
        name = "griphon",
        position = { x = 200, y = 100},
    },
    {
        name = "mage",
        position = { x = 100, y = 200},
    },
    {
        name = "peon",
        position = { x = 400, y = 100},
    },
    {
        name = "dragon",
        position = { x = 400, y = 400},
    },
}


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
       for i = 1, #mapa do   
        addCreature(mapa[i].name, mapa[i].position.x, mapa[i].position.y)
       end 

        
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

