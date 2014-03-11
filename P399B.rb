class BallSeq
  attr_accessor :color, :count
  def initialize(color)
    @color = color
    @count = 1
  end
  def to_s()
    @color + " " + @count.to_s
  end
end

class Solution
  def initialize()
    @n = gets.to_i
    @s = gets.chomp!
    @st = []
  end
  def solve()
    result = 0
    @st << BallSeq.new(@s[0])
    (1...@s.size).each do |i|
      c = @s[i]
      if c == @st.last.color
        @st.last.count += 1
      else
        @st << BallSeq.new(c)
      end
    end
    while @st.size > 1 do
      bseq = @st.shift
      if bseq.color == 'R'
        result += (1 << bseq.count)
        if @st.first.count > 1
          @st.first.count -= 1
          bseq.count += 1
        else
          @st.shift
          bseq.count += @st.shift.count + 1
        end
        @st.unshift(bseq)
      else
        result += (1 << bseq.count) - 1
        @st.first.count += bseq.count
      end
    end
    if @st.first.color == 'B'
      result += (1 << @st.first.count) - 1
    end
    puts result
  end
end

solution = Solution.new
solution.solve
