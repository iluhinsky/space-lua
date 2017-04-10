--print("LUA START: Ship1")

currentTime = GetTime()

if currentTime < 5.0 then
	DisableShield("shield1")
end
if 5.0 < currentTime then
	EnableShield("shield1")
end
if 10.0 < currentTime and currentTime < 15.0 then
	DisableShield("shield1")
end
if 15.0 < currentTime then
--	EnableShield("shield1")
end

--print("LUA FINISH: Ship1")








