--print("LUA START: Ship1")

currentTime = GetTime ()


selfID = GetSelfID ()
size = shipsID:GetSize ()

i = math.random(0, size - 1)
id = shipsID:at(i)
shipInfo = GetShipInfo (id)
selfInfo = GetShipInfo (selfID)

if 0.0 < currentTime and currentTime < 10.0 then
	dirx = (shipInfo.x - selfInfo.x) + shipInfo.vx
	diry = (shipInfo.y - selfInfo.y) + shipInfo.vy
	dirz = (shipInfo.z - selfInfo.z) + shipInfo.vz
	Shoot('weapon1', dirx, diry, dirz)
end

if currentTime > 10.0 then
	EnableShield('shield1')
	EnableShield('shield2')
end


--print("LUA FINISH: Ship1")
