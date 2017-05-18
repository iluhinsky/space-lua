--print("LUA START: Ship2")

currentTime = GetTime()

if currentTime < 3.0 then
	DisableShield("shield2")
end
if 3.0 < currentTime then
	EnableShield("shield2")
end
if 8.0 < currentTime then
--	DisableShield("shield2")
end

--is = IsDirectionAllowed('engine1', 1.0, 1.0, 0.0)
--print('is = ', is)
--Gas('engine1', 1.0, 1.0, 0.0, 10)

selfID = GetSelfID()
size = shipsID:GetSize()

--for i = 0, size - 1 do
	i = math.random(0, size - 1)
	id = shipsID:at(i)
	shipInfo = GetShipInfo(id)
	selfInfo = GetShipInfo(selfID)

	selfTeam = selfInfo.team
	shipTeam = shipInfo.team

	if id ~= selfID and selfTeam ~= shipTeam then
	--is = IsDirectionAllowed('weapon1', shipInfo.x, shipInfo.y, shipInfo.z)	
		dt = math.sqrt ((shipInfo.x - selfInfo.x) ^ 2 + (shipInfo.y - selfInfo.y) ^ 2 + (shipInfo.z - selfInfo.z) ^ 2) / 10.0
		dirx = (shipInfo.x - selfInfo.x) + shipInfo.vx * dt
		diry = (shipInfo.y - selfInfo.y) + shipInfo.vy * dt
		dirz = (shipInfo.z - selfInfo.z) + shipInfo.vz * dt
		

	Shoot('weapon1', dirx, diry, dirz)
	end
--end

--print("LUA FINISH: Ship2")

