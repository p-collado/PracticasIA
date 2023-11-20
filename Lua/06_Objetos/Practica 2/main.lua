-- Escribe codigo
require "library"
require "prepare"

-- Define tus variables globales
Enemigo = {}
Enemigo.__index = Enemigo

function Enemigo.new(max_vida, x, y, size)
    local self = setmetatable({}, Enemigo)
    self.vidaactual = max_vida
    self.x = x
    self.y = y
    self.size = size
    self.max_vida = max_vida

    return self
end

function Enemigo:Hurt(damage)
        if self.vidaactual > 0 then
            self.vidaactual = self.vidaactual - damage
            if self.vidaactual <= 0 then
                self.size = self.size / 2
            end
        end
end

-- Clase EnemigoHuidizo
EnemigoHuidizo = {}
EnemigoHuidizo.__index = EnemigoHuidizo

setmetatable(EnemigoHuidizo, Enemigo)

function EnemigoHuidizo.new(max_vida, x, y, size)
    local self = setmetatable({}, EnemigoHuidizo)
    self.max_vida = max_vida
    self.vidaactual = max_vida
    self.x = x
    self.y = y
    self.size = size

    return self
end

function EnemigoHuidizo:Hurt(damage)
     Enemigo.Hurt(self, damage)
     if self.vidaactual <= (self.max_vida / 2) then
        self.x = math.random(0, 1024)
        self.y = math.random(0, 768)
      end
end

 
-- Termina tu definicion de variables

function pintarPunto(punto)
    -- Rellenar código para pintar un punto en la pantalla
    
    -- Fin de código
end

function onUpdate(seconds)
end

function onDraw()
    -- Empieza tu código, que debe emplear la funcion pintarPunto
 
 

   
    -- Termina tu código
end

 enemigo1 = Enemigo.new(100,50,50,10)
enemigo1Huidizo = EnemigoHuidizo.new(100,100,100,10)

function onClickLeft(down)
    print("Clicked Left")
    if down then
-- Ejemplo de uso

print("Vida inicial:", enemigo1.vidaactual)
enemigo1:Hurt(10)
print("Vida después del daño:", enemigo1.vidaactual)
print("Tamaño: ", enemigo1.size)
    end
end

function onClickRight(down)
    print("Clicked Right")
    if down then
    
    print("Vida inicial:", enemigo1Huidizo.vidaactual)
        enemigo1Huidizo:Hurt(10)
        print("Vida después del daño:", enemigo1Huidizo.vidaactual)
        print("Tamaño:", enemigo1.size)
        print("Posicion después del daño:", enemigo1Huidizo.x,enemigo1Huidizo.y)
    
    end
end


function onMouseMove(posX, posY)
    --print("Mouse Moved to " .. posX .. ","..posY)
    mousePosX=posX
    mousePosY=posY
end

function onKeyPress(key, down)
    print("Key pressed: "..key)
end



callbackConfiguration(onClickLeft, onClickRight, onMouseMove, onKeyPress, onDraw, window_layer)
mainLoop()

