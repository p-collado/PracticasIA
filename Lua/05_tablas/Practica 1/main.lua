-- Escribe codigo
require "library"
require "prepare"

-- Define tus variables globales

CuadradoPosition = {x = 100, y = 100}
CuadradoSize = 300

CuadradoPositionCurrent = {x = nil, y = nil}


-- Termina tu definicion de variables

function pintarPunto(punto)
    -- Rellenar código para pintar un punto en la pantalla
    
    
    drawPoint(punto.x,punto.y)
    
    -- Fin de código
end

function onUpdate(seconds)
end

function onDraw()
    -- Empieza tu código, que debe emplear la funcion pintarPunto
    CuadradoPositionCurrent.x = CuadradoPosition.x
    CuadradoPositionCurrent.y = CuadradoPosition.y
    
    for i = 1 , CuadradoSize do    
   
    for j = 1 , CuadradoSize  do
    
    pintarPunto(CuadradoPositionCurrent)
 
    CuadradoPositionCurrent.y = CuadradoPosition.y
    CuadradoPositionCurrent.y = CuadradoPositionCurrent.y +  j
    
    end
    
    CuadradoPositionCurrent.x = CuadradoPosition.x
    CuadradoPositionCurrent.x = CuadradoPositionCurrent.x + i
    CuadradoPositionCurrent.y = CuadradoPosition.y
    
    end
    
    -- Termina tu código
end

function onClickLeft(down)
    print("Clicked Left")
    if down then
    end
end

function onClickRight(down)
    print("Clicked Right")
    if down then
    end
end


function onMouseMove(posX, posY)
    --print("Mouse Moved to " .. posX .. ","..posY)
end

function onKeyPress(key, down)
    print("Key pressed: "..key)
end



callbackConfiguration(onClickLeft, onClickRight, onMouseMove, onKeyPress, onDraw, window_layer)
mainLoop()

