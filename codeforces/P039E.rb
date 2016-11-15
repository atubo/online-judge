def nth_root_ceil(n, m)
  return n if m == 1
  i = 1
  j = n
  while j > i + 1 do
    mid = (i + j) / 2
    if mid ** m >= n
      j = mid
    else
      i = mid
    end
  end
  return j
end

class Solution
  def initialize(n)
    @n = n
    @x = []
    (1..n).each do |i|
      @x[i] = nth_root_ceil(n, i)
      break if @x[i] == 2
    end
  end

  def build_dp()
    @dp = Array.new(@x.size)
    (0...@x.size).each {|i| @dp[i] = Array.new(@x[2]+1, 1)}
    @dp[1][@x[2]] = 0 if ((@n - @x[2]) % 2 == 1)
    (3...@x.size).each do |m|
      (@x[m-1]-1).downto(@x[m]).each do |x|
        (m-1).downto(1).each do |y|
          @dp[y][x] = 0 if (@dp[y+1][x] == 1 and @dp[y][x+1] == 1)
        end
      end
    end
  end

  def solve_boundary_case(b)
    result = -1
    (b...@x.size).each do |i|
      if @dp[i][2] == 0
        result = (i - b) % 2 == 0 ? 1 : 0
        break
      end
    end
    return result
  end

  def solve(a, b)
    if (a > @x[2])
      result = (@n - a) % 2 == 1 ? 0 : 1
    elsif (a > 1)
      result = @dp[b][a]
    else
      result = solve_boundary_case(b)
    end
    return result
  end

  def print()
    (@dp.size-1).downto(1).each do |i|
      (2...@dp[i].size).each do |j|
        printf("%d ", @dp[i][j])
      end
      printf("\n")
    end
  end
end

a, b, n = gets.split.map(&:to_i)
# n = 2, a has to be 1, it's a draw
if n == 2
  puts "Missing"
  exit
end
solution = Solution.new(n)
solution.build_dp
answers = %w[Stas Masha Missing]
puts answers[solution.solve(a, b)]
