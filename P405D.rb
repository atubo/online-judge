require 'set'
N = 1000000
n = gets.to_i
x = Set.new(gets.split.map(&:to_i))
y = []
pairs = 0
for i in x
  unless x.include?(N+1-i)
    y << (N+1-i)
    next
  end
  pairs += 1 if i <= N/2
end
for i in (1..N)
  break if pairs == 0
  unless x.include?(i) or x.include?(N+1-i)
    y << i << (N+1-i)
    pairs -= 1
  end
end
puts y.size
print y.join(' ')

