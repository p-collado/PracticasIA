MOAISim.openWindow("game", 1024, 768)

viewport = MOAIViewport.new()
viewport:setSize (1024, 768)
viewport:setScale (1024, -768)

layer = MOAILayer2D.new()
layer:setViewport(viewport)
MOAISim.pushRenderPass(layer)

function createImage(texture_name, char_size)
	local gfxQuad = MOAIGfxQuad2D.new()
	gfxQuad:setTexture(texture_name)
	gfxQuad:setRect(-char_size/2, -char_size/2, char_size/2, char_size/2)
	gfxQuad:setUVRect(0, 0, 1, 1)
	return gfxQuad
end

function drawBackground(image, sizeX, sizeY)
    gfxQuad = MOAIGfxQuad2D.new()
    gfxQuad:setTexture(image)
    gfxQuad:setRect(-sizeX/2, -sizeY/2, sizeX/2, sizeY/2)
    gfxQuad:setUVRect(0, 0, 1, 1)
    prop = MOAIProp2D.new()
    prop:setDeck(gfxQuad)
    prop:setLoc(posX, posY)
    layer:insertProp(prop)
end

-- drawBackground("background.png", 1024, 768)

char_size = 64
gfxQuad = createImage("dragon.png", char_size*2)
gfxQuad1 = createImage("dragon_hit.png", char_size*2)
gfxQuad2 = createImage("dragon_attack.png", char_size*2)
gfxQuad3 = createImage("dragon_alarm.png", char_size*2)
gfxQuad4 = createImage("dragon_dead.png", char_size*2)
gfxQuad5 = createImage("dragon_idle.png", char_size*2)
gfxQuad6 = createImage("dragon_windup.png", char_size*2)

--prop mage
gfxQuadMage = createImage("mago.png", char_size/2)
  
prop = MOAIProp2D.new()
prop:setDeck(gfxQuad)

entity = Character.new()

-- Add images for the different states
entity:addImage(gfxQuad)    -- SetImage(0)  dragon.png
entity:addImageName("dragon.png")
entity:addImage(gfxQuad1)   -- SetImage(1)  dragon_hit.png
entity:addImageName("dragon_hit.png")
entity:addImage(gfxQuad2)   -- SetImage(2)  dragon_attack.png
entity:addImageName("dragon_attack.png")
entity:addImage(gfxQuad3)   -- SetImage(3)  dragon_alarm.png
entity:addImageName("dragon_alarm.png")
entity:addImage(gfxQuad4)   -- SetImage(4)  dragon_dead.png
entity:addImageName("dragon_dead.png")
entity:addImage(gfxQuad5)   -- SetImage(5)  dragon_idle.png
entity:addImageName("dragon_idle.png")
entity:addImage(gfxQuad6)   -- SetImage(6)  dragon_windup.png
entity:addImageName("dragon_windup.png")

-- Add prop to be the renderable for this character
entity:setProp(prop, layer)
-- Start the character (allow calls to OnUpdate)
entity:start()
entity:setLoc(0, 0)
entity:setRot(0)
entity:setLinearVel(10, 20)
entity:setAngularVel(30)
entity:readAndInitializeStateMachine("statemachine.xml")

-- Enable Debug Draw
debug = MOAIDrawDebug.get();
layer:setDrawDebug(debug)
-- Add this character to draw debug
MOAIDrawDebug.insertEntity(entity)


pathfinder = Pathfinder.new()
pathfinder:setStartPosition(5, 10)
pathfinder:setEndPosition(20, 40)
MOAIDrawDebug.insertEntity(pathfinder)

entity:setPathfinder(pathfinder)

mouseX = 0
mouseY = 0

function onClick(down)
  pathfinder:setStartPosition(mouseX, mouseY)
  if down == true then
	enemy = Character.new()

	prop = MOAIProp2D.new()
	prop:setDeck(gfxQuadMage)

	enemy:setProp(prop, layer)
	enemy:start()
    enemy:setLoc(mouseX, mouseY)
	enemy:setHealth(60)
	enemy:readAndInitializeStateMachine("enemystatemachine.xml")
	entity:addTarget(enemy:getPointerToThis())
  end
  
end

function onRightClick(down)
  pathfinder:setEndPosition(mouseX, mouseY)
end

function pointerCallback(x, y)
    mouseX, mouseY = layer:wndToWorld(x, y)
end

MOAIInputMgr.device.mouseLeft:setCallback(onClick)
MOAIInputMgr.device.mouseRight:setCallback(onRightClick)
MOAIInputMgr.device.pointer:setCallback(pointerCallback)

function onKeyPressed(key, down)
	if key == 32 then
		if down then
			print(tostring(key))
		else
			pathfinder:pathfindStep()
		end
	end
end

if (MOAIInputMgr.device.keyboard) then
    MOAIInputMgr.device.keyboard:setCallback(onKeyPressed)
end
