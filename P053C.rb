n = gets.to_i
p = Array.new(n)
p[0] = 1
(1...n).each {|i| p[i] = (i % 2 == 1 ? p[i-1] + i : p[i-1] - i)}
pmin = p.min
p.map!{|x| x - pmin + 1}
puts p.join(' ')
