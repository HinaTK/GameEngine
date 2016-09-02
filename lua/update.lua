
local cjson = require "cjson"

local function UpdateNext(m, t, cur)
	if cur < m.ver then
		if m[cur] == nil then
			return false,"no this version"
		else
			return m[cur](t)	
		end	
	elseif cur == m.ver then
		t.ver = m.ver
		return true,cjson.encode(t)	
	else
		return false,"Lua version greater than C++"	
	end	
end

local module_func = {}

function OnUpdate(name, val)
	local t = cjson.decode(val)
	return UpdateNext(module_func[name], t, t.ver)
end


local test = {ver = 2}

test[1] = function(t)
	table.remove(t.base, 2)
	return UpdateNext(test, t, 2)
end

module_func.test = test

