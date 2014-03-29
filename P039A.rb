class Summand
  attr_accessor :coeff, :incr
end

class Solution
  def initialize()
    @summands = []
    @a = 0
  end

  def parse_summand(s)
    match_data = /^(\+|-)?([0-9]*)\*?(a\+\+|\+\+a)/.match(s)
    sign  = match_data[1].nil?? '+' : match_data[1]
    coeff = match_data[2].empty?? 1 : match_data[2].to_i
    coeff = -coeff if sign == '-'
    incr = match_data[3] == 'a++' ? 0 : 1 # 0 - post, 1 - pre

    summand = Summand.new
    summand.coeff = coeff
    summand.incr  = incr
    @summands << summand

    s[match_data[0].size..-1]
  end

  def solve()
    @a = gets.to_i
    s = gets.chomp
    while not s.empty?
      s = parse_summand(s)
    end
    @summands.sort_by!{|s| s.coeff}

    result = 0
    a = @a
    @summands.each do |s|
      a += s.incr
      result += s.coeff * a
      a += (1 - s.incr)
    end
    puts result
  end
end

solution = Solution.new
solution.solve()
