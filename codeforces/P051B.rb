TABLE_PAT = '<table>'
ROW_PAT = '<tr>'
CELL_PAT = '<td>'

class Solution
  def initialize()
    @s = ""
    while line=gets do
      @s = @s + line.chomp!
    end
    @count_stack = []
    @count_array = []
  end

  def cell()
    @s = @s[CELL_PAT.length..-1]
    if /^#{TABLE_PAT}/ =~ @s
      table
    end
    @count_stack[-1] += 1
    @s = @s[CELL_PAT.length+1..-1]
  end

  def row()
    @s = @s[ROW_PAT.length..-1]
    while /^#{CELL_PAT}/ =~ @s do
      cell
    end
    @s = @s[ROW_PAT.length+1..-1]
  end

  def table()
    @s = @s[TABLE_PAT.length..-1]
    @count_stack.push(0)
    while /^#{ROW_PAT}/ =~ @s do
      row
    end
    @count_array.push(@count_stack.pop)
    @s = @s[TABLE_PAT.length+1..-1]
  end

  def solve()
    while /^#{TABLE_PAT}/ =~ @s do
      table
    end
    puts @count_array.sort!.join(' ')
  end
end

solution = Solution.new
solution.solve
