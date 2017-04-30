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

--print('#2: ', shipsID:GetSize())

--print("LUA FINISH: Ship2")

