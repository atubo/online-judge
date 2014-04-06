# Reference: http://graal.ens-lyon.fr/~abenoit/algo09/coins2.pdf
class Solution
  def initialize
    @n = gets.to_i
    @denom = gets.split.map(&:to_i)
  end

  def greedy(w)
    v = Array.new(@n, 0)
    (0..@n-1).each do |i|
      v[i] = w / @denom[i]
      w = w % @denom[i]
    end
    return v
  end

  def value(v)
    result = 0
    (0..@n-1).each {|i| result += v[i] * @denom[i]}
    return result
  end

  def size(v)
    v.inject(0){|x, y| x + y}
  end

  def greedy_ok?(i, j)
    v = greedy(@denom[i-1]-1)
    v[j] += 1
    (j+1..@n-1).each {|i| v[i] = 0}
    w = value(v)
    return w, size(greedy(w)) <= size(v)
  end

  def solve
    (@n-1).downto(1).each do |i|
      (@n-1).downto(0).each do |j|
        w, ok = greedy_ok?(i, j)
        if not ok
          puts w
          return
        end
      end
    end
    puts -1
  end
end

solution = Solution.new
solution.solve
