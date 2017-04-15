--print("LUA START: Ship1")

currentTime = GetTime()

if currentTime < 1.0 then
	DisableShield("shield1")
end
if 1.0 < currentTime then
	EnableShield("shield1")
end
if 3.0 < currentTime and currentTime < 3.2 then
--	DisableShield("shield1")
	isDirectionAllowed = IsDirectionAllowed("weapon1", 0.0, 1.0, 0.0)
	if isDirectionAllowed == true then
		print("LUA: Direction is right! Shooting!")
		Shoot("weapon1", 0.0, 1.0, 0.0)
	end
end
--if 11.0 < currentTime then
--	EnableShield("shield1")
--end

--print("LUA FINISH: Ship1")








