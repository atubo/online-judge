file = File.new("input.txt", "r")
pos = file.gets.to_i
a = (1..3).to_a
(1..3).each do
  x, y = file.gets.split.map{|z| z.to_i-1}
  a[x], a[y] = a[y], a[x]
end
file.close
File.open("output.txt", "w") {|file| file.write(a.find_index(pos)+1)}
