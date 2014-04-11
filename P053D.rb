class Solution
  def initialize
    @n = gets.to_i
    @a = gets.split.map(&:to_i)
    @b = gets.split.map(&:to_i)
    @m = []
  end

  def move(i)
    return if @a[i] == @b[i]
    j = i
    j += 1 while @b[j] != @a[i]
    j.downto(i+1).each do |k|
      @m << k-1
      @b[k-1], @b[k] = @b[k], @b[k-1]
    end
  end

  def solve
    (0...@n).each {|i| move(i)}
    puts @m.size
    @m.each {|x| printf("%d %d\n", x+1, x+2)}
  end
end

solution = Solution.new
solution.solve

