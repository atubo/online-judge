# 2**n % p
def remainder(n, p)
  return 1 if n == 0
  m = n / 2
  r = (remainder(m, p) * remainder(m, p)) % p
  return (n % 2 == 0 ? r: (r * 2) % p)
end

n, m = gets.split.map(&:to_i)
k = gets.to_i
has_one = false
(1..k).each do
  a, b, c = gets.split.map(&:to_i)
  has_one = true if c == 1
end
p = gets.to_i
if n > 1 and m > 1
  puts(remainder((n-1)*(m-1)-k, p))
else
  if has_one
    result = 0
  else
    result = ((n + m - 1) % 2 == 0 ? 0 : 1)
  end
  puts result
end
