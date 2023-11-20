-- Escribe codigo
require "library"
window_layer, debug_layer = prepareWindow()
-- Define tus variables globales
showedCreatures = {}

--esto es porque el library no se consigue abrir en este proyecto
creatures = {}
creatures[1] = {image = "creatures//grunt.png", dimX = 64, dimY = 64, life = 200}
creatures[2] = {image = "creatures//mage.png", dimX = 24, dimY = 24, life = 30} 
creatures[3] = {image = "creatures//gryphon.png", dimX = 128, dimY = 128, life = 500} 
creatures[4] = {image = "creatures//dragon.png", dimX = 64, dimY = 64, life = 1000}
creatures[5] = {image = "creatures//fireball.png", dimX = 33, dimY = 22, life = 1} 
creatures[6]= {image = "creatures//peon.png", dimX = 34, dimY = 34, life = 15}
-- Fin de tus variables globales

-- Define tus funciones
function getRandomCreature()
    local creature
    
    if(#showedCreatures==#creatures) then
    showedCreatures = {}
    end
    
     creature = creatures[math.random(1, #creatures)]
     
    while IsInArray(creature) do
    --repeat
        creature = creatures[math.random(1, #creatures)]
    --until not IsInArray(creature)
     end
     
      table.insert(showedCreatures,creature)
      
     return creature
    
end

function IsInArray(othercreature)
    for i, creature in ipairs(showedCreatures) do
        if creature.image == othercreature.image then
            return true
        end
    end
    return false
end

function corutineClicks()
    addCreature(getRandomCreature(),mousePositionX,mousePositionY)
    print("state of coroutine in function is", coroutine.status(clicksCoroutine))
end

function addCreature(creature, positionX, positionY)
   texture_name = creature.image
   sizeX=creature.dimX
   sizeY=creature.dimY
   
    return addImage(texture_name,positionX, positionY,sizeX,sizeY)
end


-- Fin de tus funciones

function onDraw()
    -- Escribe tu código para pintar pixel a pixel
    
    -- Fin de tu código
end

function onUpdate(seconds)
    -- Escribe tu código para ejecutar cada frame
    -- Fin del código
end

function onClickLeft(down)
    -- Escribe tu código para el click del ratón izquierdo (down será true si se ha pulsado, false si se ha soltado)
    if down then
    end
    -- Fin del código
end

function onClickRight(down)
    -- Escribe tu código para el click del ratón derecho (down será true si se ha pulsado, false si se ha soltado)
    if down then
-- Crea la corutina
local clicksCoroutine = coroutine.create(corutineClicks)
     coroutine.resume(clicksCoroutine)
    print("state of coroutine is", coroutine.status(clicksCoroutine))
    end
    -- Fin del código
end

function onMouseMove(posX, posY)
    mousePositionX = posX
    mousePositionY = posY
    -- Escribe tu código cuando el ratón se mueve

    -- Fin del código
end

function getCreature()
    for i = 1, #creatures do
        if(creatures[i].life>50) then
            coroutine.yield(creatures[i].image)
        end
    end
end

function CreaturesNames()
    return coroutine.wrap(getCreature)
end

for creatureName in CreaturesNames() do
print("Creature: ", creatureName)
end

callbackConfiguration(onClickLeft, onClickRight, onMouseMove, onKeyPress, onDraw, debug_layer)
mainLoop()

