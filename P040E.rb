# 2**n % p
def remainder(n, p)
  return 1 if n == 0
  m = n / 2
  r = (remainder(m, p) * remainder(m, p)) % p
  return (n % 2 == 0 ? r: (r * 2) % p)
end

n, m = gets.split.map(&:to_i)
# for simplicity, assume n >= m
transpose = false
if n < m
  n, m = m, n
  transpose = true
end

plus_one = Array.new(n, 0)
minus_one = Array.new(n, 0)

k = gets.to_i
(1..k).each do
  a, b, c = gets.split.map(&:to_i)
  a, b = b, a if transpose
  if c > 0
    plus_one[a-1] += 1
  else
    minus_one[a-1] += 1
  end
end
p = gets.to_i

if (n + m) % 2 == 1
  puts 0
  exit
end

exponent = - m + 1
(0...n).each do |i|
  if (plus_one[i] + minus_one[i] == m and minus_one[i] % 2 == 0)
    puts 0
    exit
  else
    exponent += [m - plus_one[i] - minus_one[i] - 1, 0].max
  end
end

puts(remainder(exponent, p))
