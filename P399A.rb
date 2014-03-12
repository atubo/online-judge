(n, p, k) = gets.split.map(&:to_i)
result = ""
result << "<< " if p-k > 1
(([1, p-k].max)..(p-1)).each {|x| result << "#{x} "}
result << "(#{p}) "
((p+1)..([p+k, n].min)).each {|x| result << "#{x} "}
result << ">>" if p+k < n
puts result
