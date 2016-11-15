a = gets.split.map(&:to_i)
if (a[2] == 0 and a[3] != 0) or (a[0] == 0 and a[1] != 0 && a[2]*a[3] != 0)
  puts "Ron"
else
  puts(a[0]*a[2]*a[4] < a[1]*a[3]*a[5] ? "Ron" : "Hermione")
end
