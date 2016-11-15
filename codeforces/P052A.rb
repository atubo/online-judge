n = gets.to_i
a = gets.split.map(&:to_i)
puts n - (1..3).map{|x| a.count(x)}.max
