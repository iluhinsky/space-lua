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

is = IsDirectionAllowed('engine1', 1.0, 1.0, 0.0)
--print('is = ', is)
Gas('engine1', 1.0, 1.0, 0.0, 10)
--print('#2: ', shipsID:GetSize())

--print("LUA FINISH: Ship2")

