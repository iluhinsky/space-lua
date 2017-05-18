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

for i = 0, size - 1 do
	id = shipsID:at(i)
	shipInfo = GetShipInfo(id)
	selfInfo = GetShipInfo(selfID)

	selfTeam = selfInfo.team
	shipTeam = shipInfo.team
	print('LUA: velocity = ', shipInfo.vx, shipInfo.vy, shipInfo.vz) --, 'coords = ', selfInfo.x, selfInfo.y, selfInfo.z)
--	vx = selfInfo.vx
--	vy = selfInfo.vy
--	print('LUA test ', selfInfo.x, vx, vy)

	if id ~= selfID and selfTeam ~= shipTeam then
		--is = IsDirectionAllowed('weapon1', shipInfo.x, shipInfo.y, shipInfo.z)	
		Shoot('weapon1', shipInfo.x - selfInfo.x, shipInfo.y - selfInfo.y, shipInfo.z - selfInfo.z)
	end
end

--print("LUA FINISH: Ship2")

