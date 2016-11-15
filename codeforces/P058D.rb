class Solution
  def initialize
    @n = gets.to_i
    @cities = []
    @n.times {@cities << gets.chomp}
    @d = gets.chomp
  end

  def solve
    length = (@cities.inject(0){|x, s| x + s.length})/(@n/2)

    left  = []
    right = []
    str_by_len = []
    for c in @cities do
      str_by_len[c.length] ||= []
      str_by_len[c.length] << c
    end
    (1..10).each do |i|
      unless str_by_len[i].nil?
        str_by_len[i].sort!
      end
    end

    (@n/2).times do
      min_s = '~' * 21
      min_i = -1
      min_j = -1
      (1..10).each do |i|
        next if str_by_len[i].nil? or str_by_len[i].empty?
        s1 = str_by_len[i].shift
        j = length - i
        next if str_by_len[j].nil? or str_by_len[j].empty?
        s2 = str_by_len[j].shift
        if s1 + @d + s2 < min_s
          min_s = s1 + @d + s2
          min_i = i
          min_j = j
        end
        str_by_len[j].unshift(s2)
        str_by_len[i].unshift(s1)
      end
      left  << str_by_len[min_i].shift
      right << str_by_len[min_j].shift
    end
    
    (@n/2).times do
      puts left.shift + @d + right.shift
    end
  end
end

solution = Solution.new
solution.solve
