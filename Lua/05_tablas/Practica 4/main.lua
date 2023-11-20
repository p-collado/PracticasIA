-- Escribe codigo
require "library"
prepareWindow()

mousePositionX = nil
mousePositionY = nil

-- Define tus variables globales
criaturas = {
    grifo = { texture = "creatures/gryphon.png", size = {x = 92, y = 92}},
    mago = { texture = "creatures/mage.png", size = {x = 64, y = 64}},
    grunt = { texture = "creatures/grunt.png", size = {x = 72, y = 72}},
    peon = { texture = "creatures/peon.png", size = {x = 32, y = 32}},
    dragon = { texture = "creatures/dragon.png", size = {x = 128, y = 128}},
}

mapa = {
    {
        name = "grifo",
        position = { x = 200, y = 100},
    },
    {
        name = "mago",
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
        {
        name = "dragon",
        position = { x = 800, y = 400},
    },
        {
        name = "dragon",
        position = { x = 0, y = 400},
    },
        {
        name = "mago",
        position = { x = 100, y = 300},
    },
            {
        name = "grunt",
        position = { x = 400, y = 600},
    },
            {
        name = "grunt",
        position = { x = 400, y = 700},
    },
}
    
-- Fin de tus variables globales

-- Define tus funciones y llamadas
function addCreature(creature_name, posX, posY)
    texture_name = criaturas[creature_name].texture
    addImage(texture_name, posX, posY, criaturas[creature_name].size.x, criaturas[creature_name].size.y)
end

function drawMap(map)
    for iCreature = 1, #mapa do
        addCreature(mapa[iCreature].name, mapa[iCreature].position.x, mapa[iCreature].position.y)
    end
end

drawMap(mapa)

-- Fin de tus funciones

function onUpdate(seconds)
end

function onClickLeft(down)
    print("Clicked Left")
    if not down then
        -- Escribe tu código para el botón izquierdo
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

