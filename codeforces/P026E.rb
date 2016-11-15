# solve for the case that a_min <= w <= sum(a_i)
def solve_normal_case(a, w)
  result = []
  w -= a[0][0]
  (1..a.size-1).each do |i|
    break if w == 0
    if w > a[i][0]
      (2 * a[i][0]).times {result.push(a[i][1])}
      w -= a[i][0]
      a[i][0] = 0
    else
      (2 * w).times {result.push(a[i][1])}
      a[i][0] -= w
      w = 0
    end
  end
  (2*a[0][0]-1).times {result.unshift(a[0][1])}
  (1..a.size-1).each do |i|
    (2*a[i][0]).times {result.unshift(a[i][1])}
  end
  result.unshift(a[0][1])
end


n, w = gets.split.map(&:to_i)
a = gets.split.map(&:to_i).map.with_index(1).to_a
a.sort_by!{|x, i| x}
sum = a.inject(0) {|s, item| s + item[0]}
if w <= 0 or w > sum
  puts "No"
  exit
end

result = []
if a[0][0] <= w and w <= sum
  result = solve_normal_case(a, w)
elsif w >= 2 and a.size >= 2
  suffix = []
  suffix.push(a[1][1])
  diff = a[0][0] - w + 1
  (2*diff).times {suffix.unshift(a[0][1])}
  suffix.unshift(a[1][1])
  a[0][0] -= diff
  a[1][0] -= 1
  prefix = solve_normal_case(a, w-1)
  result = prefix + suffix
else
  puts "No"
  exit
end

puts "Yes"
puts result.join(' ')

