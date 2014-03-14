n = gets.to_i
p = n/2
puts p*(n-p)
for i in 1..p do
  for j in p+1..n do
    printf("%d %d\n", i, j)
  end
end
