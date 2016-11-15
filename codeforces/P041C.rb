s = gets
while s.gsub!(/(.+?)dot(.+)/, '\1.\2') do
end
s.gsub!(/(.+?)at(.+)/, '\1@\2')
puts s
