
local cjson = require "cjson"

local function UpdateNext(m, t)
	print("fdfdfdfd 333")
	if m[t.ver] ~= nil then
		return m[t.ver](m, t)
	else
		return true,cjson.encode(t) 	
	end	
end

local module_func = {}
local test = {}
test.ver = 2

test[1] = function(t)
	table.remove(t.base, 2)
	return UpdateNext(test, t, 2)
end

test[2] = function(t)
	t.ver = 2
	return true,cjson.encode(t)
end

module_func.test = test

function OnUpdate(name, val, ver)
	if module_func[name].ver ~= ver then
		return false,"not the same ver C++:"..ver.." Lua:"..module_func[name].ver
	end	
	local t = cjson.decode(val)
	if t.ver == ver then
		return true,val
	end	
	module_func[name][t.ver](t)
end
