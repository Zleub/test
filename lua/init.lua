inspect = require 'lua.inspect'
modules = require 'lua.modules'

for k,v in ipairs(modules) do
	_G[v] = require('mod.'..v)
end

print(inspect(_G.Socket))
