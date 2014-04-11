s = gets.chomp!
n = gets.to_i
visited = $stdin.readlines.map(&:chomp!).sort!
t = visited.bsearch{|x| x >= s}
if t.nil? or (/#{s}/ =~ t) != 0
  puts s
else
  puts t
end
