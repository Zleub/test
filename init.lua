for k,v in pairs(_G) do
	print(k, v, type(v))
	if type(v) == 'table' and v ~= _G then
		_G[k] = nil
	end
end

print('')

for k,v in pairs(_G) do
	print(k,v)
end

print('')

map = {}
for i=0,100 do
	map[i] = 0
end

