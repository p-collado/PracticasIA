-- Escribe codigo
require "library"
prepareWindow()


-- Definition
Vector = {}
Vector.__index = Vector

-- Constructor
function Vector.new(elements)
    self = setmetatable({}, Vector)
    self.elements = elements
    return self
end

-- Vector Print
function Vector:__tostring()
    return "Vector(" .. table.concat(self.elements, ", ") .. ")"
end

-- operator +
function Vector.__add(v1, v2)
    if #v1.elements ~= #v2.elements then
        error("Los vectores deben tener el mismo numero de elementos")
    end

    result = {}
    
    for i = 1, #v1.elements do
        table.insert(result, v1.elements[i] + v2.elements[i])
    end

    return Vector.new(result)
end

-- Operator -
function Vector.__sub(v1, v2)
    if #v1.elements ~= #v2.elements then
        error("Los vectores deben tener la misma longitud para restarse.")
    end

    result = {}
    
    for i = 1, #v1.elements do
        table.insert(result, v1.elements[i] - v2.elements[i])
    end

    return Vector.new(result)
end

-- Dot
function Vector:Dot(other)
    if #self.elements ~= #other.elements then
        error("Los vectores deben tener la misma longitud para calcular el producto escalar.")
    end

    result = 0
    
    for i = 1, #self.elements do
        result = result + self.elements[i] * other.elements[i]
    end

    return result
end

-- Vector Length
function Vector:Size()

    sum = 0
    
    for i = 1, #self.elements do
        sum = sum + self.elements[i] * self.elements[i]
    end

    return math.sqrt(sum)
end

-- Método para normalizar el vector
function Vector:Normalize()

    length = self:Size()
    
    result = {}
    
    for i = 1, #self.elements do
        table.insert(result, self.elements[i] / length)
    end

    return Vector.new(result)
end

-- Método para escalar el vector
function Vector:Scale(factor)

    result = {}
    
    for i = 1, #self.elements do
        table.insert(result, self.elements[i] * factor)
    end

    return Vector.new(result)
end

function onUpdate(seconds)
end

function onClickLeft(down)
    print("Clicked Left")
    if not down then
        -- Escribe tu código para el botón izquierdo
        
VectorA = Vector.new({1, 2, 3})
VectorB = Vector.new({4, 5, 6})

print("v1 =", VectorA)
print("v2 =", VectorB)
print("Add:", VectorA + VectorB)
print("Subs:", VectorA - VectorB)
print("Dot:", VectorA:Dot(VectorB))
print("Size v1:", VectorA:Size())
print("Normlized v1:", VectorA:Normalize())
print("V1 scaled by 2:", VectorA:Scale(2))
        
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

