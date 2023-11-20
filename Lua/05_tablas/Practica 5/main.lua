-- Escribe codigo
require "library"
require "xml"
prepareWindow()

mousePositionX = nil
mousePositionY = nil

-- Define tus variables globales

creatures = readXML("criaturas.xml")
map = readXML("map.xml")

---- Fin de tus variables globales

-- Define tus funciones y llamadas

function addCreature(creature_name, posX, posY)
    for i = 1, #creatures do
    nombreelemento = creatures[i][1][1]
    if ( nombreelemento == creature_name) then
        texture_name = creatures[i][2][1]
        sizex = creatures[i][3][1][1]
        sizex = tonumber(sizex)
        sizey = creatures[i][3][2][1]
        sizey = tonumber(sizey)
        addImage(texture_name, tonumber(posX), tonumber(posY), sizex, sizey)
    end
    end
end

function drawMap(map)
    for iCreature = 1, #map do
    criaturaenmapa = map[iCreature]
    nombrecriatura = criaturaenmapa[1][1]
    posx = criaturaenmapa[2][1][1]
    posy = criaturaenmapa[2][2][1]
    addCreature(nombrecriatura, posx, posy)
    end
end

-- Fin de tus funciones

drawMap(map)

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

