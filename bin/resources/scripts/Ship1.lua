--print("LUA START: Ship1")

--SwitchShield("abc", 0, 0.0)
--[[
currentTime = 0.0
timeForNextSwitch = 10.0
isShieldWorking = false

while true do
--	print("currentTime =", GetTime())
	currentTime = GetTime()
	if currentTime > timeForNextSwitch then
		timeForNextSwitch = timeForNextSwitch + 10.0		

		if isShieldWorking then
			DisableShield("shield1")
			isShieldWorking = false
		else
			EnableShield("shield1")
			isShieldWorking = true
		end
	end
end
--]]
--print("LUA FINISH: Ship1")

currentTime = GetTime()

if currentTime < 5.0 then
	DisableShield("shield1")
end
if 5.0 < currentTime then
	EnableShield("shield1")
end
if 10.0 < currentTime and currentTime < 15.0 then
--	DisableShield("shield1")
end
if 15.0 < currentTime then
--	EnableShield("shield1")
end










