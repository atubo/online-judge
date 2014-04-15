def solve(x, y)
  m = Math.log2(x).to_i
  n = Math.log2(y).to_i
  if n == m
    return 2 ** n, [y, (1.25*2**n).to_i].min
  elsif n == m + 1
    if x > (2 ** n / 1.25).to_i
      return (2 ** n / 1.25).to_i, 2 ** n
    else
      return 2 ** m, (1.25 * 2 ** m).to_i
    end
  else
    return 2 ** m, (1.25 * 2 ** m).to_i
  end
end

y, x = gets.split.map(&:to_i)
swap = false
if x > y
  x, y = y, x
  swap = true
end

p, q = solve(x, y)
if swap
  p, q = q, p
end
printf("%d %d\n", q, p)
