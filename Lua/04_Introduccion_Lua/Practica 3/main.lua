-- Escribe codigo
require "library"
prepareWindow()

carta, carta_image = drawImage(layer, "cards\\A_C.png", 256, 256, 79, 123)
mousePositionX = 0
mousePositionY = 0
bCharHasBeenPressed = false
CardType = nil
PreviousChar = nil
NumCar = nil


function onUpdate(seconds)
end

function onClickLeft(down)
    if down then
        print("Clicked Left")
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
    image_file = nil
    key_pressed = convertKeyToChar(key)
    print("Key pressed: ", key_pressed)
    -- Escribe tu código para gestion de teclado
    
    StringKey = tostring(key_pressed)
    
    if(StringKey == "c" or StringKey == "d" or StringKey == "t" or StringKey == "p")and down then
    
    bCharHasBeenPressed = true
    
    CarType = StringKey:upper()
    PreviousChar = StringKey
    
    end
    
    if(bCharHasBeenPressed)then
    
    if(down and PreviousChar~= key_pressed and CarType ~= nil)then
    
    NumCar = tostring(key_pressed)
    NumCar = NumCar:upper()
    
    image_file = "cards\\" .. NumCar .. "_" .. CarType .. ".png"
    
    print("image_file: ", image_file)
    
    end
    end
    
    
    -- Termina tu código
    
    if image_file then
        setImage(carta_image, image_file)
    end
end


function obtenerIndice(tabla, elemento)
    for indice, valor in ipairs(tabla) do
        if valor == elemento then
            return indice
        end
    end
    return nil  -- Elemento no encontrado en la tabla
end



callbackConfiguration(onClickLeft, onClickRight, onMouseMove, onKeyPress)
mainLoop()

