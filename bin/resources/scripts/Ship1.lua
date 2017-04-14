--print("LUA START: Ship1")

currentTime = GetTime()

if currentTime < 5.0 then
	DisableShield("shield1")
end
if 5.0 < currentTime then
	EnableShield("shield1")
end
if 5.0 < currentTime and currentTime < 5.1 then
--	DisableShield("shield1")
	Shoot("weapon1", 0.0, -10.0, 0.0)
end
--if 11.0 < currentTime then
--	EnableShield("shield1")
--end

--print("LUA FINISH: Ship1")








