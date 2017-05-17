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
--print('#2: ', shipsID:GetSize())

selfID = GetSelfID()
size = shipsID:GetSize()
--print('LUA size = ', size)
for i = 0, size - 1 do
	id = shipsID:at(i)

	if id ~= selfID then
		shipInfo = GetShipInfo(id)
		selfInfo = GetShipInfo(selfID)
		--is = IsDirectionAllowed('weapon1', shipInfo.x, shipInfo.y, shipInfo.z)	
		--print('LUA is = ', is)
		Shoot('weapon1', shipInfo.x - selfInfo.x, shipInfo.y - selfInfo.y, shipInfo.z - selfInfo.z)
		Shoot('weapon1', selfInfo.x - shipInfo.x, selfInfo.y - shipInfo.y, selfInfo.z - shipInfo.z)
		if currentTime < 0.9 then
			--print('LUA: ', shipInfo.x - selfInfo.x, shipInfo.y - selfInfo.y, shipInfo.z - selfInfo.z)
		end
	end

	if id == selfID and currentTime < 0.7 then
--		print('LUA:: ', id, selfID)
		print('LUA::::: ', shipInfo.x, selfInfo.x)
--		print('LUA::: ', shipInfo.x - selfInfo.x, shipInfo.y - selfInfo.y, shipInfo.z - selfInfo.z)
	end
end

--print("LUA FINISH: Ship2")

