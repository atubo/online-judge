require 'set'
N = 1000000
n = gets.to_i
#x = Set.new(gets.split.map(&:to_i))
x = gets.split.map(&:to_i).sort!
a = []
y = []
pairs = 0
for i in x
  a[i] = 1
end
for i in (1..N)
  if a[i] and a[N+1-i]
    pairs += 1 if i <= N/2
  elsif a[i]
    y << (N + 1 -i)
  end
end
for i in (1..N)
  break if pairs == 0
  unless a[i] or a[N+1-i]
    y << i << (N+1-i)
    pairs -= 1
  end
end
puts y.size
print y.join(' ')

