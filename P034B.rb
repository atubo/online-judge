n, m = gets.split.map &:to_i
a = (gets.split.map(&:to_i).select {|x| x < 0}).sort!.take(m)
puts -a.reduce(0,:+)
