--print("LUA START: Ship1")

currentTime = GetTime()

if currentTime < 1.0 then
	DisableShield("shield1")
end
if 1.0 < currentTime then
	EnableShield("shield1")
end
if 3.0 < currentTime and currentTime < 15 then
--	DisableShield("shield1")
	isDirectionAllowed = IsDirectionAllowed("weapon1", 0.0, 1.0, 0.0)
	if isDirectionAllowed == true then
--		print("LUA: Direction is right! Shooting!")
		Shoot("weapon1", 0.0, 1.0, 0.0)
	end
end

if currentTime < 0.5 then
--	print('@@@ ', shipsID:GetSize())
--	print('@@@@ ', shipsID:at(0))
--	info = GetShipInfo(0)
--	print('ShipInfo in LUA: ', info.x, info.y, info.z, info.team)

	v = GetBlocks(0)
--	print('@@@  ', v:GetSize(), v:at(0), v:at(1), v:at(2), v:at(3))	
	blockID = v:at(2)
	blockInfo = GetBlockInfo(0, blockID)
--	print('@@@ ', blockInfo.x, blockInfo.y, blockInfo.z)
end


--print("LUA FINISH: Ship1")
