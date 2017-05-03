--print("LUA START: Ship1")

currentTime = GetTime()

if 3.0 < currentTime and currentTime < 15 then

	isDirectionAllowed = IsDirectionAllowed("weapon1", 0.0, 1.0, 0.0)
	
	if isDirectionAllowed == true then
--		print("LUA: Direction is right! Shooting!")
		Shoot("weapon1", 0.0, 1.0, 0.0)
	end
end

--print("LUA FINISH: Ship1")
