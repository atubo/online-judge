$stdin = File.open("input.txt", "r")
$stdout = File.open("output.txt", "w")
n = gets.to_i
s = gets
ones = (0...n).select{|pos| s[pos]=="1"}
diff = ones.map.with_index(1){|e,i| ones[i]-e if ones[i]}.compact
puts (diff.all?{|x| x == diff[0]} ? "YES" : "NO")
